/*
 *  Triangles.cpp
 *
 *  Created by Jacopo Volpin on 24/04/10.
 *  
 *	classe che rappresenta l'oggetto triangolo. Permette di memorizzare i numeri interi che riferiscono vertici e normali in modo 
 *  da avere in seguito un accesso diretto. Si è scelto di non memorizzare le coordinate di vertici e delle normali per non avere 
 *  replicazione di informazioni e quindi alleggerire il programma in esecuzione.
 */

#include "Triangles.h"
#include<iostream>

using namespace std;

Triangles::Triangles(){};

Triangles::Triangles(GLint c1, GLint c2,GLint c3){

	comp1=c1;	comp2=c2;	comp3=c3;
};

Triangles::Triangles(GLint c1, GLint c2,GLint c3, GLint ext1, GLint ext2, GLint ext3){

	comp1=c1;	comp2=c2;	comp3=c3;
	norm1 = ext1;	norm2 = ext2;	norm3 = ext3;
};

void Triangles::setNormal(GLfloat X, GLfloat Y, GLfloat Z){ myNormal = new Normal(X,Y,Z); };

GLint Triangles::getComp1() const{ return comp1; };

GLint Triangles::getComp2() const{ return comp2; };

GLint Triangles::getComp3() const{ return comp3; };

GLint Triangles::getNorm1() const{ return norm1; };

GLint Triangles::getNorm2() const{ return norm2; };

GLint Triangles::getNorm3() const{ return norm3; };

Normal* Triangles::getNormal() const {return myNormal;}