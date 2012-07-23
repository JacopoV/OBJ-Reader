/*
 *  ObjReader.cpp
 *  
 *
 *  Created by Jacopo Volpin on 13/04/10.
 *
 *	CREATO con piattaforma MAC OSX
 *  
 *	Classe principale per la visualizzazione dell'oggetto *.obj e detentrice dei vari campi dati necessari
 *	e condivisi con le altre classi. La presente classe ha il compito di avviare il programma, il parser
 *	per la lettura e l'elaborazione dei dati. Infine tramite le chiamate GLUT-OpenGL viene disegnato a schermo
 *  il modello in oggetto.
 *
 *	1) AVVIO : porre i file *.obj nella cartella di esecuzione del programma compilato e da bash digitale    ./Code nome_modello (senza .obj)
 *
 *  2) COMANDI NELLA FINESTRA OPENGL :  
 *									 +    zoom avanti
 *									 -    zoom indietro
 *									 z	  rotazione su asse X
 *									 x    rotazione giu asse X
 *									 n	  rotazione sinistra asse Y
 *									 m    rotazione destra asse Y
 *
 *	3) AGGIUNTA DI MENU CONSESTUALE CON IL TASTO DESTRO DEL MOUSE (premerlo all'interno della finistra di visualizzazione) CHE PERMETTE:
 *	-	Normal Option --> Calcolo manuale o calcolo dalle normali date ( se presenti ); (in alcuni modelli è visibile una netta differenza)
 *	-	Shader Option --> Accensione o spegnimento del calcolo delle normali per pixel (Phong); (migliorie nel riflesso)
 *  -	Set resolution -> Gestione della risoluzione preferita e modalità fullscreen.
 */

#include "ObjReader.h"

ObjReader *obj;
Shader *myShader;

using namespace std;

ObjReader::ObjReader(char *s){
	
	Z=-15;
	rX = rY = 0;
	shaderOption=0;
	parser = new Parser(s);
	vertex_list = new vector<Vertex>();
	triangles = new Container<Triangles>();
	quads = new Container<Quads>();
	normals = new Container<Normal>();
	run_parser();
}

/* metodo per l'avvio del parser (Parser.cpp) con il passaggio dei puntatori per l'immagazzinamento dati */
void ObjReader::run_parser() const{
	parser->start_parser(vertex_list,triangles,quads,normals);
	
}
	
/* metodo per la generazione dell'array di coordinate per i triangoli e per i quadrati secondo l'ordine
   espresso dalle componenti intere del poligono in oggetto	*/
void ObjReader::reOrder() {
	
	vertexT = new GLfloat[triangles->getSize()*9];
	vertexQ = new GLfloat[quads->getSize()*12];
	
	n_triangles=triangles->getSize();
	n_quads=quads->getSize();
	
	//gestisco triangoli
	
	for (int i=0; i<n_triangles; i++) {
		
		Triangles *t = triangles->getData(i);
		GLint c1 = (t->getComp1()-1);
		GLint c2 = (t->getComp2()-1);
		GLint c3 = (t->getComp3()-1);
		
		vertexT[(i*9)] = (vertex_list->at(c1)).getX();
		vertexT[(i*9)+1]=(vertex_list->at(c1)).getY();
		vertexT[(i*9)+2]=(vertex_list->at(c1)).getZ();
		
		vertexT[(i*9)+3]=(vertex_list->at(c2)).getX();
		vertexT[(i*9)+4]=(vertex_list->at(c2)).getY();
		vertexT[(i*9)+5]=(vertex_list->at(c2)).getZ();
		
		vertexT[(i*9)+6]=(vertex_list->at(c3)).getX();
		vertexT[(i*9)+7]=(vertex_list->at(c3)).getY();
		vertexT[(i*9)+8]=(vertex_list->at(c3)).getZ();
		
		
	}
	
	//gestisco quadrati
	
	for (int i=0; i<n_quads; i++) {
		
		Quads *q = quads->getData(i);
		GLint c1 = (q->getComp1()-1);
		GLint c2 = (q->getComp2()-1);
		GLint c3 = (q->getComp3()-1);
		GLint c4 = (q->getComp4()-1);
	
		vertexQ[(i*12)]=(vertex_list->at(c1)).getX();
		vertexQ[(i*12)+1]=(vertex_list->at(c1)).getY();
		vertexQ[(i*12)+2]=(vertex_list->at(c1)).getZ();
		
		vertexQ[(i*12)+3]=(vertex_list->at(c2)).getX();
		vertexQ[(i*12)+4]=(vertex_list->at(c2)).getY();
		vertexQ[(i*12)+5]=(vertex_list->at(c2)).getZ();
		
		vertexQ[(i*12)+6]=(vertex_list->at(c3)).getX();
		vertexQ[(i*12)+7]=(vertex_list->at(c3)).getY();
		vertexQ[(i*12)+8]=(vertex_list->at(c3)).getZ();
		
		vertexQ[(i*12)+9]=(vertex_list->at(c4)).getX();
		vertexQ[(i*12)+10]=(vertex_list->at(c4)).getY();
		vertexQ[(i*12)+11]=(vertex_list->at(c4)).getZ();
	}
	
	
	
	
	//gestione delle normali
	manageNormals(1);
	
}

