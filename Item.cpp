#include "Item.h"

Item::Item()
{
    //inicializace atributu
        m_x=0;
        m_y=0;
        m_z=0;
        m_light=new Lights();
}

void Item::draw()
{
    //vykreslení itemu
glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(m_x,m_z+10,m_y);
        m_light->getBlue();
        glutSolidSphere(2,100,10);
    glPopMatrix();
glEnable(GL_TEXTURE_2D);


}

//transformace
void Item::Transform(float x,float z)
{
    this->m_x=x;

    this->m_z=z;
}

Item::~Item()
{
    //dtor
    delete m_light;
}
