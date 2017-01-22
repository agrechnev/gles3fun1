//
// Created by Oleksiy Grechnyev on 1/18/2017.
// Create the camera matrix for opengles (projection * view)
//

#include "glcamera.h"

// log tag
#define LOG_TAG "glcamera.c"

// Set the camera matrix based on a camera object
void glcamera_matrix(ESMatrix *matrix, glcamera_Camera *camera) {
    ESMatrix view, proj;

    esMatrixLoadIdentity(&view);
    esMatrixLookAt(&view,
                   camera->eyeX, camera->eyeY, camera->eyeZ,   // Eye (camera) position
                   camera->cenX, camera->cenY, camera->cenZ,    // Center (look at) position
                   camera->upX, camera->upY, camera->upZ); // up vector

    esMatrixLoadIdentity(&proj);
    esPerspective(&proj, camera->angle, camera->aspect, camera->minD, camera->maxD);

    esMatrixMultiply(matrix, &view, &proj);
}