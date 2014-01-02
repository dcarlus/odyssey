/**
 * @file     BasicOMXHandler.c
 * @author   Denis CARLUS
 */

#include "BasicOMXHandler.h"

                                                                 /** GETTERS **/
/** @brief  Get the OMX_HANDLETYPE structure of this OMX handler. */
static OMX_HANDLETYPE* BasicOMXHandler_GetHandleType(BasicOMXHandler* self) {
    return &(self -> type) ;
}

/** @brief  Get the readiness flag of this OMX handler. */
static char BasicOMXHandler_GetReadiness(BasicOMXHandler* self) {
    return (self -> readiness) ;
}

                                                                 /** SETTERS **/
/** @brief  Set the readiness flag to true. */
static void BasicOMXHandler_SetAsReady(BasicOMXHandler* self) {
    self -> readiness = 1 ;
}


                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BasicOMXHandler. */
static void _BasicOMXHandler_Init(BasicOMXHandler* self) {
    // Getters
    self -> getType = BasicOMXHandler_GetHandleType ;
    self -> isReady = BasicOMXHandler_GetReadiness ;

    // Setters
    self -> setReady = BasicOMXHandler_SetAsReady ;
}



BasicOMXHandler BasicOMXHandler_Construct() {
    BasicOMXHandler handler ;
    _BasicOMXHandler_Init(&handler) ;
    return handler ;
}
