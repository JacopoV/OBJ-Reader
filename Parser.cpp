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

#include "Parser.h"

Parser::Parser(char *s){fp = fopen(s, "r");};
	
/* metodo di avvio del parser; apre il file specificato e riga per riga aggiunge nelle strutture dati i corrispondenti elementi */
void Parser::start_parser(vector<Vertex> *v, Container<Triangles> *tr, Container<Quads> *qs, Container<Normal> *vn){
		
		bool boot_f = true, boot_vn = true;
		float f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
		
		if(!fp){
			cout << "ERROR : file not found or wrong declaration"<<endl;
			exit(0);
		}
		
		while (!feof(fp)) {
			
			memset(str, 0, 256);
			fgets(str, 256, fp);
			
			if( strncmp("vn ",str,3) == 0 )
			{
				if(boot_vn){
					vn->initiateData();
					boot_vn=false;
				}
				sscanf((str+2),"%f %f %f",&f1,&f2,&f3);
				Normal n = Normal(f1,f2,f3);
				vn->addData(n);
				
			}
			else if(strncmp("v ",str,2) == 0 )
			{
				
				sscanf((str+1),"%f %f %f",&f1,&f2,&f3);
				Vertex tmp = Vertex(f1,f2,f3);
				v->push_back(tmp);
			}
			else if(strncmp("f ",str,2) == 0 )
			{
				if (boot_f) {
					//attivare struttura dati
					tr->initiateData();
					qs->initiateData();
					boot_f=false;
				}
				int match = sscanf((str+1),"%f %f %f %f",&f1,&f2,&f3,&f4);		//triangolo o quadrato
				
				Triangles t;
				Quads q;
				
				if(match==3){
					t = Triangles(f1,f2,f3);
					tr->addData(t);
				}	
				if(match==4){
					q = Quads(f1,f2,f3,f4);
					qs->addData(q);	
				}
				int matchN = sscanf((str+1),"%f//%f %f//%f %f//%f %f//%f",&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8);  // triangolo/quadrato + normale
				if(matchN==6){
					t = Triangles(f1,f3,f5,f2,f4,f6);
					tr->addData(t);
				}
				if(matchN==8){
					q = Quads(f1,f3,f5,f7,f2,f4,f6,f8);
					qs->addData(q);
				}
				int matchNT = sscanf((str+1),"%f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f",&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9,&f10,&f11,&f12);  // triangolo/quadrato + texture + normale
				if(matchNT==9){
					t = Triangles(f1,f4,f7,f3,f6,f9);
					tr->addData(t);
				}
				if(matchNT==12){
					q = Quads(f1,f4,f7,f10,f3,f6,f9,f12);
					qs->addData(q);
				}
			}
		}
		fclose(fp);
};