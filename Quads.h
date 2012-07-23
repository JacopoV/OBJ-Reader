/*
 *  Quads.cpp
 *
 *  Created by Jacopo Volpin on 24/04/10.
 *  
 *	classe che rappresenta l'oggetto quadrato. Permette di memorizzare i numeri interi che riferiscono vertici e normali in modo 
 *  da avere in seguito un accesso diretto. Si è scelto di non memorizzare le coordinate di vertici e delle normali per non avere 
 *  replicazione di informazioni e quindi alleggerire il programma in esecuzione.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "GLUT/glext.h"
#include "Vertex.h"
#include "Normal.h"

#ifndef QUADS_H
#define QUADS_H

class Quads {
	
private:
	
	Normal *myNormal;
	GLint comp1, comp2, comp3, comp4;
	GLint norm1, norm2, norm3, norm4;
	
public:
	Quads();
	Quads(GLint,GLint,GLint,GLint);								//costruttore per sole componenti
	Quads(GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint);		//costruttore per componenti+normali;
	void setNormal(GLfloat,GLfloat,GLfloat);
	GLint getComp1() const;
	GLint getComp2() const;
	GLint getComp3() const;
	GLint getComp4() const;
	GLint getNorm1() const;
	GLint getNorm2() const;
	GLint getNorm3() const;
	GLint getNorm4() const;
	Normal* getNormal() const;
};

#endif
