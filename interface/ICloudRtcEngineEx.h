
#pragma once
#include "ICloudRtcEngine.h"
#include <string>


namespace cloudRtc {
namespace rtcEngine {

class RtcContext;

class IRtcEngineLogHandler
{
public:
    virtual void onPrint(const char* message, int length, LOG_LEVEL_TYPE level) = 0;

protected:
    virtual ~IRtcEngineLogHandler() {}
    IRtcEngineLogHandler() {}
};

//full feature definition of rtc engine interface
class IRtcEngineEx : public IRtcEngine
{
public:
    static const char* getSdkVersion(int* build);
public:
    virtual ~IRtcEngineEx() {}
    virtual int initializeEx(const void* context) = 0;
    virtual int setVideoCanvas(const void* canvas) = 0;
    virtual int setParameters(const char* parameters) = 0;
    /**
    * get multiple parameters.
    */
    virtual int getParameters(const char* key, void* result) = 0;
    virtual int setProfile(const char* profile, bool merge) = 0;
    virtual int getProfile(void* result) = 0;
    virtual int notifyNetworkChange(void* networkInfo) = 0;
    virtual int sendReportMessage(const char* data, size_t length, int type) = 0;
    virtual int getOptionsByVideoProfile(int profile, void* options) = 0;
    virtual RtcContext* getRtcContext() = 0;
    virtual int setLogCallback(bool enabled) = 0;
	virtual int makeQualityReportUrl(const char* channel, uid_t listenerUid, uid_t speakerUid, QUALITY_REPORT_FORMAT_TYPE format, cloudRtc::util::AString& url) = 0;

    /**
    * get SHA1 values of source files for building the binaries being used, for bug tracking.
    */
    virtual const char* getSourceVersion() const = 0;

    virtual int reportWebAgentVideoStats(const void* stats) = 0;

    virtual int printLog(int level, const char* message) = 0;
    /**
    * Specify video stream parameters based on video profile
    * @param [in] width
    *        width of video resolution in pixel
    * @param [in] height
    *        height of video resolution in pixel
    * @param [in] frameRate
    *        frame rate in fps
    * @param [in] bitrate
    *        bit rate in kbps
    * @return return 0 if success or an error code
    */
    virtual int setVideoProfileEx(int width, int height, int frameRate, int bitrate) = 0;
    virtual int postRequest(void* pk) = 0;
    virtual int reportArgusCounters(int *counterId, int *value, int count, uid_t uid) = 0;

    /**
    * private interface for debug
    * output log to console
    */
    virtual int setLogConsole(bool enable) = 0;

    /**
    * private interface for cctalk
    * output log to callback, cctalk upload it bi
    */
    virtual int setLogHandler(IRtcEngineLogHandler* log_handler) = 0;
};

} // namespace cloudRtc
} // namespace rtcEngine
