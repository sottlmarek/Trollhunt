#ifndef FINALENTITY_H
#define FINALENTITY_H

#include "GrafObj.h"
#include "Model3ds.h"


class FinalEntity : public GrafObj
{
    public:
        FinalEntity();
        ~FinalEntity();
        void draw();
        bool CollisionHeroDetection(int x1,int z1, int x2, int z2);
    protected:
    private:
        Model3ds* m_model;
};

#endif // FINALENTITY_H
