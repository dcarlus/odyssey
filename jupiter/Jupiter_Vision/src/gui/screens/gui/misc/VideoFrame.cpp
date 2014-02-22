#include "VideoFrame.h"
#include <GL/gl.h>
#include <cstdlib>
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
}

void VideoFrame::update() {}

void VideoFrame::trigger() {}
