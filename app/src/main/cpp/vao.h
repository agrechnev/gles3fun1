/* By Oleksiy Grechnyev 2016
Create VAO, this includes creating vertices, VBO, EBO */
#ifndef VAO_H
#define VAO_H

#include "gles.h"

// Type of vertex data (ver_type)
// XYZ coords only
#define VAO_XYZ 1
// XYZ coolrds + RGB color
#define VAO_XYZRGB 2
// XYZ coolrds +  ST texture coords
#define VAO_XYZST 3
// XYZ coolrds + RGB color + ST texture coords
#define VAO_XYZRGBST 4

// The VAO object
typedef struct vao_Vao {
    int useEbo; //TRUE = use EBO
    GLuint nDrawElements; // Number of elements to draw

    // VAO, VBO, EBO
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
} vao_Vao;

/* Create VAO, this includes creating vertices, VBO, EBO
 * pVAO, pVBO, pEBO = pointers to VAO, VBO, EBO
 * vertices[], indices[]  = data arrays
 * indices == NULL : don't use EBO
 * ver_size = sizeof(vertices)
 * ind_size = sizeof(indices)
 * ver_type = type of vertex data, e.g. VAO_XYZRBST
 */
void vao_create(vao_Vao *pVO, GLfloat *vertices, size_t ver_size, GLuint *indices,
                size_t ind_size,
                int ver_type);

/* Delete VAO, VBO and EBO 
 *  EBO is skipped if pEBO==NULL
 */
void vao_delete(vao_Vao *pVO);

/*
* Draw a Vao object
*/
void vao_draw(vao_Vao *pVO);

#endif
