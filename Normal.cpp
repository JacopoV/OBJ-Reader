/*
 *  Normal.cpp
 *
 *  Created by Jacopo Volpin on 29/04/10.
 *
 *  classe che identifica un oggetto normale che viene detenuta da Vertex, Triangles e Quads.
 *
 */

#include "Normal.h"

Normal::Normal(){ normalX = normalY = normalZ = 0.0f;};

Normal::Normal(GLfloat x, GLfloat y, GLfloat z){ normalX=x; normalY=y, normalZ=z;};

GLfloat Normal::getNormalX() const {return normalX;};

GLfloat Normal::getNormalY() const {return normalY;};

GLfloat Normal::getNormalZ() const {return normalZ;};

void Normal::addNormalX(GLfloat X) { normalX+=X; };

void Normal::addNormalY(GLfloat Y) { normalY+=Y; };

void Normal::addNormalZ(GLfloat Z) { normalZ+=Z; };

void Normal::fixNormalX(GLfloat X) { normalX=X; };

void Normal::fixNormalY(GLfloat Y) { normalY=Y; };

void Normal::fixNormalZ(GLfloat Z) { normalZ=Z; };