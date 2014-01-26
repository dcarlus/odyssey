/** @file Security_Server.c
 * @see Security_Server.h for description.
 * @author Adrien RICCIARDI.
 */
#include <gmp.h>
#include <openssl/evp.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "Crypto/Elliptic_Curves.h"
#include "Crypto/Point.h"
#include "Crypto/Utils.h"
#include "Crypto/AES.h"
#include "Crypto/DSA.h"
#include "Log.h"
#include "Robot.h"
#include "Security.h"
#include "Security_Server.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Anti replay counter used during asymetric cryptography steps. */
static int Counters[SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT];

/** This machine public key. */
static TPoint Point_Own_Public_Key;
/** This machine private key. */
static mpz_t Private_Key;

/** The clients public keys. */
static TPoint Point_Clients_Public_Keys[SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT];

/** The elliptic curve used for all asymetric cryptography. */
static TEllipticCurve Elliptic_Curve;

/** AES OpenSSL context used to receive robot commands. */
static EVP_CIPHER_CTX *Pointer_AES_Context_Input_Commands;
/** AES OpenSSL context used to send robot data. */
static EVP_CIPHER_CTX *Pointer_AES_Context_Output_Data;
/** AES OpenSSL context used to send robot video. */
static EVP_CIPHER_CTX *Pointer_AES_Context_Output_Video;

/** AES secret key. */
static unsigned char AES_Key[AES_KEY_SIZE_BYTES];
/** AES initialization vector (IV). */
static unsigned char AES_Initialization_Vector[AES_BLOCK_SIZE_BYTES];

/** Tell which client is authenticated. */
static int Client_Index;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int SecurityServerInit(char *String_Keys_File_Path, char *String_Counters_File_Path)
{
	UtilsInitializeRandomGenerator();
	Pointer_AES_Context_Input_Commands = AESCreate();
	Pointer_AES_Context_Output_Data = AESCreate();
	Pointer_AES_Context_Output_Video = AESCreate();
	return SecurityInit(String_Keys_File_Path, String_Counters_File_Path, SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT, &Elliptic_Curve, &Point_Own_Public_Key, Private_Key, Point_Clients_Public_Keys, Counters);
}

