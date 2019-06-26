#ifndef VERTEX2D_H
#define VERTEX2D_H


#include "GLee.h"
#include <GL/glut.h>

struct Vertex2D{
	GLint position[2];
	GLfloat color[3];
	GLfloat texture[2];
};

#endif // VERETEX_H
