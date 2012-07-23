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

#include "Shader.h"

GLchar *SorgenteVertex =
"varying vec3 N;"
"varying vec4 O;" // direzione da cui arriva l'osservatore
"void main()"
"{"
"	gl_Position = ftransform();"
"	N = gl_NormalMatrix * gl_Normal;" // prendo la normale da GL NORMAL, la rototraslo e la scrivo all'interno di N che è varying (interpolante)
"   O = gl_ModelViewMatrix * gl_Vertex;"
"}"
;

GLchar *SorgenteFrag =
"varying vec3 N;"
"varying vec4 O;" // direzione da cui arriva l'osservatore
"void main()"
"{"
"	vec4 ca;"
"	vec4 cd;"
"	vec4 cs;" // COMPONENTE SPECULARE
"	vec3 n1;"
"	vec3 n2;"
"	ca = gl_FrontMaterial.ambient * gl_LightSource[0].ambient ;" // ottengo la luce ambientale
"	cd = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse ;" // ottengo la luce diffuse
"	cs = gl_FrontMaterial.specular * gl_LightSource[0].specular;" // ottengo la luce speculare
"	n1 = normalize(N);"
"	n2 = normalize(gl_LightSource[0].position.xyz);"
"	cd *= max(dot(n1,n2),0.0);" // se non lo confronto con 0.0 avrei una luce negativa che assorbe la luce ambientale (quindi se non lo metto mi genera la penombra)
"	ca += cd;"
"	n2 = n2 - normalize(O.xyz);" // ottengo vettore unitario di xyz,  e poi con la regola del parallelogramma faccio n2 - normalize(O.xyz)
"	n2 = normalize(n2);" // lo normalizzo , ora ho il versore bisettrice, direz media tra da dove proviene la luce e l'osservatore
"	float val = max(dot(n1,n2),0.0);"
"	cs *= pow(val,64.0);"
"	ca += cs;"
"	gl_FragColor = ca;"
"}"
;

#define MAX_SHADER_LOG 2048
static GLchar ShaderLog[MAX_SHADER_LOG];

void Shader::vertexShader(){
	
	GLint Ok;
	GLint PosTex;
	
	ShaderVertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	glShaderSourceARB(ShaderVertex, 1, (const GLchar **) &SorgenteVertex, NULL);
	glCompileShaderARB(ShaderVertex);
	glGetObjectParameterivARB(ShaderVertex, GL_OBJECT_COMPILE_STATUS_ARB, &Ok);
	glGetInfoLogARB(ShaderVertex, MAX_SHADER_LOG, &PosTex, ShaderLog);
	if(PosTex > 0){
		
		printf("log vertex : %s\n",ShaderLog);
	}
};

void Shader::fragShader(){
	
	GLint Ok;
	GLint PosTex;
	
	ShaderFrag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB(ShaderFrag, 1, (const GLchar **) &SorgenteFrag, NULL);
	glCompileShaderARB(ShaderFrag);
	glGetObjectParameterivARB(ShaderFrag, GL_OBJECT_COMPILE_STATUS_ARB, &Ok);
	glGetInfoLogARB(ShaderFrag, MAX_SHADER_LOG, &PosTex, ShaderLog);
	if(PosTex > 0){
		
		printf("log fragment : %s\n",ShaderLog);
	}
};

void Shader::linkShader(){
	
	
	GLint Ok;
	GLint PosTex;
	
	ShaderProg = glCreateProgramObjectARB();
	glAttachObjectARB(ShaderProg, ShaderVertex);
	glAttachObjectARB(ShaderProg, ShaderFrag);
	glLinkProgramARB(ShaderProg);
	glGetObjectParameterivARB(ShaderProg, GL_OBJECT_LINK_STATUS_ARB, &Ok);
	glGetInfoLogARB(ShaderProg, MAX_SHADER_LOG, &PosTex, ShaderLog);
	if(PosTex > 0){
		
		printf("log link : %s\n",ShaderLog);
	}
};

GLhandleARB Shader::getProgram(){ return ShaderProg; };
