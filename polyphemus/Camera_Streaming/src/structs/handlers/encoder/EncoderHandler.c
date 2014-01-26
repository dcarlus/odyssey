/**
 * @file     EncoderHandler.c
 * @author   Denis CARLUS
 */

#include "EncoderHandler.h"
#include "../../../OMXUtils.h"
#include "../../../CameraConfigurationUtils.h"
#include <stdlib.h>

                                                           /** CONFIGURATION **/
/**
 * @brief   Configure video format emitted by encoder output port.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _EncoderHandler_ConfigureOutputFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE encoder = self -> type ;

    (self -> portDef).nPortIndex = PORT_ENCODER_OUTPUT ;
    testError(OMX_GetParameter(encoder, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to get port definition for encoder output port 201") ;
}


/**
 * @brief   Copy some of the encoder output port configuration from camera
 *          output port.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _EncoderHandler_ConfigureOutputPort(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE encoder = self -> type ;

    (self -> portDef).format.video.nFrameWidth  = VIDEO_WIDTH ;
    (self -> portDef).format.video.nFrameHeight = VIDEO_HEIGHT ;
    (self -> portDef).format.video.xFramerate   = VIDEO_FRAMERATE << 16 ;
    {
        // Stolen from gstomxvideodec.c of gst-omx
        OMX_U32 width = (self -> portDef).format.video.nFrameWidth ;
        OMX_U32 bufferAlignment = (self -> portDef).nBufferAlignment - 1 ;
        (self -> portDef).format.video.nStride = (width + bufferAlignment) & (~(bufferAlignment)) ;
    }

    // Which one is effective, this or the configuration just below?
    (self -> portDef).format.video.nBitrate     = VIDEO_BITRATE ;
    testError(OMX_SetParameter(encoder, OMX_IndexParamPortDefinition, &(self -> portDef)),
              "Failed to set port definition for encoder output port 201") ;
}


/**
 * @brief   Configure bitrate.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _EncoderHandler_ConfigureBitrate(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE encoder = self -> type ;

    OMX_VIDEO_PARAM_BITRATETYPE bitrate ;
    OMX_INIT_STRUCTURE(bitrate) ;
    bitrate.eControlRate = OMX_Video_ControlRateVariable ;
    bitrate.nTargetBitrate = (self -> portDef).format.video.nBitrate ;
    bitrate.nPortIndex = PORT_ENCODER_OUTPUT ;

    testError(OMX_SetParameter(encoder, OMX_IndexParamVideoBitrate, &bitrate),
              "Failed to set bitrate for encoder output port 201") ;
}


/**
 * @brief   Configure format.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void _EncoderHandler_ConfigureFormat(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE encoder = self -> type ;

    OMX_VIDEO_PARAM_PORTFORMATTYPE format ;
    OMX_INIT_STRUCTURE(format) ;
    format.nPortIndex = PORT_ENCODER_OUTPUT ;
    format.eCompressionFormat = OMX_VIDEO_CodingAVC ;

    testError(OMX_SetParameter(encoder, OMX_IndexParamVideoPortFormat, &format),
              "Failed to set video format for encoder output port 201") ;
}


/**
 * @brief   Enable SPS/PPS before each keyframe.
 */
static void _EncoderHandler_ConfigureKeyframes(BasicOMXHandler* self) {
    OMX_ERRORTYPE error ;
    OMX_HANDLETYPE encoder = self -> type ;

    {
        OMX_VIDEO_CONFIG_AVCINTRAPERIOD keyframesConfig ;
        OMX_INIT_STRUCTURE(keyframesConfig) ;
        keyframesConfig.nPortIndex = PORT_ENCODER_OUTPUT ;
        keyframesConfig.nIDRPeriod = VIDEO_KEYFRAME_FREQUENCY ;
        testError(OMX_SetParameter(encoder, OMX_IndexConfigVideoAVCIntraPeriod, &keyframesConfig),
                  "Failed to set video format for encoder output port 201") ;
    }

    {
        OMX_CONFIG_PORTBOOLEANTYPE enableKeyframes ;
        OMX_INIT_STRUCTURE(enableKeyframes) ;
        enableKeyframes.nPortIndex = PORT_ENCODER_OUTPUT ;
        enableKeyframes.bEnabled = OMX_TRUE ;

        testError(OMX_SetParameter(encoder, OMX_IndexParamBrcmVideoAVCInlineHeaderEnable, &enableKeyframes),
                  "Failed to set video format for encoder output port 201") ;
    }
}


/**  @brief   Configure the Encoder output formats (preview and video). */
static void EncoderHandler_Configure(BasicOMXHandler* self) {
    OMX_INIT_STRUCTURE(self -> portDef) ;

    _EncoderHandler_ConfigureOutputFormat(self) ;
    _EncoderHandler_ConfigureOutputPort(self) ;
    _EncoderHandler_ConfigureBitrate(self) ;
    _EncoderHandler_ConfigureFormat(self) ;
    _EncoderHandler_ConfigureKeyframes(self) ;
}



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a EncoderHandler. */
static void _EncoderHandler_Init(BasicOMXHandler* self) {
    self -> configure = EncoderHandler_Configure ;
}


/** @brief  Create a new EncoderHandler. */
BasicOMXHandler EncoderHandler_Construct() {
    BasicOMXHandler handler = BasicOMXHandler_Construct() ;
    _EncoderHandler_Init(&handler) ;
    return handler ;
}
