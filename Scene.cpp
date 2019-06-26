#include "Scene.h"

Scene::Scene()
{
    m_hra = new GameWorld();
    m_lights = new Lights();
    campos=500;


    glClearColor (0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

/*
//MLHA
    GLfloat fogColor[4]= {0.5, 0.5, 0.5, 0.2};      // Fog Color
    glClearColor(0.5,0.5,0.5,1.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.5);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_NICEST);          // Fog Hint Value
    glFogf(GL_FOG_START, -1000.0);             // Fog Start Depth
    glFogf(GL_FOG_END,1000);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
*/





}
void Scene::drawScene()
{
        //nastaeni sceny a pohyb kamery
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(20.0, 1.3 , 1, 20000.0);
        gluLookAt(m_hra->m_player->m_x+300+m_hra->rozdil_x, m_hra->m_player->m_y+campos, m_hra->m_player->m_z-400+m_hra->rozdil_z,m_hra->m_player->m_x+m_hra->rozdil_x, m_hra->m_player->m_y,m_hra->m_player->m_z+m_hra->rozdil_z,0.0, 1.0, 0.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //vykreleni hry
        m_hra->drawGame();

}


//prepinanani pohledu
void Scene::camSwitch(){

        //switch kamery
        if(campos==500){campos=350;}
        else if(campos==350){campos=750;}
        else if(campos==750){campos=500;};

        }

Scene::~Scene()
{
  delete m_hra;
  delete m_lights;
}
