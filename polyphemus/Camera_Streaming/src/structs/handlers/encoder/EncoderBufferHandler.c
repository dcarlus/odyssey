/**
 * @file     EncoderBufferHandler.c
 * @author   Denis CARLUS
 */

#include "EncoderBufferHandler.h"
#include "EncoderHandler.h"
#include <stdlib.h>

                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BufferOMXHandler. */
static void _EncoderBufferHandler_Init(BufferOMXHandler* self) {
    self -> basic = EncoderHandler_Construct() ;
}


/** @brief  Create a new EncoderBufferHandler. */
BufferOMXHandler EncoderBufferHandler_Construct() {
    BufferOMXHandler handler = BufferOMXHandler_Construct() ;
    _EncoderBufferHandler_Init(&handler) ;
    return handler ;
}
