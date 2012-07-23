/*
 *  Shader.cpp
 *
 *  Created by Jacopo Volpin on 04/05/10.
 *
 *  classe che permette di definire il Phong Shader (o Vertex Shader, illuminazione per pixel). Se abilitata permette una netta differenza
 *  visibile nell'illuminazione del modello. Rispetto al calcolo della normale per vertice (si prende ogni vertice in comune tra i poligoni
 *	e si somma la normale di ogni poligono, quindi ottengo una media) in questo caso la normale viene calcolata per pixel, quindi ogni punto
 *  risponde in maniera differente alla luce. Si ottiene un'illuminazione e risposta più naturale.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "GLUT/glext.h"
#include<math.h>
#include<iostream>

#ifndef SHADER_H
#define SHADER_H

class Shader{
private:
	GLhandleARB ShaderProg;
	GLhandleARB ShaderVertex;
	GLhandleARB ShaderFrag;

public:
	void vertexShader();
	void fragShader();
	void linkShader();
	GLhandleARB getProgram();
};

#endif
