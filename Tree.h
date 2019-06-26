#ifndef TREE_H
#define TREE_H
#include "GrafObj.h"
#include <windows.h>
#include <stdlib.h>
#include "Model3ds.h"

class Tree : public GrafObj
{
    public:
        Tree();
        ~Tree();
        void draw();
    protected:
    private:
        Model3ds* m_model;
        Model3ds *m_koruna;
};

#endif // TREE_H
