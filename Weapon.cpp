#include "Weapon.h"

Weapon::Weapon()
{
m_model= new Model3ds(11,"data/models/sword_2.3DS","data/textures/steel.bmp");
m_model->loadModel();
}

void Weapon::draw()

{
    m_model->drawModel();
}

Weapon::~Weapon()
{
    //dtor
    delete m_model;
}
