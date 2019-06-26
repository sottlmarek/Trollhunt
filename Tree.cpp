#include "Tree.h"

Tree::Tree()
{
        m_x=0;
        m_y=0;
        m_z=0;
        m_model = new Model3ds(14,"data/models/kmen.3DS","data/textures/wood.bmp");
        m_model->loadModel();
        m_koruna = new Model3ds(2,"data/models/koruna.3DS","data/textures/texture.bmp");
        m_koruna->loadModel();


}

void Tree::draw()
{
    glPushMatrix();
    glScaled(0.7,0.7,0.7);
    m_model->drawModel();
    glRotated(90,0,1,0);
    m_koruna->drawModel();
    glPopMatrix();
/*

TESTOVACI KMEN


    glPushMatrix();
    glScaled(1,4,1);
    glutSolidCube(5);
    glPopMatrix();
*/
}


Tree::~Tree()
{
delete m_koruna;
delete m_model;
}
