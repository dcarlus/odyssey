/**
 * @file    PortsConfigurationUtils.h
 * @brief   Utility functions to configure the different ports.
 * @author  Denis CARLUS, mainly inspired from Tuomas Jormola work.
 * @version 1.0     03/01/2014
 */

#ifndef  __POLYPHEMUS__IMAGE_OMX_PORTS_CONFIG__
#define  __POLYPHEMUS__IMAGE_OMX_PORTS_CONFIG__

#include <bcm_host.h>
#include <interface/vcos/vcos_semaphore.h>
#include <interface/vmcs_host/vchost.h>

#include "OMXUtils.h"
#include "structs/AppOMXContext.h"

/**
 * @brief   Set up tunnels between the different ports to link them.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void tunneling(AppOMXContext* ctx) ;


/**
 * @brief   Enable the ports.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void enablePorts(AppOMXContext* ctx) ;


/**
 * @brief   Allocate camera input buffer and encoder output buffer, buffers for
 *          tunneled ports are allocated internally by OMX.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void allocateBuffers(AppOMXContext* ctx) ;


/**
 * @brief   Switch state of the components prior to starting the video capture
 *          and encoding loop.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void portsReady(AppOMXContext* ctx) ;



/**
 * @brief   Some busy loops to verify we're running in order.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void block_until_state_changed(
                               OMX_HANDLETYPE* hComponent,
                               OMX_STATETYPE wanted_eState
                              ) ;


/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void block_until_port_changed(
                              OMX_HANDLETYPE* hComponent,
                              OMX_U32 nPortIndex,
                              OMX_BOOL bEnabled
                             ) ;


/**
 * @brief   ...
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
void block_until_flushed(AppOMXContext* ctx) ;

#endif
