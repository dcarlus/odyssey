/**
 * @file     AppOMXContext.c
 * @author   Denis CARLUS
 */

#include "AppOMXContext.h"
#include "handlers/camera/CameraBufferHandler.h"
#include "handlers/encoder/EncoderBufferHandler.h"
#include "handlers/null_sink/NullSinkHandler.h"
#include "../CameraConfigurationUtils.h"
#include "../MainStreaming.h"
#include "../Network.h"
#include "../OMXUtils.h"
#include "../PortsConfigurationUtils.h"
#include <arpa/inet.h>
#include <assert.h>

// Client feedback (requests)
#define CLIENT_REQUEST_NONE     0
#define CLIENT_REQUEST_KEYFRAME 1

// Header got from the VideoCore is a 27-bytes data.
#define H264_HEADER_SIZE_PART1  18
#define H264_HEADER_SIZE_PART2  9
#define H264_HEADER_SIZE        H264_HEADER_SIZE_PART1 + H264_HEADER_SIZE_PART2

// States to send merged header and data
#define STATE_MESSAGE_18                    1
#define STATE_MESSAGE_9                     2
#define STATE_MESSAGE_FRAME_WITH_HEADER     4
#define STATE_MESSAGE_FRAME_WITHOUT_HEADER  8


/** @brief  Global variable used by the signal handler and capture/encoding loop. */
int WantToQuit = 0 ;

static char* serverIp;

                                                           /** CONFIGURATION **/
/** @brief  Configure the camera parameters. */
static void AppOMXContext_ConfigureCamera(AppOMXContext* self) {
    BasicOMXHandler* cameraHandler = &(self -> camera).basic ;
    cameraHandler -> configure(cameraHandler) ;
}


/** @brief  Configure the encoder parameters. */
static void AppOMXContext_ConfigureEncoder(AppOMXContext* self) {
    BasicOMXHandler* encoderHandler = &(self -> encoder).basic ;
    BasicOMXHandler* cameraHandler = &(self -> camera).basic ;
    encoderHandler -> configure(encoderHandler) ;
}


                                                                 /** GETTERS **/
/** @brief  Get the camera OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetCameraHandleType(AppOMXContext* self) {
    return &(((self -> camera).basic).type) ;
}

/** @brief  Get the encoder OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetEncoderHandleType(AppOMXContext* self) {
    return &(((self -> encoder).basic).type) ;
}

/** @brief  Get the null sink OMX_HANDLETYPE structure. */
static OMX_HANDLETYPE* AppOMXContext_GetNullSinkHandleType(AppOMXContext* self) {
    return &((self -> nullSink).type) ;
}

/** @brief  Get the handler locker semaphore of the application context. */
static VCOS_SEMAPHORE_T* AppOMXContext_GetHandlerLock(AppOMXContext* self) {
    return &(self -> handlerLock) ;
}

/** @brief  Get the camera handler. */
static BufferOMXHandler* AppOMXContext_GetCameraHandler(AppOMXContext* self) {
    return &(self -> camera) ;
}

/** @brief  Get the camera handler. */
static BufferOMXHandler* AppOMXContext_GetEncoderHandler(AppOMXContext* self) {
    return &(self -> encoder) ;
}

/** @brief  Get the flush flag. */
static char AppOMXContext_IsFlushed(AppOMXContext* self) {
    return self -> flushed ;
}


                                                                 /** SETTERS **/
/** @brief  Set the camera readiness flag to true. */
static void AppOMXContext_SetCameraReady(AppOMXContext* self) {
    BufferOMXHandler* cameraBuffer = &(self -> camera) ;
    BasicOMXHandler* camera = cameraBuffer -> getBasicHandler(cameraBuffer) ;
    camera -> setReady(camera) ;
}

/** @brief  Set the encoder availability flag to true. */
static void AppOMXContext_SetEncoderOutputBufferAvailable(AppOMXContext* self) {
    BufferOMXHandler* encoderBuffer = &(self -> encoder) ;
    BasicOMXHandler* encoder = encoderBuffer -> getBasicHandler(encoderBuffer) ;
    encoder -> setReady(encoder) ;
}

