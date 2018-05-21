/*
* \created lilian lilian@hujiang.com
* \date 2014-10-29
* \brief
*		the interface of audio-video engine.
*
* \Copyright (c) 2016 The HJAV project authors. All Rights Reserved.
*/

#ifndef HJAV_AV_ENGINE_H_
#define HJAV_AV_ENGINE_H_

#include "av_engine_defines.h"

namespace hjav {

class HJAVENGINE_DLLEXPORT AVEngine
{
public:
    static AVEngine* Create();
	static void Destory(AVEngine* engine);
    virtual ~AVEngine() {}
    
    /**
    * 设置日志输出
    * @param log_file           -[in]日志的路径-文件名
    * @param callback           -[in]日志的回调
    * @param enable             -[in]是否让引擎日志直接输出到控制台
    *
    *\note
    *   以下三种日志输出方式可同时存在。
    */
	virtual void SetTraceFile(const char* log_file) = 0;
    virtual void SetTraceCallback(hjav::HjAVTraceCallback* calllback) = 0;
    virtual void SetTraceConsole(bool enable) = 0;

    /**
    * 初始化
    *
    * @param user_id			-[in]用户id
	* @param support_video		-[in]是否支持视频
	* @param support_desktop	-[in]是否支持屏幕分享
    * @param test_only			-[in]是否是仅用于测试（自己发送给自己）
    *
    * @return -[参见HjRetCode]
    */
	virtual int Init(int user_id,
		bool support_video = false, 
		bool support_desktop = false, 
		bool test_only = false) = 0;

    /**
    * 为了版本兼容增加的临时接口(20150828)
    *1）在旧的教室中，无需调用，或置为false；
    *2）在群授课中，设置为true;
    * 
    * NOTE: 在Init()之后，其他接口之前调用；
    */
    virtual int SetNewEngineFlag(bool enable) = 0;

    /**
    * 加入房间
    *
    * @param room_id       -[in]房间id
    * @param server_ip     -[in]服务器ip
    * @param server_port   -[in]服务器port
    * @param tcp           -[in]是否TCP连接
    *
    * @return -[参见HjRetCode]
    */
    virtual int JoinRoom(unsigned int room_id, const char* server_ip, unsigned short server_port, 
                         bool tcp) = 0;

    /**
    * 离开房间
    *
    * @return -[参见HjRetCode]
    */
    virtual int LeaveRoom() = 0;

    //----------------------------------------------------------------------------
    //
    // network
    //
    //----------------------------------------------------------------------------

    /**
    * 设置服务器地址(需要更换服务器时才调用)
    *
    * @param ip            -[in]服务器ip
    * @param port          -[in]服务器port
    * @param tcp           -[in]是否TCP连接
    *
    * @return -[参见HjRetCode]
    */
	virtual int SetServerAddress(unsigned int room_id, const char* ip, unsigned short port, bool tcp) = 0;

	/**
	* 设置代理服务器
	*
	* @param proxy_type    -[in]代理类型[0：取消设置，1：使用浏览器设置，2：http，3：sock4,4：sock5]
	* @param proxy_host    -[in]代理服务器地址
	* @param proxy_port    -[in]代理服务器端口
	* @param username      -[in]用户名
	* @param password      -[in]密码
	* @param domain        -[in]域
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetProxy(
		unsigned short proxy_type,
		const char* proxy_host,
		unsigned short proxy_port,
		const char* username,
		const char* password,
		const char* domain) = 0;

	/**
	* 设置服务器连接类型，如果已经连接则断开重连
	*
	* @param tcp           -[in]是否TCP连接
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetConnectType(bool tcp) = 0;

    /**
    * 开始/停止 向房间广播自己的网络状况
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartBroadcastMyNetStat() = 0;
    virtual int StopBroadcastMyNetStat() = 0;

    /**
    * 获取我的outgoing网络状况
    *
    * @param stat           -[out]网络统计数据
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetOutgoingNetStat(HjNetStat* stat) = 0;

    /**
    * 获取我的incoming网络状况
    *
    * @param stat           -[out]网络统计数据
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetIncomingNetStat(HjNetStat* stat) = 0;

    /**
    * 获取其他人的网络状况[client->server方向的数据优先]
    *
    * @param userid         -[in]远端用户的ID
    * @param stat           -[out]网络统计数据
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetRemoteNetStat(int userid, HjNetStat* stat) = 0;

	/**
	* 获取所有人的网络状况(包括自己)[取上行、下行中的较差者]
	*
	* @param out_stats		-[out]网络统计数据
	*
	* @return >=0: 有效的返回用户数, <0: 参见HjRetCode
	*/
	virtual int GetAllUsersNetStat(HjNetStat out_stats[HJAV_MAX_USER_NUM]) = 0;

