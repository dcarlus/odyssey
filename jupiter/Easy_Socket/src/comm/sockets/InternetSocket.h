#ifndef __EASYSOCKET_INTERNET_SOCKET_H__
#define __EASYSOCKET_INTERNET_SOCKET_H__

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <string>


#include <iostream>

#include "SocketException.h"


namespace es {
    /**
     * @brief   InternetSocket class makes socket programming faster and shorter to
     *          avoid the boring manipulation of the socket descriptor at each
     *          function call, creation of structures, etc.
     *          The sockets are automatically configurated to run over the internet
     *          protocols and can be more precisely be configurated by giving the
     *          local IP address, etc. On the destruction of a InternetSocket object
     *          the socket descriptor is automatically closed.
     *
     *          This is a simple C++ wrapper of the C socket API. It doesn't do more
     *          stuff than the original API. Moreover, all the functions have the
     *          same name as the original ones in order to make it easier to use for
     *          familiar users of the C API.
     *          It can be derivated to add functionalities.
     *
     * @see     SocketException
     * @see     InternetSocketMetapackage
     *
     * @version 1.0     Creation of the C++ API for socket management.
     * @author  Denis CARLUS
     */
    class InternetSocket {
        public:
            /**
             * @brief Shutdown communication with a socket.
             * SHUTDOWN_ALL = Close incoming and outcoming communications ;
             * SHUTDOWN_OUT = Close outcoming communications only ;
             * SHUTDOWN_IN  = Close incoming communications only ;
             */
            enum SHUTDOWN_HOW {SHUTDOWN_ALL = 0, SHUTDOWN_OUT, SHUTDOWN_IN} ;


        protected:
            /** @brief  Socket descriptor of the current machine used by syscalls. */
            int m_socketDesc ;


            /** @brief To know if the descriptor has been bound to an IP and port. */
            bool m_isBound ;
            /** @brief To know if the socket has already received parameters. */
            bool m_isPrepared ;
            /** @brief To know if the descriptor is listening on a port. */
            bool m_isListening ;

            /** @brief Address of the machine. */
            struct sockaddr_in m_address ;


        public:
            /**
             * @brief   Creation of a socket made for internet communications.
             * @param   type        Type of the socket to use (SOCK_STREAM or
             *                      SOCK_DGRAM).
             * @param   protocol    Name of the wanted protocol.
             */
            InternetSocket(int type = SOCK_STREAM,
                           const std::string& protocol = "") throw (SocketException) ;

            /** @brief Destruction of an InternetSocket. */
            virtual ~InternetSocket() ;


            /**
             * @brief   Prepare the configuration of the socket without binding it.
             *          The port is then free until the socket is bound.
             * @param   ip          IP address of the machine. Use the current IP of
             *                      the machine if empty (default value).
             * @param   port        Port used for communications. Use a randomly
             *                      choosed free port if equal to 0 (default value).
             */
            void prepare(const std::string& ip = "",
                         unsigned short port = 0) throw (SocketException) ;


            /** @brief Bind the socket with the parameters given to prepare(). */
            void bindPrepare() throw (SocketException) ;


            /**
             * @brief   Bind the socket to an IP address and a port. This can be
             *          used to receive messages.
             * @param   ip          IP address of the machine. Use the current IP of
             *                      the machine if empty (default value).
             * @param   port        Port used for communications. Use a randomly
             *                      choosed free port if equal to 0 (default value).
             */
            void bind(const std::string& ip = "",
                      unsigned short port = 0) throw (SocketException) ;


            /**
             * @brief Make a connection to a distant server.
             * @param   ip          IP address of the server.
             * @param   port        Port on which the server is listening.
             * @return  The socket descriptor of the current machine.
             */
            int connect(const std::string& ip,
                        unsigned short port) throw (SocketException) ;


            /**
             * @brief   The machine listens of the port used when binding a socket
             *          (ip::port) to the descriptor.
             * @param   max         Maximal amount of waiting connections.
             */
            void listen(int max = 20) throw (SocketException) ;

            /**
             * @brief   Accept a new connection on the listening port and save the
             *          client connection.
             * @return  The client socket descriptor.
             * @warning This is a blocking function.
             */
            int accept(struct sockaddr_in* client_addr = 0) throw (SocketException) ;


            /**
             * @brief   Send a message (TCP, UDP).
             * @param   sockfd          The socket descriptor through which the
             *                          message must be sent.
             * @param   message         The message to send.
             * @param   length          Length of the message.
             * @param   flag            Flags linked to the sent message.
             * @param   Length really sent.
             */
            int send(const int sockfd,
                     const void* message,
                     const int length,
                     const int flags = 0) throw (SocketException) ;