/** @brief  Set the flush flag to true. */
static void AppOMXContext_SetFlushed(AppOMXContext* self) {
    self -> flushed = 1 ;
}

/** @brief  Set the flush flag to false. */
static void AppOMXContext_SetUnflushed(AppOMXContext* self) {
    self -> flushed = 0 ;
}


                                                               /** UTILITIES **/
static void _AppOMXContext_StopCapturing(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;
    OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
    OMX_HANDLETYPE* nullSink = self -> getNullSink(self) ;
    BufferOMXHandler* encoderHandler = self -> getEncoderHandler(self) ;
    OMX_BUFFERHEADERTYPE* encoderBuffer = encoderHandler -> getBufferHeader(encoderHandler) ;

    // Stop capturing video with the camera
    OMX_CONFIG_PORTBOOLEANTYPE capture ;
    OMX_INIT_STRUCTURE(capture) ;
    capture.nPortIndex = 71 ;
    capture.bEnabled = OMX_FALSE ;
    testError(OMX_SetParameter(*camera, OMX_IndexConfigPortCapturing, &capture),
              "Failed to switch off capture on camera video output port 71") ;

    // Return the last full buffer back to the encoder component
/*    encoderBuffer -> nFlags = OMX_BUFFERFLAG_EOS ;*/
/*    testError(OMX_FillThisBuffer(*encoder, encoderBuffer),*/
/*              "Failed to request filling of the output buffer on encoder output port 201") ;*/
}

// Flush the buffers on each component
static void _AppOMXContext_FlushBuffers(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;
    OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
    OMX_HANDLETYPE* nullSink = self -> getNullSink(self) ;

                                                                                /** CAMERA **/
    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 73, NULL),
                              "Failed to flush buffers of camera input port 73") ;
    block_until_flushed(self) ;

    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 70, NULL),
                              "Failed to flush buffers of camera preview output port 70") ;
    block_until_flushed(self) ;

    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 71, NULL),
                              "Failed to flush buffers of camera video output port 71") ;
    block_until_flushed(self) ;

                                                                                /** ENCODER **/
    testError(OMX_SendCommand(*encoder, OMX_CommandFlush, 200, NULL),
                              "Failed to flush buffers of encoder input port 200") ;
    block_until_flushed(self) ;

    testError(OMX_SendCommand(*encoder, OMX_CommandFlush, 201, NULL),
                              "Failed to flush buffers of encoder output port 201") ;
    block_until_flushed(self) ;


                                                                                /** NULL SINK **/
    testError(OMX_SendCommand(*nullSink, OMX_CommandFlush, 240, NULL),
                              "Failed to flush buffers of null sink input port 240") ;
    block_until_flushed(self) ;
}


static void _AppOMXContext_DisablePorts(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;
    OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
    OMX_HANDLETYPE* nullSink = self -> getNullSink(self) ;

                                                                                /** CAMERA **/
    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 73, NULL),
                              "Failed to disable camera input port 73") ;
    block_until_port_changed(*camera, 73, OMX_FALSE) ;

    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 70, NULL),
                              "Failed to disable camera preview output port 70") ;
    block_until_port_changed(*camera, 70, OMX_FALSE) ;

    testError(OMX_SendCommand(*camera, OMX_CommandFlush, 71, NULL),
                              "Failed to disable camera video output port 71") ;
    block_until_port_changed(*camera, 71, OMX_FALSE) ;

                                                                                /** ENCODER **/
    testError(OMX_SendCommand(*encoder, OMX_CommandFlush, 200, NULL),
                              "Failed to disable encoder input port 200") ;
    block_until_port_changed(*encoder, 200, OMX_FALSE) ;

    testError(OMX_SendCommand(*encoder, OMX_CommandFlush, 201, NULL),
                              "Failed to disable encoder output port 201") ;
    block_until_port_changed(*encoder, 201, OMX_FALSE) ;

                                                                                /** NULL SINK **/
    testError(OMX_SendCommand(*nullSink, OMX_CommandFlush, 240, NULL),
                              "Failed to disable null sink input port 240") ;
    block_until_port_changed(*nullSink, 240, OMX_FALSE) ;
}


