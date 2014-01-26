#ifndef __JUPITER__H264_DECODER__
#define __JUPITER__H264_DECODER__

    #ifdef __cplusplus
        extern "C" {
            #include <libavcodec/avcodec.h>
            #include <libavutil/mathematics.h>
            #include <libswscale/swscale.h>
        }
    #endif

#define INBUF_SIZE   4096
#define FF_INPUT_BUFFER_PADDING_SIZE   16

/**
 * @brief   A decoder of H264 frames using FFMpeg API.
 * @author  Denis CARLUS
 * @version 1.0 21/01/2014
 */
class H264Decoder {
    protected:
        /** @brief  Codec to decode the H264 frame. */
        AVCodec* m_codec ;
        /** @brief  Context of the H264 codec. */
        AVCodecContext* m_avContext ;
        /** @brief  Storage of the compressed data frame. */
        AVPacket m_avPacket ;
        /** @brief  Uncompressed picture after decoding. */
        AVFrame* m_rawPicture ;
        /** @brief  Frame counter of the last decoded frame. */
        unsigned int m_frameCounter ;
        /** @brief  Frame counter of the last read decoded frame. */
        unsigned int m_lastReadFrame ;

    public:
        /** @brief  Create a H264Decoder. */
        H264Decoder() ;

        /** @brief  Destroy a H264Decoder. */
        virtual ~H264Decoder() ;

        /**
         * @brief   Set the compressed frame and retreive the raw data.
         * @param   compressedImage Data of the compressed image.
         * @param   dataSize        Size of the data.
         * @return  TRUE if the frame has been correctly decoded, FALSE else.
         */
        virtual bool setFrame(uint8_t* compressedImage, size_t dataSize) ;

        /** @brief  Free a buffer allocated by the decoder. */
        void freeBuffer(uint8_t*& buffer) ;

        /**
         * @brief   Get the raw data of the last decoded picture.
         * @param   Buffer where the raw data are copied to. Do not allocate it
         *          as it depends on the picture size. The raw data are written
         *          as a BGR 24-bit picture.
         * @return  The size of the buffer on output.
         */
        int getRawData(uint8_t*& buffer) ;

        /**
         * @brief   Get the width of the last decoded picture.
         * @return  Width of the picture.
         * @warning Call getRawData() first.
         */
        int getWidth() ;

        /**
         * @brief   Get the height of the last decoded picture.
         * @return  Height of the picture.
         * @warning Call getRawData() first.
         */
        int getHeight() ;

    protected:
        /**
         * @brief   Convert a picture to another pixel format.
         * @param   destFrame       Frame to which data are copied.
         * @param   destPixelFormat Pixel format used for the destination frame.
         */
        bool convertPixelFormat(AVPicture& destFrame,
                                AVPixelFormat destPixelFormat) ;
} ;

#endif
