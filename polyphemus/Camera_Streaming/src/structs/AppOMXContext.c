/**
 * @file     AppOMXContext.c
 * @author   Denis CARLUS
 */

#include "AppOMXContext.h"
#include "../OMXUtils.h"
#include "../CameraConfigurationUtils.h"



                                                           /** CONFIGURATION **/
/**
 * @brief   Request a callback to be made when OMX_IndexParamCameraDeviceNumber
 *          is changed signaling that the camera device is ready for use.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _AppOMXContext_SetCallbackOnCameraReady(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;

    OMX_CONFIG_REQUESTCALLBACKTYPE cbtype ;
    OMX_INIT_STRUCTURE(cbtype) ;
    cbtype.nPortIndex = OMX_ALL ;
    cbtype.nIndex = OMX_IndexParamCameraDeviceNumber ;
    cbtype.bEnable = OMX_TRUE ;

    OMX_ERRORTYPE error ;
    error = OMX_SetConfig(*camera, OMX_IndexConfigRequestCallback, &cbtype) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to request camera device number parameter change callback for camera") ;
}


/**
 * @brief   Set device number, this triggers the callback configured just above.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _AppOMXContext_SetDeviceNumber(OMX_HANDLETYPE* hComponent) {
    OMX_PARAM_U32TYPE device ;
    OMX_INIT_STRUCTURE(device) ;
    device.nPortIndex = OMX_ALL ;
    device.nU32 = CAM_DEVICE_NUMBER ;

    OMX_ERRORTYPE error ;
    error = OMX_SetParameter(*hComponent, OMX_IndexParamCameraDeviceNumber, &device) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to set camera parameter device number") ;
}


/**
 * @brief   Set camera device number.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _AppOMXContext_SetCameraDeviceNumber(AppOMXContext* self) {
    _AppOMXContext_SetDeviceNumber(self -> getCamera(self)) ;
}


/**
 * @brief   Configure video format emitted by camera preview output port.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _AppOMXContext_ConfigureCameraPreviewFormat(AppOMXContext* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;

    OMX_PARAM_PORTDEFINITIONTYPE camera_portdef ;
    OMX_INIT_STRUCTURE(camera_portdef) ;
    camera_portdef.nPortIndex = 70 ;

    error = OMX_GetParameter(*camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to get port definition for camera preview output port 70") ;

    camera_portdef.format.video.nFrameWidth = VIDEO_WIDTH ;
    camera_portdef.format.video.nFrameHeight = VIDEO_HEIGHT ;
    camera_portdef.format.video.xFramerate = VIDEO_FRAMERATE << 16 ;
    {
        // Stolen from gstomxvideodec.c of gst-omx
        OMX_U32 width = camera_portdef.format.video.nFrameWidth ;
        OMX_U32 bufferAlignment = camera_portdef.nBufferAlignment - 1 ;
        camera_portdef.format.video.nStride = (width + bufferAlignment) & (~(bufferAlignment)) ;
    }
    camera_portdef.format.video.eColorFormat = OMX_COLOR_FormatYUV420PackedPlanar ;

    error = OMX_SetParameter(*camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to set port definition for camera preview output port 70") ;
}


/**
 * @brief   Configure video format emitted by camera video output port
 *          Use configuration from camera preview output as basis for camera
 *          video output configuration.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _AppOMXContext_ConfigureCameraVideoOutputFormat(AppOMXContext* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;

    OMX_PARAM_PORTDEFINITIONTYPE camera_portdef ;
    OMX_INIT_STRUCTURE(camera_portdef) ;
    camera_portdef.nPortIndex = 70 ;
    error = OMX_GetParameter(*camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to get port definition for camera preview output port 70") ;

    camera_portdef.nPortIndex = 71 ;
    error = OMX_SetParameter(*camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to set port definition for camera video output port 71") ;
}


/**  @brief   Configure the camera output formats (preview and video). */
static void AppOMXContext_ConfigureCamera(AppOMXContext* self) {
    _AppOMXContext_SetCallbackOnCameraReady(self) ;
    _AppOMXContext_SetCameraDeviceNumber(self) ;
    _AppOMXContext_ConfigureCameraPreviewFormat(self) ;
    _AppOMXContext_ConfigureCameraVideoOutputFormat(self) ;
}


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
    return &((self -> nullSink).type) ;
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
    // Configuration
    self -> configureCamera = AppOMXContext_ConfigureCamera ;

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