// Free all the buffers
static void _AppOMXContext_FreeBuffers(AppOMXContext* self) {
    {
                                                                                 /** CAMERA **/
        OMX_HANDLETYPE* camera = self -> getCamera(self) ;
        BufferOMXHandler* cameraHandler = self -> getCameraHandler(self) ;
        OMX_BUFFERHEADERTYPE* cameraBuffer = cameraHandler -> getBufferHeader(cameraHandler) ;

        testError(OMX_FreeBuffer(*camera, 73, cameraBuffer),
                                 "Failed to free buffer for camera input port 73") ;
    }

    {
                                                                                /** ENCODER **/
        OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
        BufferOMXHandler* encoderHandler = self -> getEncoderHandler(self) ;
        OMX_BUFFERHEADERTYPE* encoderBuffer = encoderHandler -> getBufferHeader(encoderHandler) ;

        testError(OMX_FreeBuffer(*encoder, 201, encoderBuffer),
                                 "Failed to free buffer for encoder output port 201") ;
    }
}


static void _AppOMXContext_SetComponentsAsLoaded(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;
    OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
    OMX_HANDLETYPE* nullSink = self -> getNullSink(self) ;

                                                                                /** COMPONENTS TO IDLE STATE **/
    testError(OMX_SendCommand(*camera, OMX_CommandStateSet, OMX_StateIdle, NULL),
                              "Failed to switch state of the camera component to idle") ;
    block_until_state_changed(*camera, OMX_StateIdle) ;

    testError(OMX_SendCommand(*encoder, OMX_CommandStateSet, OMX_StateIdle, NULL),
                              "Failed to switch state of the encoder component to idle") ;
    block_until_state_changed(*encoder, OMX_StateIdle) ;

    testError(OMX_SendCommand(*nullSink, OMX_CommandStateSet, OMX_StateIdle, NULL),
                              "Failed to switch state of the encoder component to idle") ;
    block_until_state_changed(*nullSink, OMX_StateIdle) ;


                                                                                /** COMPONENTS TO LOADED STATE **/
    testError(OMX_SendCommand(*camera, OMX_CommandStateSet, OMX_StateLoaded, NULL),
                              "Failed to switch state of the camera component to loaded") ;
    block_until_state_changed(*camera, OMX_StateLoaded) ;

    testError(OMX_SendCommand(*encoder, OMX_CommandStateSet, OMX_StateLoaded, NULL),
                              "Failed to switch state of the encoder component to loaded") ;
    block_until_state_changed(*encoder, OMX_StateLoaded) ;

    testError(OMX_SendCommand(*nullSink, OMX_CommandStateSet, OMX_StateLoaded, NULL),
                              "Failed to switch state of the encoder component to loaded") ;
    block_until_state_changed(*nullSink, OMX_StateLoaded) ;
}



/**
 * @brief   Common code to send picture with and variable header size (offset).
 * @param   bufferData  Buffer to fill.
 * @param   dataContent Content of the data.
 * @param   dataLength  Length of the data.
 * @param   offset      Offset in the buffer where to start writing the data.
 */
static int _AppOMXContext_SendPicture(AppOMXContext* self,
                                       char* bufferData,
                                       int8_t* dataContent,
                                       uint32_t dataLength,
                                       uint32_t offset,
                                       OMX_BUFFERHEADERTYPE* encoderBuffer) {
    if (dataLength > 256) {
        // Length of the frame data: H264 header + picture
        // data (written in Big Endian to send on network)
        uint32_t fullLength = htonl(offset + dataLength) ;
        // Total size of the sent data for write()
        uint32_t bufferSize = offset + dataLength ;

        // Copy the compressed frame data at (offset + 4 bytes)
        memcpy(bufferData + offset, dataContent, dataLength) ;

        // Send the full buffer to the client (Jupiter, IO)
        StreamingServer* ss = &(self -> streamingServer) ;
        size_t output_written ;
        char success = SecurityServerSendVideoBuffer(self -> clientSocket,
                                                     bufferData,
                                                     bufferSize) ;

        if ((!streamingReady) || (!success)) {
            printf("Failed to write to output file: %s\n", strerror(errno)) ;
            streamingReady = 0 ;
            self -> clientSocket = -2 ;
            return 0 ;
        }

        log_printer("Read from output buffer and write to output file %d/%d",
                    encoderBuffer -> nFilledLen,
                    encoderBuffer -> nAllocLen) ;
    }
    return 1 ;
}


