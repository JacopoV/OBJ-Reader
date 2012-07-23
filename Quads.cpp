/*
 *  Quads.cpp
 *
 *  Created by Jacopo Volpin on 24/04/10.
 *  
 *	classe che rappresenta l'oggetto quadrato. Permette di memorizzare i numeri interi che riferiscono vertici e normali in modo 
 *  da avere in seguito un accesso diretto. Si è scelto di non memorizzare le coordinate di vertici e delle normali per non avere 
 *  replicazione di informazioni e quindi alleggerire il programma in esecuzione.
 */

#include "Quads.h"
#include<iostream>

using namespace std;

Quads::Quads(){};

Quads::Quads(GLint c1, GLint c2,GLint c3, GLint c4){

	comp1=c1;	comp2=c2;	comp3=c3;	comp4=c4;
};

Quads::Quads(GLint c1, GLint c2,GLint c3, GLint c4, GLint ext1, GLint ext2, GLint ext3, GLint ext4){
	
	comp1=c1;	comp2=c2;	comp3=c3;	comp4=c4;
	norm1 = ext1;	norm2 = ext2;	norm3 = ext3;	norm4 = ext4;
};

void Quads::setNormal(GLfloat X, GLfloat Y, GLfloat Z){ myNormal = new Normal(X,Y,Z); };

GLint Quads::getComp1() const{ return comp1; };

GLint Quads::getComp2() const{ return comp2; };

GLint Quads::getComp3() const{ return comp3; };

GLint Quads::getComp4() const{ return comp4; };

GLint Quads::getNorm1() const{ return norm1; };

GLint Quads::getNorm2() const{ return norm2; };

GLint Quads::getNorm3() const{ return norm3; };

GLint Quads::getNorm4() const{ return norm4; };

Normal* Quads::getNormal() const {return myNormal;}