/**
 * @file    CameraBufferHandler.h
 * @brief   Struture to handle camera buffer in an object-oriented style.
 *          It is used by the AppOMXContext.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 * @see     AppOMXContext.h
 * @see     BufferOMXHandler.h
 */

#ifndef __POLYPHEMUS__IMAGE_CAMERABUFFERHANDLER__
#define __POLYPHEMUS__IMAGE_CAMERABUFFERHANDLER__

#include "../BufferOMXHandler.h"

/** @brief  Initialize a BufferOMXHandler. */
void CameraBufferHandler_Init(BufferOMXHandler* self) ;

/** @brief  Create a new CameraBufferHandler. */
BufferOMXHandler CameraBufferHandler_Construct() ;

#endif
