#ifndef VERTEX_H
#define VERTEX_H


#include "GLee.h"
#include <GL/glut.h>
struct Vertex{
	GLint position[3];
	GLfloat color[3];
	GLfloat normal[3];
	GLfloat textureCoo[2];
};

#endif // VERETEX_H
