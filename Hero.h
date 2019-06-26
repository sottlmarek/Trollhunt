#ifndef HERO_H
#define HERO_H
#include "GrafObj.h"
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "Material.h"
#include "Item.h"
#include "Lights.h"
#include "Model3ds.h"
#include "Weapon.h"
#include "Mount.h"


using namespace std;


class Hero : public GrafObj
{
    public:
        Hero();
        ~Hero();
        char* infotext;
        GLint experience;
        GLint level;
        GLint next_experience;
        GLfloat m_rotation;
        GLfloat rotace_orbu;
        void draw();
        void rotate();
        void xp(int howmany);
        void up();
        void down();
        void left();
        void right();
        void drawAttack();
        void onCollision(int x1,int z1, int x2, int z2);
        void playAttack();
        void PlayInfo();
        void rotateOrb();
        void onKilledEnemy();
        void QuestCheck(GLint max_items,GLint max_kills);
        void getDefault();
        void onCollectedItem();
        void mount();
        bool CollisionItemDetection(int x1,int z1, int x2, int z2);
        bool CollisionEnemyDetection(int x1,int z1, int x2, int z2);
        bool active_attack;
        bool CollisionWallDetection(int x1,int z1, int x2, int z2,int collisionSize);
        bool questComplete;
        bool show;

    private:
        void info(char *string , void * font, int x, int y, float r, float g, float b);
        void calculate_leveling();
        GLUquadricObj *quadratic;
        GLint attack_counter;
        GLuint show_counter;
        GLint size;
        unsigned char orientation;
        Item* m_orb;
        Lights* m_orblight;
        Model3ds* m_cape;
        Model3ds* m_body;
        Model3ds* m_foot;
        Model3ds* m_secondary_cape;
        Model3ds* m_head;
        Weapon* m_weapon;
        Lights* svetlo;
        Mount* m_mount;
        bool mounted;
        GLint killedEnemies;
        GLint CollectedItems;
        GLfloat krok;


};

#endif // HERO_H
