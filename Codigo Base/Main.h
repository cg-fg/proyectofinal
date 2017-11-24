#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>		// Archivo de cabecera para Windows
#include <math.h>			// Archivo de cabecera para Funciones Matem�ticas
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>			// Header File For Standard Library
#include <fstream>
#include <vector>
#include <crtdbg.h>
#include "GL/gl.h"			// Archivo de cabecera para la libreria OpenGL32
#include "GL/glu.h"			// Archivo de cabecera para la libreria GLu32
#include "GL/glaux.h"		// Archivo de cabecera para la libreria Glaux
#include "GL/glext.h"		// Archivo de cabecera para la libreria Glext
#include "Vector.h"
#include "cargadorTGA.h"

int  ManejaTeclado();

struct paramObjCam
{
	CVector PosicionObj;	//La posici�n (x,y,z) del objeto
	CVector PosicionObjAnt;	//La posici�n anterior (x,y,z) del objeto
	CVector Direccion;		//La direcci�n en que se dirige el objeto en forma de vector=(x,y,z)
	CVector DireccionCam;   //La direcci�n que define la posici�n de la c�mara respecto al personaje
	CVector PosicionCam;    //La posici�n de la c�mara que sigue al objeto
	CVector ObjetivoCam;	//El punto (x,y,z) que est� viendo la c�mara; en este caso al objeto

	float VelocidadObj;		//La velocidad a la que se mueve el objeto
	float DistanciaCam;		//La distancia que la c�mara est� separada del objeto
	float AngDir;			//Se usa para llevar control del angulo para el c�lculo del vector de direcci�n
	float AngDirCam;		//Se usa para llevar control del angulo para el c�lculo de posici�n de la c�mara
	float AngObj;			//Se usa para llevar control del �ngulo de rotaci�n para el modelo del objeto

	float CamaraPosAlt;		//Se usa para definir y cambiar si es necesario la altura de la c�mara
	float CamaraObjAlt;		//Se usa para definir y cambiar si es necesario la altura del objetivo de la c�mara

	float escalaX;
	float escalaY;
	float escalaZ;

	bool visible;
	bool caminando;
	bool saltando;
		
};


#endif 