	/**
	* 注册网络观察者
	*
	* @param observer -[in] -观察者
	*
	* @return -[参见HjRetCode]
	*/
	virtual int RegisterNetworkObserver(HjNetwork* observer) = 0;

	/**
	* 反注册网络观察者
	*
	* @return -[参见HjRetCode]
	*/
	virtual int UnRegisterNetworkObserver() = 0;

    /**
    * 设置网络状况回调阈值
    * @param poor_lost          -[in]较差时丢包率(%)
    * @param bad_lost           -[in]非常差时丢包率(%)
    * @param poor_rtt           -[in]较差时rtt延时(ms)
    * @param bad_rtt            -[in]非常差时rtt延时(ms)
    */
    virtual int SetNetworkCallbackLimit(int poor_lost, int bad_lost, int poor_rtt, int bad_rtt) = 0;


    /**
    * 设置媒体传输指令类型
    * @param type               -[in]参见HjMediaTransportProtocol
    */
    virtual int SetMediaTransportProtocol(HjMediaTransportProtocol type) = 0;

    //----------------------------------------------------------------------------
    //
    // audio
    //
    //----------------------------------------------------------------------------

    /**
    * 开启/停止 捕获&发送语音
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartAudioSend() = 0;
    virtual int StopAudioSend() = 0;
    virtual bool AudioSending() const = 0;

    /**
    * 获得某用户的当前说话音量等级(0~10)
    *
    * @param user_id       -用户id
    * @param level         -[out]音量等级(0~10)
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetSpeechOutputLevel(int user_id, unsigned int& level) = 0;

    /**
    * 获得自己当前说话音量等级(0~10)
    *
    * @param level         -[out]音量等级(0~10)
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetSpeechInputLevel(unsigned int& level) = 0;

    /**
    * 设置操作系统麦克风静音
    *
    * @param enable        -是否静音
    *
    * @return -[参见HjRetCode]
    */
	virtual int SetMicrophoneMute(bool enable) = 0;
	virtual int GetMicrophoneMute(bool& enable) = 0;

