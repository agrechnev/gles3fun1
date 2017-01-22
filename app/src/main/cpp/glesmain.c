//
// Created by Oleksiy Grechnyev on 1/17/2017.
// Main GLES file
//

#include <time.h>
#include <math.h>
#include <stdlib.h>

// GLES+LOG
#include "gles.h"

// log tag
#define LOG_TAG "glesmain.c"

// The modules
#include "shaders.h"
#include "vao.h"
#include "rgbtex.h"
#include "userdata.h"
#include "uniformcache.h"
#include "esTransform.h"
#include "glcamera.h"

// All global data is here
userdata_Userdata global;

/////////////////////////////////////////////
// Some functions

// Random float between 0 and 1
float glesmain_randf() {
    return (float) rand() / (float) RAND_MAX;
}

// Random unit 3-vector with spherical distribution
void glesmain_randUV3(float *x, float *y, float *z) {
    // Theta and phi
    float t = acos(2 * glesmain_randf() - 1);
    float p = M_PI * 2 * glesmain_randf();

    *x = sin(t) * cos(p);
    *y = sin(t) * sin(p);
    *z = cos(t);
}

//////////////////////////////////////
// Init my GLES app
void glesmain_init() {

    // OpenGL Options
    glEnable(GL_DEPTH_TEST);

    // Create shaders + the program

    // Vertex shader
    char vShaderStr[] =
            "#version 300 es\n"
                    "layout(location = 0) in vec3 pos;\n"
                    "layout(location = 2) in vec2 tex;\n"
                    "out vec2 texCoord;\n"
                    "uniform mat4 model;\n"
                    "uniform mat4 camera;\n"
                    "void main()\n"
                    "{\n"
                    "   gl_Position =  camera*model*vec4(pos, 1.0f);\n"
                    "   texCoord =  vec2(tex.x, 1.0f-tex.y);;\n"
                    "}\n";

    // Fragment shader
    char fShaderStr[] =
            "#version 300 es                              \n"
                    "precision mediump float;                     \n"
                    "in vec2 texCoord;                            \n"
                    "out vec4 fragColor;                          \n"
                    "uniform sampler2D ourTexture;                \n"
                    "void main()                                  \n"
                    "{                                            \n"
                    "   fragColor = texture(ourTexture, texCoord);\n"
                    "}                                            \n";


    global.program = shaders_createProgram(vShaderStr, fShaderStr);
    if (!global.program) {
        LOGE("Cannot create shader program");
        return;
    }

    // Create the uniform cache for the program
    uniformcache_create(&(global.cache), global.program);

    // Create a cube
    // VAO object  XYZ_ST
    GLfloat vVertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    // Create the VAO object
    vao_create(&(global.vaoObject), vVertices, sizeof(vVertices), NULL, 0, VAO_XYZST);

    // Set up a trivial texture
    // 2 x 2 Image, 3 bytes per pixel (R, G, B)
    GLubyte pixels[4 * 3] =
            {
                    255, 0, 0, // Red
                    0, 255, 0, // Green
                    0, 0, 255, // Blue
                    255, 255, 0 // Yellow
            };
    global.texture = rgbtex_createRGB(pixels, 2, 2);

    // Set the camera (except aspect)
    global.camera.eyeX = 0.0f;
    global.camera.eyeY = 1.0f;
    global.camera.eyeZ = 7.0f;

    global.camera.cenX = 0.0f;
    global.camera.cenY = 0.0f;
    global.camera.cenZ = 0.0f;

    global.camera.upX = 0.0f;
    global.camera.upY = 1.0f;
    global.camera.upZ = 0.0f;

    global.camera.minD = 1.0;
    global.camera.maxD = 20.0;

    global.camera.angle = 45.0;

    // Random rotation axis
    glesmain_randUV3(&global.rotX, &global.rotY, &global.rotZ);

    // Finally, the clear color (cyan)
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

//////////////////////////////////////////////////////////////////////////////////

// Set the viewport size
void glesmain_resize(int width, int height) {
    glViewport(0, 0, width, height); // Set viewport
    global.width = width; // Save data
    global.height = height;
    global.camera.aspect = (GLfloat) width / (GLfloat) height; // Set camera aspect
}


//////////////////////////////////////////////////////////////////////////////////
// Draw the frame
void glesmain_draw() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use program
    glUseProgram(global.program);

    // Use texture
    glBindTexture(GL_TEXTURE_2D, global.texture);

    // Set the matrices as uniforms
    // Camera matrix
    ESMatrix cameraMatrix;

    glcamera_matrix(&cameraMatrix, &global.camera); // Create the camera matrix

    // transpose = false
    glUniformMatrix4fv(global.cache.camera, 1, GL_FALSE, (const GLfloat *) &cameraMatrix.m);

    // Model matrix
    // Get the time as float in seconds since an arbitrary origin
    GLfloat niceTime = (GLfloat) clock() / CLOCKS_PER_SEC;

    ESMatrix modelMatrix;
    esMatrixLoadIdentity(&modelMatrix);
    esRotate(&modelMatrix, 120 * niceTime, global.rotX, global.rotY, global.rotZ);

    glUniformMatrix4fv(global.cache.model, 1, GL_FALSE, (const GLfloat *) &modelMatrix.m);

    // Draw VAO
    vao_draw(&(global.vaoObject));
}
