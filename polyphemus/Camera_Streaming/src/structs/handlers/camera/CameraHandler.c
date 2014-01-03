/**
 * @file     CameraHandler.c
 * @author   Denis CARLUS
 */

#include "CameraHandler.h"
#include "../../../OMXUtils.h"
#include "../../../CameraConfigurationUtils.h"
#include <stdlib.h>

                                                           /** CONFIGURATION **/
/**
 * @brief   Request a callback to be made when OMX_IndexParamCameraDeviceNumber
 *          is changed signaling that the camera device is ready for use.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _BasicOMXHandler_SetCallbackOnCameraReady(BasicOMXHandler* self) {
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_REQUESTCALLBACKTYPE cbtype ;
    OMX_INIT_STRUCTURE(cbtype) ;
    cbtype.nPortIndex = OMX_ALL ;
    cbtype.nIndex = OMX_IndexParamCameraDeviceNumber ;
    cbtype.bEnable = OMX_TRUE ;

    OMX_ERRORTYPE error ;
    error = OMX_SetConfig(camera, OMX_IndexConfigRequestCallback, &cbtype) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to request camera device number parameter change callback for camera") ;
}


/**
 * @brief   Set camera device number. This triggers the callback configured just
 *          above.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _BasicOMXHandler_SetCameraDeviceNumber(BasicOMXHandler* self) {
    OMX_HANDLETYPE camera = self -> type ;

    OMX_PARAM_U32TYPE device ;
    OMX_INIT_STRUCTURE(device) ;
    device.nPortIndex = OMX_ALL ;
    device.nU32 = CAM_DEVICE_NUMBER ;

    OMX_ERRORTYPE error ;
    error = OMX_SetParameter(camera, OMX_IndexParamCameraDeviceNumber, &device) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to set camera parameter device number") ;
}


/**
 * @brief   Configure video format emitted by camera preview output port.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _BasicOMXHandler_ConfigureCameraPreviewFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_PARAM_PORTDEFINITIONTYPE camera_portdef ;
    OMX_INIT_STRUCTURE(camera_portdef) ;
    camera_portdef.nPortIndex = 70 ;

    error = OMX_GetParameter(camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
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

    error = OMX_SetParameter(camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
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
static void _BasicOMXHandler_ConfigureCameraVideoOutputFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_PARAM_PORTDEFINITIONTYPE camera_portdef ;
    OMX_INIT_STRUCTURE(camera_portdef) ;
    camera_portdef.nPortIndex = 70 ;
    error = OMX_GetParameter(camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to get port definition for camera preview output port 70") ;

    camera_portdef.nPortIndex = 71 ;
    error = OMX_SetParameter(camera, OMX_IndexParamPortDefinition, &camera_portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to set port definition for camera video output port 71") ;
}


/**  @brief   Configure the camera output formats (preview and video). */
static void CameraHandler_Configure(BasicOMXHandler* self) {
    _BasicOMXHandler_SetCallbackOnCameraReady(self) ;
    _BasicOMXHandler_SetCameraDeviceNumber(self) ;
    _BasicOMXHandler_ConfigureCameraPreviewFormat(self) ;
    _BasicOMXHandler_ConfigureCameraVideoOutputFormat(self) ;
}



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a CameraHandler. */
static void _CameraHandler_Init(BasicOMXHandler* self) {
    self -> configure = CameraHandler_Configure ;
}


/** @brief  Create a new CameraHandler. */
BasicOMXHandler CameraHandler_Construct() {
    BasicOMXHandler handler = BasicOMXHandler_Construct() ;
    _CameraHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Create a new CameraHandler. */
BasicOMXHandler* CameraHandler_New() {
    BasicOMXHandler* handler = malloc(sizeof(BasicOMXHandler)) ;
    _CameraHandler_Init(handler) ;
    return handler ;
}
