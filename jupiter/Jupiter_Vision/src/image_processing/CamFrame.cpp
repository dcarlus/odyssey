#include "CamFrame.h"

using namespace std ;


CamFrame::CamFrame() {
    m_morphKernel = getStructuringElement(MORPH_ELLIPSE, Size(9, 9)) ;
}

CamFrame::CamFrame(cv::Mat& frame) {
    setFrame(frame) ;
}

CamFrame::~CamFrame() {}


void CamFrame::setFrame(cv::Mat& frame) {
    convertToHLS(frame) ;
    m_mask = cv::Mat(frame.rows, frame.cols, CV_8UC1, 255) ;
}

void CamFrame::setMask(cv::Scalar& minHLS, cv::Scalar maxHLS) {
    m_minMask = minHLS ;
    m_maxMask = maxHLS ;
}


void CamFrame::mask() {
    cv::inRange(m_hls, m_minMask, m_maxMask, m_mask) ;
    prepareMask() ;            

    m_tag.setFrame(m_mask) ;
    m_tag.run() ;
    Position center = m_tag.getFirstComponentCenter(500) ;

    if (center.x > -1.f)
        CursorPositionBuffer::getInstance() -> addPosition(center) ;
    else
        CursorPositionBuffer::getInstance() -> lostCursor() ;
}


void CamFrame::convertToHLS(cv::Mat& rgb) {
    cv::cvtColor(rgb, m_hls, CV_BGR2HLS) ;
}

void CamFrame::prepareMask() {
//    cv::dilate(m_mask, m_mask, m_morphKernel) ;
//    cv::erode(m_mask, m_mask, m_morphKernel) ;
}
