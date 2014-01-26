#include "Client.h"
#include <vector>

using namespace std ;
using namespace es ;


Client::Client(const string& serverIP, unsigned short serverPort) {
    assert(pthread_mutex_init(&m_clientState, NULL) == 0) ;

    pthread_mutex_lock(&m_clientState) ;
        Logger::print("Connecting to server " + serverIP + ":" + to_string(serverPort)) ;
        m_socket.connect(serverIP.c_str(), serverPort) ;
        m_isRunning = false ;

        srand(time(0)) ;
        m_session = to_string(rand()) ;
    pthread_mutex_unlock(&m_clientState) ;
}


Client::~Client() {
    pthread_mutex_destroy(&m_clientState) ;
}


const string& Client::getSession() {
    return m_session ;
}


void Client::start() {
    pthread_mutex_lock(&m_clientState) ;
    m_isRunning = true ;
    createThread() ;
    pthread_mutex_unlock(&m_clientState) ;
}


void Client::stop() {
    pthread_mutex_lock(&m_clientState) ;
    m_isRunning = false ;
    pthread_mutex_unlock(&m_clientState) ;
}
