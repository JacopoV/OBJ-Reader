/*
 *  Vertex.cpp
 *
 *  Created by Jacopo Volpin on 26/04/10.
 *  
 *	classe che identifica un oggetto di tipo vertice. Presenta le coordinate x,y,z (popolate dal parser) e un puntatore ad un oggetto
 *  Normal (normale) qualora venga calcolata manualmente.
 */

#include "Vertex.h"

Vertex::Vertex(){};

Vertex::Vertex(GLfloat X, GLfloat Y, GLfloat Z) { x=X; y=Y; z=Z; myNormal = new Normal();};

GLfloat Vertex::getX() const{ return x; };

GLfloat Vertex::getY() const{ return y; };

GLfloat Vertex::getZ() const{ return z; };

Normal* Vertex::getNormal() const {return myNormal;}


