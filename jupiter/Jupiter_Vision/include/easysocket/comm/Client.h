#ifndef __EASYSOCKET_CLIENT_H__
#define __EASYSOCKET_CLIENT_H__

#include "sockets/InternetSocket.h"
#include "../tools/Logger.h"

#include <assert.h>
#include <pthread.h>
#include <string>
#include <cstdlib>
#include <ctime>

namespace es {
    /**
     * @brief A client sends and receives data to one server only.
     * @version 1.0     04/08/2013
     * @version 1.1     12/01/2014
     * @author Denis CARLUS
     */
    class Client {
        protected:
            /** @brief  Session of the user. */
            std::string m_session ;
            /** @brief Socket of the client. */
            InternetSocket m_socket ;
            /** @brief  To know if the thread is running. */
            bool m_isRunning ;

            /**
             * @brief   Mutex used to generate critical sections when accessing the
             *          client thread.
             */
            pthread_mutex_t m_clientState ;

        public:
            /**
             * @brief   Creation of a new client, connected to the given server.
             * @param   serverIP    IP of the server to connect to.
             * @param   serverPort  Port of the server to be connected.
             */
            Client(const std::string& serverIP, unsigned short serverPort) ;

            /** @brief  Destruction of a client. */
            virtual ~Client() ;


            /** @brief  Get the session determined at client starting. */
            const std::string& getSession() ;


            /** @brief  Start the client thread. */
            virtual void start() ;

            /** @brief  Safely stop the thread. */
            virtual void stop() ;

        protected:
            /**
             * @brief  Function to implement in the specific client to create
             *         the background client thread.
             */
            virtual void createThread() = 0 ;

            /** @brief  Run the client thread. Call stop() to stop it. */
            virtual void run() = 0 ;
    } ;
}

#endif
