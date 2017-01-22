//
// Created by Oleksiy Grechnyev on 1/17/2017.
// Wrapper for OpenGLES, includes logger
//

#ifndef GLES_H
#define GLES_H


#include <GLES3/gl3.h>
#include <android/log.h>

// Android logger, needs LOG_TAG
// #define LOG_TAG "default"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

// TRUE and FALSE

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


#endif //GLES_H
