#ifndef MOUNT_H
#define MOUNT_H

#include "GrafObj.h"
#include "Model3ds.h"


class Mount : public GrafObj
{
    public:
        Mount();
        ~Mount();
        void draw();
    protected:
    private:
        Model3ds* blackhorn;
        Model3ds* horn;
        Model3ds* front;
        Model3ds* armor;
};

#endif // MOUNT_H
