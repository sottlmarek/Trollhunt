#ifndef ITEM_H
#define ITEM_H
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>
#include <stdlib.h>
#include "GrafObj.h"
#include "Lights.h"

class Item: public GrafObj
{
    public:
        Item();
        ~Item();
        void rotate();
        void Transform(float x,float z);
        void enableRotation();
        void disableRotation();
        GLboolean isRotating();
        void draw();
    private:
        Lights* m_light;
};

#endif // ITEM_H
