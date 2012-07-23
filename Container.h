/*
 *  Container.h
 *
 *  Created by Jacopo Volpin on 13/04/10.
 *
 *	classe di appoggio per immagazzinamento dati. Essendo templetizzata è stata utilizzata per oggetti diffrenti,
 *	in particolare con gli oggetti Triangles, Quads e Normals.
 *	Offre metodi per il get del puntatore associato all'oggetto desiderato oltre che funzioni di allungamento 
 *	automatizzate.
 */

#include "OpenGL/gl.h" 
#include "GLUT/glut.h"
#include "OpenGL/glu.h"
#include "stdio.h"
#include "string.h"
#include "Triangles.h"
#include "Quads.h"
#include<iostream>

#ifndef CONTAINER_H
#define CONTAINER_H

using namespace std;

template <typename T>
class Container {

private:
	
	T *data;
	bool created;
	int size;
	int n_data;
	
public:
	
	Container();
	void initiateData();
	bool isInitialized();
	void addData(T);
	void modifySize();
	int getSize();
	T* getData(int);
	
};


template <typename T> Container<T>::Container(){
	
	size=100;
	n_data=0;
	created=false;
};

template <typename T> void Container<T>::initiateData(){
	
	data = new T[size];
	created = true;
};

template <typename T> bool Container<T>::isInitialized(){
	if(n_data>0 && created)
		return created;
	else
		return false;
};

template <typename T> void Container<T>::addData(T n){
	
	if(n_data==size)
		modifySize();
		
	data[n_data]=n;
	n_data++;
};

template <typename T> void Container<T>::modifySize(){
	
	T *newData = new T[size*2];
	for (int i=0; i<n_data; i++) {
		newData[i]=data[i];
	}
	size=size*2;
	delete data;
	data = newData;
};

template <typename T> int Container<T>::getSize(){
	return n_data;
};

template <typename T> T* Container<T>::getData(int pos){
	return &(data[pos]);
};

#endif
