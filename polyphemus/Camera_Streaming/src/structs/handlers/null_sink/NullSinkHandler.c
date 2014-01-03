/**
 * @file     NullSinkHandler.c
 * @author   Denis CARLUS
 */

#include "NullSinkHandler.h"
#include "../../../OMXUtils.h"
#include <stdlib.h>

                                                           /** CONFIGURATION **/
/**  @brief   Configure the NullSink output formats (preview and video). */
static void NullSinkHandler_Configure(BasicOMXHandler* self) {
    // @TODO
}



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a NullSinkHandler. */
static void _NullSinkHandler_Init(BasicOMXHandler* self) {
    self -> configure = NullSinkHandler_Configure ;
}


/** @brief  Create a new NullSinkHandler. */
BasicOMXHandler NullSinkHandler_Construct() {
    BasicOMXHandler handler = BasicOMXHandler_Construct() ;
    _NullSinkHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Create a new NullSinkHandler. */
BasicOMXHandler* NullSinkHandler_New() {
    BasicOMXHandler* handler = malloc(sizeof(BasicOMXHandler)) ;
    _NullSinkHandler_Init(handler) ;
    return handler ;
}
