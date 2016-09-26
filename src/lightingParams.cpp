//
//  lightingParams
//
//  Created by Joe Geigel on 1/23/13.
//
//  This code can be compiled as either C or C++.
//

#include "lightingParams.h"
#include <iostream>

// Add any global variables you need here.
float lightPosition[] = {0.0, 0.0, 2.0, 1.0};
float diffuse[] = {1.0, 1.0, 1.0, 1.0};
float diffuseref = 0.7f;
float ambient[] = {0.8, 0.8, 0.8, 1.0};
float ambientref = 0.5f;
float specular[] = {1,0, 1,0, 1.0, 1.0};
float specularE = 100.0f;
float specularCoef = 1.0f;

/**
 * This function sets up the lighting, material, and shading parameters
 * for the Phong shader.
 *
 * You will need to write this function, and maintain all of the values
 * needed to be sent to the vertex shader.
 *
 * @param program - The ID of an OpenGL (GLSL) shader program to which
 *    parameter values are to be sent
 *
 */
void setUpPhong( GLuint program ){
	//Light Position
	GLint lightPositionL = glGetUniformLocation(program, "lightPosition");
	glUniform4f(lightPositionL, lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	//Diffuse
	GLint diffuseL = glGetUniformLocation(program, "diffuse");
	glUniform4f(diffuseL, diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	GLint diffuserefL = glGetUniformLocation(program, "diffuseref");
	glUniform1f(diffuserefL, diffuseref);
	//Ambient
	GLint ambientL = glGetUniformLocation(program, "ambient");
	glUniform4f(ambientL, ambient[0], ambient[1], ambient[2], ambient[3]);
	GLint ambientrefL = glGetUniformLocation(program, "ambientref");
	glUniform1f(ambientrefL, ambientref);
	//Specular
	GLint specularL = glGetUniformLocation(program, "specular");
	glUniform4f(specularL, specular[0], specular[1], specular[2], specular[3]);
	GLint specularEL = glGetUniformLocation(program, "specularE");
	glUniform1f(specularEL, specularE);
	GLint specularCoefL = glGetUniformLocation(program, "specularCoef");
	glUniform1f(specularCoefL, specularCoef);
}

void setLightPosition(float x, float y, float z, float w){
	lightPosition[0] = x;	
	lightPosition[1] = y;	
	lightPosition[2] = z;	
	lightPosition[3] = w;	
}

void setSpecularE(float e){
	specularE = e;
}
