/** @file Security.c
 * @see Security.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> // For write()...
#include <arpa/inet.h> // For htonl() and friends
#include "Crypto/Elliptic_Curves.h"
#include "Crypto/Point.h"
#include "Crypto/Utils.h"
#include "Crypto/AES.h"
#include "Crypto/DSA.h"
#include "Log.h"
#include "Security.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private constants
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/* A security message payload length in bytes. Yes, this is dirty. */
#define SECURITY_MESSAGE_PAYLOAD_SIZE_BYTES (sizeof(TSecurityMessageAuthentication) - (2 * ELLIPTIC_CURVE_SIZE_BYTES))

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Hold a copy of the counters file path. */
static char String_File_Path_Counters[1024];

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int SecurityGenerateKeys(char *String_Elliptic_Curve_File_Path, char *String_Jupiter_File_Path, char *String_Polyphemus_File_Path, char *String_Io_File_Path)
{
	TEllipticCurve Elliptic_Curve;
	FILE *File;
	TPoint Point_Public_Key_Jupiter, Point_Public_Key_Polyphemus, Point_Public_Key_Io;
	mpz_t Private_Key_Jupiter, Private_Key_Polyphemus, Private_Key_Io;
	int Return_Value = 0;

	// Initialize variables
	PointCreate(0, 0, &Point_Public_Key_Jupiter);
	PointCreate(0, 0, &Point_Public_Key_Polyphemus);
	PointCreate(0, 0, &Point_Public_Key_Io);
	mpz_init(Private_Key_Jupiter);
	mpz_init(Private_Key_Polyphemus);
	mpz_init(Private_Key_Io);

	// Load elliptic curve
	if (!ECLoadFromFile(String_Elliptic_Curve_File_Path, &Elliptic_Curve))
	{
		Return_Value = 1;
		goto Exit;
	}

	UtilsInitializeRandomGenerator();

	// Generate keys
	UtilsGenerateKeyPair(&Elliptic_Curve, &Point_Public_Key_Jupiter, Private_Key_Jupiter);
	UtilsGenerateKeyPair(&Elliptic_Curve, &Point_Public_Key_Polyphemus, Private_Key_Polyphemus);
	UtilsGenerateKeyPair(&Elliptic_Curve, &Point_Public_Key_Io, Private_Key_Io);

	// Create Jupiter output file
	File = fopen(String_Jupiter_File_Path, "w");
	if (File == NULL)
	{
		Return_Value = 2;
		goto Exit;
	}

	// Write elliptic curve useful parameters
	gmp_fprintf(File, "Curve_p=%Zd\n", Elliptic_Curve.p);
	gmp_fprintf(File, "Curve_n=%Zd\n", Elliptic_Curve.n);
	gmp_fprintf(File, "Curve_a4=%Zd\n", Elliptic_Curve.a4);
	gmp_fprintf(File, "Curve_a6=%Zd\n", Elliptic_Curve.a6);
	gmp_fprintf(File, "Curve_Generator_X=%Zd\n", Elliptic_Curve.Point_Generator.X);
	gmp_fprintf(File, "Curve_Generator_Y=%Zd\n", Elliptic_Curve.Point_Generator.Y);

	// Write Jupiter's keys
	gmp_fprintf(File, "Own_Public_Key_X=%Zd\n", Point_Public_Key_Jupiter.X);
	gmp_fprintf(File, "Own_Public_Key_Y=%Zd\n", Point_Public_Key_Jupiter.Y);
	gmp_fprintf(File, "Own_Private_Key=%Zd\n", Private_Key_Jupiter);

	// Write Polyphemus's public key
	gmp_fprintf(File, "Other_Public_Key_1_X=%Zd\n", Point_Public_Key_Polyphemus.X);
	gmp_fprintf(File, "Other_Public_Key_1_Y=%Zd\n", Point_Public_Key_Polyphemus.Y);
	fclose(File);

	// Create Polyphemus output file
	File = fopen(String_Polyphemus_File_Path, "w");
	if (File == NULL)
	{
		Return_Value = 3;
		goto Exit;
	}

	// Write elliptic curve useful parameters
	gmp_fprintf(File, "Curve_p=%Zd\n", Elliptic_Curve.p);
	gmp_fprintf(File, "Curve_n=%Zd\n", Elliptic_Curve.n);
	gmp_fprintf(File, "Curve_a4=%Zd\n", Elliptic_Curve.a4);
	gmp_fprintf(File, "Curve_a6=%Zd\n", Elliptic_Curve.a6);
	gmp_fprintf(File, "Curve_Generator_X=%Zd\n", Elliptic_Curve.Point_Generator.X);
	gmp_fprintf(File, "Curve_Generator_Y=%Zd\n", Elliptic_Curve.Point_Generator.Y);

	// Write Polyphemus's keys
	gmp_fprintf(File, "Own_Public_Key_X=%Zd\n", Point_Public_Key_Polyphemus.X);
	gmp_fprintf(File, "Own_Public_Key_Y=%Zd\n", Point_Public_Key_Polyphemus.Y);
	gmp_fprintf(File, "Own_Private_Key=%Zd\n", Private_Key_Polyphemus);

	// Write Jupiter's public key
	gmp_fprintf(File, "Other_Public_Key_1_X=%Zd\n", Point_Public_Key_Jupiter.X);
	gmp_fprintf(File, "Other_Public_Key_1_Y=%Zd\n", Point_Public_Key_Jupiter.Y);

	// Write Io's public key
	gmp_fprintf(File, "Other_Public_Key_2_X=%Zd\n", Point_Public_Key_Io.X);
	gmp_fprintf(File, "Other_Public_Key_2_Y=%Zd\n", Point_Public_Key_Io.Y);
	fclose(File);

	// Create Io output file
	File = fopen(String_Io_File_Path, "w");
	if (File == NULL)
	{
		Return_Value = 4;
		goto Exit;
	}

	// Write elliptic curve useful parameters
	gmp_fprintf(File, "Curve_p=%Zd\n", Elliptic_Curve.p);
	gmp_fprintf(File, "Curve_n=%Zd\n", Elliptic_Curve.n);
	gmp_fprintf(File, "Curve_a4=%Zd\n", Elliptic_Curve.a4);
	gmp_fprintf(File, "Curve_a6=%Zd\n", Elliptic_Curve.a6);
	gmp_fprintf(File, "Curve_Generator_X=%Zd\n", Elliptic_Curve.Point_Generator.X);
	gmp_fprintf(File, "Curve_Generator_Y=%Zd\n", Elliptic_Curve.Point_Generator.Y);

	// Write Io's keys
	gmp_fprintf(File, "Own_Public_Key_X=%Zd\n", Point_Public_Key_Io.X);
	gmp_fprintf(File, "Own_Public_Key_Y=%Zd\n", Point_Public_Key_Io.Y);
	gmp_fprintf(File, "Own_Private_Key=%Zd\n", Private_Key_Io);

	// Write Polyphemus's public key
	gmp_fprintf(File, "Other_Public_Key_1_X=%Zd\n", Point_Public_Key_Polyphemus.X);
	gmp_fprintf(File, "Other_Public_Key_1_Y=%Zd\n", Point_Public_Key_Polyphemus.Y);
	fclose(File);

Exit:
	ECFree(&Elliptic_Curve);
	UtilsFreeRandomGenerator();
	PointFree(&Point_Public_Key_Jupiter);
	PointFree(&Point_Public_Key_Polyphemus);
	PointFree(&Point_Public_Key_Io);
	mpz_clear(Private_Key_Jupiter);
	mpz_clear(Private_Key_Polyphemus);
	mpz_clear(Private_Key_Io);
	return Return_Value;
}

