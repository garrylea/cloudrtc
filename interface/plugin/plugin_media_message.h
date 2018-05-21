/////////////////////////////////////////////////////////////////////////////
// Name:        plugin_media_message.h
// Purpose:     
// Author:      yangfuqiang
// Modified by: 
// Created:     2017-02-16 15:58:55 
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#ifndef _PLUGIN_MEDIA_MESSAGE_H_
#define _PLUGIN_MEDIA_MESSAGE_H_

#include "plugin_media_message_typedefs.h"

namespace hjav {
    class PluginMediaMessage {
    public:
        static PluginMediaMessage* Create();
        static void Destory(PluginMediaMessage* plugin);
        static const char* GetVersion();

        //----------------------------------------------------------------------------
        // trace
        //----------------------------------------------------------------------------
        /**
        * 设置日志输出(注意：iOS&mac请使用avengine中的日志接口)
        * @param log_file           -[in]日志的路径-文件名
        * @param callback           -[in]日志的回调
        * @param enable             -[in]是否让引擎日志直接输出到控制台
        *
        * \note
        *   以下三种日志输出方式可同时存在。
        */
        virtual void SetTraceFile(const char* log_file) = 0;
        virtual void SetTraceCallback(MediaMessageTraceCallback* calllback) = 0;
        virtual void SetTraceConsole(bool enable) = 0;

        //----------------------------------------------------------------------------
        // audio playing
        //----------------------------------------------------------------------------
        /**
        * 播放文件
        *
        * @param fileNameUTF8           -文件路径
        *
        * @param callback               -通知录制进度的回调
        *
        * @param format                 -文件格式
        *
        * @param volumeScaling          -音量缩放比例[0.0,1.0)->缩小，[1.0,1.0]->不缩放，(1.0,10.0]->放大
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int StartPlayingFileLocally(
            const char fileNameUTF8[1024],
            HjMediaFilePlayCallback* callback = 0,
            HjMediaFileFormats format = kHjMediaFileFormatMp3,
            float volumeScaling = 1.0) = 0;
        
        /**
        * 停止播放文件
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int StopPlayingFileLocally() = 0;

        /**
        * 是否正在播放文件
        *
        * @return -[正在播放文件返回true，否则返回false]
        */
        virtual bool IsPlayingFileLocally() const = 0;

        /**
        * 获得当前播放进行的毫秒数
        *
        * @return -[当前播放进行的毫秒数]
        */
        virtual int64_t GetPlayingCurrentDurationMS() = 0;

        /**
        * 获得当前播放的文件的毫秒数
        *
        * @return -[当前播放的文件的毫秒数]
        */
        virtual int64_t GetPlayingTotalDurationMS() = 0;

        /**
        * 获得播放文件实时音量等级
        *
        * @param level         -[out]音量等级[0~9]
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetPlayingLevel(unsigned int& level) = 0;

        virtual int PausePlaying() = 0;
        virtual int ResumePlaying() = 0;
        virtual bool IsPlayingPaused() const = 0;

        virtual int SeekPlaying(int pos) = 0;

        //----------------------------------------------------------------------------
        // audio recording
        //----------------------------------------------------------------------------
        /**
        * 开始录音
        *
        * @param fileNameUTF8           -录音文件全路径名
        *
        * @param callback               -通知录制进度的回调
        *
        * @param format                 -文件格式
        *
        * @param volumeScaling          -音量缩放比例[0.0,1.0)->缩小，[1.0,1.0]->不缩放，(1.0,10.0]->放大
        *
        * @param sample_rate            -采样率
        *
        * @param channels               -声道
        *
        * @param bit_rate               -比特率(kbps)
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int StartRecordingMicrophone(
            const char fileNameUTF8[1024],
            HjMediaFileRecordCallback* callback = 0,
            HjMediaFileFormats format = kHjMediaFileFormatMp3,
            float volumeScaling = 1.0,
            int sample_rate = 8000,
            int channels = 1,
            float bit_rate = 16.f) = 0;

        /**
        * 停止录音
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int StopRecordingMicrophone() = 0;

        /**
        * 是否正在录音
        *
        * @return -[正在录音返回true，否则返回false]
        */
        virtual bool IsRecordingMicrophone() = 0;

        /**
        * 获得当前录制进行的毫秒数
        *
        * @return -[当前录制进行的毫秒数]
        */
        virtual int64_t GetRecordingCurrentDurationMS() = 0;

        /**
        * 获得录制文件实时音量等级
        *
        * @param level         -[out]音量等级[0~9]
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetRecordingLevel(unsigned int& level) = 0;

        //----------------------------------------------------------------------------
        // audio volume & settings
        //----------------------------------------------------------------------------
        /**
        * 设置当前进程扬声器音量[0~255]
        *
        * @param volume         -扬声器音量[0~255]
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int SetSpeakerVolume(unsigned int volume) = 0;
        virtual int GetSpeakerVolume(unsigned int& volume) = 0;

        /**
        * 设置当前进程麦克风音量[0~255]
        *
        * @param volume         -扬声器音量[0~255]
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int SetMicVolume(unsigned int volume) = 0;
        virtual int GetMicVolume(unsigned int& volume) = 0;

        /**
        * 获得录音设备数量
        *
        * @param device_num             -[out]设备数量
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetNumOfRecordingDevices(int &device_num) = 0;

        /**
        * 获得播放设备数量
        *
        * @param device_num             -[out]设备数量
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetNumOfPlayoutDevices(int &device_num) = 0;

        /**
        * 获得录音设备名
        *
        * @param index                  -[in]设备索引
        * @param strNameUTF8            -[out]设备名
        * @param strGuidUTF8            -[out]设备GUID
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetRecordingDeviceName(
            int index,
            char strNameUTF8[128],
            char strGuidUTF8[128]) = 0;

        /**
        * 获得播放设备名
        *
        * @param index                  -[in]设备索引
        * @param strNameUTF8            -[out]设备名
        * @param strGuidUTF8            -[out]设备GUID
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int GetPlayoutDeviceName(
            int index,
            char strNameUTF8[128],
            char strGuidUTF8[128]) = 0;

        /**
        * 设置录音设备
        *
        * @param index                  -[in]设备索引
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int SetRecordingDevice(int index) = 0;

        /**
        * 设置播放设备
        *
        * @param index                  -[in]设备索引
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int SetPlayoutDevice(int index) = 0;

        /**
        * 设置扬声器播放
        *
        * @param enable                  -[in]是否是扬声器播放
        *
        * @return -[成功返回0，否则返回-1]
        */
        virtual int SetLoudspeakerStatus(bool enable) = 0;
        virtual int GetLoudspeakerStatus(bool* enabled) = 0;

    protected:
        PluginMediaMessage() {}
        virtual ~PluginMediaMessage() {}
    };
}

#ifdef __cplusplus
extern "C" {
#endif

    hjav::PluginMediaMessage* CreatePluginMediaMessage();
    void DestoryPluginMediaMessage(hjav::PluginMediaMessage* plugin);
    const char* GetPluginMediaMessageVersion();
    //----------------------------------------------------------------------------
    // android
    //----------------------------------------------------------------------------
    /**
    * 设置 JNI环境配置
    * 在调用所有其他接口之前 设置;
    */
    bool SetPluginMediaMessageAndroidObjects(void* javaVM, void* env, void* context);
    void ClearPluginMediaMessageAndroidObjects();

#ifdef __cplusplus
}
#endif

#endif // _PLUGIN_MEDIA_MESSAGE_H_
