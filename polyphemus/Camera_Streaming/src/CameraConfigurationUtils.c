/**
 * @file     CameraConfigurationUtils.c
 * @author   Denis CARLUS
 */

#include "CameraConfigurationUtils.h"
#include "OMXUtils.h"
#include "structs/AppOMXContext.h"

void open_ports(int ports[],
                const char* portsName[],
                unsigned char portsCount,
                OMX_HANDLETYPE* hComponent) {
    unsigned char index ;
    for (index = 0 ; index < portsCount ; index++) {
        log_printer("Default port definition for %s port %d", portsName[index], ports[index]) ;
        dump_port(hComponent, ports[index], OMX_TRUE) ;
    }
}


void dump_port(
               OMX_HANDLETYPE* hComponent,
               OMX_U32 nPortIndex,
               OMX_BOOL dumpformats
              ) {
    OMX_ERRORTYPE error ;
    OMX_PARAM_PORTDEFINITIONTYPE portdef ;
    OMX_INIT_STRUCTURE(portdef) ;

    portdef.nPortIndex = nPortIndex ;
    error = OMX_GetParameter(*hComponent, OMX_IndexParamPortDefinition, &portdef) ;
    if (error != OMX_ErrorNone)
        omx_die(error, "Failed to get port definition for port %d", nPortIndex) ;

    dump_portdef(&portdef) ;

    if (dumpformats) {
        OMX_VIDEO_PARAM_PORTFORMATTYPE portformat ;
        OMX_INIT_STRUCTURE(portformat) ;
        portformat.nPortIndex = nPortIndex ;
        portformat.nIndex = 0 ;
        error = OMX_ErrorNone ;

        log_printer("Port %d supports these video formats:", nPortIndex) ;

        while (error == OMX_ErrorNone) {
            error = OMX_GetParameter(*hComponent, OMX_IndexParamVideoPortFormat, &portformat) ;

            if (error == OMX_ErrorNone) {
                log_printer("\t%s, compression: %s", dump_color_format(portformat.eColorFormat), dump_compression_format(portformat.eCompressionFormat)) ;
                portformat.nIndex++ ;
            }
        }
    }
}


void dump_portdef(OMX_PARAM_PORTDEFINITIONTYPE* portdef) {
    log_printer("Port %d is %s, %s, buffers wants:%d needs:%d, size:%d, pop:%d, aligned:%d",
                portdef -> nPortIndex,
                (portdef -> eDir ==  OMX_DirInput ? "input" : "output"),
                (portdef -> bEnabled == OMX_TRUE ? "enabled" : "disabled"),
                portdef -> nBufferCountActual,
                portdef -> nBufferCountMin,
                portdef -> nBufferSize,
                portdef -> bPopulated,
                portdef -> nBufferAlignment
               ) ;

    OMX_VIDEO_PORTDEFINITIONTYPE *viddef = &portdef -> format.video ;
    OMX_IMAGE_PORTDEFINITIONTYPE *imgdef = &portdef -> format.image ;

    switch (portdef -> eDomain) {
        case OMX_PortDomainVideo:
            log_printer("Video type:\n"
                            "\tWidth:\t\t%d\n"
                            "\tHeight:\t\t%d\n"
                            "\tStride:\t\t%d\n"
                            "\tSliceHeight:\t%d\n"
                            "\tBitrate:\t%d\n"
                            "\tFramerate:\t%.02f\n"
                            "\tError hiding:\t%s\n"
                            "\tCodec:\t\t%s\n"
                            "\tColor:\t\t%s\n",
                        viddef -> nFrameWidth,
                        viddef -> nFrameHeight,
                        viddef -> nStride,
                        viddef -> nSliceHeight,
                        viddef -> nBitrate,
                        ((float) (viddef -> xFramerate) / (float) 65536),
                        (viddef -> bFlagErrorConcealment == OMX_TRUE ? "yes" : "no"),
                        dump_compression_format(viddef -> eCompressionFormat),
                        dump_color_format(viddef -> eColorFormat)
                       ) ;
            break ;

        case OMX_PortDomainImage:
            log_printer("Image type:\n"
                            "\tWidth:\t\t%d\n"
                            "\tHeight:\t\t%d\n"
                            "\tStride:\t\t%d\n"
                            "\tSliceHeight:\t%d\n"
                            "\tError hiding:\t%s\n"
                            "\tCodec:\t\t%s\n"
                            "\tColor:\t\t%s\n",
                        imgdef -> nFrameWidth,
                        imgdef -> nFrameHeight,
                        imgdef -> nStride,
                        imgdef -> nSliceHeight,
                        (imgdef -> bFlagErrorConcealment == OMX_TRUE ? "yes" : "no"),
                        dump_compression_format(imgdef -> eCompressionFormat),
                        dump_color_format(imgdef -> eColorFormat)
                       ) ;
            break ;

        default:
            break ;
    }
}


