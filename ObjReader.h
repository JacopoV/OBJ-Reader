/*
 *  ObjReader.cpp
 *  
 *
 *  Created by Jacopo Volpin on 13/04/10.
 *  
 *	Classe principale per la visualizzazione dell'oggetto *.obj e detentrice dei vari campi dati necessari
 *	e condivisi con le altre classi. La presente classe ha il compito di avviare il programma, il parser
 *	per la lettura e l'elaborazione dei dati. Infine tramite le chiamate GLUT-OpenGL viene disegnato a schermo
 *  il modello in oggetto.
 *
 *  COMANDI NELLA FINESTRA OPENGL :  +    zoom avanti
 *									 -    zoom indietro
 *									 z	  rotazione su asse X
 *									 x    rotazione giu asse X
 *									 n	  rotazione sinistra asse Y
 *									 m    rotazione destra asse Y
 *
 *	AGGIUNTA DI MENU CONSESTUALE CON IL TASTO DESTRO DEL MOUSE (premerlo all'interno della finistra di visualizzazione) CHE PERMETTE:
 *	-	Normal Option --> Calcolo manuale o calcolo dalle normali date ( se presenti ); (in alcuni modelli è visibile una netta differenza)
 *	-	Shader Option --> Accensione o spegnimento del calcolo delle normali per pixel (Phong); (migliorie nel riflesso)
 *  -	Set resolution -> Gestione della risoluzione preferita e modalità fullscreen.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "stdio.h"
#include "Container.h"
#include "Parser.h"
#include "Triangles.h"
#include "Quads.h"
#include "Vertex.h"
#include "Normal.h"
#include "Shader.h"
#include<math.h>
#include<iostream>
#include<vector>
#include<stdlib.h>


#ifndef OBJREADER_H
#define OBJREADER_H


class ObjReader {

private:
	
	Parser *parser;
	vector<Vertex> *vertex_list;
	GLfloat *vertexT, *vertexQ, *normalsT, *normalsQ;		//array di supporto per utilizzo Vertex Array
	Container<Triangles> *triangles;						//struttura per triangoli
	Container<Quads> *quads;								//struttura per quadrati
	Container<Normal> *normals;								//struttura per normali
	
	GLint *indicesT, *indicesQ;
	
	float Z, rX, rY;
	GLint n_triangles, n_quads;
	GLfloat *light;
	GLint shaderOption;
	
	void run_parser() const;
	void calculateNormals();
	void orderNormals();
	void calculateVertexNormals();
	void normalize(GLfloat &,GLfloat &,GLfloat &);
	void generateLights();
	void activateVertexArray() const;
	
public:
	ObjReader(char *);
	void reOrder() ;
	void manageNormals(int);
	void rotateModel(unsigned char);
	void draw();
	void createGLUTMenus();
	void processMenuEvents(int);
	void vertexSwitch(int);
	void quit();
	
};

#endif