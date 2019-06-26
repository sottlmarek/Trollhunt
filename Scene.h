#ifndef SCENE_H
#define SCENE_H
#include "GameWorld.h"
#include "Lights.h"
#include <windows.h>
#include <stdlib.h>
#include "GLee.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

class Scene
{
    public:
        Scene();
        ~Scene();
        GameWorld* m_hra;
        Lights *m_lights;
        void drawScene();
        void camSwitch();
    protected:
    private:
        GLint campos;
};

#endif // SCENE_H
