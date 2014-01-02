/**
 * @file     CameraSetupUtils.c
 * @author   Denis CARLUS
 */

#include "CameraSetupUtils.h"
#include "structs/AppOMXContext.h"

static void log_printer(const char* message, ...) {
/*    #ifdef DEBUG*/
    va_list args ;
    char str[1024] ;
    memset(str, 0, sizeof(str)) ;
    va_start(args, message) ;
    vsnprintf(str, sizeof(str) - 1, message, args) ;
    va_end(args) ;
    size_t str_len = strnlen(str, sizeof(str)) ;

    if (str[str_len - 1] != '\n')
        str[str_len] = '\n' ;
    fprintf(stderr, str) ;
/*    #endif*/
}


void omx_die(OMX_ERRORTYPE error, const char* message, ...) {
    va_list args ;
    char str[1024] ;
    char* e ;

    memset(str, 0, sizeof(str)) ;
    va_start(args, message) ;
    vsnprintf(str, sizeof(str), message, args) ;
    va_end(args) ;

    switch(error) {
        case OMX_ErrorNone:                     e = "no error";                                      break;
        case OMX_ErrorBadParameter:             e = "bad parameter";                                 break;
        case OMX_ErrorIncorrectStateOperation:  e = "invalid state while trying to perform command"; break;
        case OMX_ErrorIncorrectStateTransition: e = "unallowed state transition";                    break;
        case OMX_ErrorInsufficientResources:    e = "insufficient resource";                         break;
        case OMX_ErrorBadPortIndex:             e = "bad port index, i.e. incorrect port";           break;
        case OMX_ErrorHardware:                 e = "hardware error";                                break;
        /* That's all I've encountered during hacking so let's not bother with the rest... */
        default:                                e = "(no description)";
    }

    fprintf(stderr, "OMX error: %s: 0x%08x %s\n", str, error, e) ;
    exit(EXIT_FAILURE) ;
}


OMX_ERRORTYPE event_handler(
                            OMX_HANDLETYPE hComponent,
                            OMX_PTR pAppData,
                            OMX_EVENTTYPE eEvent,
                            OMX_U32 nData1,
                            OMX_U32 nData2,
                            OMX_PTR pEventData
                           ) {

    dump_event(hComponent, eEvent, nData1, nData2) ;

    AppOMXContext* ctx = (AppOMXContext*) pAppData ;

    switch (eEvent) {
        case OMX_EventCmdComplete :
            vcos_semaphore_wait(ctx -> getHandlerLock(ctx)) ;
            if(nData1 == OMX_CommandFlush)
                ctx -> flush(ctx) ;
            vcos_semaphore_post(ctx -> getHandlerLock(ctx)) ;
            break ;

        case OMX_EventParamOrConfigChanged :
            vcos_semaphore_wait(ctx -> getHandlerLock(ctx)) ;
            if (nData2 == OMX_IndexParamCameraDeviceNumber)
                ctx -> setCameraReady(ctx) ;
            vcos_semaphore_post(ctx -> getHandlerLock(ctx)) ;
            break ;

        case OMX_EventError :
            omx_die(nData1, "error event received") ;
            break ;

        default :
            break ;
    }

    return OMX_ErrorNone ;
}


OMX_ERRORTYPE fill_output_buffer_done_handler (
                                               OMX_HANDLETYPE hComponent,
                                               OMX_PTR pAppData,
                                               OMX_BUFFERHEADERTYPE* pBuffer
                                              ) {
    AppOMXContext* ctx = (AppOMXContext*) pAppData ;
    vcos_semaphore_wait(ctx -> getHandlerLock(ctx)) ;

    // The main loop can now flush the buffer to output file
    ctx -> setEncoderOutputBufferAvailable(ctx) ;
    vcos_semaphore_post(ctx -> getHandlerLock(ctx)) ;
    return OMX_ErrorNone ;
}


