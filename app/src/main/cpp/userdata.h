//
// Created by Oleksiy Grechnyev on 1/18/2017.
// A structure for all global data, application specific

#ifndef USERDATA_H
#define USERDATA_H

#include "gles.h"
#include "uniformcache.h"
#include "vao.h"
#include "glcamera.h"

typedef struct userdata_Userdata {

    GLuint program;   // The active program
    vao_Vao vaoObject; // The model
    GLuint texture;  // The texture
    uniformcache_UniformCache cache; // The uniform cache
    GLuint width, height; // Dimensions

    glcamera_Camera camera; // All camera data

    // Cube rotation axis (random)
    GLfloat rotX, rotY, rotZ;

} userdata_Userdata;

#endif //USERDATA_H
