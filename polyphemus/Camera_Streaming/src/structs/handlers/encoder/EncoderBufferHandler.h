/**
 * @file    EncoderBufferHandler.h
 * @brief   Struture to handle encoder buffer in an object-oriented style.
 *          It is used by the AppOMXContext.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 * @see     AppOMXContext.h
 * @see     BufferOMXHandler.h
 */

#ifndef __POLYPHEMUS__IMAGE_ENCODERBUFFERHANDLER__
#define __POLYPHEMUS__IMAGE_ENCODERBUFFERHANDLER__

#include "../BufferOMXHandler.h"

/** @brief  Initialize a BufferOMXHandler. */
void EncoderBufferHandler_Init(BufferOMXHandler* self) ;

/** @brief  Create a new EncoderBufferHandler. */
BufferOMXHandler EncoderBufferHandler_Construct() ;

/** @brief  Delete the EncoderBufferHandler. */
void EncoderBufferHandler_Destruct(BufferOMXHandler* self) ;

#endif
