/*
 *  Normal.cpp
 *
 *  Created by Jacopo Volpin on 29/04/10.
 *
 *  classe che identifica un oggetto normale che viene detenuta da Vertex, Triangles e Quads.
 *
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "GLUT/glext.h"

#ifndef NORMAL_H
#define NORMAL_H

class Normal {
	
private:
	
	GLfloat normalX, normalY, normalZ;
	
public:
	Normal();
	Normal(GLfloat,GLfloat,GLfloat);
	GLfloat getNormalX() const;
	GLfloat getNormalY() const;
	GLfloat getNormalZ() const;
	void addNormalX(GLfloat);
	void addNormalY(GLfloat);
	void addNormalZ(GLfloat);
	void fixNormalX(GLfloat);
	void fixNormalY(GLfloat);
	void fixNormalZ(GLfloat);
};

#endif