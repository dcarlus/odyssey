#ifndef __EASYSOCKET_SOCKET_EXCEPTION_H__
#define __EASYSOCKET_SOCKET_EXCEPTION_H__

#include <exception>
#include <string>

namespace es {
    class SocketException : public std::exception {
        private:
            std::string m_message ;

        public:
            /**
             * @brief   Creation of a socket exception from the error given by the
             *          system.
             */
            SocketException() {
                char* error = 0 ;
                perror(error) ;
                m_message = std::string(error) ;
            }

            /**
             * @brief   Creation of a socket exception.
             * @param   message Message of the exception
             */
            SocketException(const std::string& message) {
                m_message = message ;
            }

            /** @brief  Destruction of a socket exception. */
            virtual ~SocketException() throw() {}


            /**
             * @brief   Get the message of the exception.
             * @return  The message of the exception
             */
            virtual const char* what() const throw() {
                return std::string("SocketException: " + m_message).c_str() ;
            }
    } ;
}

#endif
