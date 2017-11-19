
//////////////////////////////////////////////////////////////////
//////////// Laboratorio de Computacion Gráfica //////////////////

//////////// Proyecto Final.  Grupo: 01			//////////////////

//////////// Godoy Juárez Carlos Eduardo		//////////////////
//////////// González Colín Fernando			//////////////////

//////////////////////////////////////////////////////////////////

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

//animaciones
int sf1 = 0, sf2 = 0, sf3 = 0;

//angulos
int angBat = 0.0, angf3 = 0.0,
angp1, angp2, angp3, angp4, angp5, angp6, angp7;

//movimiento
float	movyf1 = -5.0, movxf1 = 0.0, movyf2 = 0.0, movxf2 = 0.0,
movxf3 = 0.0, movzf3 = 0.0;

//materiales
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat mat1Diffuse[] = { 1.0,1.0,1.0, 0.25f };			// material 1
GLfloat mat1Specular[] = { 0.25, 0.25, 0.25, 0.25 };

//Texturas
CTexture	t_adoquin, t_pasto, t_barda, t_piedra, t_teja,
t_puerta, t_pared, t_techo, t_bat, t_cielo,
t_fantasma1, t_fantasma2, t_fantasma3,
t_pintura1, t_pintura2, t_pintura3, t_pintura4,

//carlos
t_arbolcopa, t_tronco, t_last, t_hyena, t_earth,t_rip1,t_rip2,t_skeledog,t_flower,t_mantel,
t_verja, t_legion, t_rock, t_welcome, t_uchiha, t_kout, t_koutback, t_shield, t_chain, t_mace, t_rope1, t_lamina, t_headguillo, t_polmil, t_lanzas, t_transparente;

//Figuras
CFiguras objeto1;

// Variables used to calculate frames per second: (Windows)
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

