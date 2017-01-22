#include "gles.h"
// log tag
#define LOG_TAG "uniformcache.c"

#include "uniformcache.h"

/* Create uniform location caches */
void uniformcache_create(uniformcache_UniformCache *uniformCache, GLuint program){
	uniformCache->model = glGetUniformLocation(program, "model");
	uniformCache->camera = glGetUniformLocation(program, "camera");
}