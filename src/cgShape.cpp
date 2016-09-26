//
//  cgShape
//
//  Routines for tessellating a number of basic shapes.
//
//  Students are to supply their implementations for the functions in
//  this file using the function "addTriangle()" to do the tessellation.
//
//  This code can be compiled as either C or C++.
//

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include "simpleShape.h"
#include <math.h>
#include <iostream>

#include <cmath>
#define PI 3.14159265

/**
 *  Makes a simple 4 vertices (technically 6 vertices but whatever) 2D plane 
 */

void makePlane(){
	addTriangle(-0.5f, -0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				0.0f, 1.0f);
	//create second triangle
	addTriangle(0.5f, -0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f);
}


/**
 * makeCube - Create a unit cube, centered at the origin, with a given number
 * of subdivisions in each direction on each face.
 *
 * @param subdivision - number of equal subdivisons to be made in each
 *        direction along each face
 *
 * Can only use calls to addTriangle()
 */
void makeCube (int subdivisions){
    if( subdivisions < 1 )
        subdivisions = 1;
	float inc = 1.0f / ((float)subdivisions);
	for(int xdiv = 0; xdiv < subdivisions; xdiv++){
		float x = (inc * xdiv)-0.5;
		for(int ydiv = 0; ydiv < subdivisions; ydiv++){
			float y = (inc * ydiv)-0.5;
			//top side
			//create first triangle
			addTriangle(x, y, 0.5,
						x+inc, y, 0.5,
						x, y+inc, 0.5,
						y+0.5, x+0.5,
						y+inc+0.5, x+0.5,
						y+0.5, x+inc+0.5);
			//create second triangle
			addTriangle(x+inc, y, 0.5,
						x+inc, y+inc, 0.5,
						x, y+inc, 0.5,
						x+inc+0.5, y+0.5,
						x+inc+0.5, y+inc+0.5,
						x+0.5, y+inc+0.5);
			/*
			//left side
			//create first triangle
			addTriangle(0.5, x, y,
						0.5, x+inc, y,
						0.5, x, y+inc,
						0, 0,
						0, 0,
						0, 0);
			//create second triangle
			addTriangle(0.5, x+inc, y,
						0.5, x+inc, y+inc,
						0.5, x, y+inc,
						0, 0,
						0, 0,
						0, 0);
			//front side
			//create first triangle
			addTriangle(x, 0.5, y+inc,
						x+inc, 0.5, y,
						x, 0.5, y,
						0, 0,
						0, 0,
						0, 0);
			//create second triangle
			addTriangle(x, 0.5, y+inc,
						x+inc, 0.5, y+inc,
						x+inc, 0.5, y,
						0, 0,
						0, 0,
						0, 0);
			//bottom side
			//create first triangle
			addTriangle(x, y+inc, -0.5,
						x+inc, y, -0.5,
						x, y, -0.5,
						0, 0,
						0, 0,
						0, 0);
			//create second triangle
			addTriangle(x, y+inc, -0.5,
						x+inc, y+inc, -0.5,
						x+inc, y, -0.5,
						0, 0,
						0, 0,
						0, 0);
			//right side
			//create first triangle
			addTriangle(-0.5, x, y+inc,
						-0.5, x+inc, y,
						-0.5, x, y,
						0, 0,
						0, 0,
						0, 0);
			//create second triangle
			addTriangle(-0.5, x, y+inc,
						-0.5, x+inc, y+inc,
						-0.5, x+inc, y,
						0, 0,
						0, 0,
						0, 0);
			//back side
			//create first triangle
			addTriangle(x, -0.5, y,
						x+inc, -0.5, y,
						x, -0.5, y+inc,
						0, 0,
						0, 0,
						0, 0);
			//create second triangle
			addTriangle(x+inc, -0.5, y,
						x+inc, -0.5, y+inc,
						x, -0.5, y+inc,
						0, 0,
						0, 0,
						0, 0);
			*/
		}//End of for loop
	}//End of for loop
}


