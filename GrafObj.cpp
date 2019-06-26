#include "GrafObj.h"

GrafObj::GrafObj()
{
    //ctor
    m_vertexID=m_indicesID=m_texCoordBuffer=m_normalBuffer=0;
}

//pomocna transformace objektu
void GrafObj::Transform(GLfloat x,GLfloat z)
{
   m_x=m_x+x;
   m_z=m_z+z;
}

GrafObj::~GrafObj()
{
    //dtor
}
