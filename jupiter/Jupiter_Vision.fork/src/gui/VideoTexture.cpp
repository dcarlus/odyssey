#include "VideoTexture.h"
#include <iostream>
#include <GL/glu.h>

using namespace std ;

VideoTexture* VideoTexture::Singleton = 0 ;
sem_t VideoTexture::Access ;

VideoTexture::VideoTexture() {
    assert(sem_init(&Access, 0, 1) == 0) ;
    m_textureID = 0 ;
    glGenTextures(1, &m_textureID) ;
    m_isStored = false ;
}

VideoTexture::~VideoTexture() throw() {
    sem_destroy(&Access) ;
}

VideoTexture* VideoTexture::getInstance() {
    if (Singleton == 0)
        Singleton = new VideoTexture() ;

    return Singleton ;
}


void VideoTexture::update(uint8_t* data, uint32_t width, uint32_t height) {
    sem_wait(&Access) ;
        glBindTexture(GL_TEXTURE_2D, m_textureID) ;

        // Allocate memory if needed
        if (!m_isStored) {
            m_isStored = true ;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data) ;
        }
        // Else reuse allocated memory to copy data
        else {
//            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, data) ;
        }
    sem_post(&Access) ;
}


void VideoTexture::makeActive() {
    sem_wait(&Access) ;
        glBindTexture(GL_TEXTURE_2D, m_textureID) ;
    sem_post(&Access) ;
}


bool VideoTexture::isStored() {
    sem_wait(&Access) ;
        bool stored = m_isStored ;
    sem_post(&Access) ;
    return stored ;
}
