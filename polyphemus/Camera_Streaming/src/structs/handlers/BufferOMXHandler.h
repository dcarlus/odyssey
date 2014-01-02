/**
 * @file    BufferOMXHandler.h
 * @brief   Struture to handle BufferOMXHandler in an object-oriented style.
 *          It is used by the AppOMXContext.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 * @see     AppOMXContext.h
 */

#ifndef __POLYPHEMUS__IMAGE_BUFFEROMXHANDLER__
#define __POLYPHEMUS__IMAGE_BUFFEROMXHANDLER__

#include "BasicOMXHandler.h"

/** @brief	An OMX handler with buffer (in or out) */
typedef struct BufferOMXHandler {
    /** DATA **/
	BasicOMXHandler         basic ;
	OMX_BUFFERHEADERTYPE*   bufferHeader ;

    /** METHODS **/
    // Getters
    BasicOMXHandler*        (*getBasicHandler)  (struct BufferOMXHandler*) ;
    OMX_BUFFERHEADERTYPE*   (*getBufferHeader)  (struct BufferOMXHandler*) ;

    // Setters
} BufferOMXHandler ;


/** @brief  Create a new BufferOMXHandler. */
BufferOMXHandler BufferOMXHandler_Construct() ;

#endif
