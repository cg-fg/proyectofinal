//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************		Serrano Bermúdez Luis Esteban		******//
//************************************************************//
//************************************************************//
//************************************************************//
#include "Main.h"

float transZ = -9.0f;
float transX = -3.0f;
float angleX = 20.0f;
float angleY = -35.0f;
int screenW = 0.0;
int screenH = 0.0;

float movHombro = 0.0f,
movCodo = 0.0;
//Dedo 1
float movDedo1 = 0.0f, movDedo2 = 0.0f, separacion = 0.0f;
//Dedo2
float movDedo3 = 0.0f, movDedo4 = 0.0f;
//Dedo3
float movDedo5 = 0.0f, movDedo6 = 0.0f;
//Dedo gordo
float movDedo7 = 0.0f, movDedoGordo = 0.0f;

GLfloat Position[] = { 0.0f, 3.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };	// Light Position

float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;


#define MAX_FRAMES 6//aumenta numero de frames
int i_max_steps = 990;//max de cuadros frames intermedios
int i_curr_steps = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;

//Frame
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movDedo1;
	float incmovDedo1;
	float movDedo2;
	float incmovDedo2;
	float separacion;
	float incSeparacion;
	float movDedo3;
	float incmovDedo3;
	float movDedo4;
	float incmovDedo4;
	float movDedo5;
	float incmovDedo5;
	float movDedo6;
	float incmovDedo6;
	float movDedo7;
	float incmovDedo7;
	float movDedoGordo;
	float incmovDedoGordo;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];//arreglo que almacena frames
						   //int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;


//metodos del frame
void resetElements(void)
{
	movDedo1 = KeyFrame[0].movDedo1;
	movDedo2 = KeyFrame[0].movDedo2;
	separacion = KeyFrame[0].separacion;
	movDedo3 = KeyFrame[0].movDedo3;
	movDedo4 = KeyFrame[0].movDedo4;
	movDedo5 = KeyFrame[0].movDedo5;
	movDedo6 = KeyFrame[0].movDedo6;
	movDedo7 = KeyFrame[0].movDedo7;
	movDedoGordo = KeyFrame[0].movDedoGordo;
}

void interpolation(void)
{
	KeyFrame[playIndex].incmovDedo1 = (KeyFrame[playIndex + 1].movDedo1 - KeyFrame[playIndex].movDedo1) / i_max_steps;
	KeyFrame[playIndex].incmovDedo2 = (KeyFrame[playIndex + 1].movDedo2 - KeyFrame[playIndex].movDedo2) / i_max_steps;
	KeyFrame[playIndex].incSeparacion = (KeyFrame[playIndex + 1].separacion - KeyFrame[playIndex].separacion) / i_max_steps;
	KeyFrame[playIndex].incmovDedo3 = (KeyFrame[playIndex + 1].movDedo3 - KeyFrame[playIndex].movDedo3) / i_max_steps;
	KeyFrame[playIndex].incmovDedo4 = (KeyFrame[playIndex + 1].movDedo4 - KeyFrame[playIndex].movDedo4) / i_max_steps;
	KeyFrame[playIndex].incmovDedo5 = (KeyFrame[playIndex + 1].movDedo5 - KeyFrame[playIndex].movDedo5) / i_max_steps;
	KeyFrame[playIndex].incmovDedo6 = (KeyFrame[playIndex + 1].movDedo6 - KeyFrame[playIndex].movDedo6) / i_max_steps;
	KeyFrame[playIndex].incmovDedo7 = (KeyFrame[playIndex + 1].movDedo7 - KeyFrame[playIndex].movDedo7) / i_max_steps;
	KeyFrame[playIndex].incmovDedoGordo = (KeyFrame[playIndex + 1].movDedoGordo - KeyFrame[playIndex].movDedoGordo) / i_max_steps;

}


void animacion()
{
	/*fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq<-1)
	fig3.text_izq = 0;
	if (fig3.text_der<0)
	fig3.text_der = 1;
	*/
	//Movimiento del la mano
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>MAX_FRAMES - 1)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation

			movDedo1 += KeyFrame[playIndex].incmovDedo1;
			movDedo2 += KeyFrame[playIndex].incmovDedo2;
			separacion += KeyFrame[playIndex].incSeparacion;
			movDedo3 += KeyFrame[playIndex].incmovDedo3;
			movDedo4 += KeyFrame[playIndex].incmovDedo4;
			movDedo5 += KeyFrame[playIndex].incmovDedo5;
			movDedo6 += KeyFrame[playIndex].incmovDedo6;
			movDedo7 += KeyFrame[playIndex].incmovDedo7;
			movDedoGordo += KeyFrame[playIndex].incmovDedoGordo;

			i_curr_steps++;

		}

	}


	glutPostRedisplay();
}


