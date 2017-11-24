//
//Godoy Juárez Carlos Eduardo
//Computacion Grafica Grupo 06
//Programa para exentar el examen. Semestre 2018-1


#include "Main.h"
#include "3ds.h"

HDC			hDC=NULL;		// Dispositivo de contexto GDI
HGLRC		hRC=NULL;		// Contexto de renderizado
HWND		hWnd=NULL;		// Manejador de ventana
HINSTANCE	hInstance;		// Instancia de la aplicacion

bool	keys[256];			// Arreglo para el manejo de teclado
bool	active=TRUE;		// Bandera de ventana activa

int glWidth;
int glHeight;

//Variables para texturas

CTga textura[20];

//Variables para iluminacion
GLfloat LightPos[] = { -80.0f, 100.0f, 60.0f, 1.0f };		// Posición de la luz
GLfloat LightAmb[] = { 0.7f,  0.7f, 0.7f, 1.0f };		// Valores de la componente ambiente
GLfloat LightDif[] = { 0.8f,  0.8f, 0.8f, 1.0f };		// Valores de la componente difusa
GLfloat LightSpc[] = { 0.5f,  0.5f, 0.5f, 1.0f };		// Valores de la componente especular
CVector lightPosition;

GLfloat gDefaultAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat gDefaultDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat gDefaultSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat gDefaultShininess = 0.0f;

GLfloat metalAmb[] = { 0.30f,0.30f,0.30f,1.0f };
GLfloat metalDif[] = { 0.40f,0.40f,0.40f,1.0f };
GLfloat metalSpe[] = { 0.80f,0.80f,0.80f,1.0f };
GLfloat metalShi = 9.0f;


//Variables para cámara provisional
CVector Pos;
CVector Obj;
int dirMovCam;

//Variable para cambiar entre render sólido y alambrado
int renderModo;

//Apuntador para primitivas de cuadricas
GLUquadricObj	*e;

//Nombre y ubicación de los modelos
#define FILE_NAME1  "Modelos/modelo1.3ds"
#define FILE_NAME2  "Modelos/modelo2.3ds"
#define FILE_NAME3  "Modelos/modelo3.3ds"

//Contenedores de texturas de cada modelo
CTga textureModel1[4];
CTga textureModel2[4];
CTga textureModel3[4];

//Contenedor de texturas para el escenario
CTga textureName[20];

//Objeto que da acceso a las funciones del cargador 3ds
CLoad3DS g_Load3ds;

//Instancias de la estructura que almacenaran los datos de cada modelo
t3DModel g_3DModel1;
t3DModel g_3DModel2;
t3DModel g_3DModel3;

//Objeto para acceder a las variables de control del personaje
paramObjCam player1;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaracion de WndProc (Procedimiento de ventana)

GLvoid ReDimensionaEscenaGL(GLsizei width, GLsizei height)	// Redimensiona e inicializa la ventana
{
	if (height==0)							// Para que no se presente una division por cero
	{
		height=1;							// la altura se iguala a 1
	}

	glViewport(0,0,width,height);					// Resetea el puerto de vista

	glMatrixMode(GL_PROJECTION);					// Selecciona la Matriz de Proyeccion
	glLoadIdentity();								// Resetea la Matriz de Proyeccion

	// Calcula el radio de aspecto o proporcion de medidas de la ventana
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);
	
	glMatrixMode(GL_MODELVIEW);							// Selecciona la Matriz de Vista de Modelo
	glLoadIdentity();									// Resetea la Matriz de Vista de Modelo

	glWidth=width;
	glHeight=height;
}

int CargaModelos()
{
	if(!g_Load3ds.Load3DSFile(FILE_NAME1, &g_3DModel1, textureModel1))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME2, &g_3DModel2, textureModel2))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME3, &g_3DModel3, textureModel3))
		return 0;
	
	return TRUE;
}

