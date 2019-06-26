#ifndef WALL_H
#define WALL_H

#include "GrafObj.h"
#include "Targa.h"
#include "GLee.h"
#include "Vertex.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>


class Wall : public GrafObj
{
    public:
            Wall(GLint x);
            ~Wall();
            void draw();
            void loadTexture(string texture);
            TargaImage* m_surfaceTexture;
            GLuint m_texCoordBuffer;
    protected:
    private:
            GLuint m_vertexID;
            GLuint m_indicesID;
};

#endif // WALL_H