//modelos
CModel escultura;

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);					// Activamos el valor de inicio del buffer de profundidad
	glEnable(GL_DEPTH_TEST);				// Hacemos la prueba de profundidad
	glDepthFunc(GL_LEQUAL);				// Tipo de prueba de profundidad a hacer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	//Para emplear luces
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);			// Turn Blending On

								//glLightfv(GL_LIGHT1, GL_DIFFUSE, SunDiffuse);
								//glLightfv(GL_LIGHT1, GL_SPECULAR, SunSpecular);

	objCamera.Position_Camera(0.0, -3.8f, 8.5, 0, 2.5f, 0, 0, 1, 0);

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

	t_bat.LoadTGA("texturas/bat.tga");
	t_bat.BuildGLTexture();
	t_bat.ReleaseImage();

	t_cielo.LoadTGA("texturas/cielo.tga");
	t_cielo.BuildGLTexture();
	t_cielo.ReleaseImage();

	t_fantasma1.LoadTGA("texturas/fantasma1.tga");
	t_fantasma1.BuildGLTexture();
	t_fantasma1.ReleaseImage();

	t_fantasma2.LoadTGA("texturas/fantasma2.tga");
	t_fantasma2.BuildGLTexture();
	t_fantasma2.ReleaseImage();

	t_fantasma3.LoadTGA("texturas/fantasma3.tga");
	t_fantasma3.BuildGLTexture();
	t_fantasma3.ReleaseImage();

	//carlos
	t_verja.LoadTGA("texturas/verja.tga");
	t_verja.BuildGLTexture();
	t_verja.ReleaseImage();

	t_legion.LoadTGA("texturas/legion.tga");
	t_legion.BuildGLTexture();
	t_legion.ReleaseImage();

	t_rock.LoadTGA("texturas/rock.tga");
	t_rock.BuildGLTexture();
	t_rock.ReleaseImage();

	t_welcome.LoadTGA("texturas/welcome.tga");
	t_welcome.BuildGLTexture();
	t_welcome.ReleaseImage();

	t_uchiha.LoadTGA("texturas/uchiha.tga");
	t_uchiha.BuildGLTexture();
	t_uchiha.ReleaseImage();

	t_kout.LoadTGA("texturas/kout.tga");
	t_kout.BuildGLTexture();
	t_kout.ReleaseImage();

	t_koutback.LoadTGA("texturas/koutback.tga");
	t_koutback.BuildGLTexture();
	t_koutback.ReleaseImage();

	t_arbolcopa.LoadTGA("texturas/arbolcopa.tga");
	t_arbolcopa.BuildGLTexture();
	t_arbolcopa.ReleaseImage();

	t_tronco.LoadTGA("texturas/tronco.tga");
	t_tronco.BuildGLTexture();
	t_tronco.ReleaseImage();

	t_shield.LoadTGA("texturas/shield.tga");
	t_shield.BuildGLTexture();
	t_shield.ReleaseImage();

	t_chain.LoadTGA("texturas/chain.tga");
	t_chain.BuildGLTexture();
	t_chain.ReleaseImage();

	t_mace.LoadTGA("texturas/mace.tga");
	t_mace.BuildGLTexture();
	t_mace.ReleaseImage();

	t_rope1.LoadTGA("texturas/rope1.tga");
	t_rope1.BuildGLTexture();
	t_rope1.ReleaseImage();

	t_lamina.LoadTGA("texturas/lamina.tga");
	t_lamina.BuildGLTexture();
	t_lamina.ReleaseImage();

	t_headguillo.LoadTGA("texturas/headguillo.tga");
	t_headguillo.BuildGLTexture();
	t_headguillo.ReleaseImage();

	t_transparente.LoadTGA("texturas/transparente.tga");
	t_transparente.BuildGLTexture();
	t_transparente.ReleaseImage();

	t_polmil.LoadTGA("texturas/polmil.tga");
	t_polmil.BuildGLTexture();
	t_polmil.ReleaseImage();

	t_lanzas.LoadTGA("texturas/lanzas.tga");
	t_lanzas.BuildGLTexture();
	t_lanzas.ReleaseImage();

	t_last.LoadTGA("texturas/last.tga");
	t_last.BuildGLTexture();
	t_last.ReleaseImage();

	t_hyena.LoadTGA("texturas/hyena.tga");
	t_hyena.BuildGLTexture();
	t_hyena.ReleaseImage();

	t_earth.LoadTGA("texturas/earth.tga");
	t_earth.BuildGLTexture();
	t_earth.ReleaseImage();

	t_rip1.LoadTGA("texturas/rip1.tga");
	t_rip1.BuildGLTexture();
	t_rip1.ReleaseImage();

	t_rip2.LoadTGA("texturas/rip2.tga");
	t_rip2.BuildGLTexture();
	t_rip2.ReleaseImage();

	t_skeledog.LoadTGA("texturas/skeledog.tga");
	t_skeledog.BuildGLTexture();
	t_skeledog.ReleaseImage();

	t_flower.LoadTGA("texturas/flower.tga");
	t_flower.BuildGLTexture();
	t_flower.ReleaseImage();

	t_mantel.LoadTGA("texturas/mantel.tga");
	t_mantel.BuildGLTexture();
	t_mantel.ReleaseImage();
	

	//modelos
	escultura._3dsLoad("modelos/greek--culpture.3ds");
}

