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

#include "OMXUtils.h"
#include "CameraSetupUtils.h"
#include "CameraConfigurationUtils.h"
#include "PortsConfigurationUtils.h"
#include "structs/AppOMXContext.h"

/**
 * @brief   Initialization of OpenMAX and structures.
 * @param   ctx     Application context to initialize.
 */
static void initAppOMX(AppOMXContext* ctx) {
    bcm_host_init() ;

    log_printer("Initialization...") ;

    {
        OMX_ERRORTYPE error = OMX_Init() ;
        if (error != OMX_ErrorNone) {
	        omx_die(error, "OMX initialization failed...") ;
        	return ;
        }
    }


    // Initialize the application context for video capture
    AppOMXContext_Memset(ctx, 0, sizeof(*ctx)) ;
    if (vcos_semaphore_create(ctx -> getHandlerLock(ctx), "handler_lock", 1) != VCOS_SUCCESS)
        die("Failed to create handler lock semaphore...\n") ;

    // Initialize component handles
    OMX_CALLBACKTYPE callbacks ;
    AppOMXContext_Memset(ctx, 0, sizeof(callbacks)) ;
    callbacks.EventHandler = event_handler ;
    callbacks.FillBufferDone = fill_output_buffer_done_handler ;

    init_component_handle("camera", ctx -> getCamera(ctx) , ctx, &callbacks) ;
    init_component_handle("video_encode", ctx -> getEncoder(ctx) , ctx, &callbacks) ;
    init_component_handle("null_sink", ctx -> getNullSink(ctx) , ctx, &callbacks) ;
}


/**
 * @brief   Configuration of the camera parameters.
 * @param   ctx     Application context to configure.
 */
static void configureCamera(AppOMXContext* ctx) {
    log_printer("Camera configuration...") ;

    {
        // Open camera ports (default input, preview and video outputs)
        const unsigned char PORTS_COUNT = 3 ;
        enum OMX_PORT_NUMBER ports[] = {PORT_CAMERA_INPUT, PORT_CAMERA_PREVIEW, PORT_CAMERA_VIDEO} ;
        const char* portsNames[] = {"camera input", "camera preview", "camera video"} ;
        open_ports(ports, portsNames, PORTS_COUNT, ctx -> getCamera(ctx)) ;
    }

    ctx -> configureCamera(ctx) ;
}


/**
 * @brief   Configuration of the encoder parameters.
 * @param   ctx     Application context to configure.
 */
static void configureEncoder(AppOMXContext* ctx) {
    log_printer("Encoder configuration...") ;

    {
        // Open camera ports (default input, preview and video outputs)
        const unsigned char PORTS_COUNT = 2 ;
        enum OMX_PORT_NUMBER ports[] = {PORT_ENCODER_INPUT, PORT_ENCODER_OUTPUT} ;
        const char* portsNames[] = {"encoder input", "encoder output"} ;
        open_ports(ports, portsNames, PORTS_COUNT, ctx -> getEncoder(ctx)) ;
    }

    ctx -> configureEncoder(ctx) ;
}


/**
 * @brief   Configuration of the null sink parameters.
 * @param   ctx     Application context to configure.
 */
static void configureNullSink(AppOMXContext* ctx) {
    log_printer("Null Sink configuration...") ;

    {
        // Open camera ports (default input, preview and video outputs)
        const unsigned char PORTS_COUNT = 1 ;
        enum OMX_PORT_NUMBER ports[] = {PORT_NULLSINK_INPUT} ;
        const char* portsNames[] = {"null sink input"} ;
        open_ports(ports, portsNames, PORTS_COUNT, ctx -> getNullSink(ctx)) ;
    }
    // Null sink input port definition is done automatically upon tunneling
}


int main(int argc, char** argv) {
    AppOMXContext ctx = AppOMXContext_Construct() ;
    initAppOMX(&ctx) ;
    configureCamera(&ctx) ;
    configureEncoder(&ctx) ;
    configureNullSink(&ctx) ;

    // PortsConfigurationUtils
    tunneling(&ctx) ;
    enablePorts(&ctx) ;

    return 0 ;
}
