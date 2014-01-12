#include "Server.h"
#include <string>

using namespace std ;
using namespace es ;

Server::Server(unsigned short port, unsigned short max_clients) {
    m_port = port ;
    m_maxClients = max_clients ;
    m_isRunning = false ;

    assert(pthread_mutex_init(&m_serverState, NULL) == 0) ;
}

Server::~Server() {
    pthread_mutex_destroy(&m_serverState) ;
}


void Server::start() throw(SocketException) {
    Logger::print("Starting server") ;

    // Bind the socket to the machine
    if (m_socket.isPrepared())
        m_socket.bind() ;
    else
        m_socket.bind("", m_port) ;

    pthread_mutex_lock(&m_serverState) ;
        // Make the server listens
        Logger::print("Server listens on port " + to_string(m_port)) ;

        // ENTER CRITICAL SECTION!
        m_isRunning = true ;
        m_socket.listen() ;
        // EXIT CRITICAL SECTION!
    pthread_mutex_unlock(&m_serverState) ;


    // Wait for new connections
    pthread_t clientThread ;// Thread to manage the client connection
    int incoming ;          // socket dedicated to the new client
    struct sockaddr_in client ;
    ThreadParams params ;   // Parameters given to the new client thread

    while(m_isRunning) {
//        if (m_clients.size() < m_maxClients) {

            params.server = this ;
            params.client = m_socket.accept(&client) ;
            Logger::print("New client connected: " + string(inet_ntoa(client.sin_addr))) ;

            // Create the thread...
            assert(pthread_create(&clientThread, 0, &Server::initClient, &params) == 0) ;
            m_clients.insert(clientThread) ;

//        else {
//            Logger::print("Limit of client reached, new client rejected...") ;
//        }
    }
}


void Server::pause() throw(SocketException) {
    pthread_mutex_lock(&m_serverState) ;
        // ENTER CRITICAL SECTION!
        m_isRunning = false ;
        m_socket.close() ;
        // EXIT CRITICAL SECTION!
    pthread_mutex_unlock(&m_serverState) ;
}
