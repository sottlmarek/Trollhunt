#include "FinalEntity.h"

FinalEntity::FinalEntity()
{
    //ctor
    m_model=new Model3ds(30,"data/models/elder.3DS","data/textures/white.bmp");
    m_model->loadModel();
    collisionSize=20;
}

bool FinalEntity::CollisionHeroDetection(int x1,int z1, int x2, int z2)
{
       if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize)
        {
           return true;
        }
       else {return false;}
}

void FinalEntity::draw()
{
    glPushMatrix();
    glTranslated(0,20,0);
    glRotated(180,0,1,0);
    m_model->drawModel();
    glPopMatrix();
}

FinalEntity::~FinalEntity()
{
    //dtor
    delete m_model;
}
