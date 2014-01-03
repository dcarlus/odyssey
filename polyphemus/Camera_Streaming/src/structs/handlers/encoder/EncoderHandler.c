/**
 * @file     EncoderHandler.c
 * @author   Denis CARLUS
 */

#include "EncoderHandler.h"
#include "../../../OMXUtils.h"
#include <stdlib.h>

                                                           /** CONFIGURATION **/
/**  @brief   Configure the Encoder output formats (preview and video). */
static void EncoderHandler_Configure(BasicOMXHandler* self) {
    // @TODO
}



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a EncoderHandler. */
static void _EncoderHandler_Init(BasicOMXHandler* self) {
    self -> configure = EncoderHandler_Configure ;
}


/** @brief  Create a new EncoderHandler. */
BasicOMXHandler EncoderHandler_Construct() {
    BasicOMXHandler handler = BasicOMXHandler_Construct() ;
    _EncoderHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Create a new EncoderHandler. */
BasicOMXHandler* EncoderHandler_New() {
    BasicOMXHandler* handler = malloc(sizeof(BasicOMXHandler)) ;
    _EncoderHandler_Init(handler) ;
    return handler ;
}
