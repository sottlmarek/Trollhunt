#ifndef MENU_H
#define MENU_H

#include "GrafObj.h"
#include <windows.h>
#include "Targa.h"
#include "GLee.h"
#include "Vertex2D.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include "Lights.h"
#include "Material.h"


class Menu: public GrafObj
{
    public:
        Menu();
        ~Menu();
        void setInfo(GLint x,GLint z);
        void draw();


    private:
        GLuint m_vertexID;
        GLuint m_indicesID;
        GLuint m_normalBuffer;
        Lights* m_light;
        void initializeMenu();
        char* level;
        char* XP;
        TargaImage* m_menuTexture;
        GLuint m_texCoordBuffer;
        void loadTexture(string texture);
        void text(char * string, void * font, int x, int y);

};

#endif // MENU_H
