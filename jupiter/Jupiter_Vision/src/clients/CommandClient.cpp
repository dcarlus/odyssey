#include "CommandClient.h"
#include <assert.h>
#include <pthread.h>
#include <sys/select.h>
#include <iostream>

using namespace std ;
using namespace es ;

CommandClient* CommandClient::Instance = 0 ;


    #ifdef WIFI_NETWORK
        CommandClient::CommandClient() : Client("192.168.100.1", 1234) {
    #else
        CommandClient::CommandClient() : Client("192.168.0.2", 1234) {
    #endif
            assert(SecurityClientAuthenticateServer(m_socket.getSocket())) ;
            cout << "Connected to Mercury" << endl ;

            m_isLEDOn = false ;
        }

CommandClient::~CommandClient() throw() {
    sendMoveCommand(ROBOT_COMMAND_STOP) ;
    SecurityClientQuit() ;
}

CommandClient* CommandClient::getInstance() {
    if (Instance == 0)
        Instance = new CommandClient() ;
    return Instance ;
}


void* CommandClient::manageThread(void* param) {
    return 0 ;
}

void CommandClient::createThread() {}

void CommandClient::run() {}


void CommandClient::sendMoveCommand(TRobotCommand command) {
    static int socketServer = m_socket.getSocket() ;

    if ((command >= ROBOT_COMMAND_STOP) && (command <= ROBOT_COMMAND_RIGHT)) {
        #ifdef DEBUG_JUPITER
            printf("Sending command %i\n", command) ;
        #endif

        SecurityClientSendRobotCommand(socketServer, command) ;
    }
}

void CommandClient::sendLEDCommand() {
    m_isLEDOn = !m_isLEDOn ;
    if (m_isLEDOn)
        SecurityClientSendRobotCommand(m_socket.getSocket(), ROBOT_COMMAND_LED_ON) ;
    else
        SecurityClientSendRobotCommand(m_socket.getSocket(), ROBOT_COMMAND_LED_OFF) ;
}
