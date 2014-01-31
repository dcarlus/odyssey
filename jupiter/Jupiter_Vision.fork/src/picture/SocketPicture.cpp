#include "SocketPicture.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std ;

#define WINDOW_NAME "Frame display Testing"
#define BANANA_DETECT "../../media/detect/banana_classifier.xml"


SocketPicture::SocketPicture() {
    cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE) ;
    assert(m_cascade.load(BANANA_DETECT)) ;
}


SocketPicture::~SocketPicture() {

}


void SocketPicture::setData(uint8_t* data, int length, int width, int height) {
    m_frame = cv::Mat(cv::Size(width, height), CV_8UC3, data) ;
    detect() ;
}


void SocketPicture::display() {
    cv::imshow(WINDOW_NAME, m_frame) ;
    cv::waitKey(1) ;
}


void SocketPicture::detect() {
    vector<cv::Rect> objects ;
    cv::Mat grayFrame ;

    cv::cvtColor(m_frame, grayFrame, CV_BGR2GRAY) ;
    cv::equalizeHist(grayFrame, grayFrame) ;

    // Detect object
    m_cascade.detectMultiScale(grayFrame, objects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30)) ;

    for (size_t i = 0 ; i < objects.size() ; i++) {
        cv::Point center(objects[i].x + objects[i].width*0.5f, objects[i].y + objects[i].height*0.5f) ;
        cv::ellipse(m_frame, center, cv::Size(objects[i].width*0.5f, objects[i].height*0.5f), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0) ;
    }
}
