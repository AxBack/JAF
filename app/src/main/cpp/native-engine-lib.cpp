#include <jni.h>

#include "pch.h"
#include "jaf/engine.h"

#include "jaf/settings.h"

#include <map>

int id = 0;

std::map<int, JAF::Engine*> engines;

extern "C" {

JNIEXPORT jint JNICALL
Java_com_axb_jaf_NativeEngine_create(JNIEnv* pEnv, jobject /*thiz*/,
												  jobject assetManager)
{
    JAF::Engine* pEngine = new JAF::Engine;

	AAssetManager* pAssetManager = AAssetManager_fromJava(pEnv, assetManager);
	if(!pEngine->init(pAssetManager))
	{
		SAFE_DELETE(pEngine);
		return -1;
	}

	engines[id] = pEngine;
	int i = id;
	++id;
	return static_cast<jint>(i);
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_reset(JNIEnv* pEnv, jobject /*thiz*/, jint id, jstring internalFile)
{
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_destroy(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id)
{
	auto it = engines.find(id);
	if(it == engines.end())
		return;

	SAFE_DELETE(it->second);
	engines.erase(it);
	LOGI("engine destroyed");
}

JNIEXPORT jboolean JNICALL
Java_com_axb_jaf_NativeEngine_render(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id)
{
	auto it = engines.find(id);
	if(it != engines.end())
		return static_cast<jboolean>(it->second->render());
	else
		LOGI("No engine to render");
	return JNI_TRUE;
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_resume(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id)
{
	auto it = engines.find(id);
	if(it != engines.end())
		engines[id]->resume();
	else
		LOGE("No engine to resume");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_pause(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id)
{
	auto it = engines.find(id);
	if(it != engines.end())
		it->second->pause();
	else
		LOGE("No engine to pause");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_setSize(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, int w, int h)
{
	auto it = engines.find(id);
	if(it != engines.end())
		it->second->updateSize(w,h);
	else
		LOGE("No engine to set size to");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_onTouch(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, float x, float y)
{
	auto it = engines.find(id);
	if(it != engines.end())
		it->second->touch(x,y);
	else
		LOGE("No engine to touch");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_onDoubleTap(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, float x, float y)
{
	auto it = engines.find(id);
	if(it != engines.end())
		it->second->doubleTap(x,y);
	else
		LOGE("No engine to touch");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_onPinch(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, float diff)
	{
	auto it = engines.find(id);
	if(it != engines.end())
		it->second->pinch(diff);
	else
		LOGE("No engine to touch");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_onOffsetChanged(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, float x, float y)
{
    auto it = engines.find(id);
    if(it != engines.end())
        it->second->setOffset(x,y);
    else
        LOGE("No engine to touch");
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_immersiveMode(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jboolean enable)
{
	JAF::Settings::immersive(static_cast<bool>(enable));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_interactive(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jboolean enable)
{
	JAF::Settings::interactive(static_cast<bool>(enable));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_allowRocketDeviation(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jboolean allow)
{
	JAF::Settings::allowRocketDeviation(static_cast<bool>(allow));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_allowBurstDeviation(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jboolean allow)
{
	JAF::Settings::allowBurstDeviation(static_cast<bool>(allow));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_allowTrailDeviation(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jboolean allow)
{
	JAF::Settings::allowTrailDeviation(static_cast<bool>(allow));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_setNrBursts(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jint nr)
{
	JAF::Settings::nrBursts(static_cast<int>(nr));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_setMinNrRockets(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jint nr)
{
	JAF::Settings::minNrRockets(static_cast<int>(nr));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_setMaxNrRocketsPerSequence(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jint nr)
{
	JAF::Settings::maxNrRocketsPerSequence(static_cast<int>(nr));
}

JNIEXPORT void JNICALL
Java_com_axb_jaf_NativeEngine_setRotationSpan(JNIEnv* /*pEnv*/, jobject /*thiz*/, jint id, jint degrees)
{
	JAF::Settings::rotationSpan(static_cast<int>(degrees));
}

}