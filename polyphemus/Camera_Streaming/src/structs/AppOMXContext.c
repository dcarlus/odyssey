/**
 * @file     AppOMXContext.c
 * @author   Denis CARLUS
 */

#include "AppOMXContext.h"

                                                                 /** GETTERS **/
/** @brief  Get the camera OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetCameraHandleType(AppOMXContext* self) {
    return &((self -> camera).basic.type) ;
}

/** @brief  Get the encoder OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetEncoderHandleType(AppOMXContext* self) {
    return &((self -> encoder).basic.type) ;
}

/** @brief  Get the null sink OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetNullSinkHandleType(AppOMXContext* self) {
    return ((self -> nullSink).type) ;
}

/** @brief  Get the handler locker semaphore of the application context. */
static VCOS_SEMAPHORE_T* AppOMXContext_GetHandlerLock(AppOMXContext* self) {
    return &(self -> handlerLock) ;
}


                                                                 /** SETTERS **/
/** @brief  Set the camera readiness flag to true. */
static void AppOMXContext_SetCameraReady(AppOMXContext* self) {
    BufferOMXHandler* cameraBuffer = &(self -> camera) ;
    BasicOMXHandler* camera = cameraBuffer -> getBasicHandler(cameraBuffer) ;
    camera -> setReady(camera) ;
}

/** @brief  Set the encoder availability flag to true. */
static void AppOMXContext_SetEncoderOutputBufferAvailable(AppOMXContext* self) {
    BufferOMXHandler* encoderBuffer = &(self -> encoder) ;
    BasicOMXHandler* encoder = encoderBuffer -> getBasicHandler(encoderBuffer) ;
    encoder -> setReady(encoder) ;
}

/** @brief  Set the flush flag to true. */
static void AppOMXContext_SetFlushed(AppOMXContext* self) {
    self -> flushed = 1 ;
}


                                                             /** CONSTRUCTOR **/
/** @brief  Initialize an AppOMXContext. */
static void _AppOMXContext_Init(AppOMXContext* self) {
    // Getters
    self -> getCamera = AppOMXContext_GetCameraHandleType ;
    self -> getEncoder = AppOMXContext_GetEncoderHandleType ;
    self -> getNullSink = AppOMXContext_GetNullSinkHandleType ;
    self -> getHandlerLock = AppOMXContext_GetHandlerLock ;

    // Setters
    self -> setCameraReady = AppOMXContext_SetCameraReady ;
    self -> setEncoderOutputBufferAvailable = AppOMXContext_SetEncoderOutputBufferAvailable ;
    self -> flush = AppOMXContext_SetFlushed ;
}



AppOMXContext AppOMXContext_Construct() {
    AppOMXContext ctx ;
    _AppOMXContext_Init(&ctx) ;
    return ctx ;
}

void* AppOMXContext_Memset(AppOMXContext* self, int c, size_t n) {
    void* result = memset(self, c, n) ;
    _AppOMXContext_Init(self) ;
    return result ;
}
