/**
 * Thomas Ansill's awesome 3D Art Program!!!!
 * Art source: http://christine-eige.deviantart.com/art/Space-Painting-010-181463325
 * Goal: Recreate the art in 3D
 * Art Author: Christine-Eige
 * Program Author: Thomas Ansill
 */

#ifdef __cplusplus
#include <cstdlib>
#include <iostream>
#else
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#endif

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#endif

#include "shaderSetup.h"
#include "cgShape.h"
#include "simpleShape.h"
#include "lightingParams.h"
#include "viewParams.h"

#define SPHERE 0
#define CUBE 1
#define PLANE 2
#define CONE 3

#ifdef __cplusplus
using namespace std;
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//Global variables
GLuint	program;
float	angles = 0.0f;
//One object for now
GLuint	vbuffer[5];
GLuint	ebuffer[5];
int		texturePath[5] = {0,0,0,1,2};;
int		numVerts[5];

/**
 * create any shape and store it in vbuffer and ebuffer
 */ 
void createShape(int obj, int id){
	//clear any previous shape
	clearShape();

	//make the shape
	if(obj == SPHERE){
		makeSphere(1.0f, 50, 50);	
	}else if(obj == CUBE){
		makeCube(1);	
	}else if(obj == PLANE){
		makeCube(1);	
	}else if(obj == CONE){
		makeCone(1.0f, 4, 1);	
	}

	// save the vertex count
	numVerts[id] = nVertices();

	//get the points for the shape
	float *points = getVertices();
	int dataSize = nVertices() * 4 * sizeof(float);

	//get the normals for the shape
	float *normals = getNormals();
	int ndataSize = nVertices() * 3 * sizeof(float);

	//get the texture coordiantes for the shape
	float *texture = getTextureCoord();
	int tdataSize = nVertices() * 2 * sizeof(float);

	//get the element data for the shape
	GLushort *elements = getElements();
	int edataSize = nVertices() * sizeof(GLushort);

	//generate the vertex buffer
	glGenBuffers(1, &vbuffer[id]);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer[id]);
	glBufferData(GL_ARRAY_BUFFER, dataSize + ndataSize + tdataSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, points);
	glBufferSubData(GL_ARRAY_BUFFER, dataSize, ndataSize, normals);
	glBufferSubData(GL_ARRAY_BUFFER, dataSize + ndataSize, tdataSize, texture);

	//generate the element buffer
	glGenBuffers(1, &ebuffer[id]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer[id]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW);
}//End of createShape function

/**
 * select the correct buffer to display correct shape
 */ 
void selectBuffers(GLuint program, int id){
	//bind the buffers
	glBindBuffer( GL_ARRAY_BUFFER, vbuffer[id]);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[id]);

	//calculate the number of bytes of vertex data
	int dataSize = numVerts[id] * 4 * sizeof(float);
	int tdataSize = numVerts[id] * 3 * sizeof(float) + dataSize;

	//set up the vertex attribute variables
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(dataSize));

	GLuint vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tdataSize));
	
	//Load texture
	GLuint tex;
	glGenTextures(1, &tex);
	
	unsigned char* tex_2d;
	int width, height;

	if(texturePath[id] == 0)
		tex_2d = SOIL_load_image("pyramid.png", &width, &height, 0, SOIL_LOAD_RGB);
	else if(texturePath[id] == 1)
		tex_2d = SOIL_load_image("planet.png", &width, &height, 0, SOIL_LOAD_RGB);
	else
		tex_2d = SOIL_load_image("space.png", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_2d);
	SOIL_free_image_data(tex_2d);

	//Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

/**
 *	Report shader problems if there's any
 */
static void checkShaderError(GLuint program, const char *which){
	if(!program){
#ifdef __cplusplus
		cerr << "Error setting " << which << " shader - " << errorString(shaderErrorCode) << endl;
#else
		fprintf(stderr, "Error setting up %s shader - %s\n", which, errorString(shaderErrorCode));
#endif
		exit(1);
	}
}//End of checkShaderError function

