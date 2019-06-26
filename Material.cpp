#include "Material.h"
#include <windows.h>
#include "GLee.h"
#include <GL/glut.h>

//testovaci a pouzitelne materialy
//modry material
void Material::getBlueGlass(){

        GLfloat materialAmbient[4];
        GLfloat materialDiffuse[4];
        GLfloat materialSpecular[4];
        GLfloat materialShininess[1];


        // ambientni slozka barvy materialu
        materialAmbient[0]=0.05375;
        materialAmbient[1]=0.05;
        materialAmbient[2]=0.06625;
        materialAmbient[3]=1.0;
        // difuzni slozka barvy materialu
        materialDiffuse[0]=0.18275;
        materialDiffuse[1]=0.17;
        materialDiffuse[2]=0.22525;
        materialDiffuse[3]=1.0;
         // barva odlesku
        materialSpecular[0]=0.332741;
        materialSpecular[1]=0.328634;
        materialSpecular[2]=0.346435;
        materialSpecular[3]=1.0;
        // faktor odlesku
        materialShininess[0]=0.3;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);// nastaveni ambientni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialDiffuse);// nastaveni difuzni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);// nastaveni barvy odlesku materialu
        glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);


}


//bronz
void Material::getBronze(){

        GLfloat materialAmbient[4];
        GLfloat materialDiffuse[4];
        GLfloat materialSpecular[4];
        GLfloat materialShininess[1];

        // ambientni slozka barvy materialu
        materialAmbient[0]=0.25;
        materialAmbient[1]=0.148;
        materialAmbient[2]=0.06475;
        materialAmbient[3]=1.0;
        // difuzni slozka barvy materialu
        materialDiffuse[0]=0.4;
        materialDiffuse[1]=0.2368;
        materialDiffuse[2]=0.1036;
        materialDiffuse[3]=1.0;
        // barva odlesku
        materialSpecular[0]=0.774597;
        materialSpecular[1]=0.458561;
        materialSpecular[2]=0.200621;
        materialSpecular[3]=1.0;
        // faktor odlesku
        materialShininess[0]=0,4;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);// nastaveni ambientni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);// nastaveni difuzni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);// nastaveni barvy odlesku materialu
        glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
}


//zlato
void Material::getGold()
{
        GLfloat materialAmbient[4];
        GLfloat materialDiffuse[4];
        GLfloat materialSpecular[4];
        GLfloat materialShininess[1];

        // ambientni slozka barvy materialu
        materialAmbient[0]=0.24725;
        materialAmbient[1]=0.1995;
        materialAmbient[2]=0.0745;
        materialAmbient[3]=1.0;
        // difuzni slozka barvy materialu
        materialDiffuse[0]=0.75164;
        materialDiffuse[1]=0.60648;
        materialDiffuse[2]=0.22648;
        materialDiffuse[3]=1.0;
        // barva odlesku
        materialSpecular[0]=0.628281;
        materialSpecular[1]=0.366065;
        materialSpecular[2]=0.366065;
        materialSpecular[3]=1.0;
        // faktor odlesku
        materialShininess[0]=.8;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);// nastaveni ambientni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);// nastaveni difuzni slozky barvy materialu
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);// nastaveni barvy odlesku materialu
        glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

}


