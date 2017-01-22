/* By Oleksiy Grechnyev 2016
Create shaders and shader program */

#ifndef SHADERS_H
#define SHADERS_H

#include "gles.h"
/* Create shaders and the shader program from source codes in strings */
GLuint shaders_createProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

#endif