    /**
    * 设置操作系统扬声器静音
    *
    * @param enable         -是否静音
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetSpeakerMute(bool enable) = 0;
    virtual int GetSpeakerMute(bool& enable) = 0;

	/**
	* 设置麦克风静音
	*
	* @param enable        -是否静音
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetInputMute(bool enable) = 0;
	virtual int GetInputMute(bool& enable) = 0;

	/**
	* 设置扬声器静音
	*
	* @param enable         -是否静音
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetOutputMute(bool enable) = 0;
	virtual int GetOutputMute(bool& enable) = 0;

    /**
    * 设置当前进程扬声器音量[0~255]
    *
    * @param volume         -扬声器音量[0~255]
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetSpeakerVolume(unsigned int volume) = 0;
    virtual int GetSpeakerVolume(unsigned int& volume) = 0;

    /**
    * 设置当前进程麦克风音量[0~255]
    *
    * @param volume         -扬声器音量[0~255]
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetMicVolume(unsigned int volume) = 0;
    virtual int GetMicVolume(unsigned int& volume) = 0;

	/**
	* 设置麦克风音量缩放等级[0.0, 10.0]
	* 0~1为音量缩小,1为正常音量,1~10为音量放大
	*
	* @param volume -[out] -麦克风音量[0.0, 10.0]
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetInputVolumeScaling(float scaling) = 0;

	/**
	* 获得麦克风音量缩放等级[0.0, 10.0]
	* 0~1为音量缩小,1为正常音量,1~10为音量放大
	*
	* @param volume -[out] -麦克风音量[0.0, 10.0]
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetInputVolumeScaling(float& scaling) = 0;

	/**
	* 设置扬声器音量缩放等级[0.0, 10.0]
	* 0~1为音量缩小,1为正常音量,1~10为音量放大
	*
	* @param scaling -[out] -缩放等级[0.0, 10.0]
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetOutputVolumeScaling(float scaling) = 0;

	/**
	* 获得扬声器音量缩放等级[0.0, 10.0]
	* 0~1为音量缩小,1为正常音量,1~10为音量放大
	*
	* @param scaling -[out] -缩放等级[0.0, 10.0]
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetOutputVolumeScaling(float& scaling) = 0;

    //----------------------------------------------------------------------------
    // audio advanced settings.
    //----------------------------------------------------------------------------

    /**
    * 设置语音编码类型
    *
    * @param codec_type    -参见HjAudioCodecType
    * @param bitrate       -比特率（0--引擎内部决定）
    *
    * @return -[参见HjRetCode]
	*/
	virtual int SetSendAudioCodec(int codec_type, int bitrate = 0) = 0;

