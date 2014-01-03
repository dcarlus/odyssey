/**
 * @file    EncoderHandler.h
 * @brief   Struture to handle encoder, inherited from BasicOMXHandler.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 * @see     BasicOMXHandler.h
 */

#ifndef __POLYPHEMUS__IMAGE_ENCODERHANDLER__
#define __POLYPHEMUS__IMAGE_ENCODERHANDLER__

#include "../BasicOMXHandler.h"

/** @brief  Create a new EncoderHandler. */
BasicOMXHandler EncoderHandler_Construct() ;

/** @brief  Create a new EncoderHandler. */
BasicOMXHandler* EncoderHandler_New() ;

#endif