/**
 * makeCylinder - Create polygons for a cylinder with unit height, centered at
 * the origin, with separate number of radial subdivisions and height
 * subdivisions.
 *
 * @param radius - Radius of the base of the cylinder
 * @param radialDivision - number of subdivisions on the radial base
 * @param heightDivisions - number of subdivisions along the height
 *
 * Can only use calls to addTriangle()
 */
void makeCylinder (float radius, int radialDivisions, int heightDivisions){
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;
		
	float rinc = 360.0f / ((float)radialDivisions);
	float hinc = 1.0f / ((float)heightDivisions);
	for(int rdiv = 0; rdiv < radialDivisions; rdiv++){
		float theta = 360.0f-(rinc*rdiv);
		float x0 = (0.5f*sin(theta*(PI/180.0f)));
		float y0 = (0.5f*cos(theta*(PI/180.0f)));
		float x1 = (0.5f*sin((theta+rinc)*(PI/180.0f)));
		float y1 = (0.5f*cos((theta+rinc)*(PI/180.0f)));
		//create top cap
		addTriangle(0.0f, 0.0f, 0.5f,
					x0, y0, 0.5f,
					x1, y1, 0.5f);
		//create side surface
		for(int hdiv = 0; hdiv < heightDivisions; hdiv++){
			float h = (hinc * hdiv)-0.5;
			//first triangle
			addTriangle(x0, y0, h,
						x1, y1, h,
						x1, y1, h+hinc);
			//second triangle
			addTriangle(x1, y1, h+hinc,
						x0, y0, h+hinc,
						x0, y0, h);
		}//End of for loop
		//create bottom cap
		addTriangle(0.0f, 0.0f, -0.5f,
					x1, y1, -0.5f,
					x0, y0, -0.5f);
					
	}//End of for loop
}


/**
 * makeCone - Create polygons for a cone with unit height, centered at the
 * origin, with separate number of radial subdivisions and height
 * subdivisions
 *
 * @param radius - Radius of the base of the cone
 * @param radialDivision - number of subdivisions on the radial base
 * @param heightDivisions - number of subdivisions along the height
 *
 * Can only use calls to addTriangle()
 */
void makeCone (float radius, int radialDivisions, int heightDivisions){
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    float rinc = 360.0f / ((float)radialDivisions);
	float hinc = 1.0f / ((float)heightDivisions);
	float dinc = 0.5f / ((float)heightDivisions);
	for(int rdiv = 0; rdiv < radialDivisions; rdiv++){
		float theta = 360.0f-(rinc*rdiv);
		float x0 = (0.5f*sin(theta*(PI/180.0f)));
		float y0 = (0.5f*cos(theta*(PI/180.0f)));
		float x1 = (0.5f*sin((theta+rinc)*(PI/180.0f)));
		float y1 = (0.5f*cos((theta+rinc)*(PI/180.0f)));
		//create base cap
		addTriangle(0.0f, 0.0f, 0.5f,
					x1, y1, 0.5f,
					x0, y0, 0.5f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f);
		//create strip
		for(int hdiv = 0; hdiv < heightDivisions; hdiv++){
			float h = (-hinc*hdiv)+0.5;
			float dist = dinc*(heightDivisions-hdiv);
			if(hdiv != 0){
				//recalculate bottom height
				x0 = (dist*sin(theta*(PI/180.0f)));
				y0 = (dist*cos(theta*(PI/180.0f)));
				x1 = (dist*sin((theta+rinc)*(PI/180.0f)));
				y1 = (dist*cos((theta+rinc)*(PI/180.0f)));
			}
			if(hdiv != heightDivisions-1){
				//square 
				float tx0 = ((dist-dinc)*sin(theta*(PI/180.0f)));
				float ty0 = ((dist-dinc)*cos(theta*(PI/180.0f)));
				float tx1 = ((dist-dinc)*sin((theta+rinc)*(PI/180.0f)));
				float ty1 = ((dist-dinc)*cos((theta+rinc)*(PI/180.0f)));
				addTriangle(x0, y0, h,
							x1, y1, h,
							tx1, ty1, h-hinc);
				addTriangle(tx1, ty1, h-hinc,
							tx0, ty0, h-hinc,
							x0, y0, h);
			}else{
				//triangle for top
				addTriangle(x0, y0, h,
							x1, y1, h,
							0.0f, 0.0f, -0.5,
							//texture coords
							0.0f, 0.0f,
							0.0f, 1.0f,
							1.0, 1.0);
			}
		}//End of for loop
	}//End of for loop
}


