/*
*  Copyright (c) 2016 The AnyRTC project authors. All Rights Reserved.
*
*  Please visit https://www.anyrtc.io for detail.
*
* The GNU General Public License is a free, copyleft license for
* software and other kinds of works.
*
* The licenses for most software and other practical works are designed
* to take away your freedom to share and change the works.  By contrast,
* the GNU General Public License is intended to guarantee your freedom to
* share and change all versions of a program--to make sure it remains free
* software for all its users.  We, the Free Software Foundation, use the
* GNU General Public License for most of our software; it applies also to
* any other work released this way by its authors.  You can apply it to
* your programs, too.
* See the GNU LICENSE file for more info.
*/
#include "jRTMPGuestImpl.h"
#include "webrtc/api/java/jni/classreferenceholder.h"
#include "webrtc/api/java/jni/jni_helpers.h"
#include "webrtc/modules/utility/include/helpers_android.h"
#include<android/log.h>

#define TAG "org.anyrtc.anyrtmp" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

#define TAG "org.anyrtc.anyrtmp" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

JRTMPGuestImpl::JRTMPGuestImpl(jobject javaObj)
: m_pGuest(NULL)
, m_jJavaObj(NULL)
, m_jClass(NULL){
	if(javaObj)	{
		webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
		m_jJavaObj = ats.env()->NewGlobalRef(javaObj);
		m_jClass = reinterpret_cast<jclass> (ats.env()->NewGlobalRef(ats.env()->GetObjectClass(m_jJavaObj)));
	}
	m_pGuest = RTMPGuester::Create(*this);
}

JRTMPGuestImpl::~JRTMPGuestImpl(void){
	Close();
}

void JRTMPGuestImpl::Close(){
	if (m_pGuest) {
		m_pGuest->StopRtmpPlay();
		RTMPGuester::Destory(m_pGuest);
		m_pGuest = NULL;
	}

	if(m_jJavaObj)	{
		webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
		ats.env()->DeleteGlobalRef(m_jClass);
		m_jClass = NULL;
		ats.env()->DeleteGlobalRef(m_jJavaObj);
		m_jJavaObj = NULL;
	}
}

void JRTMPGuestImpl::OnRtmplayerOK() {
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	{
		// Get *** callback interface method id
		jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayerOK", "()V");
		// Callback with params
		jni->CallVoidMethod(m_jJavaObj, j_callJavaMId);
	}
}
void JRTMPGuestImpl::OnRtmplayerStatus(int cacheTime, int curBitrate,uint32_t curTime, double totalTime){
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	{
		// Get *** callback interface method id
		jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayerStatus", "(IIII)V");
		int tt = (int)totalTime;
		int ct = (curTime/1000);
		//LOGI("%d",tt);
		// Callback with params
		jni->CallVoidMethod(m_jJavaObj, j_callJavaMId, cacheTime, curBitrate,ct,tt);
	}
}
void JRTMPGuestImpl::OnRtmplayerCache(int time) {
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	{
		// Get *** callback interface method id
		jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayerCache", "(I)V");
		// Callback with params
		jni->CallVoidMethod(m_jJavaObj, j_callJavaMId, time);
	}
}
void JRTMPGuestImpl::OnRtmplayerClosed(int errcode) 
{
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	{
		// Get *** callback interface method id
		jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayerClosed", "(I)V");
		// Callback with params
		jni->CallVoidMethod(m_jJavaObj, j_callJavaMId, errcode);
	}
}

void JRTMPGuestImpl::OnGetPcmData(const void * p, const int len, const int type,const int){

}

void JRTMPGuestImpl::OnRtmplayerPlayStart(){

}
void JRTMPGuestImpl::OnRtmplayerPlayStop() {

}
void JRTMPGuestImpl::OnRtmplayer1stVideo() {

}
void JRTMPGuestImpl::OnRtmplayer1stAudio() {
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayer1stAudio", "()V");
	jni->CallVoidMethod(m_jJavaObj, j_callJavaMId);

}
void JRTMPGuestImpl::OnRtmplayerConnectionFailed(int a) {
	webrtc::AttachThreadScoped ats(webrtc_jni::GetJVM());
	JNIEnv* jni = ats.env();
	jmethodID j_callJavaMId = webrtc_jni::GetMethodID(jni, m_jClass, "OnRtmplayerConnectionFailed", "(I)V");
	jni->CallVoidMethod(m_jJavaObj, j_callJavaMId, a);
}