	/**
	* 获得语音编码类型
	*
	* @param codec_type    -参见HjAudioCodecType
	* @param bitrate       -比特率（0--引擎内部决定）
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetSendAudioCodec(int& codec_type) = 0;

    /**
    * 设置自动增益
    *
    * @param enable        -是否开启
    * @param mode          -参见HjAgcModes
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetAGC(bool enable, int mode) = 0;
    virtual int GetAGC(bool &enable, int &mode) = 0;

    /**
    * 设置回声消除
    *
    * @param enable        -是否开启
    * @param mode          -参见HjEcModes
    * @param aecm_mode     -参见HjAecmModes
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetEcho(bool enable, int mode) = 0;
    virtual int GetEcho(bool &enable, int &mode) = 0;
    virtual int SetAECMMode(int aecm_mode) = 0;

    /**
    * 设置降噪
    *
    * @param enable        -是否开启
    * @param mode          -参见HjNsModes
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetNs(bool enable, int mode) = 0;
    virtual int GetNs(bool &enable, int &mode) = 0;

    /**
    * 设置静音检测/断续传输
    *
    * @param enable_vad    -是否开启VAD
    * @param enable_dtx    -是否开启DTX
    * @param vad_mode      -参见HjVadModes
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetVAD(bool enable_vad, bool enable_dtx, int vad_mode) = 0;
    virtual int GetVAD(bool& enable_vad, bool& enable_dtx, int& vad_mode) = 0;

    /**
    * 设置目标延迟
    *
    * @param delay_ms       -[in]延迟时间ms
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetTargetPlayoutDelay(int delay_ms) = 0;

    /**
    * 设置前向纠错(会增大流量)
    *
    * @param enable         -[in]是否启用
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetFECStatus(bool enable) = 0;

    //----------------------------------------------------------------------------
    // play/record audio file
    //----------------------------------------------------------------------------

    /**
    * 指定的文件当做音源
    *
    * @param fileNameUTF8           -文件路径
    * @param loop                   -是否循环播放
    * @param mixWithMicrophone      -true:文件与麦克风混合当音源; false:文件替换麦克风当音源;
    * @param format                 -文件格式
    * @param volumeScaling          -音量缩放比例
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartPlayingFileAsMicrophone(
        const char fileNameUTF8[1024],
        bool loop,
        bool mixWithMicrophone,
        HjFileFormats format,
        float volumeScaling) = 0;
    virtual int StopPlayingFileAsMicrophone() = 0;

    /**
    * 播放文件（只有自己能听到）
    *
    * @param fileNameUTF8           -文件路径
    *     or in_stream              -输入流
    * @param loop                   -是否循环播放
    * @param format                 -文件格式
    * @param callback               -通知录制进度的回调
    * @param volumeScaling          -音量缩放比例
    * @param startPointMs           -起始位置
    * @param stopPointMs            -结束位置
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartPlayingFileLocally(
        const char fileNameUTF8[1024],
        bool loop = false,
        HjFileFormats format = kHjFileFormatHjmFile,
        HjFilePlayCallback* callback = 0,
        float volumeScaling = 1.0,
        int startPointMs = 0,
        int stopPointMs = 0) = 0;
    virtual int StartPlayingFileLocally(
        HjInStream* in_stream,
        HjFileFormats format = kHjFileFormatHjmFile,
        HjFilePlayCallback* callback = 0,
        float volumeScaling = 1.0,
        int startPointMs = 0,
        int stopPointMs = 0) = 0;
    virtual int StopPlayingFileLocally() = 0;
    virtual bool IsPlayingFileLocally() const = 0;

    /**
    * 开始录音[房间中所有声音]
    *
    * @param fileNameUTF8           -播放器接口文件录音文件全路径名
    * @param format                 -文件格式
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartFileRecord(const char* fileNameUTF8,
                                HjFileFormats format = kHjFileFormatMp3File) = 0;
	virtual int StopFileRecord() = 0;
	virtual bool IsRecording() = 0;

    /**
    * 开始录音麦克风声音[到文件]
    *
    * @param fileNameUTF8           -录音文件全路径名
    *     or out_stream             -输出流
    * @param format                 -文件格式
    * @param callback               -通知录制进度的回调
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartRecordingMicrophone(const char fileNameUTF8[1024],
                                         HjFileFormats format = kHjFileFormatHjmFile,
                                         HjFileRecordCallback* callback = 0) = 0;
    virtual int StartRecordingMicrophone(HjOutStream* out_stream,
                                         HjFileFormats format = kHjFileFormatHjmFile,
                                         HjFileRecordCallback* callback = 0) = 0;
    virtual int StopRecordingMicrophone() = 0;
    virtual bool IsRecordingMicrophone() = 0;

    /**
    * 获取文件时长
    *
    * @param fileNameUTF8           -[in]录音文件路径名
    * @param durationMs             -[out]时长
    * @param format                 -[in]文件格式
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetFileDuration(const char fileNameUTF8[1024],
                                int* durationMs,
                                HjFileFormats format = kHjFileFormatHjmFile) const = 0;

	//----------------------------------------------------------------------------
	// start/stop audio test
	//----------------------------------------------------------------------------

	/**
	* 开始麦克风语音测试
	*
	* @return -[参见HjRetCode]
	*/
	virtual int StartMicrophoneTestWizard() = 0;

	/**
	* 停止麦克风语音测试
	*
	* @return -[参见HjRetCode]
	*/
	virtual int StopMicrophoneTestWizard() = 0;

	/**
	* 开始扬声器语音测试
	*
	* @return -[参见HjRetCode]
	*/
	virtual int StartSpeakerTestWizard(const char* utf8_play_file_wav) = 0;

	/**
	* 停止扬声器语音测试
	*
	* @return -[参见HjRetCode]
	*/
	virtual int StopSpeakerTestWizard() = 0;

