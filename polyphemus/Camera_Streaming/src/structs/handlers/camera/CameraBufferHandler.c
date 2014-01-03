/**
 * @file     CameraBufferHandler.c
 * @author   Denis CARLUS
 */

#include "CameraBufferHandler.h"
#include "CameraHandler.h"
#include <stdlib.h>

                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BufferOMXHandler. */
static void _CameraBufferHandler_Init(BufferOMXHandler* self) {
    self -> basic = CameraHandler_Construct() ;
}


/** @brief  Create a new CameraBufferHandler. */
BufferOMXHandler CameraBufferHandler_Construct() {
    BufferOMXHandler handler = BufferOMXHandler_Construct() ;
    _CameraBufferHandler_Init(&handler) ;
    return handler ;
}
