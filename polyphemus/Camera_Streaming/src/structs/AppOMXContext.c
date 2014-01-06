/**
 * @file     AppOMXContext.c
 * @author   Denis CARLUS
 */

#include "AppOMXContext.h"
#include "handlers/camera/CameraBufferHandler.h"
#include "handlers/encoder/EncoderBufferHandler.h"
#include "handlers/null_sink/NullSinkHandler.h"

                                                           /** CONFIGURATION **/
/** @brief  Configure the camera parameters. */
static void AppOMXContext_ConfigureCamera(AppOMXContext* self) {
    BasicOMXHandler* cameraHandler = &(self -> camera).basic ;
    cameraHandler -> configure(cameraHandler) ;
}


/** @brief  Configure the encoder parameters. */
static void AppOMXContext_ConfigureEncoder(AppOMXContext* self) {
    BasicOMXHandler* encoderHandler = &(self -> encoder).basic ;
    BasicOMXHandler* cameraHandler = &(self -> camera).basic ;
    encoderHandler -> configure(encoderHandler) ;
}


                                                                 /** GETTERS **/
/** @brief  Get the camera OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetCameraHandleType(AppOMXContext* self) {
    return &(((self -> camera).basic).type) ;
}

/** @brief  Get the encoder OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetEncoderHandleType(AppOMXContext* self) {
    return &(((self -> encoder).basic).type) ;
}

/** @brief  Get the null sink OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetNullSinkHandleType(AppOMXContext* self) {
    return &((self -> nullSink).type) ;
}

/** @brief  Get the handler locker semaphore of the application context. */
static VCOS_SEMAPHORE_T* AppOMXContext_GetHandlerLock(AppOMXContext* self) {
    return &(self -> handlerLock) ;
}

/** @brief  Get the flush flag. */
static char AppOMXContext_IsFlushed(AppOMXContext* self) {
    return self -> flushed ;
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

/** @brief  Set the flush flag to false. */
static void AppOMXContext_SetUnflushed(AppOMXContext* self) {
    self -> flushed = 0 ;
}


                                                             /** CONSTRUCTOR **/
/** @brief  Initialize an AppOMXContext. */
static void _AppOMXContext_Init(AppOMXContext* self) {
    // Configuration
    self -> configureCamera = AppOMXContext_ConfigureCamera ;
    self -> configureEncoder = AppOMXContext_ConfigureEncoder ;

    // Getters
    self -> getCamera = AppOMXContext_GetCameraHandleType ;
    self -> getEncoder = AppOMXContext_GetEncoderHandleType ;
    self -> getNullSink = AppOMXContext_GetNullSinkHandleType ;
    self -> getHandlerLock = AppOMXContext_GetHandlerLock ;
    self -> isFlushed = AppOMXContext_IsFlushed ;

    // Setters
    self -> setCameraReady = AppOMXContext_SetCameraReady ;
    self -> setEncoderOutputBufferAvailable = AppOMXContext_SetEncoderOutputBufferAvailable ;
    self -> flush = AppOMXContext_SetFlushed ;
    self -> unflush = AppOMXContext_SetUnflushed ;


    // Initialize data
    self -> camera = CameraBufferHandler_Construct() ;
    self -> encoder = EncoderBufferHandler_Construct() ;
    self -> nullSink = NullSinkHandler_Construct() ;
}


/** @brief  Create a new AppOMXContext. */
AppOMXContext AppOMXContext_Construct() {
    AppOMXContext ctx ;
    _AppOMXContext_Init(&ctx) ;
    return ctx ;
}


/** @brief  memset() on an AppOMXContext with the right initialization*/
void* AppOMXContext_Memset(AppOMXContext* self, int c, size_t n) {
    void* result = memset(self, c, n) ;
    _AppOMXContext_Init(self) ;
    return result ;
}
