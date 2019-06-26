#ifndef WEAPON_H
#define WEAPON_H

#include "GrafObj.h"
#include "Model3ds.h"


class Weapon : public GrafObj
{
    public:
        Weapon();
        ~Weapon();
        void draw();
    protected:
    private:
        Model3ds* m_model;
};

#endif // WEAPON_H
