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
static void _CameraHandler_SetCallbackOnCameraReady(BasicOMXHandler* self) {
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_REQUESTCALLBACKTYPE cbtype ;
    OMX_INIT_STRUCTURE(cbtype) ;
    cbtype.nPortIndex = OMX_ALL ;
    cbtype.nIndex = OMX_IndexParamCameraDeviceNumber ;
    cbtype.bEnable = OMX_TRUE ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigRequestCallback, &cbtype),
              "Failed to request camera device number parameter change callback for camera") ;
}


/**
 * @brief   Set camera device number. This triggers the callback configured just
 *          above.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetCameraDeviceNumber(BasicOMXHandler* self) {
    OMX_HANDLETYPE camera = self -> type ;

    OMX_PARAM_U32TYPE device ;
    OMX_INIT_STRUCTURE(device) ;
    device.nPortIndex = OMX_ALL ;
    device.nU32 = CAM_DEVICE_NUMBER ;

    testError(OMX_SetParameter(camera, OMX_IndexParamCameraDeviceNumber, &device),
              "Failed to set camera parameter device number") ;
}


/**
 * @brief   Configure video format emitted by camera preview output port.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_ConfigureCameraPreviewFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    (self -> portDef).nPortIndex = PORT_CAMERA_PREVIEW ;
    testError(OMX_GetParameter(camera, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to get port definition for camera preview output port 70") ;

    (self -> portDef).format.video.nFrameWidth = VIDEO_WIDTH ;
    (self -> portDef).format.video.nFrameHeight = VIDEO_HEIGHT ;
    (self -> portDef).format.video.xFramerate = VIDEO_FRAMERATE << 16 ;
    {
        // Stolen from gstomxvideodec.c of gst-omx
        OMX_U32 width = (self -> portDef).format.video.nFrameWidth ;
        OMX_U32 bufferAlignment = (self -> portDef).nBufferAlignment - 1 ;
        (self -> portDef).format.video.nStride = (width + bufferAlignment) & (~(bufferAlignment)) ;
    }

    testError(OMX_SetParameter(camera, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to set port definition for camera preview output port 70") ;
}


/**
 * @brief   Configure video format emitted by camera video output port
 *          Use configuration from camera preview output as basis for camera
 *          video output configuration.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_ConfigureCameraVideoOutputFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    (self -> portDef).nPortIndex = PORT_CAMERA_PREVIEW ;
    testError(OMX_GetParameter(camera, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to get port definition for camera preview output port 70") ;

    (self -> portDef).nPortIndex = PORT_CAMERA_VIDEO ;
    testError(OMX_SetParameter(camera, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to set port definition for camera video output port 71") ;
}


/**
 * @brief   Configure frame rate.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetFramerate(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_FRAMERATETYPE framerate ;
    OMX_INIT_STRUCTURE(framerate) ;
    framerate.nPortIndex = PORT_CAMERA_PREVIEW ;
    framerate.xEncodeFramerate = (self -> portDef).format.video.xFramerate ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigVideoFramerate, &framerate),
              "Failed to set framerate configuration for camera preview output port 70") ;

    framerate.nPortIndex = PORT_CAMERA_VIDEO ;
    testError(OMX_SetConfig(camera, OMX_IndexConfigVideoFramerate, &framerate),
              "Failed to set framerate configuration for camera video output port 71") ;
}


/**
 * @brief   Configure sharpness.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetSharpness(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_SHARPNESSTYPE sharpness ;
    OMX_INIT_STRUCTURE(sharpness) ;
    sharpness.nPortIndex = OMX_ALL ;
    sharpness.nSharpness = CAM_SHARPNESS ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonSharpness, &sharpness),
              "Failed to set camera sharpness configuration") ;
}


/**
 * @brief   Configure contrast.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetContrast(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_CONTRASTTYPE contrast ;
    OMX_INIT_STRUCTURE(contrast) ;
    contrast.nPortIndex = OMX_ALL ;
    contrast.nContrast = CAM_CONTRAST ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonContrast, &contrast),
              "Failed to set camera contrast configuration") ;
}


/**
 * @brief   Configure saturation.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetSaturation(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_SATURATIONTYPE saturation ;
    OMX_INIT_STRUCTURE(saturation) ;
    saturation.nPortIndex = OMX_ALL ;
    saturation.nSaturation = CAM_SATURATION ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonSaturation, &saturation),
              "Failed to set camera saturation configuration") ;
}


/**
 * @brief   Configure brightness.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetBrightness(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_BRIGHTNESSTYPE brightness ;
    OMX_INIT_STRUCTURE(brightness) ;
    brightness.nPortIndex = OMX_ALL ;
    brightness.nBrightness = CAM_BRIGHTNESS ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonBrightness, &brightness),
              "Failed to set camera brightness configuration") ;
}


/**
 * @brief   Configure exposure.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetExposure(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_EXPOSUREVALUETYPE exposure_value ;
    OMX_INIT_STRUCTURE(exposure_value) ;
    exposure_value.nPortIndex = OMX_ALL ;
    exposure_value.xEVCompensation = CAM_EXPOSURE_VALUE_COMPENSTAION ;
    exposure_value.bAutoSensitivity = CAM_EXPOSURE_AUTO_SENSITIVITY ;
    exposure_value.nSensitivity = CAM_EXPOSURE_ISO_SENSITIVITY ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonExposureValue, &exposure_value),
              "Failed to set camera exposure value configuration") ;
}


/**
 * @brief   Configure image stabilization.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetFrameStabilization(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_FRAMESTABTYPE frame_stabilisation_control ;
    OMX_INIT_STRUCTURE(frame_stabilisation_control) ;
    frame_stabilisation_control.nPortIndex = OMX_ALL ;
    frame_stabilisation_control.bStab = CAM_FRAME_STABILISATION ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonFrameStabilisation, &frame_stabilisation_control),
              "Failed to set camera frame frame stabilisation control configuration") ;
}


/**
 * @brief   Configure white balance.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetWhiteBalance(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_WHITEBALCONTROLTYPE white_balance_control ;
    OMX_INIT_STRUCTURE(white_balance_control) ;
    white_balance_control.nPortIndex = OMX_ALL ;
    white_balance_control.eWhiteBalControl = CAM_WHITE_BALANCE_CONTROL ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonWhiteBalance, &white_balance_control),
              "Failed to set camera frame white balance control configuration") ;
}


/**
 * @brief   Configure image filter.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetImageFilter(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_CONFIG_IMAGEFILTERTYPE image_filter ;
    OMX_INIT_STRUCTURE(image_filter) ;
    image_filter.nPortIndex = OMX_ALL ;
    image_filter.eImageFilter = CAM_IMAGE_FILTER ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonImageFilter, &image_filter),
              "Failed to set camera image filter configuration") ;
}


/**
 * @brief   Configure image mirror.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_SetMirror(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE camera = self -> type ;

    OMX_MIRRORTYPE eMirror = OMX_MirrorNone ;
    if (CAM_FLIP_HORIZONTAL && !CAM_FLIP_VERTICAL)
        eMirror = OMX_MirrorHorizontal ;
    else if (!CAM_FLIP_HORIZONTAL && CAM_FLIP_VERTICAL)
        eMirror = OMX_MirrorVertical ;
    else if (CAM_FLIP_HORIZONTAL && CAM_FLIP_VERTICAL)
        eMirror = OMX_MirrorBoth ;

    OMX_CONFIG_MIRRORTYPE mirror ;
    OMX_INIT_STRUCTURE(mirror) ;
    mirror.nPortIndex = PORT_CAMERA_VIDEO ;
    mirror.eMirror = eMirror ;

    testError(OMX_SetConfig(camera, OMX_IndexConfigCommonMirror, &mirror),
              "Failed to set mirror configuration for camera video output port 71") ;
}


/**
 * @brief   Ensure camera is ready.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _CameraHandler_WaitCameraIsReady(BasicOMXHandler* self) {
    while (!(self -> readiness))
        usleep(10000) ;
}


/**  @brief   Configure the camera output formats (preview and video). */
static void CameraHandler_Configure(BasicOMXHandler* self) {
    OMX_INIT_STRUCTURE(self -> portDef) ;

    _CameraHandler_SetCallbackOnCameraReady(self) ;
    _CameraHandler_SetCameraDeviceNumber(self) ;
    _CameraHandler_ConfigureCameraPreviewFormat(self) ;
    _CameraHandler_ConfigureCameraVideoOutputFormat(self) ;

    // Set camera capture parameters
    _CameraHandler_SetFramerate(self) ;
    _CameraHandler_SetSharpness(self) ;
    _CameraHandler_SetContrast(self) ;
    _CameraHandler_SetSaturation(self) ;
    _CameraHandler_SetBrightness(self) ;
    _CameraHandler_SetExposure(self) ;
    _CameraHandler_SetFrameStabilization(self) ;
    _CameraHandler_SetWhiteBalance(self) ;
    _CameraHandler_SetImageFilter(self) ;
    _CameraHandler_SetMirror(self) ;

    _CameraHandler_WaitCameraIsReady(self) ;
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
