#include "Lights.h"

Lights::Lights()
{

getDefault();

}

void Lights::getDefault()
{
    //nactení defaultniho svetla
    //zde budou definována svetla
        glShadeModel(GL_SMOOTH);

			glLoadIdentity();
			GLfloat whiteLight[]={1.0, 1.0, 1.0, 1.0};
			GLfloat lightPosition[]={1.0, 500.0, 10.0, -100.0};


		glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


        glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
}


void Lights::getBlue()
{
    //načtení modreho svetla
    //zde budou definována svetla

        GLfloat whiteLight[]={0.0, 0.0, 1.0, 1.0};
        GLfloat lightPosition[]={1.0, 0.0, 1.0, -100.0};


		glLightfv(GL_LIGHT1, GL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, whiteLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);


}



void Lights::getMenuLight()
{
        //zde budou definována svetla pro menu


        GLfloat whiteLight[]={1.0, 1.0, 1.0, 0.0};
        GLfloat lightPosition[]={1.0, 30.0, 50.0, 0.0};


		glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);


}


Lights::~Lights()
{
   glDisable(GL_LIGHTING);
}
