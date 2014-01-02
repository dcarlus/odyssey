/**
 * @file    CameraSetupUtils.h
 * @brief   Utility functions to manage the OpenMAX API from Broadcom to access
 *          Raspberry Pi camera module and capture pictures from it.
 * @author  Denis CARLUS, mainly inspired from Tuomas Jormola work.
 * @version 1.0     02/01/2014
 */

#ifndef  __POLYPHEMUS__IMAGE_OMX_CAMERA_SETUP__
#define  __POLYPHEMUS__IMAGE_OMX_CAMERA_SETUP__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <bcm_host.h>

#include <interface/vcos/vcos_semaphore.h>
#include <interface/vmcs_host/vchost.h>

#include <IL/OMX_Core.h>
#include <IL/OMX_Component.h>
#include <IL/OMX_Video.h>
#include <IL/OMX_Broadcom.h>

/**
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
#define OMX_INIT_STRUCTURE(a) \
    memset(&(a), 0, sizeof(a)); \
    (a).nSize = sizeof(a); \
    (a).nVersion.nVersion = OMX_VERSION; \
    (a).nVersion.s.nVersionMajor = OMX_VERSION_MAJOR; \
    (a).nVersion.s.nVersionMinor = OMX_VERSION_MINOR; \
    (a).nVersion.s.nRevision = OMX_VERSION_REVISION; \
    (a).nVersion.s.nStep = OMX_VERSION_STEP


/**
 * @brief   Exit program on OpenMAX error.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void omx_die(OMX_ERRORTYPE error, const char* message, ...) ;

/**
 * @brief   OMX calls this handler for all the events it emits.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
OMX_ERRORTYPE event_handler(
                            OMX_HANDLETYPE hComponent,
                            OMX_PTR pAppData,
                            OMX_EVENTTYPE eEvent,
                            OMX_U32 nData1,
                            OMX_U32 nData2,
                            OMX_PTR pEventData
                           ) ;

/**
 * @brief   Called by OMX when the encoder component has filled the output
 *          buffer with H.264 encoded video data.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
OMX_ERRORTYPE fill_output_buffer_done_handler(
                                              OMX_HANDLETYPE hComponent,
                                              OMX_PTR pAppData,
                                              OMX_BUFFERHEADERTYPE* pBuffer
                                             ) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void dump_event(
                OMX_HANDLETYPE hComponent,
                OMX_EVENTTYPE eEvent,
                OMX_U32 nData1,
                OMX_U32 nData2
               ) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void init_component_handle(
                           const char* name,
                           OMX_HANDLETYPE* hComponent,
                           OMX_PTR pAppData,
                           OMX_CALLBACKTYPE* callbacks
                          ) ;

/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void block_until_port_changed(
                              OMX_HANDLETYPE hComponent,
                              OMX_U32 nPortIndex,
                              OMX_BOOL bEnabled
                             ) ;

#endif