/* metodo di gestione per le normali, secondo l'opzione specificata possone essere calcolate manualmente
   oppure se presenti nel file *.obj, usare quelle specificate */
void ObjReader::manageNormals(int option){
	
	
	if(normals->isInitialized() && option==1){
	  orderNormals();
		char * growl = "growlnotify --image /Users/FOX/Icons/cube.png <<EOF Using *.Obj normals";
		system(growl);
	}
	else{
	  calculateNormals();
		char * growl = "growlnotify --image /Users/FOX/Icons/cube.png <<EOF Calculating normals";
		system(growl);
	}
	
}

/* metodo per la generazione degli array di normali per triangoli e per i quadrati secondo l'ordine
   espresso dalle componenti intere del poligono in oggetto */
void ObjReader::orderNormals(){
	
	normalsT=new GLfloat[n_triangles*9];
	normalsQ=new GLfloat[n_quads*12];
	
	//gestisco triangoli
	for(int k=0; k<n_triangles; k++){
		Triangles *t = triangles->getData(k);
		GLint norm1 = t->getNorm1()-1;
		GLint norm2 = t->getNorm2()-1;
		GLint norm3 = t->getNorm3()-1;
		
		normalsT[(k*9)] =  normals->getData(norm1)->getNormalX();
		normalsT[(k*9)+1] = normals->getData(norm1)->getNormalY();
		normalsT[(k*9)+2] = normals->getData(norm1)->getNormalZ();
		normalsT[(k*9)+3] = normals->getData(norm2)->getNormalX();
		normalsT[(k*9)+4] = normals->getData(norm2)->getNormalY();
		normalsT[(k*9)+5] = normals->getData(norm2)->getNormalZ();
		normalsT[(k*9)+6] = normals->getData(norm3)->getNormalX();
		normalsT[(k*9)+7] = normals->getData(norm3)->getNormalY();
		normalsT[(k*9)+8] = normals->getData(norm3)->getNormalZ();
	}
	
	//gestisco quadrati
	for (int k=0; k<n_quads; k++) {
		Quads *q = quads->getData(k);
		GLint norm1 = q->getNorm1()-1;
		GLint norm2 = q->getNorm2()-1;
		GLint norm3 = q->getNorm3()-1;
		GLint norm4 = q->getNorm4()-1;
		
		normalsQ[k*12] = normals->getData(norm1)->getNormalX();
		normalsQ[(k*12)+1] = normals->getData(norm1)->getNormalY();
		normalsQ[(k*12)+2] = normals->getData(norm1)->getNormalZ();
		normalsQ[(k*12)+3] = normals->getData(norm2)->getNormalX();
		normalsQ[(k*12)+4] = normals->getData(norm2)->getNormalY();
		normalsQ[(k*12)+5] = normals->getData(norm2)->getNormalZ();
		normalsQ[(k*12)+6] = normals->getData(norm3)->getNormalX();
		normalsQ[(k*12)+7] = normals->getData(norm3)->getNormalY();
		normalsQ[(k*12)+8] = normals->getData(norm3)->getNormalZ();
		normalsQ[(k*12)+9] = normals->getData(norm4)->getNormalX();
		normalsQ[(k*12)+10] = normals->getData(norm4)->getNormalY();
		normalsQ[(k*12)+11] = normals->getData(norm1)->getNormalZ();
	}
}