const char* dump_compression_format(OMX_VIDEO_CODINGTYPE c) {
    char *f ;

    switch(c) {
        case OMX_VIDEO_CodingUnused:     return "not used";
        case OMX_VIDEO_CodingAutoDetect: return "autodetect";
        case OMX_VIDEO_CodingMPEG2:      return "MPEG2";
        case OMX_VIDEO_CodingH263:       return "H.263";
        case OMX_VIDEO_CodingMPEG4:      return "MPEG4";
        case OMX_VIDEO_CodingWMV:        return "Windows Media Video";
        case OMX_VIDEO_CodingRV:         return "RealVideo";
        case OMX_VIDEO_CodingAVC:        return "H.264/AVC";
        case OMX_VIDEO_CodingMJPEG:      return "Motion JPEG";
        case OMX_VIDEO_CodingVP6:        return "VP6";
        case OMX_VIDEO_CodingVP7:        return "VP7";
        case OMX_VIDEO_CodingVP8:        return "VP8";
        case OMX_VIDEO_CodingYUV:        return "Raw YUV video";
        case OMX_VIDEO_CodingSorenson:   return "Sorenson";
        case OMX_VIDEO_CodingTheora:     return "OGG Theora";
        case OMX_VIDEO_CodingMVC:        return "H.264/MVC";
        default:
            f = calloc(23, sizeof(char)) ;
            if (f == NULL)
                die("Failed to allocate memory") ;

            snprintf(f, 23 * sizeof(char) - 1, "format type 0x%08x", c) ;
            return f ;
    }
}