int SecurityInit(char *String_Keys_File_Path, char *String_Counters_File_Path, int Others_Public_Keys_Count, TEllipticCurve *Pointer_Elliptic_Curve, TPoint *Pointer_Point_Own_Public_Key, mpz_t Private_Key, TPoint Point_Others_Public_Keys[], int Counters[])
{
	FILE *File;
	int i, Return_Value;
	char String_Field_Name[32];

	// Initialize variables
	ECInit(Pointer_Elliptic_Curve);
	PointCreate(0, 0, Pointer_Point_Own_Public_Key);
	mpz_init(Private_Key);
	for (i = 0; i < Others_Public_Keys_Count; i++) PointCreate(0, 0, &Point_Others_Public_Keys[i]);

	// Load keys file
	Return_Value = 1;
	File = fopen(String_Keys_File_Path, "r");
	if (File == NULL) goto Exit_Error;

	// Load curve parameters
	if (gmp_fscanf(File, "Curve_p=%Zd\n", Pointer_Elliptic_Curve->p) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Curve_n=%Zd\n", Pointer_Elliptic_Curve->n) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Curve_a4=%Zd\n", Pointer_Elliptic_Curve->a4) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Curve_a6=%Zd\n", Pointer_Elliptic_Curve->a6) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Curve_Generator_X=%Zd\n", Pointer_Elliptic_Curve->Point_Generator.X) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Curve_Generator_Y=%Zd\n", Pointer_Elliptic_Curve->Point_Generator.Y) == 0) goto Exit_Error;
	Log(LOG_DEBUG, "[Security.SecurityInit] Elliptic curve successfully loaded.");

	// Load this machine public key
	if (gmp_fscanf(File, "Own_Public_Key_X=%Zd\n", Pointer_Point_Own_Public_Key->X) == 0) goto Exit_Error;
	if (gmp_fscanf(File, "Own_Public_Key_Y=%Zd\n", Pointer_Point_Own_Public_Key->Y) == 0) goto Exit_Error;
	Log(LOG_DEBUG, "[Security.SecurityInit] Own public key successfully loaded.");

	// Load this machine private key
	if (gmp_fscanf(File, "Own_Private_Key=%Zd\n", Private_Key) == 0) goto Exit_Error;
	Log(LOG_DEBUG, "[Security.SecurityInit] Own private key successfully loaded.");

	// Load other machines public keys
	for (i = 0; i < Others_Public_Keys_Count; i++)
	{
		// Read X field
		sprintf(String_Field_Name, "Other_Public_Key_%d_X=%%Zd\n", i + 1);
		if (gmp_fscanf(File, String_Field_Name, Point_Others_Public_Keys[i].X) == 0) goto Exit_Error;

		// Read Y field
		sprintf(String_Field_Name, "Other_Public_Key_%d_Y=%%Zd\n", i + 1);
		if (gmp_fscanf(File, String_Field_Name, Point_Others_Public_Keys[i].Y) == 0) goto Exit_Error;
	}
	Log(LOG_DEBUG, "[Security.SecurityInit] Others public key(s) successfully loaded.");
	fclose(File);

	// Load counters file
	Return_Value = 2;
	File = fopen(String_Counters_File_Path, "r");
	if (File == NULL) goto Exit_Error;

	for (i = 0; i < Others_Public_Keys_Count; i++)
	{
		if (fscanf(File, "%d", &Counters[i]) == 0) goto Exit_Error;
	}
	Log(LOG_DEBUG, "[Security.SecurityInit] Counter(s) successfully loaded.");
	fclose(File);

	// Keep counters file path
	if (strlen(String_Counters_File_Path) > sizeof(String_File_Path_Counters)) Log(LOG_ERR, "[Security.SecurityInit] Counters file path is too long.\n");
	strncpy(String_File_Path_Counters, String_Counters_File_Path, sizeof(String_File_Path_Counters) - 1);

	// All was successfully loaded
	return 0;

	// Free variables
