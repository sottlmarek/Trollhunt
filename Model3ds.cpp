#include "Model3ds.h"

Model3ds::Model3ds(int id, char* model3dsFilePath,char* texture3dsFilePath){
	m_modelFilePath = model3dsFilePath;
	m_texture3dsFilePath = texture3dsFilePath;
	m_modelId = id;
	m_num_texture = id;

	processSourceFile();
};

Model3ds::~Model3ds(void){
}


void Model3ds::processSourceFile(){

	//if(strcmp(m_modelFilePath,"-0-") != 0){
	std::string path = m_modelFilePath;
	if(path.find("-0-") == std::string::npos){
		std::cout << "Loading model ... " << path <<std::endl;

		//system("PAUSE");

	//    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
		glShadeModel(GL_SMOOTH); // Type of shading for the polygons

		// Viewport transformation
		//glViewport(0,0,screen_width,screen_height);

		// Projection transformation
	//    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
	//    glLoadIdentity(); // We initialize the projection matrix as identity
	//    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"

	//    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

		glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

		//Load3DS (&m_object,model3dsFile);
		loadModel();

		if(m_texture3dsFilePath != ""){
			m_3dsModel.id_texture = loadTexture();
			//m_object.id_texture=LoadBitmap(texture3dsFile); // The Function LoadBitmap() return the current texture ID

			if (m_3dsModel.id_texture==-1){
				//MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
				std::cerr<<"Image file: "<<m_texture3dsFilePath<<" not found"<<std::endl;
				//exit (0);
			}
		}else{
			std::cerr<<"No image file with texture was defined."<<std::endl;
		}

	}else{
		std::cout << "Model3DS::Model3DS(int,char*,char*) - if==false - no Model defined"<<std::endl;
	}



	//loadModel();
};

