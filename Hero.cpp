#include "Hero.h"


Hero::Hero()
{
    //inicializace zakladnich atributu
        getDefault();
        next_experience=100;
        m_orb = new Item;
        m_orblight= new Lights;
        experience=0;
        infotext="";
        level=0;
        show_counter=0;
        attack_counter=0;
        show=false;
        mounted=false;
        krok=2.0;

        svetlo = new Lights();
        m_weapon= new Weapon();
        m_mount = new Mount();
        //loading modelů
        m_cape= new Model3ds(4,"data/models/cape.3DS","data/textures/black.bmp");
        m_cape->loadModel();
        m_body= new Model3ds(4,"data/models/body.3DS","data/textures/black.bmp");
        m_body->loadModel();
        m_foot= new Model3ds(4,"data/models/nohy.3DS","data/textures/black.bmp");
        m_foot->loadModel();
        m_secondary_cape= new Model3ds(9,"data/models/second_cape.3DS","data/textures/black.bmp");
        m_secondary_cape->loadModel();
        m_head=new Model3ds(10,"data/models/head.3DS","data/textures/skin.bmp");
        m_head->loadModel();
        //defaultni kolizni vzdalenost
        collisionSize=10;


}

void Hero::getDefault()
{
    //reset pro novou mapu
        m_x=0;
        m_y=0;
        m_z=0;
        m_rotation=0;
        rotace_orbu=0;
        CollectedItems=0;
        killedEnemies=0;
        questComplete=false;
}


void Hero::QuestCheck(GLint max_items,GLint max_kills){
    //test splneni ukolu

    if((killedEnemies==max_kills) && (CollectedItems==max_items) && (questComplete==false))
    {
    infotext="Quest complete";
    show=true;
    killedEnemies=0;
    CollectedItems=0;
    questComplete=true;
    PlaySound("data/sounds/Battle_Victory.wav", NULL, SND_ASYNC);
    };

}


void Hero::calculate_leveling()
{
    //vypocet xp, next xp, a levelu
            show_counter=0;
            if(experience>=next_experience)
            {
            level++;
            infotext="Level up";
            next_experience=1.5*next_experience;
            show=true;
            }
}


//zvyseni zkusenostnich bodu
void Hero::xp(int howmany)
{
    infotext="+50XP";

    show=true;
    experience=this->experience+howmany;
    calculate_leveling();

}


//vykresleni hrdiny
void Hero::draw()
{
    Material::getBlueGlass();


    //vykreslení orbu okolo hrdiny
    glPushMatrix();
        glTranslatef(m_x,m_y,m_z);

                glPushMatrix();
                    glRotatef(rotace_orbu,0,1,0);
                    glTranslated(15,0,0);
                    m_orb->draw();
                glPopMatrix();

    glPopMatrix();


    Material::getBlueGlass();

    glPushMatrix();
        if(!mounted){glTranslatef(0,0,m_z-5);}
                else{glTranslatef(0,25,m_z-5);}
        if(show==true) info(infotext,GLUT_BITMAP_HELVETICA_12,m_x,m_y+show_counter,1,1,1);
    glPopMatrix();

    //vykresleni hrdiny
    Material::getBronze();


    glPushMatrix();
            glTranslatef(m_x,m_y,m_z);

            // Rust hrdiny s levelem
            glScaled(level*0.00000009+1,level*0.009+1,level*0.009+1);
            glRotatef(m_rotation,0.0,1.0,0.0);
            //mount
            if(mounted==true)
            {
            m_mount->draw() ;
            glTranslatef(0,20,0);
            }
            glRotatef(-90,0.0,1.0,0.0);
            glScaled(0.4,0.4,0.4);
            m_cape->drawModel();
            glPushMatrix();
            glTranslated(-10,60,-10);
            glRotated(30,0,0,1);
            glScaled(0.6,0.6,0.6);
            glRotated(20,1,0,0);
            //sword on back
            m_weapon->draw();
    glPopMatrix();


    //ruce
    glPushMatrix();
            glScaled(1.2,1.2,1.2);
            glTranslated(0,15,0);
            m_foot->drawModel();
            glPopMatrix();


            //nohy a telo
            m_foot->drawModel();
            m_body->drawModel();
            m_secondary_cape->drawModel();

            //hlava a jeji uprava
                            glPushMatrix();
                                glTranslated(-7,4.5,0);
                                m_head->drawModel();
                            glPopMatrix();

            //attack
            drawAttack();
    glPopMatrix();


svetlo->getDefault();

}

