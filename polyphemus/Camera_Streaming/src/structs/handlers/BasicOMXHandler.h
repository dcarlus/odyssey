/**
 * @file    BasicOMXHandler.h
 * @brief   Struture to handle BufferOMXHandler in an object-oriented style.
 *          It is used by the AppOMXContext.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 * @see     AppOMXContext.h
 */

#ifndef __POLYPHEMUS__IMAGE_BASICOMXHANDLER__
#define __POLYPHEMUS__IMAGE_BASICOMXHANDLER__

#include <IL/OMX_Core.h>

/**
 * @brief	A basic OMX handler structure.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 */
typedef struct BasicOMXHandler {
    /** DATA **/
	OMX_HANDLETYPE      type ;
	char                readiness ;

    /** METHODS **/
    // Getters
    OMX_HANDLETYPE*     (*getType)  (struct BasicOMXHandler*) ;
    char                (*isReady)  (struct BasicOMXHandler*) ;

    // Setters
    void                (*setReady) (struct BasicOMXHandler*) ;
} BasicOMXHandler ;


/** @brief  Create a new BasicOMXHandler. */
BasicOMXHandler BasicOMXHandler_Construct() ;

#endif
