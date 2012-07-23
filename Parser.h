/*
 *  Parser.cpp
 *
 *  Created by Jacopo Volpin on 12/04/10.
 *  
 *	classe per le lettura del file *.obj e relativo immagazzinamento dei dati. Essendo puntatori a strutture dati 
 *	presenti in ObjReader, vi è condivisione di memoria e non replicazione dati.
 *	Per l'oggetto Vertex è stato utilizzato un vector in quanto sempre presenti nel file *.obj.
 *  Per il resto è stato optato l'utilizzo di una struttura dati simile.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "stdio.h"
#include "string.h"
#include "Container.h"
#include "Triangles.h"
#include "Quads.h"
#include "Vertex.h"
#include<string.h>
#include<iostream>
#include<vector>

#ifndef PARSER_H
#define	PARSER_H


using namespace std;

class Parser {

private:
	
	FILE *fp;
	char str[256];
	
public:
	
	Parser(char *);
	void start_parser(vector<Vertex> *, Container<Triangles> *, Container<Quads> *, Container<Normal> *);
};

#endif