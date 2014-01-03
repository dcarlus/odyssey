/**
 * @file     EncoderBufferHandler.c
 * @author   Denis CARLUS
 */

#include "EncoderBufferHandler.h"
#include "EncoderHandler.h"
#include <stdlib.h>

                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BufferOMXHandler. */
void EncoderBufferHandler_Init(BufferOMXHandler* self) {
    self -> basic = EncoderHandler_New() ;
}


/** @brief  Create a new EncoderBufferHandler. */
BufferOMXHandler EncoderBufferHandler_Construct() {
    BufferOMXHandler handler = BufferOMXHandler_Construct() ;
    EncoderBufferHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Delete the EncoderBufferHandler. */
void EncoderBufferHandler_Destruct(BufferOMXHandler* self) {
    if (self != 0) {
        BasicOMXHandler_Destruct(self -> basic) ;
        free(self) ;
        self = 0 ;
    }
}