void dump_event(
                OMX_HANDLETYPE hComponent,
                OMX_EVENTTYPE eEvent,
                OMX_U32 nData1,
                OMX_U32 nData2
               ) {
    char* e ;

    switch (eEvent) {
        case OMX_EventCmdComplete:          e = "command complete";                   break;
        case OMX_EventError:                e = "error";                              break;
        case OMX_EventParamOrConfigChanged: e = "parameter or configuration changed"; break;
        case OMX_EventPortSettingsChanged:  e = "port settings changed";              break;
        /* That's all I've encountered during hacking so let's not bother with the rest... */
        default:
            e = "(no description)";
    }

    log_printer("Received event 0x%08x %s, hComponent:0x%08x, nData1:0x%08x, nData2:0x%08x\n",
                eEvent, e, hComponent, nData1, nData2) ;
}


void init_component_handle(
                           const char* name,
                           OMX_HANDLETYPE* hComponent,
                           OMX_PTR pAppData,
                           OMX_CALLBACKTYPE* callbacks
                          ) {
    char fullname[32] ;

    // Get handle
    memset(fullname, 0, sizeof(fullname)) ;
    strcat(fullname, "OMX.broadcom.") ;
    strncat(fullname, name, strlen(fullname) - 1) ;
    log_printer("Initializing component %s\n", fullname) ;

    if ((r = OMX_GetHandle(hComponent, fullname, pAppData, callbacks)) != OMX_ErrorNone)
        omx_die(r, "Failed to get handle for component %s", fullname) ;

    // Disable ports
    OMX_INDEXTYPE types[] = {
                             OMX_IndexParamAudioInit,
                             OMX_IndexParamVideoInit,
                             OMX_IndexParamImageInit,
                             OMX_IndexParamOtherInit
                            } ;
    OMX_PORT_PARAM_TYPE ports ;
    OMX_INIT_STRUCTURE(ports) ;
    OMX_GetParameter(*hComponent, OMX_IndexParamVideoInit, &ports) ;

    int i ;
    for (i = 0 ; i < 4 ; i++) {
        if (OMX_GetParameter(*hComponent, types[i], &ports) == OMX_ErrorNone) {
            OMX_U32 nPortIndex ;

            OMX_U32 max = ports.nStartPortNumber + ports.nPorts ;
            for (nPortIndex = ports.nStartPortNumber ; nPortIndex < max ; nPortIndex++) {
                log_printer("Disabling port %d of component %s\n", nPortIndex, fullname) ;

puts("GOUPS ---> ???? WHAT ELSE !") ;
                OMX_ERRORTYPE error ;
                error = OMX_SendCommand(*hComponent, OMX_CommandPortDisable, nPortIndex, NULL) ;
puts("PIJONA")
                if (error != OMX_ErrorNone) {
puts("HIIHAH") ;
                    omx_die(r, "Failed to disable port %d of component %s", nPortIndex, fullname) ;
                }
puts("PIUPU") ;
                block_until_port_changed(*hComponent, nPortIndex, OMX_FALSE) ;
puts("OPOE") ;
            }
        }
    }
}


void block_until_port_changed(
                              OMX_HANDLETYPE hComponent,
                              OMX_U32 nPortIndex,
                              OMX_BOOL bEnabled
                             ) {
    OMX_ERRORTYPE r ;
    OMX_PARAM_PORTDEFINITIONTYPE portdef ;
    OMX_INIT_STRUCTURE(portdef) ;
    portdef.nPortIndex = nPortIndex ;
    OMX_U32 i = 0 ;
    while (i++ == 0 || portdef.bEnabled != bEnabled) {
        if ((r = OMX_GetParameter(hComponent,
                                  OMX_IndexParamPortDefinition,
                                  &portdef)) != OMX_ErrorNone) {
            omx_die(r, "Failed to get port definition") ;
        }

        if (portdef.bEnabled != bEnabled) {
            usleep(10000) ;
        }
    }
}