void DescargaModelos()
{
	g_Load3ds.UnLoad3DSFile(&g_3DModel1, textureModel1);
	g_Load3ds.UnLoad3DSFile(&g_3DModel2, textureModel2);
	g_Load3ds.UnLoad3DSFile(&g_3DModel3, textureModel3);
}


void CargaTexturas()
{
	textura[1].LoadTGA("Texturas/fondo2.tga"); //Fondo img
	textura[0].LoadTGA("Texturas/bloques.tga");
	textura[2].LoadTGA("Texturas/kout.tga"); // botes
	textura[3].LoadTGA("Texturas/sorpresa.tga"); // sorpresa
	textura[4].LoadTGA("Texturas/block.tga"); //block
	
}

void DescargaTextura()
{
	textura[1].Elimina();
	textura[0].Elimina();
	textura[2].Elimina();
	textura[3].Elimina();
	textura[4].Elimina();
}


int IniGL(GLvoid)										// Aqui se configuran los parametros iniciales de OpenGL
{
	glShadeModel(GL_SMOOTH);							// Activa Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Fondo negro
	glClearDepth(1.0f);									// Valor para el Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Activa Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a usar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Correccion de cálculos de perspectiva

	glCullFace(GL_BACK);								// Configurado para eliminar caras traseras
	glEnable(GL_CULL_FACE);								// Activa eliminacion de caras ocultas

	/*glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Posicion de la luz0
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);		// Componente ambiente
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);		// Componente difusa
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);		// Componente especular

	glEnable(GL_LIGHT0);					// Activa luz0
	glEnable(GL_LIGHTING);					// Habilita la iluminación*/


	e=gluNewQuadric();

	//Datos de cámara provisional
	Pos = CVector(80.0f, 120.0f, 170.0f);
	Obj = CVector(0.0f, 0.0f, 0.0f);
	dirMovCam = 1;

	renderModo = 2;

	CargaTexturas();
	return TRUE;										
}

void DibujaEjes()
{
	glBegin(GL_LINES);
		//Eje X
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);

		//Eje Y
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f,  100.0f, 0.0f);

		//Eje Z
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f,  100.0f);
	glEnd();

	glPointSize(10.0f);

	glBegin(GL_POINTS);
		//"Flecha" eje X
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);

		//"Flecha" eje Y
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,  100.0f, 0.0f);

		//"Flecha" eje Z
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  100.0f);
	glEnd();

	glPointSize(1.0f);

	glColor3f(1.0f,1.0f,1.0f);
}

