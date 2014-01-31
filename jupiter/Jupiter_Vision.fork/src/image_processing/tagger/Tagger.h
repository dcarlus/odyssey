#ifndef __TAGGER_H__
#define __TAGGER_H__

#include "../../tools/geometry/Position.h"
#include "../component/Component.h"
#include "../component/Pixel.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>

using namespace cv ;

#ifndef PICTURE_WINDOW
    #define PICTURE_WINDOW "Picture"
#endif

#ifndef COLOR_WINDOW
    #define COLOR_WINDOW "Colorized"
#endif

class Tagger {
	typedef std::map<unsigned int, Component>::iterator ComponentIterator ;

    protected:
        /** @brief  The picture used by the tagger. */
        Mat m_picture ;
        /** @brief  Type of the picture to open (color depth). */
        int m_type ;

        /** @brief  To know if the image is shown. */
        bool m_showPicture ;
        /** @brief  To know if the tagger is ready to be runned. */
        bool m_ready ;

        /** @brief List of the connected components. */
        std::map<unsigned int, Component> m_connectedComponents ;

        /** @brief  Map of pixels with their connected component. */
        Pixel** m_pixelMap ;


    public:
        /** @brief  Create a tagger. */
        Tagger(int type) ;

        /** @brief  Destroy a tagger. */
        virtual ~Tagger() ;


        /** @brief  Open a picture. */
        void load(char* file) ;

        /** @brief  Run the tagging task. */
        void run() ;


        /**
         * @biref   Get the center of the first component found with a pixel
         *          count bigger or equal to the given threshold.
         */
        Position getFirstComponentCenter(int threshold = 0) ;

        /**
         * @brief  Create a new picture with colored components.
         * @param   threshold   Minimal size of the components to draw.
         *                      0 to draw all the components.
         */
        void colorizeComponents(int threshold = 0) ;

        /**
         * @brief  Count amount of detected connected components.
         * @param   threshold   Minimal size of the components to count.
         *                      0 to count all the components.
         */
        virtual unsigned int countConnectedComponents(int threshold = 0) ;


        /** @brief  Change the colors of the components. */
        virtual void changeColors() ;

        /** @brief  Set the frame on which the tagger must work. */
        void setFrame(Mat& picture) ;


    protected:
        /** @brief  Detect the background color. */
        virtual void detectBackgroundColor() = 0 ;

        /** @brief  Detect a connected components. */
        virtual void detectConnectedComponents(int y, int x, int beforeY, int beforeX) = 0 ;

        /**
         * @brief   Set the pixel matrice.
         * @param   recreate    Need to recreate a 2D array to fit the picture
         *                      size.
         */
        void setPixelMatrice(bool recreate = true) ;
} ;

#endif