int Model3ds::loadModel(){
	int i; //Index variable

	FILE *file; //File pointer

	unsigned short chunk_id; //Chunk identifier
	unsigned int chunk_lenght; //Chunk lenght

	unsigned char current_char; //Char variable
	unsigned short elements_count; //Number of elements in each chunk

	unsigned short face_flags; //Flag that stores some face information

	if ((file=fopen (m_modelFilePath, "rb"))== NULL) return 0; //Open the file

	while (ftell (file) < _filelength (_fileno (file))) //Loop to scan the whole file
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&chunk_id, 2, 1, file); //Read the chunk header
		//printf("ChunkID: %x\n",chunk_id);
		fread (&chunk_lenght, 4, 1, file); //Read the lenght of the chunk
		//printf("ChunkLenght: %x\n",chunk_lenght);

		switch (chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000:
				i=0;
				do
				{
					fread (&current_char, 1, 1, file);
                    m_3dsModel.name[i]=current_char;
					i++;
                }while(current_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices)
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110:
				fread (&elements_count, sizeof (unsigned short), 1, file);
                m_3dsModel.vertices_count = elements_count;
                //printf("Number of vertices: %d\n",elements_count);
                for (i=0; i<elements_count; i++)
                {
					fread (&m_3dsModel.vertices[i].x, sizeof(float), 1, file);
 					//printf("Vertices list x: %f\n",m_3dsModel.vertices[i].x);
                    fread (&m_3dsModel.vertices[i].y, sizeof(float), 1, file);
 					//printf("Vertices list y: %f\n",m_3dsModel.vertices[i].y);
					fread (&m_3dsModel.vertices[i].z, sizeof(float), 1, file);
 					//printf("Vertices list z: %f\n",m_3dsModel.vertices[i].z);
				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons)
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
				fread (&elements_count, sizeof (unsigned short), 1, file);
                m_3dsModel.polygons_count = elements_count;
                //printf("Number of polygons: %d\n",elements_count);
                for (i=0; i<elements_count; i++)
                {
					fread (&m_3dsModel.polygons[i].a, sizeof (unsigned short), 1, file);
					//printf("Polygon point a: %d\n",m_3dsModel.polygons[i].a);
					fread (&m_3dsModel.polygons[i].b, sizeof (unsigned short), 1, file);
					//printf("Polygon point b: %d\n",m_3dsModel.polygons[i].b);
					fread (&m_3dsModel.polygons[i].c, sizeof (unsigned short), 1, file);
					//printf("Polygon point c: %d\n",m_3dsModel.polygons[i].c);
					fread (&face_flags, sizeof (unsigned short), 1, file);
					//printf("Face flags: %x\n",face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points)
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
				fread (&elements_count, sizeof (unsigned short), 1, file);
				for (i=0; i<elements_count; i++)
				{
					fread (&m_3dsModel.mapcoords[i].u, sizeof (float), 1, file);
					//printf("Mapping list u: %f\n",m_3dsModel.mapcoords[i].u);
                    fread (&m_3dsModel.mapcoords[i].v, sizeof (float), 1, file);
					//printf("Mapping list v: %f\n",m_3dsModel.mapcoords[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(file, chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose (file); // Closes the file stream
	return (1); // Returns ok


};


int Model3ds::loadTexture(){
	int i, j=0; //Index variables

	FILE *file; //File pointer
    unsigned char *texture; //The pointer to the memory zone in which we will load the texture

    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    m_num_texture++; // The counter of the current texture is increased

    if( (file = fopen(m_texture3dsFilePath, "rb"))==NULL) return (-1); // Open the file for reading

    fread(&fileheader, sizeof(fileheader), 1, file); // Read the fileheader

    fseek(file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, file);

            // And store it
            texture[j+0] = rgb.rgbtRed; // Red component
            texture[j+1] = rgb.rgbtGreen; // Green component
            texture[j+2] = rgb.rgbtBlue; // Blue component
            texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(file); // Closes the file stream

    glBindTexture(GL_TEXTURE_2D, m_num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, texture);

    free(texture); // Free the memory we used to load the texture

    return (m_num_texture); // Returns the current texture OpenGL ID

	//return (-1);
};
void Model3ds::drawModel(void){

	glPushMatrix();
	glRotated(-90,1,0,0);
	//glutSolidTeapot(2.0);

	//if(strcmp(m_modelFilePath,"-0-") != 0){
	std::string path = m_modelFilePath;
	if(path.find("-0-") == std::string::npos){
	/**********************  3DS DISPLAY  ***************************/
		int index;

		glBindTexture(GL_TEXTURE_2D, m_3dsModel.id_texture); // We set the active texture

		glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
		for (index=0;index<m_3dsModel.polygons_count;index++){

			// computes polygon normals
			Struct_3dsVertex a[1];
			Struct_3dsVertex b[1];
			Struct_3dsVertex n[1];
			float l = 0.0;
			a[0].x = m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].x - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].x;
			a[0].y = m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].y - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].y;
			a[0].z = m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].z - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].z;
			b[0].x = m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].x - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].x;
			b[0].y = m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].y - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].y;
			b[0].z = m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].z - m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].z;
			n[0].x = (a[0].y * b[0].z) - (a[0].z * b[0].y);
			n[0].y = (a[0].z * b[0].x) - (a[0].x * b[0].z);
			n[0].z = (a[0].x * b[0].y) - (a[0].y * b[0].x);
			if (l == 0.0f)
				l = 1.0f;
			// Normalize normals(divide by root of dot product)
			l = (float)sqrt(n[0].x * n[0].x + n[0].y * n[0].y + n[0].z * n[0].z);
			n[0].x /= l;
			n[0].y /= l;
			n[0].z /= l;
			glNormal3d(n[0].x, n[0].y, n[0].z);

			//----------------- FIRST VERTEX -----------------
			// Texture coordinates of the first vertex
			glTexCoord2f( m_3dsModel.mapcoords[ m_3dsModel.polygons[index].a ].u,
						  m_3dsModel.mapcoords[ m_3dsModel.polygons[index].a ].v);
			// Coordinates of the first vertex
			glVertex3f( m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].x,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].y,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].a ].z); //Vertex definition

			//----------------- SECOND VERTEX -----------------
			// Texture coordinates of the second vertex
			glTexCoord2f( m_3dsModel.mapcoords[ m_3dsModel.polygons[index].b ].u,
						  m_3dsModel.mapcoords[ m_3dsModel.polygons[index].b ].v);
			// Coordinates of the second vertex
			glVertex3f( m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].x,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].y,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].b ].z);

			//----------------- THIRD VERTEX -----------------
			// Texture coordinates of the third vertex
			glTexCoord2f( m_3dsModel.mapcoords[ m_3dsModel.polygons[index].c ].u,
						  m_3dsModel.mapcoords[ m_3dsModel.polygons[index].c ].v);
			// Coordinates of the Third vertex
			glVertex3f( m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].x,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].y,
						m_3dsModel.vertices[ m_3dsModel.polygons[index].c ].z);
		}
		glEnd();
		glPopMatrix();
		glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
	}else{
	/**********************  3DS DISPLAY  ***************************/
		std::cout<<"Model3dS::displayModel() No 3dmodel was defined for this marker. GlCube will be displayed instead"<<std::endl;
		system("PAUSE");

	}

};
