#ifndef __JUPITER__COMMAND_CLIENT__
#define __JUPITER__COMMAND_CLIENT__

extern "C" {
    #include <Log.h>
    #include <Security_Client.h>
    #include <Robot.h>
}

#include <easysocket/comm.h>
#include <easysocket/tools.h>

class CommandClient : public es::Client, private NoCopy {
    private:
        /** @brief  Unique instance of the streaming client. */
        static CommandClient* Instance ;

        /** @brief  State of the LED on Mercury. */
        bool m_isLEDOn ;



        /** @brief  Create the CommandClient. */
        CommandClient() ;

        /** @brief  Destroy the CommandClient. */
        virtual ~CommandClient() throw() ;


    public:
        /** @brief  Get the CommandClient instance. */
        static CommandClient* getInstance() ;

        /**
         * @brief   Send a command to Mercury to make it move.
         * @param   command Command symbol.
         */
        void sendMoveCommand(TRobotCommand command) ;

        /** @brief   Send a LED command to switch its state. */
        void sendLEDCommand() ;

        /** @brief   Receive the battery load. */
        char getBatteryLoadRate() ;


    protected:
        /** @brief  Intermediate function to easily create a thread. */
        static void* manageThread(void* param) ;

        /**
         * @brief  Function to implement in the specific client to create
         *         the background client thread.
         */
        virtual void createThread() ;

        /** @brief  Run the client thread. Call stop() to stop it. */
        virtual void run() ;
} ;

#endif
