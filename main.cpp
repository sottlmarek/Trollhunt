#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>
#include <stdlib.h>
#include "Scene.h"
#include "Menu.h"


GLuint height=768;
GLuint width=1024;


Scene* world;
Menu* game_menu;


void init2(void){
        game_menu = new Menu;
}

void init(void){
world = new Scene();
}

void onTimer(int state){

    //rotující orb
    world->m_hra->m_player->rotateOrb();
    //attack
    world->m_hra->m_player->playAttack();
    //level up,xp, quest completing
    world->m_hra->m_player->PlayInfo();
    //Quest completing test
    world->m_hra->m_player->QuestCheck(world->m_hra->count_item,world->m_hra->count_enemy);




    glutTimerFunc(13,onTimer,0);
    glutPostRedisplay();
}


void onDisplayPanel(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game_menu->setInfo(world->m_hra->m_player->level,world->m_hra->m_player->experience);
    game_menu->draw();


    glutPostRedisplay();
    glFlush ();
	glutSwapBuffers();
}


void onDisplay(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// vykreslime objekt

            world->drawScene();

	// zapiseme zmeny
	glFlush ();
	glutSwapBuffers();

}

void onReshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}


void onMouseClick(int button, int state, int x, int y){

world->m_hra->m_player->active_attack=true;
//THIS IS THE SOUND SAMPLE FROM WITCHER 1
PlaySound("data/sounds/yrden-shoot04.wav",NULL,SND_ASYNC);


}

void onMouseMotion(int x, int y){

}

void onKeyboard(unsigned char key, int x, int y){
switch (key) {
		case 27:
			exit(0);
			break;

        case 'd':
			world->m_hra->m_player->up();

			break;

        case 'a':
			world->m_hra->m_player->down();

			break;


        case 'w':
			world->m_hra->m_player->left();
        break;


        case 's':
			world->m_hra->m_player->right();

        break;

        case 'm':
			world->m_hra->m_player->mount();
        break;

        case 'c':
			world->camSwitch();
        break;

	}
	glutPostRedisplay();

}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (width,height);
	glutInitWindowPosition (0, 0);
	int mainWindow = glutCreateWindow ("Legend of Shadowhorn Forest");
	init();
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyboard);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMotion);
	glutTimerFunc(0,onTimer,0);
	glutCreateSubWindow(mainWindow, 0,668,1024,100);
	init2();
	glutDisplayFunc(onDisplayPanel);
	glutMainLoop();
    return 0;
}
