#ifndef __JUPITER__SOCKET_PICTURE__
#define __JUPITER__SOCKET_PICTURE__

#include <opencv2/opencv.hpp>
#include "../interfaces/Displayable.h"

/**
 * @brief   A Picture loaded from the data read on socket.
 * @author  Denis CARLUS
 * @version 1.0 21/01/2014
 */
class SocketPicture : public Displayable {
    protected:
        /** @brief  Frame represented as OpenCV Mat object. */
        cv::Mat m_frame ;

    public:
        /** @brief  Create a Picture. */
        SocketPicture() ;

        /** @brief  Destroy a Picture. */
        virtual ~SocketPicture() ;


        /**
         * @brief   Set the data of the Picture.
         * @param   data    Data of the frame.
         * @param   length  Length of the frame data.
         * @param   width   Width of the frame.
         * @param   height  Height of the frame.
         */
        void setData(uint8_t* data, int length, int width, int height) ;


        /** @brief  Display the frame on screen. */
        virtual void display() ;
} ;

#endif
