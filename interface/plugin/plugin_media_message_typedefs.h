/////////////////////////////////////////////////////////////////////////////
// Name:        plugin_media_message_typedefs.h
// Purpose:     
// Author:      yangfuqiang
// Modified by: 
// Created:     2017-02-16 16:00:37 
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#ifndef _PLUGIN_MEDIA_MESSAGE_TYPEDEFS_H_
#define _PLUGIN_MEDIA_MESSAGE_TYPEDEFS_H_

#ifdef HJMEDIA_MESSAGE_EXPORT
#define HJMEDIA_MESSAGE_DLLEXPORT _declspec(dllexport)
#else
#ifdef WIN32
#define HJMEDIA_MESSAGE_DLLEXPORT _declspec(dllimport)
#else
#define HJMEDIA_MESSAGE_DLLEXPORT
#endif //WIN32
#endif //HJMEDIA_MESSAGE_EXPORT

#define HJMEDIA_MESSAGE_VERSION				"1.0.0.1"

#if !defined(_MSC_VER)
#include <stdint.h>
#else
// Define C99 equivalent types, since pre-2010 MSVC doesn't provide stdint.h.
typedef __int64             int64_t;
#endif

namespace hjav {
    enum HjMediaFileFormats
    {
        kHjMediaFileFormatMp3 = 0,
        kHjMediaFileFormatAmrNB = 1,
        kHjMediaFileFormatAmrWB = 2,
    };

    class HjMediaFilePlayCallback
    {
    public:
        virtual ~HjMediaFilePlayCallback(){}
        virtual void OnMediaFilePlaying(const char fileNameUTF8[1024], int64_t time_ms) = 0;
        virtual void OnMediaFilePlayEnded(const char fileNameUTF8[1024]) = 0;
    protected:
        HjMediaFilePlayCallback() {}
    };

    class HjMediaFileRecordCallback
    {
    public:
        virtual ~HjMediaFileRecordCallback(){}
        virtual void OnMediaFileRecording(const char fileNameUTF8[1024], int64_t time_ms) = 0;
    protected:
        HjMediaFileRecordCallback() {}
    };

    enum MediaMessageTraceLevel {
        kMediaMessageTraceStateInfo = 0x0001,
        kMediaMessageTraceWarning = 0x0002,
        kMediaMessageTraceError = 0x0004,
    };

    class MediaMessageTraceCallback
    {
    public:
        virtual void OnMediaMessageLog(const char* message, int length, MediaMessageTraceLevel level) = 0;

    protected:
        virtual ~MediaMessageTraceCallback() {}
        MediaMessageTraceCallback() {}
    };
} // namespace hjav

#endif // _PLUGIN_MEDIA_MESSAGE_TYPEDEFS_H_
