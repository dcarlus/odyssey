/**
 * @file     BufferOMXHandler.c
 * @author   Denis CARLUS
 */

#include "BufferOMXHandler.h"

                                                                 /** GETTERS **/
/** @brief  Get the BasicOMXHandler structure of this OMX handler. */
static BasicOMXHandler* BufferOMXHandler_GetBasicOMXHandler(BufferOMXHandler* self) {
    return &(self -> basic) ;
}

/** @brief  Get the BUFFERHEADERTYPE structure of this OMX handler. */
static OMX_BUFFERHEADERTYPE* BufferOMXHandler_GetBufferHeader(BufferOMXHandler* self) {
    return (self -> bufferHeader) ;
}


                                                                 /** SETTERS **/



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BufferOMXHandler. */
static void _BufferOMXHandler_Init(BufferOMXHandler* self) {
    // Getters
    self -> getBasicHandler = BufferOMXHandler_GetBasicOMXHandler ;
    self -> getBufferHeader = BufferOMXHandler_GetBufferHeader ;

    // Setters
}



BufferOMXHandler BufferOMXHandler_Construct() {
    BufferOMXHandler handler ;
    _BufferOMXHandler_Init(&handler) ;
    return handler ;
}