void dibujaBote1(float radio, int lados)
{
	float ang;
	float a[3], b[3], c[3], d[3];
	float delta;
	float alt = 8.0f;

	CVector Nv1, Nv2, Nv3, Nv4;

	delta = 360.0f / lados;

	//Primer ciclo: se calculan las normales por plano sin dibujar el bote
	for (int i = 0; i < lados; i++)
	{
		ang = i*delta;

		//a
		a[0] = radio*(float)cos(ang*PI / 180.0f);
		a[1] = 0.0f;
		a[2] = radio*(float)sin(ang*PI / 180.0f);

		//b
		b[0] = a[0];
		b[1] = alt;
		b[2] = a[2];
		ang = (i + 1) * delta;

		//c
		c[0] = radio*(float)cos(ang*PI / 180.0f);
		c[1] = alt;
		c[2] = radio*(float)sin(ang*PI / 180.0f);

		//d
		d[0] = c[0];
		d[1] = 0.0f;
		d[2] = c[2];

		//Se calculan las normales por vértice para los planos del cilindro
		Nv1 = Normaliza(CVector(a[0], a[1], a[2]) - CVector(0.0f, 0.0f, 0.0f));
		Nv2 = Normaliza(CVector(b[0], b[1], b[2]) - CVector(0.0f, alt, 0.0f));
		Nv3 = Normaliza(CVector(c[0], c[1], c[2]) - CVector(0.0f, alt, 0.0f));
		Nv4 = Normaliza(CVector(d[0], d[1], d[2]) - CVector(0.0f, 0.0f, 0.0f));

		glBegin(GL_QUADS);
		glNormal3f(Nv1.x, Nv1.y, Nv1.z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(a[0], a[1], a[2]);
		glNormal3f(Nv2.x, Nv2.y, Nv2.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(b[0], b[1], b[2]);
		glNormal3f(Nv3.x, Nv3.y, Nv3.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(c[0], c[1], c[2]);
		glNormal3f(Nv4.x, Nv4.y, Nv4.z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(d[0], d[1], d[2]);
		glEnd();

		//Tapa superior
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(c[0], c[1], c[2]);
		glVertex3f(b[0], b[1], b[2]);
		glVertex3f(0.0f, alt, 0.0f);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		//Tapa inferior
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(a[0], a[1], a[2]);
		glVertex3f(d[0], d[1], d[2]);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
	}
}

void dibujaBote(float radio, int lados)  // delgado
{
	float ang;
	float a[3], b[3], c[3], d[3];
	float delta;
	float alt = 5.0f;

	CVector Nv1, Nv2, Nv3, Nv4;

	delta = 360.0f / lados;

	//Primer ciclo: se calculan las normales por plano sin dibujar el bote
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < lados; i++)
		{
			if (j == 0) {
				ang = i*delta;

				//a
				a[0] = radio*(float)cos(ang*PI / 180.0f);
				a[1] = 0.0f;
				a[2] = radio*(float)sin(ang*PI / 180.0f);

				//b
				b[0] = a[0];
				b[1] = alt;
				b[2] = a[2];
				ang = (i + 1) * delta;

				//c
				c[0] = radio*(float)cos(ang*PI / 180.0f);
				c[1] = alt;
				c[2] = radio*(float)sin(ang*PI / 180.0f);

				//d
				d[0] = c[0];
				d[1] = 0.0f;
				d[2] = c[2];

				//Se calculan las normales por vértice para los planos del cilindro
				Nv1 = Normaliza(CVector(a[0], a[1], a[2]) - CVector(0.0f, 0.0f, 0.0f));
				Nv2 = Normaliza(CVector(b[0], b[1], b[2]) - CVector(0.0f, alt, 0.0f));
				Nv3 = Normaliza(CVector(c[0], c[1], c[2]) - CVector(0.0f, alt, 0.0f));
				Nv4 = Normaliza(CVector(d[0], d[1], d[2]) - CVector(0.0f, 0.0f, 0.0f));


				glBegin(GL_QUADS);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textura[1].texID);
				glNormal3f(Nv1.x, Nv1.y, Nv1.z);
				glVertex3f(a[0], a[1], a[2]);
				glNormal3f(Nv2.x, Nv2.y, Nv2.z);
				glVertex3f(b[0], b[1], b[2]);
				glNormal3f(Nv3.x, Nv3.y, Nv3.z);
				glVertex3f(c[0], c[1], c[2]);
				glNormal3f(Nv4.x, Nv4.y, Nv4.z);
				glVertex3f(d[0], d[1], d[2]);
				glEnd();

				//Tapa superior
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glVertex3f(c[0], c[1], c[2]);
				glVertex3f(b[0], b[1], b[2]);
				glVertex3f(0.0f, alt, 0.0f);
				glEnd();

				glColor3f(0.0, 0.0, 0.0);

				//Tapa inferior
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3f(a[0], a[1], a[2]);
				glVertex3f(d[0], d[1], d[2]);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glEnd();

				glColor3f(0.0f, 1.0f, 0.0f);
			}
		}
		}
	}

void dibujaEscenario(int render)
{
	if (render == 1)//sólido
		glPolygonMode(GL_FRONT, GL_FILL);
	else if (render == 2)//alambrado
		glPolygonMode(GL_FRONT, GL_LINE);

	//Fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[1].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 0.0f, -25.0f);
			glTexCoord2f(2.0f, 0.0f); glVertex3f(200.0f, 0.0f, -25.0f);
			glTexCoord2f(2.0f, 1.0f); glVertex3f(200.0f, 150.0f,-25.0f);
			glTexCoord2f(0.0, 1.0f);  glVertex3f(-50.0f, 150.0f, -25.0f);
		glEnd();

	//Primer caja
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura[0].texID);
			//front
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(25.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(25.0f, 25.0f, 0.0f);
				glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 25.0f, 0.0f);
			glEnd();
			//top
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 25.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(25.0f, 25.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(25.0f, 25.0f, -25.0f);
				glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 25.0f, -25.0f);
			glEnd();
			//back
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(25.0f, 25.0f, -25.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(25.0f, 0.0f, -25.0f);
				glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -25.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 25.0f, -25.0f);
			glEnd();
			//right
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(25.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(25.0f, 0.0f, -25.0f);
				glTexCoord2f(1.0, 1.0f);  glVertex3f(25.0f, 25.0f, -25.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(25.0f, 25.0f, 0.0f);
			glEnd();
		
			//left
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -25.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 25.0f, 0.0f);
				glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 25.0f, -25.0f);
			glEnd();

			//bottom
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(25.0f, 0.0f, -25.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(25.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -25.0f);
			glEnd();

	glDisable(GL_TEXTURE_2D);

	//Caja2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[3].texID);
		glPushMatrix();
		glTranslatef(40.0, 65.0, 0.0);
		//front
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
			glEnd();
		glPopMatrix();
		//top
		glPushMatrix();
			glTranslatef(40.0, 65.0, 0.0);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
			glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
			glEnd();
		glPopMatrix();
		//back
		glPushMatrix();
		glTranslatef(40.0, 65.0, 0.0);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
			glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
			glEnd();
		glPopMatrix();
		//right
		glPushMatrix();
		glTranslatef(40.0, 65.0, 0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
			glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
		glEnd();
		glPopMatrix();

		//left
		glPushMatrix();
		glTranslatef(40.0, 65.0, 0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
		glEnd();
		glPopMatrix();

		//bottom
		glPushMatrix();
		glTranslatef(40.0, 65.0, 0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
		glEnd();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D); 

	// Caja 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[0].texID);
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(55.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 4
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[0].texID);
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(70.0, 65.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 5
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[0].texID);
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(90.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 6
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[0].texID);
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(105.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 7
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[3].texID);
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(120.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 8
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[0].texID);
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(15.0f, 15.0f, -15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 15.0f, -15.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(135.0, 105.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, -15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -15.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 9
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[4].texID);
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(135.0, 20.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 10
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[4].texID);
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(135.0, 10.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 11
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[4].texID);
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(135.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Caja 12
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura[4].texID);
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();
	//top
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 10.0f, 0.0f);
	glTexCoord2f(0.0, 1.0f);  glVertex3f(0.0f, 10.0f, -10.0f);
	glEnd();
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(145.0, 30.0, 0.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 1.0f);  glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Primer tubo



	//BOTES

		//bote1
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura[0].texID);
			glTranslatef(0.0f, 25.0f, -15.0f);
			dibujaBote(4, 100);
			glDisable(GL_TEXTURE_2D);

		glPopMatrix();

	//Se regresa al modo de dibujo sólido en caso de haber usado modo alambrado
	if (render == 2)
		glPolygonMode(GL_FRONT, GL_FILL);

	//Siempre al final se vuelve al color blanco (default de OpenGL) para que otros gráficos no se vean afectados
	glColor3f(1.0f, 1.0f, 1.0f);
}

int RenderizaEscena(GLvoid)								// Aqui se dibuja todo lo que aparecera en la ventana
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//gluLookAt(80.0f, 120.0f, 170.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);
	gluLookAt(Pos.x, Pos.y, Pos.z, Obj.x, Obj.y, Obj.z, 0, 1, 0);
	
	DibujaEjes();
	dibujaEscenario(renderModo);
					
	return TRUE;
}

/*void ActualizaLuzParam() 
{
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Posicion de la luz0
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);		// Componente ambiente
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);		// Componente difusa
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);		// Componente especular

	lightPosition.x = LightPos[0];
	lightPosition.y = LightPos[1];
	lightPosition.z = LightPos[2];
}*/

/*void DibujaLuz(CVector l)
{
	//Dibuja una esfera que representa la fuente luminosa
	glDisable(GL_LIGHTING);			// Deshabilita iluminación

	glPushMatrix();
	glTranslatef(l.x, l.y, l.z);	// Traslada a la posicion de la luz

	glColor3f(1.0f, 1.0f, 0.0f);	// Color amarillo
	gluSphere(e, 1.0f, 16, 8);	// Dibuja la esfera
	glPopMatrix();


	glEnable(GL_LIGHTING);			// Habilita Iluminación
	glColor3f(1.0f, 1.0f, 1.0f);
}*/

GLvoid DestruyeVentanaOGL(GLvoid)						// Elimina la ventana apropiadamente
{
	if (hRC)											// Si existe un contexto de renderizado...
	{
		if (!wglMakeCurrent(NULL,NULL))					// Si no se pueden liberar los contextos DC y RC...
		{
			MessageBox(NULL,"Falla al liberar DC y RC.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Si no se puede eliminar el RC?
		{
			MessageBox(NULL,"Falla al liberar el contexto de renderizado.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Se pone RC en NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Si no se puede eliminar el DC
	{
		MessageBox(NULL,"Falla al liberar el contexto de renderizado.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Se pone DC en NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Si no se puede destruir la ventana
	{
		MessageBox(NULL,"No se pudo liberar hWnd.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Se pone hWnd en NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Si no se puede eliminar el registro de la clase
	{
		MessageBox(NULL,"No se pudo eliminar el registro de la clase.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Se pone hInstance en NULL
	}
}

//	Este código crea la ventana de OpenGL.  Parámetros:					
//	title			- Titulo en la parte superior de la ventana			
//	width			- Ancho de la ventana								
//	height			- Alto de la ventana								
//	bits			- Número de bits a usar para el color (8/16/24/32)	
  
BOOL CreaVentanaOGL(char* title, int width, int height, int bits)
{
	GLuint	PixelFormat;				// Guarda el resultado despues de determinar el formato a usar
	WNDCLASS	wc;						// Estructura de la clase ventana
	DWORD		dwExStyle;				// Estilo extendido de ventana
	DWORD		dwStyle;				// Estilo de ventana
	RECT		WindowRect;				// Guarda los valores Superior Izquierdo / Inferior Derecho del rectángulo
	WindowRect.left=(long)0;			// Inicia el valor Izquierdo a 0
	WindowRect.right=(long)width;		// Inicia el valor Derecho al ancho especificado
	WindowRect.top=(long)0;				// Inicia el valor Superior a 0
	WindowRect.bottom=(long)height;		// Inicia el valor Inferior al alto especificado

	hInstance			= GetModuleHandle(NULL);				// Guarda una instancia de la ventana
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redibuja el contenido de la ventana al redimensionarla
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// Maneja los mensajes para WndProc
	wc.cbClsExtra		= 0;									// Ningun dato extra para la clase
	wc.cbWndExtra		= 0;									// Ningun dato extra para la ventana
	wc.hInstance		= hInstance;							// Inicia la instancia
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Carga el ícono por defecto
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Carga el puntero de flecha
	wc.hbrBackground	= NULL;									// No se requiere ningun fondo
	wc.lpszMenuName		= NULL;									// No hay menú en la ventana
	wc.lpszClassName	= "OpenGL";								// Fija el nombre de la clase.

	if (!RegisterClass(&wc))									// Intenta registrar la clase de ventana
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}
		
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;					// Estilo extendido de ventana
	dwStyle=WS_OVERLAPPEDWINDOW;									// Estilo de ventana

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Ajusta la ventana al tamaño especificado

	// Crea la ventana
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Estilo extendido para la ventana
								"OpenGL",							// Nombre de la clase
								title,								// Título de la ventana
								dwStyle |							// Definición del estilo de la ventana
								WS_CLIPSIBLINGS |					// Estilo requerido de la ventana
								WS_CLIPCHILDREN,					// Estilo requerido de la ventana
								0, 0,								// Posición de la ventana
								WindowRect.right-WindowRect.left,	// Calcula el ancho de la ventana
								WindowRect.bottom-WindowRect.top,	// Calcula el alto de la ventana
								NULL,								// No hay ventana superior
								NULL,								// No hay menú
								hInstance,							// Instancia
								NULL)))								// No se pasa nada a WM_CREATE
	{
		DestruyeVentanaOGL();										// Resetea el despliegue
		MessageBox(NULL,"Error al crear la ventana.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Si no se creo el contexto de dispositivo...
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede crear un contexto de dispositivo GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Si Windows no encontró un formato de pixel compatible
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede encontrar un formato de pixel compatible.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Si no se pudo habilitar el formato de pixel
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede usar el formato de pixel.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(hRC=wglCreateContext(hDC)))				// Si no se creo el contexto de renderizado
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede crear un contexto de renderizado GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					// Si no se puede activar el contexto de renderizado
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede usar el contexto de renderizado GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	ShowWindow(hWnd,SW_SHOW);				// Muestra la ventana
	SetForegroundWindow(hWnd);				// Le da la prioridad mas alta
	SetFocus(hWnd);							// Pasa el foco del teclado a la ventana
	ReDimensionaEscenaGL(width, height);	// Inicia la perspectiva para la ventana OGL

	if (!IniGL())							// Si no se inicializa la ventana creada
	{
		DestruyeVentanaOGL();				// Resetea el despliegue
		MessageBox(NULL,"Falla en la inicialización.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	return TRUE;							// Todo correcto
}

LRESULT CALLBACK WndProc(	HWND	hWnd,	// Manejador para esta ventana
							UINT	uMsg,	// Mensaje para esta ventana
							WPARAM	wParam,	// Información adicional del mensaje
							LPARAM	lParam)	// Información adicional del mensaje
{
	switch (uMsg)							// Revisa los mensajes de la ventana
	{
		case WM_ACTIVATE:					// Revisa el mensaje de activación de ventana
		{
			if (!HIWORD(wParam))			// Revisa el estado de minimización
			{
				active=TRUE;				// El programa está activo
			}
			else
			{
				active=FALSE;				// El programa no está activo
			}

			return 0;						// Regresa al ciclo de mensajes
		}

		case WM_SYSCOMMAND:					// Intercepta comandos del sistema
		{
			switch (wParam)					// Revisa llamadas del sistema
			{
				case SC_SCREENSAVE:			// ¿Screensaver tratando de iniciar?
				case SC_MONITORPOWER:		// ¿Monitor tratando de entrar a modo de ahorro de energía?
				return 0;					// Evita que suceda
			}
			break;							// Sale del caso
		}

		case WM_CLOSE:						// Si se recibe un mensaje de cerrar...
		{
			PostQuitMessage(0);				// Se manda el mensaje de salida
			return 0;						// y se regresa al ciclo
		}

		case WM_KEYDOWN:					// Si se está presionando una tecla...
		{
			keys[wParam] = TRUE;			// Si es así, se marca como TRUE
			return 0;						// y se regresa al ciclo
		}

		case WM_KEYUP:						// ¿Se ha soltado una tecla?
		{
			keys[wParam] = FALSE;			// Si es así, se marca como FALSE
			return 0;						// y se regresa al ciclo
		}

		case WM_SIZE:						// Si se redimensiona la ventana...
		{
			ReDimensionaEscenaGL(LOWORD(lParam),HIWORD(lParam));  	// LoWord=Width, HiWord=Height
			return 0;						// y se regresa al ciclo
		}
	}

	// Pasa todos los mensajes no considerados a DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

// Este es el punto de entrada al programa; la función principal 
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instancia
					HINSTANCE	hPrevInstance,		// Instancia previa
					LPSTR		lpCmdLine,			// Parametros de la linea de comandos
					int			nCmdShow)			// Muestra el estado de la ventana
{
	MSG		msg;									// Estructura de mensajes de la ventana
	BOOL	done=FALSE;								// Variable booleana para salir del ciclo

	// Crea la ventana OpenGL
	if (!CreaVentanaOGL("Laboratorio de Computación Gráfica",640,480,16))
	{
		return 0;									// Salir del programa si la ventana no fue creada
	}

	while(!done)									// Mientras done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Revisa si hay mensajes en espera
		{
			if (msg.message==WM_QUIT)				// Si se ha recibido el mensje de salir...
			{
				done=TRUE;							// Entonces done=TRUE
			}
			else									// Si no, Procesa los mensajes de la ventana
			{
				TranslateMessage(&msg);				// Traduce el mensaje
				DispatchMessage(&msg);				// Envia el mensaje
			}
		}
		else										// Si no hay mensajes...
		{
			// Dibuja la escena. 
			if (active)								// Si está activo el programa...
			{
				if (keys[VK_ESCAPE])				// Si se ha presionado ESC
				{
					done=TRUE;						// ESC indica el termino del programa
				}
				else								// De lo contrario, actualiza la pantalla
				{
					RenderizaEscena();				// Dibuja la escena
					SwapBuffers(hDC);				// Intercambia los Buffers (Double Buffering)
				}

				if(!ManejaTeclado()) return 0;
			}
			
		}
	}

	// Finalización del programa
	DescargaTextura();
	DestruyeVentanaOGL();							// Destruye la ventana
	return (msg.wParam);							// Sale del programa
}

int ManejaTeclado()
{
	if(keys[VK_UP])
	{		
		
	}
	if(keys[VK_DOWN])
	{
		
	}
	if(keys[VK_LEFT])
	{
		
	}
	if(keys[VK_RIGHT])
	{
		
	}

	if(keys[VK_PRIOR])
	{
		
	}
	if(keys[VK_NEXT])
	{
		
	}

	if(keys[VK_HOME])
	{
		
	}

	if(keys[VK_END])
	{
		
	}

	//Manejo de la cámara provisional
	if (GetKeyState(VK_LSHIFT) & 0x80)
	{
		dirMovCam = 2;
	}
	else
		dirMovCam = 1;

	if (keys['Q'])
	{
		if (dirMovCam == 1)
			Pos.x += 0.05f;
		else
			Pos.x -= 0.05f;
	}

	if (keys['W'])
	{
		if (dirMovCam == 1)
			Pos.y += 0.03f;
		else
			Pos.y -= 0.03f;
	}

	if (keys['E'])
	{
		if (dirMovCam == 1)
			Pos.z += 0.03f;
		else
			Pos.z -= 0.03f;
	}

	if (keys['A'])
	{
		if (dirMovCam == 1)
			Obj.x += 0.03f;
		else
			Obj.x -= 0.03f;
	}

	if (keys['S'])
	{
		if (dirMovCam == 1)
			Obj.y += 0.03f;
		else
			Obj.y -= 0.03f;
	}

	if (keys['D'])
	{
		if (dirMovCam == 1)
			Obj.z += 0.03f;
		else
			Obj.z -= 0.03f;
	}

	if ((GetAsyncKeyState(VK_TAB) & 1) == 1)
	{
		if (renderModo == 1)
			renderModo = 2;
		else
			renderModo = 1;
	}

	return TRUE;
}