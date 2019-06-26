#include "Enemy.h"

Enemy::Enemy()
{
        m_head= new Model3ds(12,"data/models/troll_head.3DS","data/textures/blue.bmp");
        m_head->loadModel();
        m_body= new Model3ds(13,"data/models/troll_body.3DS","data/textures/armor.bmp");
        m_body->loadModel();
        m_mace= new Model3ds(14,"data/models/troll_mace.3DS","data/textures/wood.bmp");
        m_mace->loadModel();
        m_hand= new Model3ds(12,"data/models/troll_hand.3DS","data/textures/blue.bmp");
        m_hand->loadModel();
        m_feet= new Model3ds(12,"data/models/troll_feet.3DS","data/textures/blue.bmp");
        m_feet->loadModel();

}

void Enemy::draw()
{
   glPushMatrix();
   glRotated(180,0,1,0);
   glScaled(0.5,0.5,0.5);

        m_head->drawModel();
        m_body->drawModel();
        m_hand->drawModel();
        m_mace->drawModel();
        m_feet->drawModel();

   glPopMatrix();

}


Enemy::~Enemy()
{
    //dtor
    delete m_head;
    delete m_body;
    delete m_mace;
    delete m_hand;
    delete m_feet;

}
