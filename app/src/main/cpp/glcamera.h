//
// Created by Oleksiy Grechnyev on 1/18/2017.
// Create the camera matrix for opengles (projection * view)
//

#ifndef GLCAMERA_H
#define GLCAMERA_H

#include "gles.h"
#include "esTransform.h"

// The OpenGL Camera object, see the fields below for description
// All fields must be initialized by hand before creating the camera matrix
typedef struct glcamera_Camera {
    // Eye (Camera origin)
    GLfloat eyeX, eyeY, eyeZ;

    // Center (where to look at)
    GLfloat cenX, cenY, cenZ;

    // The UP axis
    GLfloat upX, upY, upZ;

    // The min and max distance
    GLfloat minD, maxD;

    // The width/height aspect ratio
    GLfloat aspect;

    // The camera viewport angle in degrees (for now)
    GLfloat angle;
} glcamera_Camera;

// Set the camera matrix based on a camera object
void glcamera_matrix(ESMatrix *matrix, glcamera_Camera *camera);

#endif //GLCAMERA_H
