/**
 * @file     PortsConfigurationUtils.c
 * @author   Denis CARLUS
 */

#include "PortsConfigurationUtils.h"


void tunneling(AppOMXContext* ctx) {
    OMX_HANDLETYPE* camera = ctx -> getCamera(ctx) ;
    OMX_HANDLETYPE* encoder = ctx -> getEncoder(ctx) ;
    OMX_HANDLETYPE* nullSink = ctx -> getNullSink(ctx) ;

    // Tunnel camera preview output port and null sink input port
    log_printer("Setting up tunnel from camera preview output port 70 to null sink input port 240...") ;
    testError(OMX_SetupTunnel(*camera, PORT_CAMERA_PREVIEW, *nullSink, PORT_NULLSINK_INPUT),
              "Failed to setup tunnel between camera preview output port 70 and null sink input port 240") ;

    // Tunnel camera video output port and encoder input port
    log_printer("Setting up tunnel from camera video output port 71 to encoder input port 200...") ;
    testError(OMX_SetupTunnel(*camera, PORT_CAMERA_VIDEO, *encoder, PORT_ENCODER_INPUT),
              "Failed to setup tunnel between camera video output port 71 and encoder input port 200") ;


    // Switch components to idle state
    log_printer("Switching state of the camera component to idle...") ;                 // Camera
    testError(OMX_SendCommand(*camera, OMX_CommandStateSet, OMX_StateIdle, NULL),
              "Failed to switch state of the camera component to idle") ;
    block_until_state_changed(camera, OMX_StateIdle) ;


    log_printer("Switching state of the encoder component to idle...") ;                // Encoder
    testError(OMX_SendCommand(*encoder, OMX_CommandStateSet, OMX_StateIdle, NULL),
              "Failed to switch state of the encoder component to idle") ;
    block_until_state_changed(encoder, OMX_StateIdle) ;

    log_printer("Switching state of the null sink component to idle...") ;              // Null sink
    testError(OMX_SendCommand(*nullSink, OMX_CommandStateSet, OMX_StateIdle, NULL),
              "Failed to switch state of the null sink component to idle") ;
    block_until_state_changed(nullSink, OMX_StateIdle) ;
}


void enablePorts(AppOMXContext* ctx) {

}



void block_until_state_changed(
                               OMX_HANDLETYPE* hComponent,
                               OMX_STATETYPE wanted_eState
                              ) {
    OMX_STATETYPE eState ;
    int i = 0 ;

    while (i++ == 0 || eState != wanted_eState) {
        OMX_GetState(*hComponent, &eState) ;
        if (eState != wanted_eState)
            usleep(10000) ;
    }
}


void block_until_port_changed(
                              OMX_HANDLETYPE* hComponent,
                              OMX_U32 nPortIndex,
                              OMX_BOOL bEnabled
                             ) {
    OMX_ERRORTYPE error ;
    OMX_PARAM_PORTDEFINITIONTYPE portdef ;
    OMX_INIT_STRUCTURE(portdef) ;
    portdef.nPortIndex = nPortIndex ;
    OMX_U32 i = 0 ;

    while (i++ == 0 || portdef.bEnabled != bEnabled) {
        error = OMX_GetParameter(*hComponent, OMX_IndexParamPortDefinition, &portdef) ;
        if (error != OMX_ErrorNone)
            omx_die(error, "Failed to get port definition") ;

        if (portdef.bEnabled != bEnabled)
            usleep(10000) ;
    }
}


void block_until_flushed(AppOMXContext* ctx) {
    int quit ;

    while (!quit) {
        vcos_semaphore_wait(ctx -> getHandlerLock(ctx)) ;
        if (ctx -> isFlushed(ctx)) {
            ctx -> unflush(ctx) ;
            quit = 1 ;
        }
        vcos_semaphore_post(ctx -> getHandlerLock(ctx)) ;

        if (!quit)
            usleep(10000) ;
    }
}