//jizda na zvireti, aktivace a deaktivace, zmena kolizini velikosti
void Hero::mount()
{
    if(mounted==true)
    {
    mounted=false;
    krok=krok/2;
    collisionSize=collisionSize/3.5;
    }
        else
            {
                mounted=true;
                krok=krok*2;
                collisionSize=collisionSize*3.5;
                infotext="Blackhorn mounted";
                show=true;
                PlaySound("data/sounds/bear-roar.wav", NULL, SND_ASYNC);
            };


}

//vypis infa nad hracem
void Hero::info(char * string, void * font, int x, int y,float r, float g, float b)
{
    glDisable(GL_TEXTURE_2D);
    Material::getGold();
    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(x,y);
    while (*string)glutBitmapCharacter(font, *string++);
    glEnable(GL_TEXTURE_2D);

}

//vykrelseni utoku
void Hero::drawAttack()
{
    quadratic=gluNewQuadric();// Vrátí ukazatel na nový kvadrik
    Material::getGold();
    glTranslated(0,10,0);
    glRotatef(90,1,0,0);
    glScaled(2,2,2);
    gluDisk(quadratic,size-3,size,32,32);




}

//animace utoku
void Hero::playAttack()
{
        if(attack_counter<15 && active_attack==true)
        {
        attack_counter++;
        size=size+3;

        }
                else{
                    active_attack=false;
                    attack_counter=0;
                    size=0;
                    }


}

//animace informaci nad hracem
void Hero::PlayInfo()
{
    if(show_counter<50 && show==true){
    show_counter++;
    }        else       {
                        show_counter=0;show=false;
                        }
}

//detekce kolizi
void Hero::onCollision(int x1,int z1, int x2, int z2)
{

    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='u'){Transform(+krok,0);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='d'){Transform(-krok,0);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='l'){Transform(0,-krok);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='r'){Transform(0,+krok);}
}

//nalezeni itemu
bool Hero::CollisionItemDetection(int x1,int z1, int x2, int z2)
{
       if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize)
        {
           return true;
        }

       else {return false;}

}

//detekce kolize se stenou
bool Hero::CollisionWallDetection(int x1,int z1, int x2, int z2,int collisionSize)
{
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='u'){Transform(+krok,0);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='d'){Transform(-krok,0);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='l'){Transform(0,-krok);}
    if(abs(x1-x2)<collisionSize && abs(z1-z2)<collisionSize && orientation=='r'){Transform(0,+krok);}
}


//zabity nepritel
void Hero::onKilledEnemy()
{
    killedEnemies++;

}

//sebrany item
void Hero::onCollectedItem()
{
   CollectedItems++;
}

//stret s nepritelem
bool Hero::CollisionEnemyDetection(int x1,int z1, int x2, int z2)
{
       if(abs(x1-x2)<collisionSize+10 && abs(z1-z2)<collisionSize+10)
       {
           return true;
       }
       else{return false;}
}

//animace rotace orbu
void Hero::rotateOrb()
{
    rotace_orbu=rotace_orbu+5;
    if(rotace_orbu==360)rotace_orbu=0;
}

//pohyb doleva
void Hero::left()
{
    Transform(0,krok);
    m_rotation=90.0;
    orientation='l';

}

//pohyb doprava
void Hero::right()
{
    Transform(0,-krok);
    m_rotation=-90.0;
    orientation='r';
}

//pohyb nahoru
void Hero::up()
{
    Transform(-krok,0);
    m_rotation=0.0;
    orientation='u';
}

//pohyb dolu
void Hero::down()
{
    Transform(krok,0);
    m_rotation=180.0;
    orientation='d';
}


Hero::~Hero()
{
    //dtor
    delete m_orb;
    delete m_cape;
    delete m_foot;
    delete m_body;
    delete m_weapon;
    delete m_secondary_cape;
    delete m_head;
}