Exit_Error:
	ECFree(Pointer_Elliptic_Curve);
	PointFree(Pointer_Point_Own_Public_Key);
	mpz_clear(Private_Key);
	for (i = 0; i < Others_Public_Keys_Count; i++) PointFree(&Point_Others_Public_Keys[i]);
	return Return_Value;
}

void SecurityFillAuthenticationMessage(int Counter, TEllipticCurve *Pointer_Elliptic_Curve, mpz_t Output_Random_Number, TSecurityMessageAuthentication *Pointer_Message)
{
	TPoint Point_Key_Part;

	// Initialize variables
	PointCreate(0, 0, &Point_Key_Part);

	// Fill counter field
	Pointer_Message->Counter = htonl(Counter);
	Log(LOG_DEBUG, "[Security.SecurityFillAuthenticationMessage] Counter value = %d.", Counter);

	// Choose a random number
	UtilsGenerateRandomNumber(Pointer_Elliptic_Curve->p, Output_Random_Number);

	// Compute key part
	ECMultiplication(Pointer_Elliptic_Curve, &Pointer_Elliptic_Curve->Point_Generator, Output_Random_Number, &Point_Key_Part);
	UTILS_MPZ_EXPORT(Point_Key_Part.X, Pointer_Message->Key_Part_X);
	UTILS_MPZ_EXPORT(Point_Key_Part.Y, Pointer_Message->Key_Part_Y);

	PointFree(&Point_Key_Part);
}

