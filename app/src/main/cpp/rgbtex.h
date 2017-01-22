/* By Oleksiy Grechnyev 2016
Create a simple RGB texture from an array
I am too lazy to load files now */
#ifndef RGBTEX_H
#define RGBTEX_H

#include "gles.h"

// Create an RGB texture from an array of bytes
GLuint rgbtex_createRGB(GLubyte *pixels, GLsizei width, GLsizei height);

#endif