            /**
             * @brief   Send a message (TCP, UDP).
             * @param   sockfd          The socket descriptor through which the
             *                          message must be sent.
             * @param   message         The message to send.
             * @param   flag            Flags linked to the sent message.
             * @param   Length really sent.
             */
            int send(const int sockfd,
                     const std::string& message,
                     const int flags = 0) throw (SocketException) ;


            /**
             * @brief   Send a message (TCP, UDP).
             * @param   sockfd          The socket descriptor through which the
             *                          message must be sent.
             * @param   message         The message to send.
             * @param   length          Length of the message.
             * @param   Length really sent.
             */
            int write(const int sockfd,
                      const void* message,
                      const int length) ;

            /**
             * @brief   Send a message (TCP, UDP).
             * @param   sockfd          The socket descriptor through which the
             *                          message must be sent.
             * @param   message         The message to send.=
             * @param   Length really sent.
             */
            int write(const int sockfd,
                      const std::string& message) ;


            /**
             * @brief   Receive a message (TCP, UDP).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   buffer          Buffer where will be put the message.
             * @param   length          Length of the message (buffer).
             * @param   flag            Flags linked to the sent message.
             * @return  The length read in the buffer.
             */
            int recv(const int sockfd,
                     void* buffer,
                     unsigned int length,
                     unsigned int flags = 0) throw (SocketException) ;


            /**
             * @brief   Receive a message (TCP, UDP).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   buffer          Buffer where will be put the message.
             * @param   flag            Flags linked to the sent message.
             * @return  The length read in the buffer.
             * @warning The length of the message cannot exceed 4096 characters.
             */
            int recv(const int sockfd,
                     std::string& buffer,
                     unsigned int flags = 0) throw (SocketException) ;


            /**
             * @brief   Receive a message (TCP, UDP).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   buffer          Buffer where will be put the message.
             * @param   length          Length of the message (buffer).
             * @return  The length read in the buffer.
             */
            int read(const int sockfd,
                     void* buffer,
                     const unsigned int length) ;


            /**
             * @brief   Receive a message (TCP, UDP).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   buffer          Buffer where will be put the message.
             * @return  The length read in the buffer.
             */
            int read(const int sockfd,
                     std::string& buffer) ;


            /**
             * @brief   Send a message with the not connected mode (UDP...).
             * @param   sockfd          The socket descriptor through which the
             *                          message must be sent.
             * @param   to_ip           IP of the machine to send the message.
             * @param   port            Port to correctly send the message.
             * @param   message         The message to send.
             * @param   length          Length of the message.
             * @param   flag            Flags linked to the sent message.
             * @param   Length really sent.
             */
            int sendto(const int sockfd,
                       const std::string& to_ip,
                       unsigned short port,
                       const void* message,
                       unsigned int length,
                       unsigned int flags = 0) throw (SocketException) ;


            /**
             * @brief   Receive a message with the not connected mode (UDP...).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   from            Structure to retreive the sender IP and port.
             * @param   from_length     Size of the structure containing the
             *                          informations about the sender.
             * @param   buffer          Buffer where will be put the message.
             * @param   length          Length of the message (buffer).
             * @param   flag            Flags linked to the sent message.
             * @return  The length read in the buffer.
             */
            int recvfrom(int sockfd,
                         sockaddr& from,
                         socklen_t& from_length,
                         void* buffer,
                         unsigned int length,
                         unsigned int flags = 0) throw (SocketException) ;


            /**
             * @brief   Receive a message with the not connected mode (UDP...).
             * @param   sockfd          Socket descriptor of the sender.
             * @param   from            Structure to retreive the sender IP and port.
             * @param   from_length     Size of the structure containing the
             *                          informations about the sender.
             * @param   buffer          Buffer where will be put the message.
             * @param   flag            Flags linked to the sent message.
             * @return  The length read in the buffer.
             */
            int recvfrom(int sockfd,
                         sockaddr& from,
                         socklen_t& from_length,
                         std::string& buffer,
                         unsigned int flags = 0) throw (SocketException) ;


            /**
             * @brief   Close the communications with this socket.
             */
            void close() ;


            /**
             * @brief   Close the communications with this socket with more accurate
             *          control on the stopped communications.
             */
            void shutdown(SHUTDOWN_HOW how) throw (SocketException) ;


            /** @brief Get the socket descriptor of the machine. */
            int getSocket() const ;

            /** @brief Get the address structure of the machine. */
            const sockaddr_in& getAddress() const ;

            /** @brief To know if the socket is bound to the machine. */
            bool isBound() const ;

            /** @brief To know if the socket is prepared with parameters. */
            bool isPrepared() const ;

            /** @brief To know if the socket is listening on its port. */
            bool isListening() const ;
    } ;
}

#endif 
