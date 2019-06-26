#include "GameWorld.h"

GameWorld::GameWorld()
{
        //pocatecni level
        level=1;
        //vzdalenosti objektu od sebe, zakladni metrika sceny
        metric=35;
        //vytvoreni vnorenych objektu ve hre
        m_tree=new Tree();
        m_player=new Hero();
        m_enemy=new Enemy();
        m_item=new Item();
        m_stone=new RuneStone();
        m_wiseElder= new FinalEntity();
        m_ground=new Terrain(30*metric,30*metric);
        m_wall=new Wall(metric/2);
        //vykreslovani okoli hrdiny
        levelOfdetail=280;
        //mapy
        path="levels/map";
        actual_map=path+itoa(level,buffer,10)+".lvl";
        readLevel(actual_map);
        //splen hlavni ukol
        mainQuest=false;

}


void GameWorld::setNextLevel()
{
level++;
}


GLuint GameWorld::getLevel()
{
return level;
}



void GameWorld::readLevel(string level){

/*
// CTENI PO ZNAKU (NUTNE PRETYPOVAT JELIKOZ SE NACITA ORD. HODNOTA
char znak;
  int value;
    ifstream in;

                  in.open("levels/level1.lvl");
                  if (in.is_open()) {
                                 for (int i=0; i < 20 ; i ++)  {
                                     for (int j=0; j < 20; j++){
                                in.get(znak);
                                value=znak;
                                m_Environment[i][j]=value;
                                cout << m_Environment[i][j] << " ";
                                    }
                                 }
                                 in.close();
                                    }
                     else { cerr << " Nepodarilo se otevrit soubor" << endl;}

*/

    ifstream in(level.c_str());
    string line;
    int i, j, hodnota;

    if (!in.is_open()){
        std::cerr << "Nepodarilo se nacist mapu" << std::endl;
    };

    i = 0;
    count_enemy=0;
    count_item=0;

    while(getline (in, line)){
        j = 0;
        istringstream linestream(line);
        string polozka;
        while (getline (linestream, polozka,' ')){
            hodnota = atoi(polozka.c_str());
            m_Environment[i][j] = hodnota;
            if(hodnota>=5 && hodnota<=8){count_enemy++;};
            if(hodnota==3){count_item++;};

            if(j<30)j++;
        }
        if(i<30) i++;

    }

    in.close();
}