	/**
	* 获得正在播放的测试文件当前音量等级
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetSpeakerTestLevel(unsigned int& level) = 0;

	/**
	* 获得正在捕获的测试麦克风当前音量等级
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetMicrophoneTestLevel(unsigned int& level) = 0;

    //----------------------------------------------------------------------------
    // audio device settings.
    //----------------------------------------------------------------------------

    /**
    * 获得录音设备数量
    *
    * @param device_num             -[out]设备数量
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetNumOfRecordingDevices(int &device_num) = 0;

    /**
    * 获得播放设备数量
    *
    * @param device_num             -[out]设备数量
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetNumOfPlayoutDevices(int &device_num) = 0;

    /**
    * 获得录音设备名
    *
    * @param index                  -[in]设备索引
    * @param strNameUTF8            -[out]设备名
    * @param strGuidUTF8            -[out]设备GUID
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetRecordingDeviceName(int index,
        char strNameUTF8[128],
        char strGuidUTF8[128]) = 0;

    /**
    * 获得播放设备名
    *
    * @param index                  -[in]设备索引
    * @param strNameUTF8            -[out]设备名
    * @param strGuidUTF8            -[out]设备GUID
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetPlayoutDeviceName(int index,
        char strNameUTF8[128],
        char strGuidUTF8[128]) = 0;

    /**
    * 设置录音设备
    *
    * @param index                  -[in]设备索引
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetRecordingDevice(int index) = 0;

    /**
    * 设置播放设备
    *
    * @param index                  -[in]设备索引
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetPlayoutDevice(int index) = 0;


    //----------------------------------------------------------------------------
    //
    // VIDEO
    //1)realtime; 2)desktop; 3)video file;
    //
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    // VIDEO--common
    //----------------------------------------------------------------------------
    /**
    * 设置发送编码信息
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @param codec_type             -[in] -编码类型（参见HjVideoCodecType）
    * @param width                  -[in] -图像宽
    * @param height,                -[in] -图像高
    * @param bitrate                -[in] -比特率
    * @param max_fps                -[in] -最大帧率
    * @param key_frame_interval     -[in] -关键帧间隔(ms)
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetVideoSendCodec(const HjVideoType& video_type,
                                  int codec_type,
                                  int width,
                                  int height,
                                  int bitrate,
                                  int max_fps,
                                  int key_frame_interval) = 0;

    /**
    * 设置发送的视频流模式（高清/标清/自动）
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @param send                   -[in] -设置类型，true-发送流, false-接收流
    * @param level_mode             -[in] -模式（高清/标清/自动）
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetVideoLevelMode(const HjVideoType& video_type, bool send, const HjVideoLevelMode& level_mode) = 0;
    virtual int GetVideoLevelMode(const HjVideoType& video_type, bool send, HjVideoLevelMode& level_mode) const = 0;

    /**
    * 捕获视频
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @return -[参见HjRetCode]
    */
    virtual int StartVideoCapture(const HjVideoType& video_type) = 0;
    virtual int StopVideoCapture(const HjVideoType& video_type) = 0;
    virtual bool VideoCapturing(const HjVideoType& video_type) const = 0;

    /**
    * 发送视频
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @return -[参见HjRetCode]
    */
    virtual int StartVideoSend(const HjVideoType& video_type) = 0;
    virtual int StopVideoSend(const HjVideoType& video_type) = 0;
    virtual bool VideoSending(const HjVideoType& video_type) const = 0;

    /**
    * 添加/删除用户的视频渲染窗口
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @param user_id                -[in] -用户id(id==自己，代表preview)
    * @param window                 -[in] -窗口 (ios: VideoRenderIosView)
    * @param z_order                -[in] -z序
	* @param left                   -[in] -左边起点（0~1）
	* @param top                    -[in] -顶边起点（0~1）
	* @param right                  -[in] -右边距（0~1）
	* @param bottom                 -[in] -下边距（0~1）
    *
    * @param renderer               -[in] -外部renderer.
    *
    * @return -[参见HjRetCode]
    */
    virtual int AddVideoRenderer(const HjVideoType& video_type,
                                 const int user_id,
                                 void* window,
                                 const unsigned int z_order,
                                 const float left,
                                 const float top,
                                 const float right,
                                 const float bottom) = 0;
    virtual int AddVideoExternalRenderer(const HjVideoType& video_type,
                                         const int user_id,
                                         HjExternalRenderer* renderer) = 0;
    virtual int RemoveVideoRenderer(const HjVideoType& video_type, const int user_id) = 0;

