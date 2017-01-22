/* By Oleksiy Grechnyev 2017
Create shaders and shader program
 from 2 constant strings */

#include <stdio.h>
#include <stdlib.h>

// #include "esUtil.h"

#include "gles.h"
#define LOG_TAG "shaders.c"


/* Create shaders and the shader program from external files*/
GLuint shaders_createProgram(const char *vertexShaderSource, const char *fragmentShaderSource){
    
    // Read files
    if (vertexShaderSource==NULL || fragmentShaderSource==NULL) {
        LOGE("Null shader source.");
        return 0;
    }
    

    // Build the shader program
    // Vertex shader

    LOGI("Compiling vertex shader");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for errors
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        LOGE("Error: Cannot compile shader");
        LOGE(" ", infoLog);
        return 0;
    }
    
    // Fragment shader
    LOGI("Compiling fragment shader");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);
    // Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        LOGE("Error: Cannot compile shader");
        LOGE(" ", infoLog);
        return 0;
    }
    
    // Shader program
    LOGI("Linking shader program");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        LOGE("Error: Cannot link shader program");
        LOGE(" ", infoLog);
        return 0;
    }
    
    // Delete shaders: we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