void SecuritySignAuthenticationMessage(TEllipticCurve *Pointer_Elliptic_Curve, mpz_t Private_Key, TSecurityMessageAuthentication *Pointer_Message)
{
	mpz_t Signature_Number_U, Signature_Number_V;

	// Initialize variables
	mpz_init(Signature_Number_U);
	mpz_init(Signature_Number_V);

	// Generate ECDSA signature
	DSASign(Pointer_Elliptic_Curve, (unsigned char *) Pointer_Message, SECURITY_MESSAGE_PAYLOAD_SIZE_BYTES, Private_Key, Signature_Number_U, Signature_Number_V);

	// Append signature to message
	UTILS_MPZ_EXPORT(Signature_Number_U, Pointer_Message->Signature_Number_U);
	UTILS_MPZ_EXPORT(Signature_Number_V, Pointer_Message->Signature_Number_V);

	#if LOG_ENABLE == 1
	{
		char String_Number_U[256], String_Number_V[256];

		gmp_sprintf(String_Number_U, "%Zd", Signature_Number_U);
		gmp_sprintf(String_Number_V, "%Zd", Signature_Number_V);
		Log(LOG_DEBUG, "[Security.SecuritySignAuthenticationMessage] Generated signature : U = %s, V = %s.", String_Number_U, String_Number_V);
	}
	#endif

	mpz_clear(Signature_Number_U);
	mpz_clear(Signature_Number_V);
}

int SecurityCheckAuthenticationMessageSignature(TSecurityMessageAuthentication *Pointer_Message, TEllipticCurve *Pointer_Elliptic_Curve, TPoint *Pointer_Point_Public_Key, mpz_t Received_Signature_Number_U, mpz_t Received_Signature_Number_V)
{
	return DSACheck(Pointer_Elliptic_Curve, (unsigned char *) Pointer_Message, SECURITY_MESSAGE_PAYLOAD_SIZE_BYTES, Pointer_Point_Public_Key, Received_Signature_Number_U, Received_Signature_Number_V);
}

int SecurityReceiveAuthenticationMessage(int Socket_Source, TSecurityMessageAuthentication *Pointer_Message, int *Pointer_Received_Counter, TPoint *Pointer_Point_Received_Key_Part, mpz_t Received_Signature_Number_U, mpz_t Received_Signature_Number_V)
{
	// Receive message
	if (read(Socket_Source, Pointer_Message, sizeof(TSecurityMessageAuthentication)) != sizeof(TSecurityMessageAuthentication)) return 0;

	// Retrieve counter
	*Pointer_Received_Counter = ntohl(Pointer_Message->Counter);

	// Retrieve key part
	UTILS_MPZ_IMPORT(Pointer_Message->Key_Part_X, Pointer_Point_Received_Key_Part->X);
	UTILS_MPZ_IMPORT(Pointer_Message->Key_Part_Y, Pointer_Point_Received_Key_Part->Y);

	// Retrieve U and V
	UTILS_MPZ_IMPORT(Pointer_Message->Signature_Number_U, Received_Signature_Number_U);
	UTILS_MPZ_IMPORT(Pointer_Message->Signature_Number_V, Received_Signature_Number_V);

	#if LOG_ENABLE == 1
	{
		char String_Number_U[256], String_Number_V[256];

		gmp_sprintf(String_Number_U, "%Zd", Received_Signature_Number_U);
		gmp_sprintf(String_Number_V, "%Zd", Received_Signature_Number_V);
		Log(LOG_DEBUG, "[Security.SecurityReceiveAuthenticationMessage] Received signature : U = %s, V = %s.", String_Number_U, String_Number_V);
	}
	#endif
	return 1;
}

int SecuritySendAuthenticationMessage(int Socket_Destination, TSecurityMessageAuthentication *Pointer_Message)
{
	if (write(Socket_Destination, Pointer_Message, sizeof(TSecurityMessageAuthentication)) != sizeof(TSecurityMessageAuthentication)) return 0;
	else return 1;
}

void SecuritySaveCounters(int Counters[], int Counters_Count)
{
	FILE *File;
	int i;

	File = fopen(String_File_Path_Counters, "w");
	if (File == NULL)
	{
		Log(LOG_ERR, "[Security.SecuritySaveCounters] Could not save counters.");
		return;
	}

	for (i = 0; i < Counters_Count; i++) fprintf(File, "%d\n", Counters[i]);
	fclose(File);
}