void GameWorld::drawGame()
{

glPushMatrix();
//glTranslated(0,50,0);

// rozmístění nepratel, stromů , hrace atd.

    for(int i=0; i<30;i++){
        for(int j=0; j<30;j++){
            int item=m_Environment[i][j];

            if(j==10 and i==10)text("Shadowhorn Forest",GLUT_BITMAP_HELVETICA_12,i*metric,100,j*metric,0,0,0);
            switch(item){

//stromy
            case 1:

                glPushMatrix();
                    glTranslated(i*metric, 0, j*metric);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_tree->draw();
                glPopMatrix();
                m_player->onCollision(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric);
            break;
//hrac
            case 2:
                glPushMatrix();
                    glTranslated(i*metric, 0, j*metric);
                    rozdil_x=i*metric;
                    rozdil_z=j*metric;
                    m_player->draw();
                glPopMatrix();


            break;


//predmety
            case 3:
                glPushMatrix();
                    //collected items
                    if(m_player->CollisionItemDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))
                    {
                        m_Environment[i][j]=0;
                        m_player->xp(50);
                        m_player->onCollectedItem();
                        PlaySound("data/sounds/pickup.wav", NULL, SND_ASYNC);
                    };

                    text("<Light Orb>",GLUT_BITMAP_HELVETICA_12,i*metric,25,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_item->draw();
                glPopMatrix();

            break;

//runestone
            case 4:
                glPushMatrix();
                    //collected items
                    if(m_stone->CollisionHeroDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric) && m_player->questComplete)
                    {
                        setNextLevel();
                        actual_map=path+itoa(level,buffer,10)+".lvl";
                        m_player->getDefault();
                        readLevel(actual_map);
                        m_player->infotext="New realm reached";
                        m_player->show=true;
                        PlaySound("data/sounds/wow-level-up-sound.wav", NULL, SND_ASYNC);
                    };
                    text("<Rune stone>",GLUT_BITMAP_HELVETICA_12,i*metric,85,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))
                    {
                        //natoceni kamenu
                        m_stone->draw();
                        glTranslated(0,0,-30);
                        m_stone->draw();
                        glTranslated(0,55,-10);
                        glRotated(90,1,0,0);
                        m_stone->draw();


                    }
                glPopMatrix();


            break;

 //nepratele
 //Trolls
 //maly troll
            case 5:
                glPushMatrix();
                if(m_player->CollisionEnemyDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric) && m_player->active_attack)
                    {
                        m_Environment[i][j]=0;
                        m_player->xp(50);
                        m_player->onKilledEnemy();
                    };
                    text("<Troll Acolyte>",GLUT_BITMAP_HELVETICA_12,i*metric,25,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    glScaled(0.5,0.5,0.5);
                    glRotated(i*metric+j,0,1,0);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_enemy->draw();
                glPopMatrix();
            break;
//velky troll
            case 6:
                glPushMatrix();
                if(m_player->CollisionEnemyDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric) && m_player->active_attack)
                    {
                        m_Environment[i][j]=0;
                        m_player->xp(50);
                        m_player->onKilledEnemy();
                    };
                    text("<Giant Troll>",GLUT_BITMAP_HELVETICA_12,i*metric,65,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    glScaled(2,2,2);
                    glRotated(i*metric+j,0,1,0);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_enemy->draw();
                glPopMatrix();
            break;

//troll
            case 7:

                //Material::getGold();
                glPushMatrix();
                if(m_player->CollisionEnemyDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric) && m_player->active_attack)
                    {
                        m_Environment[i][j]=0;
                        m_player->xp(50);
                        m_player->onKilledEnemy();
                    };
                    text("<Troll>",GLUT_BITMAP_HELVETICA_12,i*metric,35,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    glRotated(i*metric+j,0,1,0);
                     if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_enemy->draw();
                glPopMatrix();
            break;


//BOSS
            case 8:

                //Material::getGold();
                glPushMatrix();
                if(m_player->CollisionEnemyDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric) && m_player->active_attack)
                    {
                        m_Environment[i][j]=0;
                        m_player->xp(50);
                        m_player->onKilledEnemy();
                    };
                    text("<Lazarus, Troll Titan>",GLUT_BITMAP_HELVETICA_12,i*metric,125,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                     glScaled(4,4,4);
                    glRotated(i*metric+j,0,1,0);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_enemy->draw();
                glPopMatrix();
            break;
//wall
            case 9:
                //Material::getGold();
                glPushMatrix();
                    glTranslated(i*metric, 0, j*metric);
                    m_player->CollisionWallDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric,metric-5);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_wall->draw();
                glPopMatrix();
            break;


            //final object
            case 10:
                glPushMatrix();
                    //uvede konec hry
                     if(m_stone->CollisionHeroDetection(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))
                    {
                        m_player->infotext="Main Quest Complete";
                        m_player->show=true;
                        mainQuest=true;
                    };
                    //check main quest
                    if(mainQuest==true)text("THE END",GLUT_BITMAP_HELVETICA_18,m_player->m_x+rozdil_x+20,45,m_player->m_z+rozdil_z,0,0,0);
                    text("<Thunder, Wise Forest Elder>",GLUT_BITMAP_HELVETICA_12,i*metric,55,j*metric,0,0,0);
                    glTranslated(i*metric, 0, j*metric);
                    if(visibilityTest(m_player->m_x+rozdil_x,m_player->m_z+rozdil_z,i*metric,j*metric))m_wiseElder->draw();
                glPopMatrix();

            break;

        }


        }



    }

    glPopMatrix();
    //zeme
    m_ground->draw();
    //text umisteni mimo mapu
    onOutOfMap();

}


//generování písma
void GameWorld::text(char * string, void * font, int x, int y, int z, float r, float g, float b)
{
    glDisable(GL_TEXTURE_2D);
    //Material::getGold();
    glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(0,0,z);
        glRasterPos2i(x,y);
        while (*string)glutBitmapCharacter(font, *string++);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

//level od detail zobrazeni,zobrazujeme pouze objekty v urcite vzdalenosti od hrdiny (optimalizace vykonu)
bool GameWorld::visibilityTest(GLint x, GLint z, GLint i, GLint j)
{
    if(abs(x-i)<levelOfdetail && abs(z-j)<levelOfdetail){return true;}else{return false;}
}


//restrikce a omezení hrací plochy

void GameWorld::onOutOfMap()
{
    //pozice jichz nemuze hridna dosahnout, aby nevysel z mapy
    if(m_player->m_x < (0-rozdil_x)){m_player->m_x=0-rozdil_x;};
    if(m_player->m_x > ((29*metric)-rozdil_x)){m_player->m_x=(29*metric)-rozdil_x;};
    if(m_player->m_z < (0-rozdil_z)){m_player->m_z=0-rozdil_z;};
    if(m_player->m_z > ((29*metric)-rozdil_z)){m_player->m_z=(29*metric)-rozdil_z;};
}



//destruktor
GameWorld::~GameWorld()
{
    delete m_player;
    delete m_tree;
    delete m_enemy;
    delete m_ground;
    delete m_item;
    delete m_wall;
    delete m_stone;
}