void reshape(int w, int h)
{
	if (!h)
		h = 1;

	glViewport(0, 0, w, h);
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
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
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

void mostrarModelos() {
	glPushMatrix(); {
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(6.0, -3.0, 5.0);
		glScalef(0.15, 0.15, 0.15);
		escultura.GLrender(NULL, _SHADED, 1.0);
	}glPopMatrix();

}

void dibujarMurcielagos() {
	glPushMatrix(); {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, t_bat.GLindex);
		glRotatef(-angBat, 0.0, 1.0, 0.0);
		glTranslatef(8.0, 20.0, 0.0);
		glBegin(GL_QUADS); { //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-3.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0, 0.0, 1.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(3.0, 0.0, -1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-3.0, 0.0, -1.0);
		}glEnd();
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	glPushMatrix(); {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, t_bat.GLindex);
		glRotatef(angBat, 0.0, 1.0, 0.0);
		glTranslatef(8.0, 25.0, 0.0);
		glBegin(GL_QUADS); { //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0, 0.0, 1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0, 0.0, 1.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0, 0.0, -1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0, 0.0, -1.0);
		}glEnd();
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();
}

void dibujarFantasmas() {
	glPushMatrix(); {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, t_fantasma1.GLindex);
		glTranslatef(movxf1, movyf1, -8.5);
		glRotatef(180, 0.0, 1.0, 0.0);
		glBegin(GL_QUADS); { //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.8, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4, 0.8, 0.0);
		}glEnd();
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	glPushMatrix(); {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, t_fantasma3.GLindex);
		glTranslatef(movxf2, movyf2, -8.5);
		glRotatef(180, 0.0, 1.0, 0.0);
		glBegin(GL_QUADS); { //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.8, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4, 0.8, 0.0);
		}glEnd();
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	glPushMatrix(); {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, t_fantasma2.GLindex);
		glTranslatef(movxf3, -3.95, movzf3);
		glRotatef(angf3, 0.0, 1.0, 0.0);
		glBegin(GL_QUADS); { //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, -0.8, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.8, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4, 0.8, 0.0);
		}glEnd();
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

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
	//Cielo
	glPushMatrix(); {
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.0, 30.0, 0.0);
		glScalef(150.0, 0.5, 150.0);
		prisma(t_cielo.GLindex, t_cielo.GLindex, t_cielo.GLindex, t_cielo.GLindex, t_cielo.GLindex, t_cielo.GLindex);
	}glPopMatrix();


	//carlos
	//Arbol tronco
	glPushMatrix(); {
		glColor3f(0.47, 0.33, 0.28);
		glTranslatef(13.0, -5.5, 16.0);
		objeto1.cilindro(1.0, 3.0, 25.0, t_tronco.GLindex);
	} glPopMatrix();

	//Arbol Parte Arriba
	glPushMatrix(); {
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(13.0, -2.5, 16.0);
		objeto1.cono(7.0, 2.5, 25.0, t_arbolcopa.GLindex);
	} glPopMatrix();

	//Barda Izquierda Enfrente
	glPushMatrix(); {
		glTranslatef(-11.0, -3.5, 20.0);
		glScalef(17.8, 2.0, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		prisma(t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Barda Derecha Enfrente
	glPushMatrix(); {
		glTranslatef(11.0, -3.5, 20.0);
		glScalef(17.8, 2.0, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		prisma(t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Barda Atras
	glPushMatrix(); {
		glTranslatef(0.0, -3.5, -20.0);
		glScalef(40.8, 2.0, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		prisma(t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Barda Costado Derecho
	glPushMatrix(); {
		glTranslatef(20.0, -3.5, 0.0);
		glScalef(0.0, 2.0, 42.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		prisma(t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Barda Costado Izquierdo
	glPushMatrix(); {
		glTranslatef(-20.0, -3.5, 0.0);
		glScalef(0.0, 2.0, 42.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		prisma(t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex, t_verja.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Caminito
	glPushMatrix(); {
		glTranslatef(0.0, -4.6, 15.0);
		glScalef(2.0, 0.0, 10.0);
		prisma(t_rock.GLindex, t_rock.GLindex, t_rock.GLindex, t_rock.GLindex, t_rock.GLindex, t_rock.GLindex);
	}glPopMatrix();

	//Letrero Keep Out
	glPushMatrix(); {  // mensaje
		glTranslatef(-4.3, -1.6, 13.0);
		glScalef(3.0, 2.0, 0.5);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		prisma(t_kout.GLindex, t_koutback.GLindex, t_kout.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Palito que lo sostiene
	glPushMatrix(); {
		glTranslatef(-4.3, -3.6, 13.0);
		glScalef(1.0, 2.0, 0.2);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Tapete Welcome
	glPushMatrix(); {
		glTranslatef(0.0, -4.6, 8.5);
		glScalef(3.0, 0.0, 3.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_welcome.GLindex, t_welcome.GLindex, t_welcome.GLindex, t_welcome.GLindex, t_welcome.GLindex, t_welcome.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Simbolo Legion
	glPushMatrix(); {
		glTranslatef(0.0, 0.26, 7.3);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_legion.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Simbolo Uchiha Izquierdo
	glPushMatrix(); {
		glTranslatef(-5.9, 5.1, 7.3);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_uchiha.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Simbolo Uchiha Derecha
	glPushMatrix(); {
		glTranslatef(5.9, 5.1, 7.3);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_uchiha.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Cementerios

	//Cementerio izquierda
	//base	
	glPushMatrix(); {
		glTranslatef(-45.0, -4.5, 0.0);
		glScalef(40.0, 0.1, 40.0);
		prisma(t_earth.GLindex, t_earth.GLindex, t_earth.GLindex, t_earth.GLindex, t_earth.GLindex, t_earth.GLindex);
	}glPopMatrix();

	//Lapidas Cementerio izq

	//Lapida 1
	glPushMatrix(); {
		glTranslatef(-60.0, -2.5, -14.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip1.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 2
	glPushMatrix(); {
		glTranslatef(-50.0, -2.5, -14.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 3
	glPushMatrix(); {
		glTranslatef(-40.0, -2.5, -14.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip1.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 4
	glPushMatrix(); {
		glTranslatef(-30.0, -2.5, -14.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 5
	glPushMatrix(); {
		glTranslatef(-60.0, -2.5, -6.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 6
	glPushMatrix(); {
		glTranslatef(-50.0, -2.5, -6.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 7
	glPushMatrix(); {
		glTranslatef(-40.0, -2.5, -6.0);
		glRotatef(-20.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip1.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 8
	glPushMatrix(); {
		glTranslatef(-30.0, -2.5, -6.0);
		glRotatef(-20.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 9
	glPushMatrix(); {
		glTranslatef(-40.0, -2.5, 2.0);
		glRotatef(-50.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Lapida 10
	glPushMatrix(); {
		glTranslatef(-60.0, -2.5, 8.0);
		glRotatef(-79.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip2.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();


	//Lapida 11
	glPushMatrix(); {
		glTranslatef(-53.0, -2.5, 7.0);
		glRotatef(-59.0, 1.0, 0.0, 0.0);
		glScalef(3.0, 3.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rip1.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Skeledog
	glPushMatrix(); {
		glTranslatef(-40.0, -2.5, 7.0);
		glScalef(6.0, 6.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_skeledog.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//flowers (dinosaurio)(Bekar)
	glPushMatrix(); {
		glTranslatef(-30.0, -2.5, 12.0);
		glScalef(6.0, 6.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_flower.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();


	//base	
	glPushMatrix(); {
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(150.0, 0.5, 150.0);
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
		glTranslatef(0.0, -0.7, -5.0);
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

void dibujarSalaTortura() {

	//Silla 
	//Pata enfrente izq
	glPushMatrix(); {
		glTranslatef(-0.4, -0.4, -5.3);
		glScalef(0.3, 0.7, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Pata enfrente der
	glPushMatrix(); {
		glTranslatef(0.4, -0.4, -5.3);
		glScalef(0.3, 0.7, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Pata atras izq
	glPushMatrix(); {
		glTranslatef(-0.4, -0.4, -5.9);
		glScalef(0.3, 0.7, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Pata atras der
	glPushMatrix(); {
		glTranslatef(0.4, -0.4, -5.9);
		glScalef(0.3, 0.7, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Base silla donde te sientas
	glPushMatrix(); {
		glTranslatef(0.0, 0.0, -5.6);
		glScalef(1.2, 0.03, 1.2);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Respaldo

	//Respaldo silla, "columna" izquierda
	glPushMatrix(); {
		glTranslatef(-0.5, 0.6, -6.0);
		glScalef(0.2, 1.2, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Respaldo silla, "columna" derecha
	glPushMatrix(); {
		glTranslatef(0.5, 0.6, -6.0);
		glScalef(0.2, 1.2, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Respaldo silla, columnitas intermedias 
	//columnita intermedia 1
	glPushMatrix(); {
		glTranslatef(-0.2, 0.4, -6.0);
		glScalef(0.08, 0.8, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//columnita intermedia 2
	glPushMatrix(); {
		glTranslatef(0.2, 0.4, -6.0);
		glScalef(0.08, 0.8, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Respaldo, el "respaldo" (rectangulo)
	glPushMatrix(); {
		glTranslatef(0.0, 0.8, -6.0);
		glScalef(0.8, 0.2, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Brazos de la silla
	//Brazo izquierdo
	glPushMatrix(); {
		glTranslatef(-0.5, 0.4, -5.5);
		glScalef(0.2, 0.1, 0.9);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Brazo derecho
	glPushMatrix(); {
		glTranslatef(0.5, 0.4, -5.5);
		glScalef(0.2, 0.1, 0.9);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Sostiene brazo izq
	glPushMatrix(); {
		glTranslatef(-0.45, 0.2, -5.2);
		glScalef(0.2, 0.3, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Sostiene brazo derecho
	glPushMatrix(); {
		glTranslatef(0.45, 0.2, -5.2);
		glScalef(0.2, 0.3, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Escudo pared
	glPushMatrix(); {
		glTranslatef(-1.4, 0.26, -6.3);
		glRotatef(-43.0, 1.0, 0.0, 0.0);
		glScalef(1.0, 1.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_shield.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Cadenas
	glPushMatrix(); {
		glTranslatef(2.3, 1.8, -6.8);
		glScalef(2.0, 2.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_chain.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Mace
	glPushMatrix(); {
		glTranslatef(-2.3, 1.8, -6.8);
		glScalef(1.5, 1.5, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_mace.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Simbolo Policia Militar
	glPushMatrix(); {
		glTranslatef(0.0, 2.0, -6.8);
		glScalef(1.4, 1.4, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_polmil.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Skull con su corona ( se llama lanzas la imagen)
	glPushMatrix(); {
		glTranslatef(1.7, 0.4, -6.8);
		glScalef(0.8, 0.8, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_lanzas.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Ultima cena
	glPushMatrix(); {
		glTranslatef(1.0, -2.65, -6.7);
		glScalef(6.0, 4.0, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_last.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//hyena
	glPushMatrix(); {
		glTranslatef(6.0, -4.3, -6.2);
		glScalef(2.0, 1.0, 1.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_hyena.GLindex, t_transparente.GLindex, t_hyena.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//MESA
	//Patita derecha atras
	glPushMatrix(); {
		glTranslatef(7.0, -0.1, -5.2);
		glScalef(0.1, 1.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Patita izquierda atras 
	glPushMatrix(); {
		glTranslatef(5.0, -0.1, -2.2);
		glScalef(0.1, 1.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Patita derecha enfrente
	glPushMatrix(); {
		glTranslatef(7.0, -0.1, -2.2);
		glScalef(0.1, 1.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Patita izquierda enfrente
	glPushMatrix(); {
		glTranslatef(5.0, -0.1, -5.2);
		glScalef(0.1, 1.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Plano donde va la comida, la "mesa"
	glPushMatrix(); {
		glTranslatef(6.0, 0.5, -3.5);
		glScalef(2.5, 0.2, 4.0);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Mantel
	glPushMatrix(); {
		glTranslatef(6.0, 0.65, -3.5);
		glScalef(2.0, 0.05, 4.2);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_mantel.GLindex, t_transparente.GLindex, t_mantel.GLindex, t_mantel.GLindex, t_mantel.GLindex, t_mantel.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//AGREGAR COMIDA EN MODELO 3DS :C


	//GUILLOTINA
	//Patita izquierda
	glPushMatrix(); {
		glTranslatef(-7.0, -0.3, -5.2);
		glScalef(0.3, 0.2, 1.4);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Patita Derecha
	glPushMatrix(); {
		glTranslatef(-5.0, -0.5, -5.2);
		glScalef(0.3, 0.2, 1.4);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Columna izquierda 
	glPushMatrix(); {
		glTranslatef(-7.0, 0.8, -5.2);
		glScalef(0.3, 3.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Columna derecha 
	glPushMatrix(); {
		glTranslatef(-5.0, 0.8, -5.2);
		glScalef(0.3, 3.0, 0.3);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Palito sostiene inclinado izquierda atras
	glPushMatrix(); {
		glTranslatef(-7.0, 0.0, -5.6);
		glRotatef(35.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 1.0, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Palito sostiene inclinado derecho atras
	glPushMatrix(); {
		glTranslatef(-5.0, 0.0, -5.6);
		glRotatef(35.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 1.0, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Palito sostiene inclinado izquierda enfrente
	glPushMatrix(); {
		glTranslatef(-7.0, 0.0, -4.8);
		glRotatef(-35.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 1.0, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();


	//Palito sostiene inclinado derecha
	glPushMatrix(); {
		glTranslatef(-5.0, 0.0, -4.8);
		glRotatef(-35.0, 1.0, 0.0, 0.0);
		glScalef(0.1, 1.0, 0.1);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Tapa que sostiene cuerda
	glPushMatrix(); {
		glTranslatef(-6.0, 2.35, -5.2);
		glScalef(2.2, 0.1, 1.2);
		prisma(t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex, t_koutback.GLindex);
	}glPopMatrix();

	//Plano que tiene la cuerda colgando
	glPushMatrix(); {
		glTranslatef(-6.0, 2.05, -5.2);
		glScalef(0.7, 0.7, 0.0);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_rope1.GLindex, t_rope1.GLindex, t_rope1.GLindex, t_rope1.GLindex, t_rope1.GLindex, t_rope1.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Plano que tiene la navaja de guillotina
	glPushMatrix(); {
		glTranslatef(-6.0, 1.4, -5.2);
		glScalef(1.1, 1.1, 0.05);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_lamina.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();

	//Plano que tiene la Posicion para cabeza
	glPushMatrix(); {
		glTranslatef(-6.0, 0.3, -5.2);
		glScalef(1.7, 0.4, 0.2);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);
		prisma(t_headguillo.GLindex, t_headguillo.GLindex, t_headguillo.GLindex, t_headguillo.GLindex, t_transparente.GLindex, t_transparente.GLindex);
		glDisable(GL_ALPHA_TEST);
	}glPopMatrix();


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
	dibujarSalaTortura();
	dibujarLapidas();
	dibujarFantasmas();
	dibujarMurcielagos();
	mostrarModelos();
	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: exit(0);
		break;

	case 'W':
	case 'w':
		objCamera.Move_Camera(CAMERASPEED + 0.1);
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		break;

	case 'S':
	case 's':
		objCamera.Move_Camera(-(CAMERASPEED + 0.1));
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		break;

	case 'A':
	case 'a':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.1));
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		break;

	case 'D':
	case 'd':
		objCamera.Strafe_Camera(CAMERASPEED + 0.1);
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
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
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		break;
	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		printf("X:%f\nY:%f\nZ:%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void animacion() {
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
	if (dwElapsedTime >= 30)
	{
		angBat = (angBat + 2) % 360;

		//fantasma1
		if (sf1 == 0) {
			movyf1 += 0.1;
			if (movyf1 >= -2.0)
				sf1 = 30;

		}
		else {
			if (sf1 - 1 == 0) {
				movyf1 = -10.0;
				movxf1 = 2.0;
				if (movxf1 >= 6.0)
					movxf1 = -6.0;
			}
			sf1--;
		}

		//fantasma2
		if (sf2 == 0) {
			movyf2 += 0.1;
			if (movyf2 >= -2.0)
				sf2 = 30;

		}
		else {
			if (sf2 - 1 == 0) {
				movyf2 = -10.0;
				movxf2 -= 2.0;
				if (movxf2 <= -6.0)
					movxf2 = 6.0;
			}
			sf2--;
		}

		//fantasma 2
		if (sf3 == 0) {
			angf3 = 180;
			movzf3 = -7.25;
			movxf3 += 0.15;
			if (movxf3 >= 8.25)
				sf3++;
		}
		else if (sf3 == 1) {
			movzf3 += 0.15;
			angf3 = 90;
			if (movzf3 >= 7.25)
				sf3++;
		}
		else if (sf3 == 2) {
			angf3 = 0;
			movxf3 -= 0.15;
			if (movxf3 <= -8.25)
				sf3++;
		}
		else if (sf3 == 3) {
			angf3 = 270;
			movzf3 -= 0.15;
			if (movzf3 <= -7.25)
				sf3 = 0;
		}
		dwLastUpdateTime = dwCurrentTime;
	}
	glutPostRedisplay();
}

void audio() {
	PlaySound("song1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Proyecto Final");
	audio();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(animacion);
	glutMainLoop();
	return 0;
}

