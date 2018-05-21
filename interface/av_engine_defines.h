/*
* \created lilian lilian@hujiang.com
* \date 2014-10-29
* \brief
*		defines for audio-video engine.
*
* \Copyright (c) 2014 The HJAV project authors. All Rights Reserved.
*/

#ifndef HJAV_AV_ENGINE_DEFINES_H_
#define HJAV_AV_ENGINE_DEFINES_H_

#ifdef HJAVENGINE_EXPORT
#define HJAVENGINE_DLLEXPORT _declspec(dllexport)
#else
#ifdef WIN32
#define HJAVENGINE_DLLEXPORT _declspec(dllimport)
#else
#define HJAVENGINE_DLLEXPORT
#endif //WIN32
#endif //HJAVENGINE_EXPORT

#define HJAV_LOG_TAG				"HJAV"
#define HJAV_VERSION				"3.1.0.22"
#define HJAV_MAX_USER_NUM			64

// #define HJAV_INCLUDE_PLUGIN

namespace hjav {

#ifdef HJAV_INCLUDE_PLUGIN
enum HjPluginIID {
    kIIDMediaMessage = 1,
};
#endif

enum HjRetCode {
    kHjRetOK                            = 0,
    kHjRetUnknown                       = -1,
    kHjRetNotInit                       = -2,
    kHjRetAlreadyExist                  = -3,
    kHjRetParamError                    = -4,
};

enum HjTraceLevel {
    kHjTraceError                       = 1,
    kHjTraceWarning                     = 2,
    kHjTraceInfo                        = 3,
    kHjTraceDebug                       = 4,
};

//TODO(lilian):编码信息直接说出 是否合适?
enum HjAudioCodecType {
    kHjAudioCodecIsac32k1ch             = 1,
    kHjAudioCodecIsac16k1ch             = 2,
    kHjAudioCodecIlbc                   = 3,
    kHjAudioCodecAacEld32k2ch           = 4,
    kHjAudioCodecAacEld16k1ch           = 5,   //NOTE:此种编码与engine1.0不兼容，暂时勿用。[打点]
    kHjAudioCodecOpus48k2ch             = 6,
    kHjAudioCodecOpus16k1ch             = 7,
    kHjAudioCodecOpus8k1ch              = 8,
};

// type of Automatic Gain Control
enum HjAgcModes                  
{
    // previously set mode
    kHjAgcUnchanged                     = 0,
    // platform default
    kHjAgcDefault                       = 1,              
    // adaptive mode for use when analog volume control exists (e.g. for PC softphone)
    kHjAgcAdaptiveAnalog                = 2,
    // scaling takes place in the digital domain (e.g. for conference servers and embedded devices)
    kHjAgcAdaptiveDigital               = 3,
    // can be used on embedded devices where the capture signal level is predictable
    kHjAgcFixedDigital                  = 4,
};

// type of Echo Control
enum HjEcModes
{
    kHjEcUnchanged = 0,          // previously set mode
    kHjEcDefault,                // platform default
    kHjEcConference,             // conferencing default (aggressive AEC)
    kHjEcAec,                    // Acoustic Echo Cancellation
    kHjEcAecm,                   // AEC mobile
};

// mode of AECM
enum HjAecmModes
{
    kHjAecmQuietEarpieceOrHeadset = 0,
    // Quiet earpiece or headset use
    kHjAecmEarpiece,             // most earpiece use
    kHjAecmLoudEarpiece,         // Loud earpiece or quiet speakerphone use
    kHjAecmSpeakerphone,         // most speakerphone use (default)
    kHjAecmLoudSpeakerphone      // Loud speakerphone
};

// type of Noise Suppression
enum HjNsModes    
{
    kHjNsUnchanged = 0,             // previously set mode
    kHjNsDefault,                   // platform default
    kHjNsConference,                // conferencing default
    kHjNsLowSuppression,            // lowest suppression
    kHjNsModerateSuppression,
    kHjNsHighSuppression,
    kHjNsVeryHighSuppression,       // highest suppression
};

// degree of bandwidth reduction
enum HjVadModes          
{
    kHjVadConventional = 0,      // lowest reduction
    kHjVadAggressiveLow,
    kHjVadAggressiveMid,
    kHjVadAggressiveHigh         // highest reduction
};

enum HjFileFormats
{
    kHjFileFormatWavFile                = 1,
    kHjFileFormatCompressedFile         = 2,
    kHjFileFormatAviFile                = 3,
    kHjFileFormatPreencodedFile         = 4,
    kHjFileFormatPcm16kHzFile           = 5,
    kHjFileFormatPcm8kHzFile            = 6,
    kHjFileFormatPcm32kHzFile           = 7,
    kHjFileFormatMp3File                = 8,
    kHjFileFormatHjmFile                = 9,
};

enum HjVideoCodecType
{
    kHjVideoCodecUnknown = -1,
    kHjVideoCodecH264 = 1,
    kHjVideoCodecI420 = 2,
};

enum HjMediaTransportProtocol
{
    kHjMediaTransportOld = 0,
    kHjMediaTransportNew,               //default.
    kHjMediaTransportNewNew,
};

enum HjNetLevel
{
    kHjNetGood = 0,
    kHjNetNormal,
    kHjNetPoor,
    kHjNetBad,
    kHjNetDisconnect,
};

enum HjVideoLevelMode
{
    kHjVideoModeAuto = 0,
    kHjVideoModeHD,
    kHjVideoModeSD,
};

struct HjVideoDeviceInfo
{
    HjVideoDeviceInfo() {
        index = 0;
        camara_face = 0;
        device_name_utf8[63] = 0;
        unique_id_utf8[127] = 0;
    }
    int index;
    int camara_face;        //see also: HjCamaraFace
    char device_name_utf8[64];
    char unique_id_utf8[128];
};

enum HjCamaraFace
{
    kHjCamaraFaceUnknown = 0,
    kHjCamaraFaceFront,
    kHjCamaraFaceBack,
};

enum HjVideoType
{
    kHjVideoRealtime = 0,
    kHjVideoDesktop,
    kHjVideoFile,
};

class HjExternalRenderer
{
public:
    // This method will be called when the stream to be rendered changes in
    // resolution or number of streams mixed in the image.
    virtual int FrameSizeChange(int width,
                                int height,
                                int number_of_streams) = 0;