    /**
    * 开始/停止 接收指定用户的视频数据[默认为接收]
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @param user_id                -[in] -用户id
    *
    * @return -[参见HjRetCode]
    */
    virtual int StartVideoReceive(const HjVideoType& video_type, int user_id) = 0;
    virtual int StopVideoReceive(const HjVideoType& video_type, int user_id) = 0;

    /**
    * 设置视频没有数据时的静态图片
    *
    * @param video_type             -[in] -视频类型(参见HjVideoType)
    * @param preview_jpg_utf8       -[in] -静态图片
    *
    * @return -[参见HjRetCode]
    */
    // 设置视频预览窗口默认图片(在视频未启动时显示)
    virtual int SetVideoPreviewJPG(const HjVideoType& video_type, const char* preview_jpg_utf8) = 0;
    // 设置远端视频显示窗口默认图片(在视频未启动时显示)
    virtual int SetVideoRenderJPG(const HjVideoType& video_type, const char* render_jpg_utf8) = 0;
    // 设置远端视频数据超时时显示的图片(在视频数据超时时显示)
    virtual int SetVideoRenderTimeoutJPG(const HjVideoType& video_type, const char* render_timeout_jpg_utf8) = 0;

    //----------------------------------------------------------------------------
    // VIDEO--device settings
    //----------------------------------------------------------------------------

    /**
    * 获得视频设备名称，当返回-1时获取完成 [deprecated!]
    *
    * @param device_index           -[in] -设备索引，从0开始
    * @param device_name_utf8       -[out] -设备名
    * @param unique_id_utf8         -[out] -设备唯一编号
    *
    * @return -[返回-1时获取完成，否则返回设备列表中的位置]
    * e.g:
    * int i = 0;
    * while((i = GetVideoCaptureDevice(i,device_name_utf8, unique_id_utf8)) != -1)
    * {
    *		// add to list;
    *		i++;
    * }
    */
    virtual int GetVideoCaptureDevice(int device_index, char device_name_utf8[64], char unique_id_utf8[128]) = 0;

    /**
    * 获取视频采集设备数目
    *
    * @return -[>=0: 设备数目; <0: 失败]
    */
    virtual int NumberOfVideoDevice() = 0;

    /**
    * 获取设备信息
    *
    * @param device_index           -[in] -设备索引，从0开始
    * @param device_info            -[out] -设备信息
    *
    * @return -[参见HjRetCode]
    */
    virtual int GetVideoDevice(int device_index, HjVideoDeviceInfo* device_info) = 0;

    /**
    * 获取当前视频设备的索引
    *
    * @return -[>=0: 设备索引; <0: 失败]
    */
    virtual int CurrentVideoDevice() const = 0;

    /**
    * 设置视频设备[设置后需要调用者负责stop/start]
    *
    * @param device_index           -[in] -设备索引
    *
    * @return -[参见HjRetCode]
    */
    virtual int SetVideoDevice(int device_index) = 0;

#ifdef WIN32
    /**
    * 注册设备通知者
    *
    * @param hWnd                   -[in] -关联的窗口句柄
    * @param uMessageID             -[in] -消息ID(wParam==DBT_DEVICEARRIVAL is add, else is remove)
    *
    * @return -[参见HjRetCode]
    */
    virtual int RegDeviceNotification(void* hWnd, unsigned int uMessageID) = 0;
    virtual int UnRegDeviceNotification() = 0;
#endif //WIN32

