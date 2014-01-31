#ifndef __POLYPHEMUS__VIDEO_FRAME__
#define __POLYPHEMUS__VIDEO_FRAME__

#include "../AlComponent.h"

/**
 * @brief   A video frame is used to display a video on screen from the
 *          VideoTexture singleton.
 * @author  Denis CARLUS
 * @version 1.0 26/01/2014
 */
class VideoFrame : public AlComponent {
    public:
        /**
         * @brief   Create a new VideoFrame display.
         * @param   Position of the VideoFrame.
         */
        VideoFrame(const Position& pos, const Dimension& size) ;

        /** @brief  Destroy the VideoFrame. */
        virtual ~VideoFrame() ;


        /** @brief  Display the component. */
        virtual void display() ;

        /** @brief  Update the component. */
        virtual void update() ;

        /** @brief  Trigger the component action. */
        virtual void trigger() ;
} ;

#endif
