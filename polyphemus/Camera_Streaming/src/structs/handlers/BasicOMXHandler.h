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
#include <IL/OMX_Broadcom.h>

typedef OMX_PARAM_PORTDEFINITIONTYPE OMXPortDefType ;

/**
 * @brief	A basic OMX handler structure.
 * @author  Denis CARLUS
 * @version 1.0     02/01/2014
 */
typedef struct BasicOMXHandler {
    /** DATA **/
	OMX_HANDLETYPE  type ;
	OMXPortDefType  portDef ;
	char            readiness ;

    /** METHODS **/
    void                (*configure)(struct BasicOMXHandler*) ;

    // Getters
    OMX_HANDLETYPE*     (*getType)      (struct BasicOMXHandler*) ;
    OMXPortDefType*     (*getPortDef)   (struct BasicOMXHandler*) ;
    char                (*isReady)      (struct BasicOMXHandler*) ;

    // Setters
    void                (*setReady)     (struct BasicOMXHandler*) ;
} BasicOMXHandler ;


/** @brief  Create a new BasicOMXHandler. */
BasicOMXHandler BasicOMXHandler_Construct() ;

/** @brief  Delete the BasicOMXHandler. */
void BasicOMXHandler_Destruct(BasicOMXHandler* self) ;

#endif