	//----------------------------------------------------------------------------
	// VIDEO--desktop
	//----------------------------------------------------------------------------

	/**
	* 设置屏幕分享捕获范围
	*
	* @param left               -[in] -左
	* @param top                -[in] -上
	* @param right              -[in] -右
	* @param bottom             -[in] -下
	*
	* @return -[参见HjRetCode]
	*/
	virtual int SetDesktopCaptureRect(int left, int top, int right, int bottom) = 0;

    //----------------------------------------------------------------------------
    // VIDEO--videofile
    //----------------------------------------------------------------------------

    /**
    * 设置视频文件播放的回调
    *
    * @param callback           -[in] -回调指针, NULL-代表清除回调
    * @return -[参见HjRetCode]
    */
    virtual int RegisterVideoFileCallback(HjFilePlayCallback* callback) = 0;

    /**
    * 打开视频文件
    * 1)PLAY/STOP: StartVideoCapture/StopVideoCapture;
    * 2)SEND/STOP: StartVideoSend/StopVideoSend;
    *
    * @param file_name_utf8     -[in] -路径文件名
    * @param loop               -[in] -是否循环播放
    * @param loop               -[in] -是否只播放音频
    *
    * @return -[参见HjRetCode]
    */
    virtual int OpenVideoFile(const char file_name_utf8[1024], bool loop, bool only_audio = false) = 0;
    virtual int CloseVideoFile() = 0;
    virtual bool VideoFileOpened() const = 0;

    /**
    * 控制 文件播放逻辑
    *
    * @return -VideoFileDuration()返回的时间单位为ms.
    * @return -[参见HjRetCode]
    */
    virtual int PauseVideoFile() = 0;
    virtual int ResumeVideoFile() = 0;
    virtual bool VideoFilePlaying() const = 0;
    virtual long VideoFileDuration() const = 0;
    virtual int SeekVideoFile(long dest_ms) = 0;
    virtual int PreviewFirstVideoFrame(int width, int height, unsigned char* buffer, int& buffer_size) = 0;  //out ARGB

    /**
    * 设置视频文件播放音量
    * @param scaling            -音量缩放比率(default=1.0)[0.0, 2.0]
    * @note 
    * 1)0~1为音量缩小,1.0为正常音量,1.0~2.0为音量放大;
    * 2)>1.0可能会导致声音爆音，所以尽量不要>1.0；
    * @return -[参见HjRetCode]
    */
    virtual int SetVideoFileVolume(float scaling) = 0;
    virtual int GetVideoFileVolume(float& scaling) const = 0;

#ifdef _MSC_VER
	//----------------------------------------------------------------------------
	//
	// hook player
	//
	//----------------------------------------------------------------------------

	/**
	* 注册HOOK播放器观察者
	*
	* @param observer -[in] -观察者
	*
	* @return -[参见HjRetCode]
	*/
	virtual int RegisterHookPlayerObserver(HjHookPlayerObserver* observer) = 0;

	/**
	* 反注册HOOK播放器观察者
	*
	* @return -[参见HjRetCode]
	*/
	virtual int UnRegisterHookPlayerObserver() = 0;

	/**
	* 开始HOOK播放器
	*
	* @param soft -[in] -是否使用软件混音
	*
	* @param utf8_player_path -[in] -被HOOK的播放器路径
	*
	* @param utf8_dll_path -[in] -HOOK的播放器所使用的DLL路径（为空则使用当前exe下的默认路径）
	*
	* @return -[参见HjRetCode]
	*/
    virtual int StartHookPlayer(bool soft,
                                const char* utf8_player_path,
                                const char* utf8_dll_path) = 0;

	/**
	* 停止HOOK播放器
	*
	* @return -[参见HjRetCode]
	*/
	virtual int StopHookPlayer() = 0;