    // This method is called when a new frame should be rendered.
    // This frame is I420 data.
    virtual int DeliverFrame(unsigned char* buffer,
                             int buffer_size,
                             unsigned int timestamp,
                             // Handle of the underlying video frame.
                             void* handle) = 0;

    // Returns true if the renderer supports textures. DeliverFrame can be called
    // with NULL |buffer| and non-NULL |handle|.
    virtual bool IsTextureSupported() = 0;

    // This method is called before a new frame should be rendered.
    // Get the current render window's size.
    virtual bool GetWindowSize(int& width, int& height) { return false; }

    virtual ~HjExternalRenderer()
    {
    }
};

struct HjNetStat
{
    HjNetStat() : uid(0), rtt_ms(0), raw_lost_rate(.0f), lost_rate(.0f), net_level(0)
    {
    }

	int uid;
    int rtt_ms;
    float raw_lost_rate;        //原始丢包率[未加丢包重传]，单位:%
    float lost_rate;            //丢包率[加入丢包重传]，单位:%
    int net_level;              //参见: HjNetLevel
};

#ifdef _MSC_VER
class HjHookPlayerObserver
{
public:
	virtual ~HjHookPlayerObserver() {}

	/**
	* 被HOOK的播放器结束进程
	*
	* @return -[无返回值]
	*/
	virtual void OnHookPlayerExit() = 0;

protected:
	HjHookPlayerObserver() {}
};
#endif

class HjAVTraceCallback
{
public:
    virtual void Print(const char* message, int length, HjTraceLevel level) = 0;

protected:
	virtual ~HjAVTraceCallback() {}
	HjAVTraceCallback() {}
};

class HjNetwork
{
public:
	virtual void OnNetworkFailed() = 0;
    virtual void OnNetworkBad(float lostrate, int delay) = 0;
    virtual void OnNetworkPoor(float lostrate, int delay) = 0;
    //note: need change engine server address.
    virtual void changeServer() = 0;

protected:
	virtual ~HjNetwork() {}
	HjNetwork() {}
};

class HjFilePlayCallback
{
public:
    virtual ~HjFilePlayCallback(){}
    virtual void OnPlaying(const char fileNameUTF8[1024], const long timeMs) = 0;
    virtual void OnPlayEnded(const char fileNameUTF8[1024]) = 0;
protected:
    HjFilePlayCallback() {}
};

class HjFileRecordCallback
{
public:
    virtual ~HjFileRecordCallback(){}
    virtual void OnRecording(const char fileNameUTF8[1024], const int timeMs) = 0;
protected:
    HjFileRecordCallback() {}
};

class HjInStream
{
public:
    virtual int Read(void *buf, int len) = 0;
    virtual bool EofRead() const = 0;
    virtual int Rewind() { return -1; }
    virtual ~HjInStream() {}
protected:
    HjInStream() {}
};

class HjOutStream
{
public:
    virtual bool Write(const void *buf, int len) = 0;
    virtual int Rewind() { return -1; }
    virtual ~HjOutStream() {}
protected:
    HjOutStream() {}
};

} // namespace hjav
#endif //HJAV_AV_ENGINE_DEFINES_H_
