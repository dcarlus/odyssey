/**
 * @file     CameraBufferHandler.c
 * @author   Denis CARLUS
 */

#include "CameraBufferHandler.h"
#include "CameraHandler.h"
#include <stdlib.h>

                                                             /** CONSTRUCTOR **/
/** @brief  Initialize a BufferOMXHandler. */
void CameraBufferHandler_Init(BufferOMXHandler* self) {
    self -> basic = CameraHandler_New() ;
}


/** @brief  Create a new CameraBufferHandler. */
BufferOMXHandler CameraBufferHandler_Construct() {
    BufferOMXHandler handler = BufferOMXHandler_Construct() ;
    CameraBufferHandler_Init(&handler) ;
    return handler ;
}


/** @brief  Delete the CameraBufferHandler. */
void CameraBufferHandler_Destruct(BufferOMXHandler* self) {
    if (self != 0) {
        BasicOMXHandler_Destruct(self -> basic) ;
        free(self) ;
        self = 0 ;
    }
}
