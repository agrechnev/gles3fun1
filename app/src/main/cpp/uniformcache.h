/* By Oleksiy Grechnyev 2016
 * Set up uniform location cache
 * Includes structure UniformCache
 */

#ifndef UNIFORMCACHE_H
#define UNIFORMCACHE_H
#include "gles.h"

typedef struct uniformcache_UniformCache {
	GLuint model;
	GLuint camera;
} uniformcache_UniformCache;

/* Create uniform caches */
void uniformcache_create(uniformcache_UniformCache *uniformCache, GLuint program);

#endif