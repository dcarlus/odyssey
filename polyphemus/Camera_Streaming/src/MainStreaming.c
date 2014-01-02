/**
 * @file     MainStreaming.c
 * @author   Denis CARLUS
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "CameraSetupUtils.h"
#include "structs/AppOMXContext.h"

static void initAppOMX(AppOMXContext* ctx) {
    bcm_host_init() ;

    {
        OMX_ERRORTYPE error = OMX_Init() ;
        if (error != OMX_ErrorNone) {
	        omx_die(error, "OMX initialization failed...") ;
        	return ;
        }
    }


    // Initialize the application context for video capture
    AppOMXContext_Memset(ctx, 0, sizeof(*ctx)) ;
    if (vcos_semaphore_create(ctx -> getHandlerLock(ctx), "handler_lock", 1) != VCOS_SUCCESS) {
        fprintf(stderr, "Failed to create handler lock semaphore...\n") ;
        exit(EXIT_FAILURE) ;
    }

    // Initialize component handles
    OMX_CALLBACKTYPE callbacks ;
    AppOMXContext_Memset(ctx, 0, sizeof(callbacks)) ;
    callbacks.EventHandler = event_handler ;
    callbacks.FillBufferDone = fill_output_buffer_done_handler ;

    init_component_handle("camera", ctx -> getCamera(ctx) , ctx, &callbacks) ;
/*    init_component_handle("video_encode", ctx -> getEncoder(ctx) , ctx, &callbacks) ;*/
/*    init_component_handle("null_sink", ctx -> getNullSink(ctx) , ctx, &callbacks) ;*/
}


int main(int argc, char** argv) {
    AppOMXContext ctx = AppOMXContext_Construct() ;
    initAppOMX(&ctx) ;

    return 0 ;
}
