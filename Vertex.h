/*
 *  Vertex.cpp
 *
 *  Created by Jacopo Volpin on 26/04/10.
 *  
 *	classe che identifica un oggetto di tipo vertice. Presenta le coordinate x,y,z (popolate dal parser) e un puntatore ad un oggetto
 *  Normal (normale) qualora venga calcolata manualmente.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "GLUT/glext.h"
#include "Normal.h"

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
	
private:
	
	GLfloat x,y,z;
	Normal *myNormal;

public:
	Vertex();
	Vertex(GLfloat,GLfloat,GLfloat);
	GLfloat getX() const;
	GLfloat getY() const;
	GLfloat getZ() const;
	Normal* getNormal() const;
};

#endif