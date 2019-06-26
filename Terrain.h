#ifndef TERRAIN_H
#define TERRAIN_H

#include "GrafObj.h"
#include "Targa.h"
#include "GLee.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
class Terrain : public GrafObj
{
    public:
        Terrain(int max_x,int max_z);
        ~Terrain();
        void draw();


    private:
        void loadTexture(string texture);
        GLuint m_vertexID;
        GLuint m_indicesID;
        GLuint m_texCoordBuffer;
        TargaImage* m_surfaceTexture;
};

#endif // TERRAIN_H