/* metodo per il calcolo delle normali quando non sono espresse dal file *.obj o per scelta dal
   menu contestuale */
void ObjReader::calculateNormals(){
	
	
	
	normalsT=new GLfloat[n_triangles*9];
	normalsQ=new GLfloat[n_quads*12];
	
	GLfloat x, y, z;
	GLfloat ax, ay, az, bx, by, bz;
	GLint pos=0;
	
	//generazione normali per triangoli
	for (int k=0; k<n_triangles*9 ; k++) {
		
		Triangles *t = triangles->getData(pos);
		
		ax=vertexT[k+3]-vertexT[k];
		ay=vertexT[k+4]-vertexT[k+1];
		az=vertexT[k+5]-vertexT[k+2];
		bx=vertexT[k+6]-vertexT[k];
		by=vertexT[k+7]-vertexT[k+1];
		bz=vertexT[k+8]-vertexT[k+2];
		
		x=(ay * bz) - (az * by);
		y=(az * bx) - (ax * bz);
		z=(ax * by) - (ay * bx);
		
		normalize(x, y, z);
		t->setNormal(x, y, z);
		pos++;
		k+=8;
	}
	
	
	pos=0;
	
	
	//generazione normali per quadrati
	for (int k=0; k<n_quads*12 ; k++) {
		
		Quads *q = quads->getData(pos);
		
		ax=vertexQ[k+3]-vertexQ[k];
		ay=vertexQ[k+4]-vertexQ[k+1];
		az=vertexQ[k+5]-vertexQ[k+2];
		bx=vertexQ[k+6]-vertexQ[k];
		by=vertexQ[k+7]-vertexQ[k+1];
		bz=vertexQ[k+8]-vertexQ[k+2];
		
		x=(ay * bz) - (az * by);
		y=(az * bx) - (ax * bz);
		z=(ax * by) - (ay * bx);
		
		normalize(x, y, z);	
		q->setNormal(x, y, z);
		pos++;
		k+=11;
	}
	
	calculateVertexNormals();
	
}

