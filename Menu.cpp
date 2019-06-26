#include "Menu.h"

Menu::Menu()
{
    //inicializace
        initializeMenu();


    //2D vrchily pro menu vychazejici z upravene struktury Vertex2D
    Vertex2D vertices[] = {
		{ {0, 0},    {1.0, 1.0, 0.0} ,    { 0.0, 0.0}    },     // 0
		{ {0,100},    {1.0, 1.0, 0.0},    { 0.0, 1.0}    },     // 1
		{ {1024, 0},  {0.0, 1.0, 0.0},    { 1.0, 0.0}  },       // 2
		{ {1024,100},  {1.0, 1.0, 0.0},   { 1.0, 1.0}  }        // 3
		};


    GLubyte indices[] = {0,1,2,3};

	// vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_vertexID);
	// aktivujeme buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);

	// zaalokujeme pamet pro vrcholy a barvy
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 0, GL_STATIC_DRAW);

	// naplnime pamet
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	// definujeme pointery na vrcholy a barvy
	glVertexPointer(2, GL_INT, sizeof(Vertex2D), 0);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex2D), (void*)(2*sizeof(GL_INT)));
    glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex2D),(void*)(2*sizeof(GL_INT)+(3*sizeof(GL_FLOAT))) );


	// vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_indicesID);
	// aktivujeme buffer pro indexy
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
	// zaalokujeme pamet
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), 0, GL_STATIC_DRAW);
	// naplnime pamet
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

	// aktivujeme pole vrcholu,barev,textur
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


void Menu::initializeMenu()
{
        //nastaveni sceny a projekce
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0, 1024, 0, 100);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //svetla a buffery
        m_vertexID = m_indicesID = m_normalBuffer = m_texCoordBuffer = 0;
        m_light= new Lights();
        m_light->getMenuLight();
        loadTexture("data/textures/menu.tga");
        XP="";
        level="";
}

//nacteni textury
void Menu::loadTexture(string texture)
{
m_menuTexture = new TargaImage();

    	if (!m_menuTexture->load(texture))
    {
        std::cerr << "Could not load the wall texture" << std::endl;
    }

    glGenTextures(1, &m_texCoordBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // opakovani textury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_menuTexture->getWidth(),m_menuTexture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_menuTexture->getImageData());
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // vylepseni zobrazovani
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glEnable(GL_TEXTURE_2D);
}

//nastveni vypisu statistiky
void Menu::setInfo(GLint x, GLint z)
{
    char bufferx[2];
    char bufferz[10];

    level=itoa(x,bufferx,10);
    XP=itoa(z,bufferz,10);
}



void Menu::draw()
{
    //textove informace
    text("Level:",GLUT_BITMAP_HELVETICA_12,140,40);
    text(level,GLUT_BITMAP_HELVETICA_12,180,40);
    text("XP:",GLUT_BITMAP_HELVETICA_12,140,60);
    text(XP,GLUT_BITMAP_HELVETICA_12,170,60);
    //informace o ukolech
    text("Main Quest: Save forest elder.",GLUT_BITMAP_HELVETICA_12,630,60);
    text("Quest: Kill all enemies and collect all orbs.",GLUT_BITMAP_HELVETICA_12,630,40);

    //bindovani bufferu a nastaveni ukazatelu
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
    glVertexPointer(2, GL_INT, sizeof(Vertex2D), 0);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex2D), (void*)(2*sizeof(GL_INT)));
    glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex2D),(void*)(2*sizeof(GL_INT)+(3*sizeof(GL_FLOAT))) );



    //bindovani textury
    glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);
    //vykresleni pozadi menu
    glDrawElements(GL_TRIANGLE_STRIP,4, GL_UNSIGNED_BYTE, 0);






}
//funkce pro vypis textu
void Menu::text(char * string, void * font, int x, int y)
{
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glRasterPos2i(x,y);
        glColor3f(0.0,0.0,0.0);
        while (*string)glutBitmapCharacter(font, *string++);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}


Menu::~Menu()
{
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDeleteBuffers(1, &m_vertexID);
	glDeleteBuffers(1, &m_indicesID);
	glDeleteBuffers(1, &m_texCoordBuffer);
	delete m_menuTexture;
	glDisable(GL_TEXTURE_2D);
}