const char* dump_color_format(OMX_COLOR_FORMATTYPE c) {
    char *f ;

    switch (c) {
        case OMX_COLOR_FormatUnused:                 return "OMX_COLOR_FormatUnused: not used";
        case OMX_COLOR_FormatMonochrome:             return "OMX_COLOR_FormatMonochrome";
        case OMX_COLOR_Format8bitRGB332:             return "OMX_COLOR_Format8bitRGB332";
        case OMX_COLOR_Format12bitRGB444:            return "OMX_COLOR_Format12bitRGB444";
        case OMX_COLOR_Format16bitARGB4444:          return "OMX_COLOR_Format16bitARGB4444";
        case OMX_COLOR_Format16bitARGB1555:          return "OMX_COLOR_Format16bitARGB1555";
        case OMX_COLOR_Format16bitRGB565:            return "OMX_COLOR_Format16bitRGB565";
        case OMX_COLOR_Format16bitBGR565:            return "OMX_COLOR_Format16bitBGR565";
        case OMX_COLOR_Format18bitRGB666:            return "OMX_COLOR_Format18bitRGB666";
        case OMX_COLOR_Format18bitARGB1665:          return "OMX_COLOR_Format18bitARGB1665";
        case OMX_COLOR_Format19bitARGB1666:          return "OMX_COLOR_Format19bitARGB1666";
        case OMX_COLOR_Format24bitRGB888:            return "OMX_COLOR_Format24bitRGB888";
        case OMX_COLOR_Format24bitBGR888:            return "OMX_COLOR_Format24bitBGR888";
        case OMX_COLOR_Format24bitARGB1887:          return "OMX_COLOR_Format24bitARGB1887";
        case OMX_COLOR_Format25bitARGB1888:          return "OMX_COLOR_Format25bitARGB1888";
        case OMX_COLOR_Format32bitBGRA8888:          return "OMX_COLOR_Format32bitBGRA8888";
        case OMX_COLOR_Format32bitARGB8888:          return "OMX_COLOR_Format32bitARGB8888";
        case OMX_COLOR_FormatYUV411Planar:           return "OMX_COLOR_FormatYUV411Planar";
        case OMX_COLOR_FormatYUV411PackedPlanar:     return "OMX_COLOR_FormatYUV411PackedPlanar: Planes fragmented when a frame is split in multiple buffers";
        case OMX_COLOR_FormatYUV420Planar:           return "OMX_COLOR_FormatYUV420Planar: Planar YUV, 4:2:0 (I420)";
        case OMX_COLOR_FormatYUV420PackedPlanar:     return "OMX_COLOR_FormatYUV420PackedPlanar: Planar YUV, 4:2:0 (I420), planes fragmented when a frame is split in multiple buffers";
        case OMX_COLOR_FormatYUV420SemiPlanar:       return "OMX_COLOR_FormatYUV420SemiPlanar, Planar YUV, 4:2:0 (NV12), U and V planes interleaved with first U value";
        case OMX_COLOR_FormatYUV422Planar:           return "OMX_COLOR_FormatYUV422Planar";
        case OMX_COLOR_FormatYUV422PackedPlanar:     return "OMX_COLOR_FormatYUV422PackedPlanar: Planes fragmented when a frame is split in multiple buffers";
        case OMX_COLOR_FormatYUV422SemiPlanar:       return "OMX_COLOR_FormatYUV422SemiPlanar";
        case OMX_COLOR_FormatYCbYCr:                 return "OMX_COLOR_FormatYCbYCr";
        case OMX_COLOR_FormatYCrYCb:                 return "OMX_COLOR_FormatYCrYCb";
        case OMX_COLOR_FormatCbYCrY:                 return "OMX_COLOR_FormatCbYCrY";
        case OMX_COLOR_FormatCrYCbY:                 return "OMX_COLOR_FormatCrYCbY";
        case OMX_COLOR_FormatYUV444Interleaved:      return "OMX_COLOR_FormatYUV444Interleaved";
        case OMX_COLOR_FormatRawBayer8bit:           return "OMX_COLOR_FormatRawBayer8bit";
        case OMX_COLOR_FormatRawBayer10bit:          return "OMX_COLOR_FormatRawBayer10bit";
        case OMX_COLOR_FormatRawBayer8bitcompressed: return "OMX_COLOR_FormatRawBayer8bitcompressed";
        case OMX_COLOR_FormatL2:                     return "OMX_COLOR_FormatL2";
        case OMX_COLOR_FormatL4:                     return "OMX_COLOR_FormatL4";
        case OMX_COLOR_FormatL8:                     return "OMX_COLOR_FormatL8";
        case OMX_COLOR_FormatL16:                    return "OMX_COLOR_FormatL16";
        case OMX_COLOR_FormatL24:                    return "OMX_COLOR_FormatL24";
        case OMX_COLOR_FormatL32:                    return "OMX_COLOR_FormatL32";
        case OMX_COLOR_FormatYUV420PackedSemiPlanar: return "OMX_COLOR_FormatYUV420PackedSemiPlanar: Planar YUV, 4:2:0 (NV12), planes fragmented when a frame is split in multiple buffers, U and V planes interleaved with first U value";
        case OMX_COLOR_FormatYUV422PackedSemiPlanar: return "OMX_COLOR_FormatYUV422PackedSemiPlanar: Planes fragmented when a frame is split in multiple buffers";
        case OMX_COLOR_Format18BitBGR666:            return "OMX_COLOR_Format18BitBGR666";
        case OMX_COLOR_Format24BitARGB6666:          return "OMX_COLOR_Format24BitARGB6666";
        case OMX_COLOR_Format24BitABGR6666:          return "OMX_COLOR_Format24BitABGR6666";
        case OMX_COLOR_Format32bitABGR8888:          return "OMX_COLOR_Format32bitABGR8888";
        case OMX_COLOR_Format8bitPalette:            return "OMX_COLOR_Format8bitPalette";
        case OMX_COLOR_FormatYUVUV128:               return "OMX_COLOR_FormatYUVUV128";
        case OMX_COLOR_FormatRawBayer12bit:          return "OMX_COLOR_FormatRawBayer12bit";
        case OMX_COLOR_FormatBRCMEGL:                return "OMX_COLOR_FormatBRCMEGL";
        case OMX_COLOR_FormatBRCMOpaque:             return "OMX_COLOR_FormatBRCMOpaque";
        case OMX_COLOR_FormatYVU420PackedPlanar:     return "OMX_COLOR_FormatYVU420PackedPlanar";
        case OMX_COLOR_FormatYVU420PackedSemiPlanar: return "OMX_COLOR_FormatYVU420PackedSemiPlanar";
        default:
            f = calloc(23, sizeof(char)) ;
            if (f == NULL)
                die("Failed to allocate memory") ;

            snprintf(f, 23 * sizeof(char) - 1, "format type 0x%08x", c) ;
            return f ;
    }
}
