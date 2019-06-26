#include "Mount.h"

Mount::Mount()
{
    //ctor
    blackhorn = new Model3ds(22,"data/models/mount_body.3DS","data/textures/mount.bmp");
    blackhorn->loadModel();
    horn = new Model3ds(23,"data/models/mount_horns.3DS","data/textures/black.bmp");
    horn->loadModel();
    front = new Model3ds(23,"data/models/mount_front.3DS","data/textures/black.bmp");
    horn->loadModel();
    armor = new Model3ds(24,"data/models/mount_armor.3DS","data/textures/black.bmp");
    armor->loadModel();
}
void Mount::draw()
{
    //vykrelseni "Blackhorna"
    blackhorn->drawModel();
    horn->drawModel();
    front->drawModel();
    armor->drawModel();

}
Mount::~Mount()
{
    //dtor
    delete blackhorn;
    delete horn;
    delete front;
    delete armor;

}
