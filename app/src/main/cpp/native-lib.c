// By Oleksiy Grechnyev
// The JNI entry point, a very thin wrapper to  glesmain

#include <jni.h>

#include "glesmain.h"

JNIEXPORT void JNICALL
Java_com_agrechnev_gles3fun1_JNILibrary_init(JNIEnv *env, jobject obj) {
    glesmain_init();
}

JNIEXPORT void JNICALL
Java_com_agrechnev_gles3fun1_JNILibrary_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    glesmain_resize(width, height);
}

JNIEXPORT void JNICALL
Java_com_agrechnev_gles3fun1_JNILibrary_draw(JNIEnv *env, jobject obj) {
    glesmain_draw();
}