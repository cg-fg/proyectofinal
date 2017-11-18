#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

float	angleX = 0.0, angleY = 0.0, angleZ = 0.0,
transX = 0.0, transY = 0.0, transZ = 0.0;

CCamera objCamera;

GLfloat g_lookupdown = 0.0f;

//materiales
GLfloat SunDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };			// Diffuse Light Values
GLfloat SunSpecular[] = { 0.5, 0.5, 0.5, 1.0 };				// Specular Light Values

GLfloat mat1Diffuse[] = { 1.0,1.0,1.0, 0.25f };			// material 1
GLfloat mat1Specular[] = { 0.25, 0.25, 0.25, 0.25 };

//Texturas
CTexture	t_adoquin, t_pasto, t_barda, t_piedra, t_teja,
			t_puerta, t_pared, t_techo,
			t_pintura1, t_pintura2, t_pintura3, t_pintura4;

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);					// Activamos el valor de inicio del buffer de profundidad
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);				// Hacemos la prueba de profundidad
	glDepthFunc(GL_LEQUAL);				// Tipo de prueba de profundidad a hacer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glEnable(GL_COLOR_MATERIAL);
	
	//Para emplear luces
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, SunDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SunSpecular);
		
	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

//texturas
	glEnable(GL_TEXTURE_2D);

	t_adoquin.LoadTGA("texturas/adoquin.tga");
	t_adoquin.BuildGLTexture();
	t_adoquin.ReleaseImage();

	t_pasto.LoadTGA("texturas/pasto.tga");
	t_pasto.BuildGLTexture();
	t_pasto.ReleaseImage();

	t_pintura1.LoadTGA("texturas/pintura1.tga");
	t_pintura1.BuildGLTexture();
	t_pintura1.ReleaseImage();

	t_pintura2.LoadTGA("texturas/pintura2.tga");
	t_pintura2.BuildGLTexture();
	t_pintura2.ReleaseImage();

	t_pintura3.LoadTGA("texturas/pintura3.tga");
	t_pintura3.BuildGLTexture();
	t_pintura3.ReleaseImage();

	t_pintura4.LoadTGA("texturas/pintura4.tga");
	t_pintura4.BuildGLTexture();
	t_pintura4.ReleaseImage();

	t_barda.LoadTGA("texturas/barda.tga");
	t_barda.BuildGLTexture();
	t_barda.ReleaseImage();

	t_piedra.LoadTGA("texturas/piedra.tga");
	t_piedra.BuildGLTexture();
	t_piedra.ReleaseImage();

	t_teja.LoadTGA("texturas/teja.tga");
	t_teja.BuildGLTexture();
	t_teja.ReleaseImage();

	t_puerta.LoadTGA("texturas/puerta.tga");
	t_puerta.BuildGLTexture();
	t_puerta.ReleaseImage();

	t_pared.LoadTGA("texturas/pared.tga");
	t_pared.BuildGLTexture();
	t_pared.ReleaseImage();

	t_techo.LoadTGA("texturas/techo.tga");
	t_techo.BuildGLTexture();
	t_techo.ReleaseImage();
}

void reshape(int w, int h)
{
	 if (!h)
		h=1;

	 glViewport(0, 0,w,h);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
	 glMatrixMode(GL_MODELVIEW);
	 //glLoadIdentity();
	 return;
}

void prisma(
	GLuint textura0, GLuint textura1,
	GLuint textura2, GLuint textura3,
	GLuint textura4, GLuint textura5
)
{
	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas V�rtice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas V�rtice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas V�rtice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas V�rtice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas V�rtice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas V�rtice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas V�rtice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas V�rtice 7 V7
	};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1Specular);

	glBindTexture(GL_TEXTURE_2D, textura0); //textura 0
	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura1); //textura 1
	glBegin(GL_POLYGON);	//Right 
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura2); //textura 2
	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura3); //textura 3
	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura4); //textura 4
	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura5); //textura 5
	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(4.0, 0.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(4.0, 4.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0, 4.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[7]);
	glEnd();
}