void InitGL(void)     // Inicializamos parametros
{

	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing

														//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	///////////////////////////////////////////////////
	//Valores Frame
	KeyFrame[0].movDedo1 = 12.0;
	KeyFrame[0].movDedo2 = -53.50;
	KeyFrame[0].separacion = 0.0;
	KeyFrame[0].movDedo3 = 45.00;
	KeyFrame[0].movDedo4 = -33.00;
	KeyFrame[0].movDedo5 = 24.00;
	KeyFrame[0].movDedo6 = -43.50;
	KeyFrame[0].movDedo7 = 0.0;
	KeyFrame[0].movDedoGordo = -10.50;

	KeyFrame[1].movDedo1 = -63.0;
	KeyFrame[1].movDedo2 = -91.0;
	KeyFrame[1].separacion = 0.0;
	KeyFrame[1].movDedo3 = -73.50;
	KeyFrame[1].movDedo4 = -100.50;
	KeyFrame[1].movDedo5 = -70.50;
	KeyFrame[1].movDedo6 = -100.50;
	KeyFrame[1].movDedo7 = 15.0;
	KeyFrame[1].movDedoGordo = -1195.50;

	KeyFrame[2].movDedo1 = 0.0;
	KeyFrame[2].movDedo2 = 0.0;
	KeyFrame[2].separacion = -13.50;
	KeyFrame[2].movDedo3 = -66.0;
	KeyFrame[2].movDedo4 = -100.50;
	KeyFrame[2].movDedo5 = 0.0;
	KeyFrame[2].movDedo6 = 0.0;
	KeyFrame[2].movDedo7 = -10.50;
	KeyFrame[2].movDedoGordo = -76.50;

	KeyFrame[3].movDedo1 = 45.0;
	KeyFrame[3].movDedo2 = 0.0;
	KeyFrame[3].separacion = 0.0;
	KeyFrame[3].movDedo3 = 45.0;
	KeyFrame[3].movDedo4 = 0.0;
	KeyFrame[3].movDedo5 = 45.0;
	KeyFrame[3].movDedo6 = 0.0;
	KeyFrame[3].movDedo7 = 45.0;
	KeyFrame[3].movDedoGordo = 0.0;

	KeyFrame[4].movDedo1 = 0.0;
	KeyFrame[4].movDedo2 = -100.5;
	KeyFrame[4].separacion = 0.0;
	KeyFrame[4].movDedo3 = 1.5;
	KeyFrame[4].movDedo4 = -100.5;
	KeyFrame[4].movDedo5 = 0.0;
	KeyFrame[4].movDedo6 = -100.5;
	KeyFrame[4].movDedo7 = 90.0;
	KeyFrame[4].movDedoGordo = 0.0;

	KeyFrame[5].movDedo1 = 0.0;
	KeyFrame[5].movDedo2 = 0.0;
	KeyFrame[5].separacion = 0.0;
	KeyFrame[5].movDedo3 = 0.0;
	KeyFrame[5].movDedo4 = 0.0;
	KeyFrame[5].movDedo5 = 0.0;
	KeyFrame[5].movDedo6 = 0.0;
	KeyFrame[5].movDedo7 = 0.0;
	KeyFrame[5].movDedoGordo = 0.0;
}

