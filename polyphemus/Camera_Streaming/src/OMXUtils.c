/**
 * @file     OMXUtils.c
 * @author   Denis CARLUS
 */

#include "OMXUtils.h"

void die(const char* message) {
    fprintf(stderr, message) ;
    exit(EXIT_FAILURE) ;
}

void log_printer(const char* message, ...) {
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
