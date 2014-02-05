#include "H264Decoder.h"
#include <cassert>
#include <iostream>
#include <errno.h> 

using namespace std ;


H264Decoder::H264Decoder() {
    av_init_packet(&m_avPacket) ;
    m_frameCounter = 0 ;

    m_codec = avcodec_find_decoder(CODEC_ID_H264) ;
    if (!m_codec) {
        cerr << "Codec H264 not found" << endl ;
        exit(1) ;
    }

    m_avContext = avcodec_alloc_context3(m_codec) ;
    m_rawPicture = avcodec_alloc_frame() ;

    // Do not send complete frames
    if ((m_codec -> capabilities) & CODEC_CAP_TRUNCATED)
        m_avContext -> flags |= CODEC_FLAG_TRUNCATED ;

    if (avcodec_open2(m_avContext, m_codec, NULL) < 0) {
        cerr << "Codec H264 could not be opened" << endl ;
        exit(1) ;
    }
}

H264Decoder::~H264Decoder() {
    avcodec_close(m_avContext) ;
    av_free(m_avContext) ;
    av_free(m_rawPicture) ;
}


bool H264Decoder::setFrame(uint8_t* compressedImage, size_t dataSize) {
    m_avPacket.data = compressedImage ;
    m_avPacket.size = dataSize ;

    int length ;
    int hasGotPicture ;
    while (m_avPacket.size > 0) {
        length = avcodec_decode_video2(m_avContext, m_rawPicture, &hasGotPicture, &m_avPacket) ;

        if (length < 0) {
            cerr << "Error while decoding frame #" << m_frameCounter << endl ;
            return false ;
        }

        m_avPacket.size -= length ;
    }

    m_frameCounter++ ;
    return true ;
}

void H264Decoder::freeBuffer(uint8_t*& buffer) {
    av_free(buffer) ;
}


int H264Decoder::getRawData(uint8_t*& buffer) {
    m_lastReadFrame = m_frameCounter ;

    AVPicture rgbFrame ;
    PixelFormat rgbFormat = PIX_FMT_BGR24 ;
    if (convertPixelFormat(rgbFrame, rgbFormat)) {
        int width = m_rawPicture -> width ;
        int height = m_rawPicture -> height ;
        int bufferSize = avpicture_get_size(rgbFormat, width, height) ;

        int length = 0 ;
        buffer = (uint8_t*) av_malloc(bufferSize) ;
        length = avpicture_layout(&rgbFrame, rgbFormat, width, height, buffer, bufferSize) ;
        avpicture_free(&rgbFrame) ;
        return length ;
    }
    else
        return -1 ;
}

int H264Decoder::getWidth() {
    assert(m_lastReadFrame == m_frameCounter) ;
    return m_rawPicture -> width ;
}

int H264Decoder::getHeight() {
    assert(m_lastReadFrame == m_frameCounter) ;
    return m_rawPicture -> height ;
}


bool H264Decoder::convertPixelFormat(AVPicture& destFrame,
                                     PixelFormat destPixelFormat) {
    PixelFormat yuvFormat = (PixelFormat) m_rawPicture -> format ;
    int width = m_rawPicture -> width ;
    int height = m_rawPicture -> height ;

    if (width > 0 && height > 0) {
        SwsContext* colorConvertContext ;
        avpicture_alloc(&destFrame, destPixelFormat, width, height) ;
        // Set up the conversion
        colorConvertContext = sws_getContext(width, height, yuvFormat,          // Source (YUV)
                                             width, height, destPixelFormat,    // Destination
                                             SWS_BILINEAR, NULL, NULL, NULL) ;  // Filters and parameters

        if (colorConvertContext == NULL) {
            cerr << "Error on SWS Context creation" << endl ;
            return false ;
        }

        // Apply the conversion on the RGB frame
        sws_scale(colorConvertContext,
                  m_rawPicture -> data, m_rawPicture -> linesize, 0, height,
                  destFrame.data, destFrame.linesize) ;

        sws_freeContext(colorConvertContext) ;

        return true ;
    }

    return false ;
}
