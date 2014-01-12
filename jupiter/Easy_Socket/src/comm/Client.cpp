#include "Client.h"
#include <vector>

using namespace std ;
using namespace es ;

Client* Client::Instance = 0 ;


Client::Client(const string& serverIP, unsigned short serverPort) {
    assert(pthread_mutex_init(&m_clientState, NULL) == 0) ;

    pthread_mutex_lock(&m_clientState) ;
        Logger::print("Connecting to server " + serverIP + ":" + to_string(serverPort)) ;
        m_socket.connect(serverIP.c_str(), serverPort) ;
        m_isRunning = false ;

        srand(time(0)) ;
        m_session = to_string(rand()) ;

        if (Instance != 0)
            delete Instance ;
        Instance = this ;
    pthread_mutex_unlock(&m_clientState) ;
}


Client::~Client() {
    pthread_mutex_destroy(&m_clientState) ;
}


Client* Client::getInstance() {
    return Instance ;
}



const string& Client::getSession() {
    return m_session ;
}


void Client::start() {
    pthread_t clientThread ;
    assert(pthread_create(&clientThread, 0, &Client::manageThread, 0) == 0) ;

    pthread_mutex_lock(&m_clientState) ;
    m_isRunning = true ;
    pthread_mutex_unlock(&m_clientState) ;
}


void Client::stop() {
    pthread_mutex_lock(&m_clientState) ;
    m_isRunning = false ;
    pthread_mutex_unlock(&m_clientState) ;
}


void* Client::manageThread(void* param) {
    Instance -> run() ;
    return 0 ;
}