/* calcolo manuale delle normali per vertice*/
void ObjReader::calculateVertexNormals(){
	
	
	//calcolo normali per vertici : triangoli
	for (int k=0; k<n_triangles; k++) {
		Triangles * t = triangles->getData(k);
		GLfloat nX = t->getNormal()->getNormalX();
		GLfloat nY = t->getNormal()->getNormalY();
		GLfloat nZ = t->getNormal()->getNormalZ();
		GLint comp1 = t->getComp1()-1;
		GLint comp2 = t->getComp2()-1;
		GLint comp3 = t->getComp3()-1;
		
		vertex_list->at(comp1).getNormal()->addNormalX(nX);
		vertex_list->at(comp1).getNormal()->addNormalY(nY);
		vertex_list->at(comp1).getNormal()->addNormalZ(nZ);
		
		vertex_list->at(comp2).getNormal()->addNormalX(nX);
		vertex_list->at(comp2).getNormal()->addNormalY(nY);
		vertex_list->at(comp2).getNormal()->addNormalZ(nZ);
		
		vertex_list->at(comp3).getNormal()->addNormalX(nX);
		vertex_list->at(comp3).getNormal()->addNormalY(nY);
		vertex_list->at(comp3).getNormal()->addNormalZ(nZ);
	}
	
	//calcolo normali per vertici : quadrati
	for (int k=0; k<n_quads; k++) {
		Quads * q = quads->getData(k);
		GLfloat nX = q->getNormal()->getNormalX();
		GLfloat nY = q->getNormal()->getNormalY();
		GLfloat nZ = q->getNormal()->getNormalZ();
		GLint comp1 = q->getComp1()-1;
		GLint comp2 = q->getComp2()-1;
		GLint comp3 = q->getComp3()-1;
		GLint comp4 = q->getComp4()-1;
		
		vertex_list->at(comp1).getNormal()->addNormalX(nX);
		vertex_list->at(comp1).getNormal()->addNormalY(nY);
		vertex_list->at(comp1).getNormal()->addNormalZ(nZ);
		
		vertex_list->at(comp2).getNormal()->addNormalX(nX);
		vertex_list->at(comp2).getNormal()->addNormalY(nY);
		vertex_list->at(comp2).getNormal()->addNormalZ(nZ);
		
		vertex_list->at(comp3).getNormal()->addNormalX(nX);
		vertex_list->at(comp3).getNormal()->addNormalY(nY);
		vertex_list->at(comp3).getNormal()->addNormalZ(nZ);
		
		vertex_list->at(comp4).getNormal()->addNormalX(nX);
		vertex_list->at(comp4).getNormal()->addNormalY(nY);
		vertex_list->at(comp4).getNormal()->addNormalZ(nZ);
	}
	
	//normalizzo tutto
	for (int k=0; k<vertex_list->size(); k++) {
		GLfloat x=vertex_list->at(k).getNormal()->getNormalX();
		GLfloat y=vertex_list->at(k).getNormal()->getNormalY();
		GLfloat z=vertex_list->at(k).getNormal()->getNormalZ();
		
		normalize(x, y, z);
		
		vertex_list->at(k).getNormal()->fixNormalX(x);
		vertex_list->at(k).getNormal()->fixNormalY(y);
		vertex_list->at(k).getNormal()->fixNormalZ(z);
	}
	
	
	
	//aggiunta normali per triangoli
	for (int k=0; k<n_triangles ; k++) {
		
		Triangles *t = triangles->getData(k);
		GLint comp1 = t->getComp1()-1;
		GLint comp2 = t->getComp2()-1;
		GLint comp3 = t->getComp3()-1;
		
		normalsT[(k*9)] = vertex_list->at(comp1).getNormal()->getNormalX();
		normalsT[(k*9)+1] = vertex_list->at(comp1).getNormal()->getNormalY();
		normalsT[(k*9)+2] = vertex_list->at(comp1).getNormal()->getNormalZ();
		
		normalsT[(k*9)+3] = vertex_list->at(comp2).getNormal()->getNormalX();
		normalsT[(k*9)+4] = vertex_list->at(comp2).getNormal()->getNormalY();
		normalsT[(k*9)+5] = vertex_list->at(comp2).getNormal()->getNormalZ();
		
		normalsT[(k*9)+6] = vertex_list->at(comp3).getNormal()->getNormalX();
		normalsT[(k*9)+7] = vertex_list->at(comp3).getNormal()->getNormalY();
		normalsT[(k*9)+8] = vertex_list->at(comp3).getNormal()->getNormalZ();
	}
	
	//aggiunta normali per triangoli
	for (int k=0; k<n_quads ; k++) {
		
		Quads *q = quads->getData(k);
		GLint comp1 = q->getComp1()-1;
		GLint comp2 = q->getComp2()-1;
		GLint comp3 = q->getComp3()-1;
		GLint comp4 = q->getComp4()-1;
		
		normalsQ[(k*12)] = vertex_list->at(comp1).getNormal()->getNormalX();
		normalsQ[(k*12)+1] = vertex_list->at(comp1).getNormal()->getNormalY();
		normalsQ[(k*12)+2] = vertex_list->at(comp1).getNormal()->getNormalZ();
		
		normalsQ[(k*12)+3] = vertex_list->at(comp2).getNormal()->getNormalX();
		normalsQ[(k*12)+4] = vertex_list->at(comp2).getNormal()->getNormalY();
		normalsQ[(k*12)+5] = vertex_list->at(comp2).getNormal()->getNormalZ();
		
		normalsQ[(k*12)+6] = vertex_list->at(comp3).getNormal()->getNormalX();
		normalsQ[(k*12)+7] = vertex_list->at(comp3).getNormal()->getNormalY();
		normalsQ[(k*12)+8] = vertex_list->at(comp3).getNormal()->getNormalZ();
		
		normalsQ[(k*12)+9] = vertex_list->at(comp4).getNormal()->getNormalX();
		normalsQ[(k*12)+10] = vertex_list->at(comp4).getNormal()->getNormalY();
		normalsQ[(k*12)+11] = vertex_list->at(comp4).getNormal()->getNormalZ();
	}
}

