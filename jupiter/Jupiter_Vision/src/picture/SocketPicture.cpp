#include "SocketPicture.h"
#include <iostream>

using namespace std ;

#define WINDOW_NAME "Frame display Testing"

SocketPicture::SocketPicture() {
    cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE) ;
}


SocketPicture::~SocketPicture() {

}


void SocketPicture::setData(uint8_t* data, int length, int width, int height) {
    m_frame = cv::Mat(cv::Size(width, height), CV_8UC3, data) ;
}


void SocketPicture::display() {
    cv::imshow(WINDOW_NAME, m_frame) ;
    cv::waitKey(1) ;
}
