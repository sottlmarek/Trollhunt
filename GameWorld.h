#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "GLee.h"
#include <GL/glut.h>
#include "GrafObj.h"
#include "Tree.h"
#include "Hero.h"
#include "Enemy.h"
#include "Terrain.h"
#include "Runestone.h"
#include "Menu.h"
#include "Wall.h"
#include "FinalEntity.h"



using namespace std;

class GameWorld
{
    public:
        GameWorld();
        ~GameWorld();
        void setNextLevel();
        GLuint getLevel();
        void drawGame();
        GLint rozdil_x;
        GLint rozdil_z;
        GLint count_item;
        GLint count_enemy;
        Hero* m_player;

    private:
        void text(char * string, void * font, int x, int y, int z, float r, float g, float b);
        GLint levelOfdetail;
        Tree* m_tree;
        Item* m_item;
        Enemy* m_enemy;
        RuneStone* m_stone;
        void readLevel(char Filename);
        GLuint level;
        GLuint m_Environment[30][30];
        void readLevel(string level);
        GLuint metric;
        void onOutOfMap();
        char buffer[2];
        string actual_map;
        string path;
        Terrain* m_ground;
        Wall* m_wall;
        FinalEntity* m_wiseElder;
        bool mainQuest;
        bool visibilityTest(GLint x, GLint z, GLint i, GLint j);



};

#endif // GAMEWORLD_H