/* metodo per la normalizzazione di un vettore date le coordinate x,y,z */
void ObjReader::normalize(GLfloat &x, GLfloat &y, GLfloat &z){

	GLfloat len=(GLfloat)sqrt((x * x) + (y * y) + (z * z));
	if (len == 0.0f)
        len = 1.0f;

	//normalizzazione
	x /= len;
    y /= len;
    z /= len;
}

/* metodo per la rotazione del modello nella finestra di visualizzazione */
void ObjReader::rotateModel(unsigned char t){
	
	if(t=='+') Z += 0.5f;
	if(t=='-') Z -= 0.5f;
	
	if(t=='z') rX += 10.0f;
	if(t=='x') rX -= 10.0f;
	
	if(t=='n') rY += 10.0f;
	if(t=='m') rY -= 10.0f;
}

/* metodo per la generazione della luce */
void ObjReader::generateLights(){

	GLfloat black[4] = {0, 0, 0, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black); 
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	
	light = new GLfloat[4];
	light[0] = 2;
	light[1] = 2;
	light[2] = 2;
	light[3] = 0;
	
	//luci
	GLfloat aLite[4] = {0.2, 0.2, 0.2, 1};
	GLfloat dLite[4] = {0.8, 0.8, 0.8, 1};
	GLfloat sLite[4] = {0.8, 0.8, 0.8, 1};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, aLite);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dLite);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sLite);
	glLightfv(GL_LIGHT0, GL_POSITION, light); // posizionamento luce
}

/* metodo per il disengo delle oggetto date le strutture vertexT,vertexQ,normalsT,normalsQ */
void ObjReader::activateVertexArray() const{
	
	//impiego dei vertex array per semplicità ed efficienza. Evitate numerose ed onerose chiamate glBegin() e glEnd()
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, vertexT);
	glNormalPointer(GL_FLOAT, 0, normalsT);
	glDrawArrays(GL_TRIANGLES, 0, n_triangles*3);
	
	
	glVertexPointer(3, GL_FLOAT, 0, vertexQ);
	glNormalPointer(GL_FLOAT, 0, normalsQ);
	glDrawArrays(GL_QUADS, 0,n_quads*4);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

/* medoto di preparazione del il disegno: viene settata la luce, materiale, traslazione*/
void ObjReader::draw() {
	
	bool gr=true;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//abilitazione della luce
	generateLights();
	
	//materiale
	GLfloat ambiente[4] = {1.0, 1.0, 0.0, 1}; // quarto valore per gestire il canale alfa!
	GLfloat direttiva[4] = {1.0, 1.0,0.0, 1};
	GLfloat brillante[4] = {1.0, 1.0, 1.0, 1};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	glMateriali(GL_FRONT, GL_SHININESS, 32); // brillantezza (Ns)
	
	glTranslatef(0, 0, Z);
	glRotatef(-rX, 1, 0 ,0); 
	glRotatef(-rY, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
	
	//se shaderOption == 1 significa che dal menu contestuale è stato richiesto il Vertex Shader (Phong)
	if(shaderOption==1){
		glUseProgramObjectARB(myShader->getProgram());
		if(gr){
		char * growl = "growlnotify --image /Users/FOX/Icons/cube.png <<EOF Vertex shader ON";
		system(growl);
			gr=false;
		}
	}
	else {
		char * growl = "growlnotify --image /Users/FOX/Icons/cube.png <<EOF Vertex shader OFF";
		system(growl);
	}

	activateVertexArray();
	
	glUseProgramObjectARB(0);// resetta la pipeline
}

/* metodo di supporto per collegare il cambio di stato dal menu contestuale per la selezione dello shader */
void ObjReader::vertexSwitch(int option){
	shaderOption=option;
}

/* metodo chiusura programma */
void ObjReader::quit(){
	
	delete vertex_list;
	delete parser;
	delete normalsQ;
	delete normalsT;
	delete vertexQ;
	delete vertexT;
	delete triangles;
	delete quads;
	delete normals;
	delete myShader;
	delete obj;
	delete light;
    exit(0);
}

/* metodo per definizione dell osservatore e dell'angolo focale richiesto */
static void redraw(int w,int h){
	
	//evita la divisione per zero, quando la finestra è troppo piccola
	if(h == 0)
		h = 1;
	
	float ratio = 1.0* w / h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	
	// setto la visione corretta 
	gluPerspective(30,ratio,1,1000); //angolo focale di 30° suggerito
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0f,1.0f,0.0f);
}

