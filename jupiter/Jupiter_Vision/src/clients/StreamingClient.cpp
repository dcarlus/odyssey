#include "StreamingClient.h"
#include "../picture/SocketPicture.h"
#include <assert.h>
#include <pthread.h>
#include <sys/select.h>
#include <iostream>
#include <Utils.h>
#include <Security.h>

using namespace std ;
using namespace es ;

StreamingClient* StreamingClient::Instance = 0 ;


    #ifdef WIFI_NETWORK
        StreamingClient::StreamingClient() : Client("192.168.100.1", 9587) {
    #else
        StreamingClient::StreamingClient() : Client("192.168.0.2", 9587) {
    #endif
    }

StreamingClient::~StreamingClient() throw() {}

StreamingClient* StreamingClient::getInstance() {
    if (Instance == 0)
        Instance = new StreamingClient() ;
    return Instance ;
}


void* StreamingClient::manageThread(void* param) {
    Instance -> run() ;
    return 0 ;
}

void StreamingClient::createThread() {
    pthread_t clientThread ;

    assert(pthread_create(&clientThread, 0, &StreamingClient::manageThread, 0) == 0) ;
//    pthread_join(clientThread, 0) ;
}

void StreamingClient::run() {
    SocketPicture pic ;
    int socketfd = m_socket.getSocket() ;
    uint8_t bufferFrame[SECURITY_VIDEO_BUFFER_MAXIMUM_SIZE_BYTES] ;

    while (m_isRunning) {
        // Receive a frame from Polyphemus
        int32_t bufferSize = 0 ;
//        SecurityClientReceiveVideoBuffer(socketfd, &bufferSize, sizeof(bufferSize)) ;
//        m_socket.recv(socketfd, &bufferSize, sizeof(bufferSize), MSG_WAITALL) ;
//        bufferSize = ntohl(bufferSize) ;
        int success = SecurityClientReceiveVideoBuffer(socketfd, bufferFrame, &bufferSize) ;
//        int received = m_socket.recv(socketfd, bufferFrame, bufferSize, MSG_WAITALL) ;

        // Limit to handle only frames that have contents (sometimes there are
        // missing data...)
        if (success && (bufferSize > 256)) {
            // Decode the compressed frame
            uint8_t* rawBuffer = 0 ;
            if (m_decoder.setFrame(bufferFrame, bufferSize)) {
                int rawSize = m_decoder.getRawData(rawBuffer) ;
                if (rawSize > 0) {
                    int width = m_decoder.getWidth() ;
                    int height = m_decoder.getHeight() ;

                    // Set the data used for image processing
                    pic.setData(rawBuffer, rawSize, width, height) ;
                    pic.display() ;
                    m_decoder.freeBuffer(rawBuffer) ;
                }
            }
        }
    }
}