/**
 * @brief  Capture the video from the camera.
 * @author  Tuomas Jormola
 * Copyright © 2013 Tuomas Jormola <tj@solitudo.net> <http://solitudo.net>
 */
static void AppOMXContext_CaptureVideo(AppOMXContext* self) {
    OMX_HANDLETYPE* camera = self -> getCamera(self) ;
    OMX_HANDLETYPE* encoder = self -> getEncoder(self) ;
    OMX_HANDLETYPE* nullSink = self -> getNullSink(self) ;
    BufferOMXHandler* encoderHandler = self -> getEncoderHandler(self) ;
    static OMX_PARAM_PORTDEFINITIONTYPE encoder_portdef ;
    static OMX_BUFFERHEADERTYPE* encoderBuffer = NULL ;
    static OMX_CONFIG_PORTBOOLEANTYPE capture ;
/*    OMX_BUFFERHEADERTYPE* encoderBuffer = encoderHandler -> getBufferHeader(encoderHandler) ;*/
    BasicOMXHandler* encoderBasicHandler = encoderHandler -> getBasicHandler(encoderHandler) ;
    static int isInitialized = 0 ;


// Do not work if this code is placed in the
// PortsConfigurationUtils::allocateBuffers() function...
//..............................................................................
    if (!isInitialized) {
        OMX_INIT_STRUCTURE(encoder_portdef) ;
        encoder_portdef.nPortIndex = PORT_ENCODER_OUTPUT ;
        testError(OMX_GetParameter(*encoder, OMX_IndexParamPortDefinition, &encoder_portdef),
                "Failed to get port definition for encoder output port 201") ;
        testError(OMX_AllocateBuffer(*encoder,
                                    &encoderBuffer,
                                    PORT_ENCODER_OUTPUT,
                                    NULL,
                                    encoder_portdef.nBufferSize),
                "Failed to allocate buffer for encoder output port 201") ;

        log_printer("Switching state of the encoder component to executing...") ;
        testError(OMX_SendCommand(*encoder, OMX_CommandStateSet, OMX_StateExecuting, NULL),
                "Failed to switch state of the encoder component to executing") ;
        block_until_state_changed(encoder, OMX_StateExecuting) ;
    //..............................................................................



        log_printer("Switching on capture on camera video output port 71...") ;

        OMX_INIT_STRUCTURE(capture) ;
        capture.nPortIndex = PORT_CAMERA_VIDEO ;
        capture.bEnabled = OMX_TRUE ;
        testError(OMX_SetParameter(*camera, OMX_IndexConfigPortCapturing, &capture),
                "Failed to switch on capture on camera video output port 71") ;

        log_printer("Configured port definition for camera input port 73") ;
        dump_port(camera, PORT_CAMERA_INPUT, OMX_FALSE) ;
        log_printer("Configured port definition for camera preview output port 70") ;
        dump_port(camera, PORT_CAMERA_PREVIEW, OMX_FALSE) ;
        log_printer("Configured port definition for camera video output port 71") ;
        dump_port(camera, PORT_CAMERA_VIDEO, OMX_FALSE) ;
        log_printer("Configured port definition for encoder input port 200") ;
        dump_port(encoder, PORT_ENCODER_INPUT, OMX_FALSE) ;
        log_printer("Configured port definition for encoder output port 201") ;
        dump_port(encoder, PORT_ENCODER_OUTPUT, OMX_FALSE) ;
        log_printer("Configured port definition for null sink input port 240") ;
        dump_port(nullSink, PORT_NULLSINK_INPUT, OMX_FALSE) ;
        
        isInitialized = 1 ;
    }

    log_printer("Start capture...") ;

    int quit_detected = 0 ;                                                     // Detect when the user want to quit
    int quit_in_keyframe = 0 ;                                                  // Detect if a frame is synchronized before quitting
    int need_next_buffer_to_be_filled = 1 ;                                     // Request for a new frame
    unsigned char interframesCounter = 0 ;                                      // Counter of interframes (between two keyframes)
    unsigned char maxInterframes = VIDEO_KEYFRAME_FREQUENCY - 1 ;               // Maximal amount of interframes
    char bufferData[65567] ;                                                    // Buffer used to write sent informations
    StreamingServer* ss = &(self -> streamingServer) ;                          // Shortcut to the streaming server object

    while (1) {
        if (!WantToQuit && (self -> clientSocket == -2)) {
            log_printer("Server ready to stream video") ;

            // Wait for the unique client
            self -> clientSocket = ss -> listen(ss) ;
            if ((self -> clientSocket) < 0) {
                ss -> close(ss) ;
                die("Error : the client could not connect.\n") ;
            }

            log_printer("Client connected !") ;
        }
        else {
            log_printer("Stop server") ;
            break ;
        }


        // State used to concatenate H264 SPS/PPS to frame data.
        int stateSending = STATE_MESSAGE_18 ;

        // Encode the video frames to compress them and send them to the client
        while (1) {
            if (encoderBasicHandler -> isReady(encoderBasicHandler)) {
                if (WantToQuit && !quit_detected) {
                    log_printer("Exit signal detected, waiting for next key frame boundary before exiting...") ;
                    quit_detected = 1 ;
                    quit_in_keyframe = (encoderBuffer -> nFlags) & OMX_BUFFERFLAG_SYNCFRAME ;
                }

                if (quit_detected) {
                    log_printer("Key frame boundry reached, exiting loop...") ;
                    break ;
                }


                // Data get from the encoder (header, data, ...)
                int8_t* dataContent = (int8_t*) (encoderBuffer -> pBuffer) + (encoderBuffer -> nOffset) ;
                // Size of the returned data by the encoder
                uint32_t dataLength = encoderBuffer -> nFilledLen ;

                // Sometimes the decoder is desynchronized...
                // So if a keyframe should be sent but there is no header...
                // Send an interframe instead. Significantly reduces errors.
                if (((stateSending == STATE_MESSAGE_18) && (dataLength != H264_HEADER_SIZE_PART1))
                        || ((stateSending == STATE_MESSAGE_9) && (dataLength != H264_HEADER_SIZE_PART2)))
                    stateSending = STATE_MESSAGE_FRAME_WITHOUT_HEADER ;
		else if (dataLength == H264_HEADER_SIZE_PART1) {
                    stateSending = STATE_MESSAGE_18 ;
		}

                // Switch between the states of the state machine.
                // It always follows the same order (18-byte data, 9-byte data,
                // and finally compressed picture data).
                switch (stateSending) {
                    case STATE_MESSAGE_18:
                        // Copy data to the buffer at offset 4
                        memcpy(bufferData, dataContent, dataLength) ;
                        // Set the next state
                        stateSending = STATE_MESSAGE_9 ;
                        break ;

                    case STATE_MESSAGE_9:
                        // Copy data to the buffer at offset 4 + 18 = 22
                        memcpy(bufferData + H264_HEADER_SIZE_PART1, dataContent, dataLength) ;
                        // Set the next state
                        stateSending = STATE_MESSAGE_FRAME_WITH_HEADER ;
                        break ;

                    case STATE_MESSAGE_FRAME_WITH_HEADER:
                        if (!_AppOMXContext_SendPicture(self, bufferData, dataContent, dataLength, H264_HEADER_SIZE, encoderBuffer))
                            return ;
                        stateSending = STATE_MESSAGE_FRAME_WITHOUT_HEADER ;
                        interframesCounter = 0 ;
                        break ;

                    case STATE_MESSAGE_FRAME_WITHOUT_HEADER:
                        interframesCounter++ ;
                        if (!_AppOMXContext_SendPicture(self, bufferData, dataContent, dataLength, 0, encoderBuffer))
                            return ;
                         
                        if (interframesCounter >= maxInterframes)
                            stateSending = STATE_MESSAGE_18 ;
                        break ;
                }

                if (!WantToQuit)
                    need_next_buffer_to_be_filled = 1 ;
            }

            // Buffer flushed, request a new buffer to be filled by the encoder component
            if (need_next_buffer_to_be_filled) {
                need_next_buffer_to_be_filled = 0 ;
                encoderBasicHandler -> setUnready(encoderBasicHandler) ;

                testError(OMX_FillThisBuffer(*encoder, encoderBuffer),
                          "Failed to request filling of the output buffer on encoder output port 201") ;
            }

            // Would be better to use signaling here but hey this works too
            usleep(1000) ;
        }

        log_printer("Stop video streaming...") ;
    }

    _AppOMXContext_StopCapturing(self) ;
    _AppOMXContext_FlushBuffers(self) ;
    _AppOMXContext_DisablePorts(self) ;
    _AppOMXContext_FreeBuffers(self) ;
    _AppOMXContext_SetComponentsAsLoaded(self) ;

    // Close the output file
    log_printer("Server shutdowns\n") ;
    ss -> close(ss) ;
/*    vcos_semaphore_delete(&(self -> handlerLock)) ;*/
    testError(OMX_Deinit(), "OMX de-initalization failed") ;
}



                                                             /** CONSTRUCTOR **/