	virtual bool Hooking() = 0;
	/**
	* 重置所支持的播放器列表
	*
	* @return -[参见HjRetCode]
	*/
	virtual int ResetHookPlayerList() = 0;

	/**
	* 所支持的播放器数量
	*
	* @param count -[in] -支持的播放器数量
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetHookPlayerCount(int& count) = 0;

	/**
	* 获得所支持的播放器的详细信息
	*
	* @param index -[in] -索引
	*
	* @param utf8_key -[in] -播放器在注册表中的关键字
	*
	* @param utf8_display_name -[in] -播放器显示名
	*
	* @param utf8_display_icon -[in] -播放器图标所在路径（exe所在路径）
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetHookPlayerItem(
		int index,
		char utf8_key[1024],
		char utf8_display_name[1024],
		char utf8_display_icon[1024]) = 0;

	/**
	* 获得正在被HOOK的播放器的详细信息
	*
	* @param utf8_key -[in] -播放器在注册表中的关键字
	*
	* @param utf8_display_name -[in] -播放器显示名
	*
	* @param utf8_display_icon -[in] -播放器图标所在路径（exe所在路径）
	*
	* @return -[参见HjRetCode]
	*/
	virtual int GetCurrentPlayer(
		char utf8_key[1024],
		char utf8_display_name[1024],
		char utf8_display_icon[1024]) = 0;

	/**
	* 是否支持硬件混音
	*
	* @param suport -[in] -是否支持软件混音
	*
	* @return -[参见HjRetCode]
	*/
	virtual int IsSupportHardMixer(bool& suport) = 0;
#endif // _MSC_VER


    //----------------------------------------------------------------------------
    //
    // system actions (mobile only)
    //
    //----------------------------------------------------------------------------
    //app进入后台时调用
    virtual void OnAppDidEnterBackgroud() = 0;
    //app回到前台时调用
    virtual void OnAppDidBecameActive() = 0;

	virtual int ResetAudioDevice() = 0;
	virtual int SetLoudspeakerStatus(bool enable) = 0;
	virtual int GetLoudspeakerStatus(bool* enabled) const = 0;

protected:
    AVEngine() {}
};

} //namespace hjav




#ifdef __cplusplus
extern "C" {
#endif

//--------------------GLOBAL-COMMON----------------------------------
/*
\brief 创建/删除 引擎对象
*/
hjav::AVEngine* CreateHjAVEngine();
void DestroyHjAVEngine(hjav::AVEngine* engine);

#ifdef HJAV_INCLUDE_PLUGIN
void* CreatePlugin(hjav::HjPluginIID iid);
bool DestroyPlugin(hjav::HjPluginIID iid, void* plugin);
const char* GetPluginVersion(hjav::HjPluginIID iid);
#endif

/*
\brief 获取当前引擎的版本号
*/
const char* GetHjVersion();

//--------------------ANDROID----------------------------------
/*
\brief  设置/清除 JNI环境配置
\note:
1)在调用所有其他接口之前 设置;
2)在调用所有其他接口之后 清除;
*/
int SetHjAndroidObjects(void* javaVM, void* env, void* context);
void ClearHjAndroidObjects();
 
//--------------------IOS--------------------------------------
/*
\brief 创建/删除 用于视频渲染的UIView
\note:
1)AddVideoRenderer接口参数中的窗口必须是又以下接口创建；
*/
void CreateHjIosUIView(void** uiview);
void DeleteHjIosUIView(void* uiview);

//--------------------WINDOWS----------------------------------
/*
\brief 检测/设置 当前系统是否支持CoreAudioAPI
\note
1)此接口存在的原因是，因为检测时可能会有一定的阻塞，应用层可安排在一个后台线程中调用，避免阻塞UI。
*/
bool CheckSupportWinCoreAudio();
void SetWinCoreAudioIsSupport(bool support);

#ifdef __cplusplus
}
#endif

#endif // HJAV_AV_ENGINE_H_
