#ifndef MODEL_3DS
#define MODEL_3DS

#include <iostream>
#include <windows.h>
#include "GLee.h"
#include <gl/gl.h>
#include <gl/glut.h>
#include "General3dModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include "math.h"

 /**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

#define MAX_VERTICES_3DS 8000 // Max number of vertices (for each object)
#define MAX_TRIANGLES_3DS 8000 // Max number of polygons (for each object)

// Our vertex type
struct Struct_3dsVertex{
    float x,y,z;
};

// The polygon (triangle), 3 numbers that aim 3 vertices
struct Struct_3dsTriangles{
    unsigned short a,b,c;
};

// The mapcoord type, 2 texture coordinates for each vertex
struct Struct_3dsMapcoord{
    float u,v;
};

// The object type
struct Struct_3dsModelStructure{
	char name[20];

	int vertices_count;
    int polygons_count;

    Struct_3dsVertex vertices[MAX_VERTICES_3DS];
    Struct_3dsTriangles polygons[MAX_TRIANGLES_3DS];
    Struct_3dsMapcoord mapcoords[MAX_VERTICES_3DS];
    int id_texture;
};

///Class Model3ds definition
class Model3ds : public General3dModel{
	private:
		char* m_modelFilePath;
		char* m_texture3dsFilePath;
		int	m_modelId;
		int m_num_texture;

		Struct_3dsModelStructure m_3dsModel;

	public:
		Model3ds(int id, char* model3dsFilePath,char* texture3dsFilePath);
		~Model3ds(void);

		void processSourceFile();
		int loadModel();
		int loadTexture();
		void drawModel(void);
};

#endif
