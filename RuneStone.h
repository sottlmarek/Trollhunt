#ifndef RUNESTONE_H
#define RUNESTONE_H

#include "GrafObj.h"
#include "Targa.h"
#include "GLee.h"
#include "Vertex.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>


class RuneStone : public GrafObj
{
    public:
        RuneStone();
        ~RuneStone();
        void draw();
        bool CollisionHeroDetection(int x1,int z1, int x2, int z2);

;
    private:
        GLuint m_vertexID;
        GLuint m_indicesID;
        TargaImage* m_surfaceTexture;
        GLuint m_texCoordBuffer;
        void loadTexture(string texture);
};

#endif // RUNESTONE_H
