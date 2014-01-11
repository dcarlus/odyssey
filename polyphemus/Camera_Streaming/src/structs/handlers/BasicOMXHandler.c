/**
 * @file     BasicOMXHandler.c
 * @author   Denis CARLUS
 */

#include "BasicOMXHandler.h"
#include <stdlib.h>

                                                                 /** GETTERS **/
/** @brief  Get the OMX_HANDLETYPE structure of this OMX handler. */
static OMX_HANDLETYPE* BasicOMXHandler_GetHandleType(BasicOMXHandler* self) {
    return &(self -> type) ;
}

/** @brief  Get the port definition of this OMX handler. */
static OMXPortDefType* BasicOMXHandler_GetPortDef(BasicOMXHandler* self) {
    return &(self -> portDef) ;
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

/** @brief  Set the readiness flag to true. */
static void BasicOMXHandler_SetAsNotReady(BasicOMXHandler* self) {
    self -> readiness = 0 ;
}


                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BasicOMXHandler. */
static void _BasicOMXHandler_Init(BasicOMXHandler* self) {
    // Getters
    self -> getType = BasicOMXHandler_GetHandleType ;
    self -> getPortDef = BasicOMXHandler_GetPortDef ;
    self -> isReady = BasicOMXHandler_GetReadiness ;

    // Setters
    self -> setReady = BasicOMXHandler_SetAsReady ;
    self -> setUnready = BasicOMXHandler_SetAsNotReady ;


    // Data
    self -> readiness = 0 ;
}


/** @brief  Create a new BasicOMXHandler. */
BasicOMXHandler BasicOMXHandler_Construct() {
    BasicOMXHandler handler ;
    _BasicOMXHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Delete the BasicOMXHandler. */
void BasicOMXHandler_Destruct(BasicOMXHandler* self) {
    if (self != 0) {
        free(self) ;
        self = 0 ;
    }
}
