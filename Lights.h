#ifndef LIGHTS_H
#define LIGHTS_H
#include <GL/glut.h>


class Lights
{
    public:
        Lights();
        ~Lights();
        void switchLights();
        void getDefault();
        void getBlue();
        void getMenuLight();
    private:
        bool lightsEnabled;
};

#endif // LIGHTS_H