int SecurityServerAuthenticateClient(int Socket_Client)
{
	TSecurityMessageAuthentication Message;
	mpz_t Random_Number, Received_Signature_Number_U, Received_Signature_Number_V;
	TPoint Point_Received_Key_Part;
	int Received_Counter, Return_Value = 0, i;

	// Initialize variables
	mpz_init(Random_Number);
	mpz_init(Received_Signature_Number_U);
	mpz_init(Received_Signature_Number_V);
	PointCreate(0, 0, &Point_Received_Key_Part);

	//---------- First step : receive client's key part message ----------
	// Receive client's authentication message
	if (!SecurityReceiveAuthenticationMessage(Socket_Client, &Message, &Received_Counter, &Point_Received_Key_Part, Received_Signature_Number_U, Received_Signature_Number_V))
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : can't receive data from client socket.");
		goto Exit;
	}

	// Find client using its signature
	for (i = 0; i < SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT; i++)
	{
		if (SecurityCheckAuthenticationMessageSignature(&Message, &Elliptic_Curve, &Point_Clients_Public_Keys[i], Received_Signature_Number_U, Received_Signature_Number_V))
		{
			Client_Index = i;
			Log(LOG_DEBUG, "[Security_Server.SecurityServerAuthenticateClient] Client %d authenticated.", Client_Index);
			break;
		}
	}
	// No client could be authenticated, so the signature is bad
	if (i == SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT)
	{
		Log(LOG_DEBUG, "[Security_Server.SecurityServerAuthenticateClient] Could not find matching signature.");
		goto Exit;
	}

	// Check anti replay counter
	Log(LOG_DEBUG, "[Security_Server.SecurityServerAuthenticateClient] Current counter = %d, Received counter = %d.", Counters[Client_Index], Received_Counter);
	if (Received_Counter <= Counters[Client_Index])
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : received counter is too small.");
		goto Exit;
	}
	Counters[Client_Index] = Received_Counter + 1;

	//---------- Second step : send own key part to client ----------
	// Fill message payload
	SecurityFillAuthenticationMessage(Counters[Client_Index], &Elliptic_Curve, Random_Number, &Message);

	// Sign message
	SecuritySignAuthenticationMessage(&Elliptic_Curve, Private_Key, &Message);

	// Send message to client
	if (!SecuritySendAuthenticationMessage(Socket_Client, &Message))
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : could not send message to client socket.");
		goto Exit;
	}

	// Get AES IV from signature U number
	memcpy(AES_Initialization_Vector, Message.Signature_Number_U, sizeof(AES_Initialization_Vector) / 2);
	memset(AES_Initialization_Vector + (sizeof(AES_Initialization_Vector) / 2), 0, sizeof(AES_Initialization_Vector) / 2); // Set AES counter to zero
	#if LOG_ENABLE == 1
	{
		char String_Initialization_Vector[256] = {0};
		int i;
		
		for (i = 0; i < sizeof(AES_Initialization_Vector); i++) sprintf(String_Initialization_Vector, "%s%02X ", String_Initialization_Vector, AES_Initialization_Vector[i]);
		Log(LOG_DEBUG, "[Security_Server.SecurityServerAuthenticateClient] AES initialization vector : %s.", String_Initialization_Vector);
	}
	#endif

	//---------- Third step : generate session key ----------
	// Compute Diffie-Hellman shared key
	ECMultiplication(&Elliptic_Curve, &Point_Received_Key_Part, Random_Number, &Point_Received_Key_Part);
	UTILS_MPZ_EXPORT(Point_Received_Key_Part.X, AES_Key);
	#if LOG_ENABLE == 1
	{
		char String_Key[256];

		gmp_sprintf(String_Key, "%Zd", Point_Received_Key_Part.X);
		Log(LOG_DEBUG, "[Security_Server.SecurityServerAuthenticateClient] AES secret key : %s.", String_Key);
	}
	#endif

	//---------- Fourth step : create AES links ----------
	// Robot input commands link
	if (AESDecipherInit(Pointer_AES_Context_Input_Commands, AES_Key, AES_Initialization_Vector) == -1)
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : can't create AES input link for robot commands.");
		goto Exit;
	}
		
	// Robot output data link
	if (AESCipherInit(Pointer_AES_Context_Output_Data, AES_Key, AES_Initialization_Vector) == -1)
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : can't create AES output link for robot data.");
		goto Exit;
	}

	// Robot output video link
	if (AESDecipherInit(Pointer_AES_Context_Output_Video, AES_Key, AES_Initialization_Vector) == -1)
	{
		Log(LOG_ERR, "[Security_Server.SecurityServerAuthenticateClient] Error : can't create AES output link for robot video.");
		goto Exit;
	}

	SecuritySaveCounters(Counters, SECURITY_SERVER_MAXIMUM_CLIENTS_COUNT);

	// All successful
	Return_Value = 1;

Exit:
	mpz_clear(Random_Number);
	mpz_clear(Received_Signature_Number_U);
	mpz_clear(Received_Signature_Number_V);
	PointFree(&Point_Received_Key_Part);
	return Return_Value;
}

int SecurityServerReceiveRobotCommand(int Socket_Client, TRobotCommand *Pointer_Received_Command)
{
	return SecurityReceiveRobotControlMessage(Socket_Client, Pointer_AES_Context_Input_Commands, (int *) Pointer_Received_Command);
}

int SecurityServerSendRobotData(int Socket_Client, int Data)
{
	return SecuritySendRobotControlMessage(Socket_Client, Pointer_AES_Context_Output_Data, Data);
}

void SecurityServerQuit(void)
{
	UtilsFreeRandomGenerator();
	AESCleanUp(Pointer_AES_Context_Input_Commands);
	AESCleanUp(Pointer_AES_Context_Output_Data);
	AESCleanUp(Pointer_AES_Context_Output_Video);
}
