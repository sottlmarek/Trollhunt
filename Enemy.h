#ifndef ENEMY_H
#define ENEMY_H
#include "GrafObj.h"
#include "Model3ds.h"

class Enemy : public GrafObj
{
    public:
        Enemy();
        ~Enemy();
        void draw();
    protected:
    private:
        Model3ds* m_head;
        Model3ds* m_body;
        Model3ds* m_mace;
        Model3ds* m_hand;
        Model3ds* m_feet;

};

#endif // ENEMY_H
