#ifndef __JUPITER__STREAMING_CLIENT__
#define __JUPITER__STREAMING_CLIENT__

#include <easysocket/comm.h>
#include <easysocket/tools.h>
#include "../picture/H264Decoder.h"

class StreamingClient : public es::Client, private NoCopy {
    private:
        /** @brief  Unique instance of the streaming client. */
        static StreamingClient Instance ;
        /** @brief  Decoder used by the client to get uncompressed picture data. */
        H264Decoder m_decoder ;


        /** @brief  Create the StreamingClient. */
        StreamingClient() ;

        /** @brief  Destroy the StreamingClient. */
        virtual ~StreamingClient() throw() ;


    public:
        /** @brief  Get the StreamingClient instance. */
        static StreamingClient* getInstance() ;


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