/* callback per richiamare le intere procedure di disegno */
static void paint_all(){
	
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();  
	glColor3f(1,1,1);
	obj->draw();
	glutSwapBuffers();
}

/* callback per la gestioen dei comandi da tastiera */
static void commands(unsigned char t, int, int){
	
	obj->rotateModel(t);
	glutPostRedisplay();
}

/* callback per la gestione delle opzioni scelte con il tasto destro del mouse */
static void processMenuEvents(int option) {
	switch (option) {
		case 1 : 
			obj->manageNormals(1);break;
		case 2 : 
			obj->manageNormals(0);break;
		case 3 : 
			obj->vertexSwitch(1);break;
		case 4 : 
			obj->vertexSwitch(0);break;
		case 5 : 
			glutPositionWindow(0, 0);glutReshapeWindow(640, 480);break;
		case 6 : 
			glutPositionWindow(0, 0);glutReshapeWindow(800, 600);break;
		case 7 : 
			glutPositionWindow(0, 0);glutReshapeWindow(1280, 800);break;
		case 8 : 
			glutFullScreen();break;
		case 9 : 
			obj->quit();break;
	}
	glutPostRedisplay();
}

/* metodo globale per l'inizializzazione dell' ObjReader con il passatto della stringa che riferisce il modello */
void ObjInizialize(char *s){
	
	obj = new ObjReader(s);
	obj->reOrder();
}

/* metodo per la creazione del menu constuale collegato al tasto destro del mouse */
void createGLUTMenus() {
	
	int submenu1, submenu2, submenu3;
	
	submenu1 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Use OBJ normals",1);
	glutAddMenuEntry("Calculate normals",2);
	submenu2 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Vertex Shader ON",3);
	glutAddMenuEntry("Vertex Shader OFF",4);
	submenu3 = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("640x480",5);
	glutAddMenuEntry("800x600",6);
	glutAddMenuEntry("1280x800",7);
	glutAddMenuEntry("Fullscreen",8);
	glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Normals options", submenu1);
	glutAddSubMenu("Shader options", submenu2);
	glutAddSubMenu("Set resolution", submenu3);
	glutAddMenuEntry("Quit",9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* main del programma ObjReader: si controlla che sia stato passato come argomento (da terminale) il modello da visualizzare */
int main(int argc, char **argv){
	
	if(argv[1]!=NULL){
		strcat(argv[1], ".obj");
		ObjInizialize(argv[1]);
	}
	else {
		cout << "ERROR : *.obj file not declared"<<endl;
		exit(0);
	}
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("OBJReader");
	
	cout << "running..."<<endl;
	cout << "OBJreader 1.0" <<endl;
	cout << "Volpin Jacopo 574659 - UniPD"<<endl;
	cout << glGetString(GL_VENDOR)<<endl;
	cout << glGetString(GL_RENDERER)<<endl;
	cout << glGetString(GL_VERSION)<<endl;

	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	createGLUTMenus();
	
	glutReshapeFunc(redraw);
	glutDisplayFunc(paint_all);
	glutKeyboardFunc(commands);
	 
	
	myShader = new Shader();
	
	myShader->vertexShader();
	myShader->fragShader();
	myShader->linkShader();
	
	
	glutMainLoop();
	return 0;
}