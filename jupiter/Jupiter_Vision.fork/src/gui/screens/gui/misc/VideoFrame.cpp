#include "VideoFrame.h"
#include <GL/gl.h>
#include <cstdlib>
#include "../../../VideoTexture.h"
#include <iostream>

using namespace std ;

VideoFrame::VideoFrame(const Position& pos,
                       const Dimension& size) : AlComponent(pos, false) {
    updateBounds(pos, size) ;
}

VideoFrame::~VideoFrame() {}


void VideoFrame::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    glLoadIdentity() ;

    if (VideoTexture::getInstance() -> isStored()) {
        glEnable(GL_TEXTURE_2D) ;
        VideoTexture::getInstance() -> makeActive() ;
        glBegin(GL_QUADS) ;
            glTexCoord2f(0, 0) ; glVertex2i(m_bounds.getX(),    m_bounds.getY()) ;
            glTexCoord2f(1, 0) ; glVertex2i(m_bounds.getMaxX(), m_bounds.getY()) ; 
            glTexCoord2f(1, 1) ; glVertex2i(m_bounds.getMaxX(), m_bounds.getMaxY()) ;
            glTexCoord2f(0, 1) ; glVertex2i(m_bounds.getX(),    m_bounds.getMaxY()) ;
        glEnd() ;
        glDisable(GL_TEXTURE_2D) ;
    }
}

void VideoFrame::update() {}

void VideoFrame::trigger() {}
