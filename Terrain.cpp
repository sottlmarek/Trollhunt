#include "Terrain.h"
#include "Vertex.h"

Terrain::Terrain(int max_x,int max_z)
{
    m_x=0;
	m_y=0;
	m_z=0;
	m_vertexID=m_texCoordBuffer=m_indicesID=m_normalBuffer=0;

	loadTexture("data/textures/grass.tga");

    	Vertex vertices[] = {
		{ {-300, 0, -300},    {0.0, 1.0, 0.0} ,   { 0, -1, 0},{ 0.0, 0.0}   }, // 0
		{ {max_x+300,  0, -300},    {0.0, 1.0, 0.0},    { 0, -1, 0},{ 0, 1.0}  }, // 1
		{ {-300, 0, max_z+300},    {0.0, 1.0, 0.0},    { 0, -1, 0},{ 1.0, 0.0}  }, // 2
		{ {max_x+300,  0, max_z+300},    {0.0, 1.0, 0.0},    { 0, -1, 0},{ 1.0, 1.0}  }, // 3
                            };


		GLubyte indices[] = {0,1,2,3

		};

	// vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_vertexID);
	// aktivujeme buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);

	// zaalokujeme pamet pro vrcholy a barvy
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 0, GL_STATIC_DRAW);

	// naplnime pamet
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	// definujeme pointery na vrcholy a barvy
	glVertexPointer(3, GL_INT, sizeof(Vertex), 0);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)+3*sizeof(GL_FLOAT)) );
    glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex),(void*)(3*sizeof(GL_INT)+(5*sizeof(GL_FLOAT))) );


	// vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_indicesID);
	// aktivujeme buffer pro indexy
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
	// zaalokujeme pamet
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), 0, GL_STATIC_DRAW);
	// naplnime pamet
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);


	glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_NORMAL_ARRAY, m_normalBuffer); //Bind the vertex buffer
    glBufferData(GL_NORMAL_ARRAY, sizeof(vertices), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_NORMAL_ARRAY, 0, sizeof(vertices), vertices);



	// aktivujeme pole vrcholu,barev,normal,textur
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

//nacteni textury
void Terrain::loadTexture(string texture)
{
m_surfaceTexture = new TargaImage();

    	if (!m_surfaceTexture->load(texture))
    {
        std::cerr << "Could not load the grass texture" << std::endl;
    }

    glGenTextures(1, &m_texCoordBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // opakovani textury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // opakovani textury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_surfaceTexture->getWidth(),m_surfaceTexture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_surfaceTexture->getImageData());
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // vylepseni zobrazovani
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glEnable(GL_TEXTURE_2D);
}

void Terrain::draw()
{
    //draw terenu

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
	glBindBuffer(GL_NORMAL_ARRAY, m_normalBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);

	glVertexPointer(3, GL_INT, sizeof(Vertex), 0);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)+3*sizeof(GL_FLOAT)) );
	glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex),(void*)(3*sizeof(GL_INT)+(3*sizeof(GL_FLOAT))+(3*sizeof(GL_FLOAT))) );

    glDrawElements(GL_TRIANGLE_STRIP,4, GL_UNSIGNED_BYTE, 0);



}

Terrain::~Terrain()
{
    //dtor
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDeleteBuffers(1,  &m_vertexID);
	glDeleteBuffers(1,  &m_indicesID);
	glDeleteBuffers(1,  &m_normalBuffer);
	glDeleteBuffers(1,  &m_texCoordBuffer);
	delete m_surfaceTexture;
}
