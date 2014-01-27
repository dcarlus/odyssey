#ifndef __CAMFRAME_H__
#define __CAMFRAME_H__

#include <opencv2/opencv.hpp>
#include "tagger/BWTagger.h"
#include "../tools/CursorPositionBuffer.h"

#include <iostream>

#ifndef WINDOW_MASK
    #define WINDOW_MASK "Color mask"
#endif

#ifndef WINDOW_ORIGINAL
    #define WINDOW_ORIGINAL "Webcam frame"
#endif

class CamFrame {
    protected:
        /** @brief  Minimal H L S values to detect object. */
        cv::Scalar m_minMask ;
        /** @brief  Maximal H L S values to detect object. */
        cv::Scalar m_maxMask ;
        /** @brief  Kernel applied on morphologic transformations. */
        cv::Mat m_morphKernel ;
        /** @brief  Decomposition of the original picture in channels H L S. */
        cv::Mat m_HLS[3] ;
        /** @brief  The HLS converted picture from the webcam. */
        cv::Mat m_hls ;
        /** @brief  The thresholded picture. */
        cv::Mat m_mask ;

        /** @brief  Tagger used to set the connected components of the frame. */
        BWTagger m_tag ;


    public:
        /** Create a CamFrame. */
        CamFrame() ;

        /** Create a CamFrame. */
        CamFrame(cv::Mat& frame) ;

        /** Destruction of a CamFrame. */
        virtual ~CamFrame() ;


        /** @brief  Set the frame to run process on. */
        void setFrame(cv::Mat& frame) ;

        /** @brief  Set the mask values to detect objects. */
        void setMask(cv::Scalar& minHLS, cv::Scalar maxHLS) ;


        /** @brief  Generate a mask of the HLS picture. */
        void mask() ;


    protected:
        /** @brief  Convert the original picture to HLS. */
        void convertToHLS(cv::Mat& rgb) ;

        /** Prepare the mask with erosion, then dilatation of the pixels. */
        void prepareMask() ;
} ;

#endif
