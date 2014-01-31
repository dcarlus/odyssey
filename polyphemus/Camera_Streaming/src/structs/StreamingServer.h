/**
 * @file    StreamingServer.h
 * @brief   The StreamingServer contains all the required informations to
 *          communicate with a client through secured connection.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 */

#ifndef __POLYPHEMUS__STREAMING_SERVER__
#define __POLYPHEMUS__STREAMING_SERVER__

/** @brief	Contains data used by the streaming server. */
typedef struct StreamingServer {
    /** DATA **/
    char*           ip ;
    unsigned short  port ;
    int             socket ;
    // @TODO    Complete with security data?


    /** METHODS **/
    // Utilities
    int     (*listen)   (struct StreamingServer* self) ;
    int     (*read)     (struct StreamingServer* self, const int client, void* msg, const int length) ;
    int     (*write)    (struct StreamingServer* self, const int client, const void* msg, const int length) ;
    void    (*close)    (struct StreamingServer* self) ;
} StreamingServer ;


/** @brief  Create a new StreamingServer. */
StreamingServer StreamingServer_Construct(const char* ip,
                                          const unsigned short port) ;

#endif
