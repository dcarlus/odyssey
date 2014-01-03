/**
 * @file    CameraConfigurationUtils.h
 * @brief   Utility functions to configure the Raspberry Pi camera module.
 * @author  Denis CARLUS, mainly inspired from Tuomas Jormola work.
 * @version 1.0     03/01/2014
 */

#ifndef  __POLYPHEMUS__IMAGE_OMX_CAMERA_CONFIG__
#define  __POLYPHEMUS__IMAGE_OMX_CAMERA_CONFIG__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <IL/OMX_Core.h>
#include <IL/OMX_Component.h>
#include <IL/OMX_Video.h>
#include <IL/OMX_Broadcom.h>


// Hard coded parameters
#define VIDEO_WIDTH                     640
#define VIDEO_HEIGHT                    480
#define VIDEO_FRAMERATE                 24
#define VIDEO_BITRATE                   10000000
#define CAM_DEVICE_NUMBER               0
#define CAM_SHARPNESS                   0                       // -100 .. 100
#define CAM_CONTRAST                    0                       // -100 .. 100
#define CAM_BRIGHTNESS                  50                      // 0 .. 100
#define CAM_SATURATION                  0                       // -100 .. 100
#define CAM_EXPOSURE_VALUE_COMPENSTAION 0
#define CAM_EXPOSURE_ISO_SENSITIVITY    100
#define CAM_EXPOSURE_AUTO_SENSITIVITY   OMX_FALSE
#define CAM_FRAME_STABILISATION         OMX_TRUE
#define CAM_WHITE_BALANCE_CONTROL       OMX_WhiteBalControlAuto // OMX_WHITEBALCONTROLTYPE
#define CAM_IMAGE_FILTER                OMX_ImageFilterNoise    // OMX_IMAGEFILTERTYPE
#define CAM_FLIP_HORIZONTAL             OMX_FALSE
#define CAM_FLIP_VERTICAL               OMX_FALSE


/** @brief  Open a list of ports. */
void open_ports(int ports[],
                const char* portsName[],
                unsigned char portsCount,
                OMX_HANDLETYPE* hComponent) ;


/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void dump_port(
               OMX_HANDLETYPE* hComponent,
               OMX_U32 nPortIndex,
               OMX_BOOL dumpformats
              ) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void dump_portdef(OMX_PARAM_PORTDEFINITIONTYPE* portdef) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
const char* dump_compression_format(OMX_VIDEO_CODINGTYPE c) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
const char* dump_color_format(OMX_COLOR_FORMATTYPE c) ;

#endif
