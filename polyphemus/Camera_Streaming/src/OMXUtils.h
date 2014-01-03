/**
 * @file    OMXUtils.h
 * @brief   Utility functions to abstract some parts of the OpenMAX API.
 * @author  Denis CARLUS, mainly inspired from Tuomas Jormola work.
 * @version 1.0     03/01/2014
 */

#ifndef  __POLYPHEMUS__IMAGE_OMX_UTILS__
#define  __POLYPHEMUS__IMAGE_OMX_UTILS__

#include <stdio.h>

#include <interface/vcos/vcos_semaphore.h>
#include <interface/vmcs_host/vchost.h>

#include <IL/OMX_Core.h>


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
 * @brief  Print debug messages.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void log_printer(const char* message, ...) ;

/**
 * @brief   Exit program on OpenMAX error.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void omx_die(OMX_ERRORTYPE error, const char* message, ...) ;

/**
 * @brief   Make the application stop with an error message.
 * @author  Denis CARLUS
 */
void die(const char* message) ;

#endif