/**
 * makeSphere - Create sphere of a given radius, centered at the origin,
 * using spherical coordinates with separate number of thetha and
 * phi subdivisions.
 *
 * @param radius - Radius of the sphere
 * @param slides - number of subdivisions in the theta direction
 * @param stacks - Number of subdivisions in the phi direction.
 *
 * Can only use calls to addTriangle
 */
void makeSphere (float radius, int slices, int stacks){
    if( slices < 3 )
        slices = 3;
    if( stacks < 3 )
        stacks = 3;
	float rinc = 360.0f / ((float)slices);
    for(int ldiv = 0; ldiv < slices; ldiv++){
		//Slices
		float theta = rinc*ldiv;
		float dtinc = 180.0/((float)(stacks-1));
		for(int tdiv = 0; tdiv < stacks-2; tdiv++){
			//Stacks
			float dist = radius*sin(((tdiv+1)*dtinc)*(PI/180.0f));
			float x0 = (dist*sin(theta*(PI/180.0f)));
			float y0 = (dist*cos(theta*(PI/180.0f)));
			float x1 = (dist*sin((theta+rinc)*(PI/180.0f)));
			float y1 = (dist*cos((theta+rinc)*(PI/180.0f)));
			float height = radius*cos((dtinc*(tdiv+1))*(PI/180.0f));
			//texture only
			float ttheta = dtinc*tdiv;
			if(tdiv == 0){
				//top cone top
				addTriangle(0.0f, 0.0f, 1.0f,
							x1, y1, height,
							x0, y0, height,
							//normals
							0.0f, 0.0f, 1.0f,
							x1, y1, height,
							x0, y0, height,
							//texture coords
							(theta-(rinc/2.0f))/360.0f, 0.0f,
							(theta)/360.0f, (ttheta+dtinc)/180.0f,
							(theta-rinc)/360.0f, (ttheta+dtinc)/180.0f);
				addTriangle(0.0f, 0.0f, -1.0f,
							x0, y0, height*-1,
							x1, y1, height*-1,
							//normals
							0.0f, 0.0f, -1.0f,
							x0, y0, height*-1,
							x1, y1, height*-1,
							//texture coords
							(theta-(rinc/2.0f))/360.0f, 1.0f,
							(theta-rinc)/360.0f, 1.0f-(dtinc/180.0f),
							(theta)/360.0f, 1.0f-(dtinc/180.0f));
			}else{
				float tdist = radius*sin((tdiv*dtinc)*(PI/180.0f));
				float tx0 = (tdist*sin(theta*(PI/180.0f)));
				float ty0 = (tdist*cos(theta*(PI/180.0f)));
				float tx1 = (tdist*sin((theta+rinc)*(PI/180.0f)));
				float ty1 = (tdist*cos((theta+rinc)*(PI/180.0f)));
				float theight = radius*cos((dtinc*tdiv)*(PI/180.0f));
				addTriangle(x0, y0, height,
							tx1, ty1, theight,
							x1, y1, height,
							//normals
							x0, y0, height,
							tx1, ty1, theight,
							x1, y1, height,
							//texture coords
							((theta-rinc)/360.0f), (ttheta+dtinc)/180.0f,
							((theta)/360.0f), ttheta/180.0f,
							(theta/360.0f), (ttheta+dtinc)/180.0f);
				addTriangle(x0, y0, height,
							tx0, ty0, theight,
							tx1, ty1, theight,
							//normals
							x0, y0, height,
							tx0, ty0, theight,
							tx1, ty1, theight,
							//texture coords
							((theta-rinc)/360.0f), (ttheta+dtinc)/180.0f,
							((theta-rinc)/360.0f), ttheta/180.0f,
							(theta/360.0f), ttheta/180.0f);
			}
		}//End of for loop
	}//End of for loop
}

