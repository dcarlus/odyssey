#include "StreamingServer.h"
#include "../Network.h"
#include "../OMXUtils.h"


/**
 * @brief   Listen for a client to connect to a previously created server.
 * @param   Socket_Server The server socket.
 * @return  A non-negative value if a client has been accepted (this is the
 *          client's socket),
 * @return  -1 if the server failed to listen for a client,
 * @return  -2 if the server failed to accept a client.
 */
static int StreamingServer_Listen(StreamingServer* self) {
    return NetworkServerListen(self -> socket) ;
}


/**
 * @brief   Send a message to a client.
 * @param   self    The StreamingServer used to send the message.
 * @param   client  Client socket through which the message is sent.
 * @param   msg     Message to send.
 * @param   length  Length of the message to send.
 * @return  Length really sent.
 * @return  -2 if the server failed sending the message to the client.
 */
static int StreamingServer_Send(StreamingServer* self,
                                const int client,
                                const void* msg,
                                const int length) {
    return NetworkServerSend(client, msg, length, 0) ;
}


/**
 * @brief   Close the server socket.
 * @param   self    StreamingServer whose socket must be closed.
 */
static void StreamingServer_Close(StreamingServer* self) {
    close(self -> socket) ;
}


                                                             /** CONSTRUCTOR **/
/**
 * @brief   Initialize an StreamingServer.
 * @param   self    The StreamingServer to initialize.
 */
static void _StreamingServer_Init(StreamingServer* self) {
    // Initialize data
    self -> socket = NetworkServerCreate(self -> ip, self -> port) ;

    if ((self -> socket) == -1)
        die("Error : can't bind server socket.\n") ;
    else if ((self -> socket) == -2)
        die("Error : can't bind server.\n") ;


    // Set methods
    self -> listen  = StreamingServer_Listen ;
    self -> send    = StreamingServer_Send ;
    self -> close   = StreamingServer_Close ;
}

/**
 * @brief   Create a new StreamingServer.
 * @param   ip      IP address of the server.
 * @param   port    Port used by the server.
 */
StreamingServer StreamingServer_Construct(const char* ip,
                                          const unsigned short port) {
    StreamingServer self = {(char*) ip, port, -3} ;
    _StreamingServer_Init(&self) ;
    return self ;
}
