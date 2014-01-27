#ifndef __POLYPHEMUS__VIDEO_TEXTURE__
#define __POLYPHEMUS__VIDEO_TEXTURE__

#include <easysocket/tools.h>
#include <GL/gl.h>
#include <assert.h>
#include <semaphore.h>

/**
 * @brief   A video texture is an image displayed with Allegro + OGL library and
 *          loaded from main memory to GPU memory. It is a shared object between
 *          threads to write and read picture.
 * @author  Denis CARLUS
 * @version 1.0 26/01/2014
 */
class VideoTexture : private NoCopy {
    private:
        /** @brief  Singleton of the VideoTexture. */
        static VideoTexture* Singleton ;

        /**
         * @brief Regulate the access to the singleton to avoid concurrency
         *        problems.
         */
        static sem_t Access ;

        /** @brief  ID given by OpenGL to retreive the texture. */
        GLuint m_textureID ;
        /** @brief  To know if the texture is already stored. */
        bool m_isStored ;

                                            /** CONSTRUCTION AND DESTRUCTION **/
        /** @brief Construction of a VideoTexture. */
        VideoTexture() ;

        /** @brief Destruction of the VideoTexture. */
        ~VideoTexture() throw() ;


    public:
        /**
         * @brief Get the unique instance of VideoTexture.
         * @return  The unique instance of VideoTexture.
         */
        static VideoTexture* getInstance() ;


        /**
         * @brief   Load the texture from main memory to update the video frame.
         * @param   Data of the raw picture.
         * @param   Width of the picture.
         * @param   Height of the picture.
         */
        void update(uint8_t* data, uint32_t width, uint32_t height) ;


        /** @brief  Make the texture active for updates, show, etc. */
        void makeActive() ;

        /** @brief  To know if the texture is loaded. */
        bool isStored() ;
} ;

#endif