void prisma(void)
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

	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
														//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(transX, 0.0f, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	//Poner Código Aquí.
	glRotatef(movHombro, 0.0, 0.0, 1.0);//jerarquia de movimiento
	glTranslatef(1.25, 0.0, 0.0);//centro de A
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScalef(2.5, 1.0, 1.0);
	prisma();//A
	glPopMatrix();

	glTranslatef(1.25, 0.0, 0.0);
	glRotatef(movCodo, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	prisma(); //B
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.35, 0.375);
	glRotatef(movDedo1, 0.0, 0.0, 1.0);
	glRotatef(separacion, 0.0, 1.0, 0.0);
	glTranslatef(0.375, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.75, 0.3, 0.25);
	glColor3f(0.0, 0.0, 1.0);
	prisma();//c
	glPopMatrix();

	glTranslatef(0.375, 0.0, 0.0);
	glRotatef(movDedo2, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glScalef(1.0, 0.3, 0.25);
	glColor3f(0.0, 1.0, 1.0);
	prisma();//D
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.35, -0.375);
	glRotatef(movDedo3, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.3, 0.25);
	glColor3f(0.0, 0.0, 1.0);
	prisma();//I
	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(movDedo4, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glScalef(1.0, 0.3, 0.25);
	glColor3f(0.0, 1.0, 1.0);
	prisma();//J
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.35, 0.0);
	glRotatef(movDedo5, 0.0, 0.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(1.0, 0.3, 0.25);
	glColor3f(0.0, 0.1, 1.0);
	prisma();//G
	glPopMatrix();

	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(movDedo6, 0.0, 0.0, 1.0);
	glTranslatef(.75, 0.0, 0.0);
	glScalef(1.5, 0.3, 0.25);
	glColor3f(0.0, 1.0, 1.0);
	prisma();//H
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -0.35, 0.375);
	glRotatef(-movDedo7, 0.0, 1.0, 0.0);
	glTranslatef(0.375, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.75, 0.3, 0.25);
	glColor3f(0.0, 0.0, 1.0);
	prisma();//E
	glPopMatrix();

	glTranslatef(0.375, 0.0, 0.0);
	glRotatef(-movDedoGordo, 0.0, 1.0, 0.0);
	glTranslatef(0.375, 0.0, 0.0);
	glScalef(0.75, 0.3, 0.25);
	glColor3f(0.0, 1.0, 1.0);
	prisma();//F
	glPopMatrix();

	glutSwapBuffers();//c
					  // Swap The Buffers
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	//glOrtho(-5,5,-5,5,0.2,20);	
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
														//glLoadIdentity();									
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':
	case 'W':
		transZ += 0.2f;
		break;
	case 's':
	case 'S':
		transZ -= 0.2f;
		break;
	case 'a':
	case 'A':
		transX += 0.2f;
		break;
	case 'd':
	case 'D':
		transX -= 0.2f;
		break;
	case 'r':
		if (movHombro < 110.0)
			movHombro += 1.0f;
		break;
	case 'R':
		if (movHombro > -130.0)
			movHombro -= 1.0f;
		break;
	case 't':
		if (movCodo < 5.0)
			movCodo += 1.5f;
		break;
	case 'T':
		if (movCodo > -95.0)
			movCodo -= 1.5f;
		break;
	case 'y':
		if (movDedo1 < 0.0)
			movDedo1 += 1.5f;
		break;
	case 'Y':
		if (movDedo1 > -90.0)
			movDedo1 -= 1.5f;
		break;
	case 'u':
		if (movDedo2 > -100.0)
			movDedo2 -= 1.5f;
		break;
	case 'U':
		if (movDedo2 < 0.0)
			movDedo2 += 1.5f;
		break;
	case 'i':
		separacion -= 1.5f;
		break;
	case 'I':
		separacion += 1.5f;
		break;
	case 'h':
		if (movDedo3 < 45.0)
			movDedo3 += 1.5f;
		break;
	case 'H':
		if (movDedo3 > -90.0)
			movDedo3 -= 1.5f;
		break;
	case 'j':
		if (movDedo4 > -100.0)
			movDedo4 -= 1.5f;
		break;
	case 'J':
		if (movDedo4 < 30.0)
			movDedo4 += 1.5f;
		break;
	case 'n':
		if (movDedo5 < 45.0)
			movDedo5 += 1.5f;
		break;
	case 'N':
		if (movDedo5 > -90.0)
			movDedo5 -= 1.5f;
		break;
	case 'm':
		if (movDedo6 > -100.0)
			movDedo6 -= 1.5f;
		break;
	case 'M':
		if (movDedo6 < 30.0)
			movDedo6 += 1.5f;
		break;
	case 'z':
		if (movDedo7 < 90.0)
			movDedo7 += 1.5f;
		break;
	case 'Z':
		if (movDedo7 > -90.0)
			movDedo7 -= 1.5f;
		break;
	case 'x':
		if (movDedoGordo < 90.0)
			movDedoGordo += 1.5f;
		break;
	case 'X':
		if (movDedoGordo > 0.0)
			movDedoGordo -= 1.5f;
		break;
	case 'p':
		printf("\nDedo 1: %f", movDedo1);
		printf("\nDedo 2: %f", movDedo2);
		printf("\nDedo 3: %f", movDedo3);
		printf("\nDedo 4: %f", movDedo4);
		printf("\nDedo 5: %f", movDedo5);
		printf("\nDedo 6: %f", movDedo6);
		printf("\nDedo 7: %f", movDedo7);
		printf("\nDedo Gordo: %f", movDedoGordo);
		printf("\nSeparacion 1: %f", separacion);
		printf("\nDedo 1: %f", movDedo1);
		break;
	case 'l':
	case 'L':
		if (play == false)
		{
			resetElements();
			//First Interpolation	

			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		angleX -= 2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY += 2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -= 2.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	screenW = glutGet(GLUT_SCREEN_WIDTH);
	screenH = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11, reporte"); // Nombre de la Ventana
	printf("Resolution H: %i \n", screenW);
	printf("Resolution V: %i \n", screenH);
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	glutMainLoop();          // 

	return 0;
}



