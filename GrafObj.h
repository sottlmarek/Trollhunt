#ifndef GRAFOBJ_H
#define GRAFOBJ_H
#include <windows.h>
#include <stdlib.h>
#include "GLee.h"
#include <GL/glut.h>

class GrafObj
{
    public:
        GrafObj();
        virtual void draw()=0;
        ~GrafObj();
        GLfloat m_x;
        GLfloat m_y;
        GLfloat m_z;
        GLfloat collisionSize;
        void Transform(GLfloat x,GLfloat z);
    protected:
        GLuint m_vertexID;
        GLuint m_indicesID;
        GLuint m_normalBuffer;
        GLuint m_texCoordBuffer;
};

#endif // GRAFOBJ_H