void dibujarLapidas() {
	//cruz 1
	glPushMatrix(); {//cruz-vertical 1
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-2.0, -4.0, -8.0);
		glScalef(0.5, 1.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-horizontal
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-2.0, -3.0, -8.0);
		glScalef(1.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-vertical 2
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-2.0, -2.5, -8.0);
		glScalef(0.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	//cruz 2
	glPushMatrix(); {//cruz-vertical 1
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(2.0, -4.0, -8.0);
		glScalef(0.5, 1.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-horizontal
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(2.0, -3.0, -8.0);
		glScalef(1.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-vertical 2
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(2.0, -2.5, -8.0);
		glScalef(0.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	//cruz 3
	glPushMatrix(); {//cruz-vertical 1
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-6.0, -4.0, -8.0);
		glScalef(0.5, 1.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-horizontal
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-6.0, -3.0, -8.0);
		glScalef(1.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-vertical 2
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(-6.0, -2.5, -8.0);
		glScalef(0.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();
		
	//cruz 4
	glPushMatrix(); {//cruz-vertical 1
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(6.0, -4.0, -8.0);		
		glRotatef(25.0, 0.0, 0.0, 1.0);
		glScalef(0.5, 1.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-horizontal
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(5.65, -3.10, -8.0);
		glRotatef(25.0, 0.0, 0.0, 1.0);
		glScalef(1.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();

	glPushMatrix(); {//cruz-vertical 2
		glColor3f(0.8, 0.0, 0.8);
		glTranslatef(5.40, -2.7, -8.0);
		glRotatef(25.0, 0.0, 0.0, 1.0);
		glScalef(0.5, 0.5, 0.5);
		prisma(t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex, t_barda.GLindex);
	}glPopMatrix();
}

void dibujarEscenario() {		
	//base	
	glPushMatrix(); {
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(40.0, 0.5, 40.0);
		prisma(t_pasto.GLindex, t_pasto.GLindex, t_pasto.GLindex, t_pasto.GLindex, t_pasto.GLindex, t_pasto.GLindex);
	}glPopMatrix();

	//Castillo
	glPushMatrix(); { //piso
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -4.99, 0.0);
		glScalef(16.0, 0.5, 14.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-izq-bajo-1
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-3.0, -3.74, 7.0);
		glScalef(4.0, 2.0, 0.1);
		prisma(t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-izq-bajo-2
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-7.5, -3.74, 7.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-der-bajo
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.5, -3.74, 7.0);
		glScalef(7.0, 2.0, 0.1);
		prisma(t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-restante
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, 0.26, 7.0);
		glScalef(16.0, 6.0, 0.1);
		prisma(t_piedra.GLindex, t_pared.GLindex, t_pintura1.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo-inferior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-8.0, -2.74, 0.0);
		glScalef(0.1, 4.0, 14.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();
	
	glPushMatrix(); { //izquierdo-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-8.0, 1.26, 0.0);
		glScalef(0.1, 4.0, 14.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho-inferior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(8.0, -2.74, 0.0);
		glScalef(0.1, 4.0, 14.0);
		prisma(t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(8.0, 1.26, 0.0);
		glScalef(0.1, 4.0, 14.0);
		prisma(t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-inferior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, -2.74, -7.0);
		glScalef(16.0, 4.0, 0.1);
		prisma(t_pared.GLindex, t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, 1.26, -7.0);
		glScalef(16.0, 4.0, 0.1);
		prisma(t_pared.GLindex, t_pared.GLindex, t_piedra.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-inferior-interior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0, -2.74, -3.0);
		glScalef(8.0, 4.0, 0.1);
		prisma(t_pintura2.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo-inferior-interior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, -2.74, 2.0);
		glScalef(0.1, 4.0, 10.0);
		prisma(t_pared.GLindex, t_pintura3.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();


	glPushMatrix(); { //derecho-inferior-interior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, -2.74, 2.0);
		glScalef(0.1, 4.0, 10.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pintura4.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	//escaleras
	glPushMatrix(); { //plataforma
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -2.79, 1.0);
		glScalef(2.0, 0.3, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.1
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -2.565, -0.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.2
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -2.215, -1.0);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.3
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -1.865, -1.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.4
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -1.515, -2.0);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.5
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -1.165, -2.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 1.6
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -0.815, -2.75);
		glScalef(2.0, 0.35, 0.5);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.1
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -4.565, 4.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.2
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -4.215, 4.0);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.3
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -3.865, 3.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.4
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -3.515, 3.0);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.5
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -3.165, 2.5);
		glScalef(2.0, 0.35, 1.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 2.6
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(0.0, -2.815, 2.25);
		glScalef(2.0, 0.35, 0.5);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.1
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-1.5, -2.565, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.2
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-2.0, -2.215, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.3
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-2.5, -1.865, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.4
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-3.0, -1.515, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.5
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-3.5, -1.165, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 3.6
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(-3.75, -0.815, 1.0);
		glScalef(0.5, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.1
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(1.5, -2.565, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.2
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(2.0, -2.215, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.3
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(2.5, -1.865, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.4
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(3.0, -1.515, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.5
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(3.5, -1.165, 1.0);
		glScalef(1.0, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //escalon 4.6
		glColor3f(0.0, 0.0, 0.25);
		glTranslatef(3.75, -0.815, 1.0);
		glScalef(0.5, 0.35, 2.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	//Suelo del pimer piso
	glPushMatrix(); { //piso-trasero
		glColor3f(0.0, 0.05, 0.25);
		glTranslatef(0.0, -0.7 , -5.0);
		glScalef(16, 0.125, 4.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_techo.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //piso-izquierdo
		glColor3f(0.0, 0.05, 0.25);
		glTranslatef(-6.0, -0.7, 2.0);
		glScalef(4.0, 0.125, 10.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_techo.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //piso-derecho
		glColor3f(0.0, 0.05, 0.25);
		glTranslatef(6.0, -0.7, 2.0);
		glScalef(4.0, 0.125, 10.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_techo.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	//paredes internas del primer piso
	glPushMatrix(); { //trasero-izquierdo-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-2.5, 0.25, -3.0);
		glScalef(3.0, 2.0, 0.1);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-derecho-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(2.5, 0.25, -3.0);
		glScalef(3.0, 2.0, 0.1);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo 0-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 0.25, -6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho 0-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 0.25, -6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo 1-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 0.25, -2.0);
		glScalef(0.1, 2.0, 4.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho 1-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 0.25, -2.0);
		glScalef(0.1, 2.0, 4.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo 2-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 0.25, 4.5);
		glScalef(0.1, 2.0, 5.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho 2-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 0.25, 4.5);
		glScalef(0.1, 2.0, 5.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-restante-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, 2.25, -3.0);
		glScalef(8.0, 2.0, 0.1);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //izquierdo-restante-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 2.25, 0.0);
		glScalef(0.1, 2.0, 14.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //derecho-restante-interior-superior
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 2.25, 0.0);
		glScalef(0.1, 2.0, 14.0);
		prisma(t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex, t_pared.GLindex);
	}glPopMatrix();

	//Techo
	glPushMatrix(); { 
		glColor3f(0.0, 0.10, 0.10);
		glTranslatef(0.0, 3.24, 0.0);
		glScalef(16.0, 0.1, 14.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_techo.GLindex, t_teja.GLindex);
	}glPopMatrix();

	//Torres
	glPushMatrix(); { //frente-frente-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-6.0, 5.25, 7.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-frente-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(6.0, 5.25, 7.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-trasero-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-6.0, 5.25, -3.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-trasero-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(6.0, 5.25, -3.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-frente-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-6.0, 5.25, 3.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-frente-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(6.0, 5.25, 3.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-trasero-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-6.0, 5.25, -7.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-trasero-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(6.0, 5.25, -7.0);
		glScalef(4.0, 4.0, 0.1);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_piedra.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-izq-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-8.0, 5.25, 5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-izq-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(8.0, 5.25, 5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-izq-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-8.0, 5.25, -5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-izq-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(8.0, 5.25, -5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();
	
	glPushMatrix(); { //frente-der-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 5.25, 5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-der-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 5.25, 5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-der-izq
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-4.0, 5.25, -5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-der-der
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(4.0, 5.25, -5.0);
		glScalef(0.1, 4.0, 4.0);
		prisma(t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex, t_piedra.GLindex);
	}glPopMatrix();

	//techos de torres
	glPushMatrix(); { //frente-izq
		glColor3f(0.0, 0.10, 0.10);
		glTranslatef(6.0, 7.25, 5.0);
		glScalef(4.0, 0.1, 4.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_teja.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //frente-der
		glColor3f(0.0, 0.10, 0.10);
		glTranslatef(-6.0, 7.25, 5.0);
		glScalef(4.0, 0.1, 4.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_teja.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-izq
		glColor3f(0.0, 0.10, 0.10);
		glTranslatef(6.0, 7.25, -5.0);
		glScalef(4.0, 0.1, 4.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_teja.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //trasero-der
		glColor3f(0.0, 0.10, 0.10);
		glTranslatef(-6.0, 7.25, -5.0);
		glScalef(4.0, 0.1, 4.0);
		prisma(t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_adoquin.GLindex, t_teja.GLindex);
	}glPopMatrix();

	//Puertas
	//par1-frente
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-1.0, -3.74, 6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(1.0, -3.74, 6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par2-frente-izq
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-7.0, -3.74, 6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-5.0, -3.74, 6.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par3-frente-interno
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-1.0, 0.25, -3.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(1.0, 0.25, -3.5);
		glScalef(0.1, 2.0, 1.0);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par4-trasero-interno-izq
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-3.5, 0.25, -6.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-3.5, 0.25, -4.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par5-trasero-interno-izq
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(3.5, 0.25, -6.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(3.5, 0.25, -4.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par6-frente-interno-izq
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-4.5, 0.25, 0.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(-4.5, 0.25, 2.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//par7-frente-interno-izq
	glPushMatrix(); { //izq
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(4.5, 0.25, 0.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	glPushMatrix(); { //der
		glColor3f(0.5, 0.20, 0.10);
		glTranslatef(4.5, 0.25, 2.0);
		glScalef(1.0, 2.0, 0.1);
		prisma(t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex, t_puerta.GLindex);
	}glPopMatrix();

	//glPushMatrix(); {}glPopMatrix();

}

void display(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	glPushMatrix();
		glRotatef(g_lookupdown, 1.0f, 0, 0);
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);	
		dibujarEscenario();
		dibujarLapidas();
	glPopMatrix();
	glutSwapBuffers ( );
} 

void keyboard(unsigned char key, int x, int y)
{
	 switch (key) 
	 {
		case 27: exit(0);
				 break;

		case 'W':
		case 'w':
			objCamera.Move_Camera(CAMERASPEED + 0.2);
			break;

		case 'S':
		case 's':
			objCamera.Move_Camera(-(CAMERASPEED + 0.2));
			break;

		case 'A':
		case 'a':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
			break;

		case 'D':
		case 'd':
			objCamera.Strafe_Camera(CAMERASPEED + 0.4);
			break;

		case 'Q':
		case 'q':
			transY += 0.75;
			break;

		case 'E':
		case 'e':
			transY -= 0.75;
			break;
	 }
	  glutPostRedisplay();
	  return;
}    

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;
	case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;
	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;
	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;
	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv){
	 glutInit(&argc, argv);
	 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	 glutInitWindowSize (750, 750);
	 glutInitWindowPosition (0, 0);
	 glutCreateWindow ("Proyecto Final");
	 init();
	 glutDisplayFunc(display); 
	 glutReshapeFunc(reshape);
	 glutKeyboardFunc(keyboard);
	 glutSpecialFunc(arrow_keys);
	 glutMainLoop();
	 return 0;
}