/** @brief  Initialize an AppOMXContext. */
static void _AppOMXContext_Init(AppOMXContext* self) {
    // Configuration
    self -> configureCamera = AppOMXContext_ConfigureCamera ;
    self -> configureEncoder = AppOMXContext_ConfigureEncoder ;

    // Getters
    self -> getCamera = AppOMXContext_GetCameraHandleType ;
    self -> getEncoder = AppOMXContext_GetEncoderHandleType ;
    self -> getNullSink = AppOMXContext_GetNullSinkHandleType ;
    self -> getHandlerLock = AppOMXContext_GetHandlerLock ;
    self -> getCameraHandler = AppOMXContext_GetCameraHandler ;
    self -> getEncoderHandler = AppOMXContext_GetEncoderHandler ;
    self -> isFlushed = AppOMXContext_IsFlushed ;

    // Setters
    self -> setCameraReady = AppOMXContext_SetCameraReady ;
    self -> setEncoderOutputBufferAvailable = AppOMXContext_SetEncoderOutputBufferAvailable ;
    self -> flush = AppOMXContext_SetFlushed ;
    self -> unflush = AppOMXContext_SetUnflushed ;

    // Utilities
    self -> capture = AppOMXContext_CaptureVideo ;


    // Initialize data
    #ifdef NETWORK_WIFI
        self -> streamingServer = StreamingServer_Construct(serverIp, 9587) ;
    #else
        self -> streamingServer = StreamingServer_Construct(serverIp, 9587) ;
    #endif
    self -> camera = CameraBufferHandler_Construct() ;
    self -> encoder = EncoderBufferHandler_Construct() ;
    self -> nullSink = NullSinkHandler_Construct() ;
    self -> clientSocket = -2 ;
}


/** @brief  Create a new AppOMXContext. */
AppOMXContext AppOMXContext_Construct(char* ip) {
    AppOMXContext self ;
    serverIp = ip ;
    _AppOMXContext_Init(&self) ;
    return self ;
}


/** @brief  memset() on an AppOMXContext with the right initialization*/
void* AppOMXContext_Memset(AppOMXContext* self, int c, size_t n) {
    void* result = memset(self, c, n) ;
    _AppOMXContext_Init(self) ;
    return result ;
}