int SecuritySendRobotControlMessage(int Socket_Destination, EVP_CIPHER_CTX *Pointer_AES_Context, int Data)
{
	TSecurityMessageRobotControl Message;
	unsigned char Encrypted_Message[AES_CIPHERED_MESSAGE_SIZE_BYTES(sizeof(Message))];
	int Encrypted_Message_Size;

	// Fill message payload
	Message.Data = htonl(Data);

	// Compute integrity hash
	if (!UtilsComputeHash(&Message, SECURITY_MESSAGE_ROBOT_CONTROL_PAYLOAD_SIZE_BYTES, Message.Hash))
	{
		Log(LOG_ERR, "[Security.SecuritySendRobotControlMessage] Error : failed to compute message hash.");
		return 0;
	}

	// Cipher message
	if (EVP_EncryptUpdate(Pointer_AES_Context, Encrypted_Message, &Encrypted_Message_Size, (unsigned char *) &Message, sizeof(Message)) == 0)
	{
		Log(LOG_ERR, "[Security.SecuritySendRobotControlMessage] Error : could not cipher AES message.");
		return 0;
	}
	// Check ciphered message size
	if (Encrypted_Message_Size != sizeof(Message))
	{
		Log(LOG_ERR, "[Security.SecuritySendRobotControlMessage] Error : bad ciphered message size (%d bytes).", Encrypted_Message_Size);
		return 0;
	}

	// Send encrypted message
	if (write(Socket_Destination, Encrypted_Message, sizeof(Encrypted_Message)) != sizeof(Encrypted_Message))
	{
		Log(LOG_ERR, "[Security.SecuritySendRobotControlMessage] Error : could not write to socket.");
		return 0;
	}

	return 1;
}

int SecurityReceiveRobotControlMessage(int Socket_Source, EVP_CIPHER_CTX *Pointer_AES_Context, int *Pointer_Received_Data)
{
	TSecurityMessageRobotControl Message;
	unsigned char Encrypted_Message[sizeof(Message)]/*AES_CIPHERED_MESSAGE_SIZE_BYTES(sizeof(Message))*/, Decrypted_Message[/*AES_CIPHERED_MESSAGE_SIZE_BYTES(sizeof(Message))*/sizeof(Message)], Computed_Hash[UTILS_HASH_SIZE_BYTES];
	int Decrypted_Message_Size, Received_Message_Size;

	// Receive ciphered message
	Received_Message_Size = read(Socket_Source, Encrypted_Message, sizeof(Encrypted_Message));
	if (Received_Message_Size !=  sizeof(Encrypted_Message))
	{
		Log(LOG_ERR, "[Security.SecurityReceiveRobotControlMessage] Error : could not retrieve message from socket (received message size is %d bytes).", Received_Message_Size);
		return 0;
	}

	// Decipher message
	if (EVP_DecryptUpdate(Pointer_AES_Context, Decrypted_Message, &Decrypted_Message_Size, Encrypted_Message, sizeof(Message)) == 0)
	{
		Log(LOG_ERR, "[Security.SecurityReceiveRobotControlMessage] Error : could not decipher AES message.");
		return 0;
	}
	// Check plaintext message size
	if (Decrypted_Message_Size != sizeof(Message))
	{
		Log(LOG_ERR, "[Security.SecurityReceiveRobotControlMessage] Error : bad received message size (%d bytes).", Decrypted_Message_Size);
		return 0;
	}
	memcpy(&Message, Decrypted_Message, sizeof(Message));

	// Check integrity
	if (!UtilsComputeHash(&Message, SECURITY_MESSAGE_ROBOT_CONTROL_PAYLOAD_SIZE_BYTES, Computed_Hash))
	{
		Log(LOG_ERR, "[Security.SecurityReceiveRobotControlMessage] Error : failed to compute message hash.");
		return 0;
	}
	// Compare hashes
	if (memcmp(Computed_Hash, Message.Hash, SECURITY_MESSAGE_ROBOT_CONTROL_PAYLOAD_SIZE_BYTES) != 0)
	{
		Log(LOG_ERR, "[Security.SecurityReceiveRobotControlMessage] Error : received and computed hashes do not match.");
		return 0;
	}

	// Message seems to be good
	*Pointer_Received_Data = ntohl(Message.Data);
	return 1;
}