/**
 *	Initialize the program, set up shapes
 */
void init(){
	//Load shaders and create program
	program = shaderSetup("vshader.glsl", "fshader.glsl");	
	checkShaderError(program, "shader");

	//Create shapes
	createShape(CONE, 0);
	createShape(CONE, 1);
	createShape(CONE, 2);
	createShape(SPHERE, 3);
	createShape(PLANE,4);

	//OpenGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}//End of init function

#ifdef __cplusplus
extern "C"{
#endif

/**
 *	Render the 3D scene
 */
void display(void){
	//clear and draw params
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use the program
	glUseProgram(program);

	//set up Phong Illumination
	setUpPhong(program);

	//set up viewing and projection parameters
	setUpFrustum(program);

	//set up the camera
	setUpCamera(program,
		0.0f, 0.1f, 6.5f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	//##########################
	//Space background - id = 4
	//##########################

	//set up the transformations
	setUpTransforms(program,
		11.0f, 11.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -10.0f);

	//draw it
	selectBuffers(program, 4);
	glDrawElements(GL_TRIANGLES, numVerts[4], GL_UNSIGNED_SHORT, (void *)0);

	//##########################
	//Pyramid 1 - id = 0
	//##########################
	
	//set up lighting
	setLightPosition(50.0f, -50.0f, 40.0f, 1.0f);
	setSpecularE(3.0f);
	//setLightPosition(50.0f, -50.0f, 10.0f, 1.0f);
	setUpPhong(program);
	
	//set up the transformations
	setUpTransforms(program,
		2.0f, 2.0f, 1.5f,
		-90.0f, 0.0f, -10.0f,
		0.0f, 1.2f, 0.0f);

	selectBuffers(program, 0);
	glDrawElements(GL_TRIANGLES, numVerts[0], GL_UNSIGNED_SHORT, (void *)0);

	//##########################
	//Pyramid 2 - id = 1
	//##########################
	
	//set up the transformations
	setUpTransforms(program,
		1.0f, 1.0f, 0.8f,
		-90.0f, 0.0f, 50.0f,
		1.3f, 1.5f, -0.5f);

	selectBuffers(program, 1);
	glDrawElements(GL_TRIANGLES, numVerts[1], GL_UNSIGNED_SHORT, (void *)0);

	//##########################
	//Pyramid 3 - id = 2
	//##########################
	
	//set up the transformations
	setUpTransforms(program,
		1.0f, 1.0f, 0.8f,
		-90.0f, 0.0f, -10.0f,
		-1.1f, 1.6f, -0.5f);

	selectBuffers(program, 2);
	glDrawElements(GL_TRIANGLES, numVerts[2], GL_UNSIGNED_SHORT, (void *)0);

	//##########################
	//Planet - id = 3
	//##########################
	
	//set up the transformations
	setUpTransforms(program,
		1.0f, 1.0f, 1.6f, //why the planet is oblong? hmmm.
		90.0f, 0.0f, 90.0f+angles,
		1.1f, -1.4f, -1.5f);

	selectBuffers(program, 3);
	glDrawElements(GL_TRIANGLES, numVerts[3], GL_UNSIGNED_SHORT, (void *)0);


	//swap the buffers
	glutSwapBuffers();
}//End of display function

/**
 * Basic program controls
 */
void keyboard( unsigned char key, int x, int y ){
	switch(key){
		//Terminate the program
		case 'q': case 'Q':
			exit(0);
			break;
	}
	glutPostRedisplay();
}//End of keyboard function

/**
 * Brings cool animations to the program!
 */

void animate(void){
	angles += 0.5;
	glutPostRedisplay();
}

#ifdef __cplusplus
}
#endif

/**
 * Main function - initializes GLUT and runs it
 */
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( 1000, 600);
	glutCreateWindow("CG - Final Project - Thomas Ansill");	

#ifndef __APPLE__
	glewInit();
#endif

	init();

	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard);
	glutIdleFunc(animate);

	glutMainLoop();
	return 0;
}//End of main function
