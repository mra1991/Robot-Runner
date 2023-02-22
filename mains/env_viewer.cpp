#define NUM_OF_ENVS 10

#define PI (3.141592653589793)

#include <vector>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glut.h>

#include "../classes/objHandler.h"
#include "../classes/decorative.h"
#include "../classes/environment.h"

using namespace std;

objHandler* objects_unit;
environment* env[NUM_OF_ENVS];
int env_index;

//camera position
float cameraX = 0.0f;
float cameraY = 4.0f;
float cameraZ = 10.0f;
float cameraAngleX = 0.0f; //camera rotation about x-axis
float cameraAngleY = 0.0f; //camera rotation about y-axis

/* Lighting Variables */
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;

		case 'w': //move camera one step forward
			cameraX += sin(cameraAngleY * PI / 180);
			cameraZ += -cos(cameraAngleY * PI / 180);
			break;	
	
		case 's': //move camera one step back
			cameraX += -sin(cameraAngleY * PI / 180);
			cameraZ += cos(cameraAngleY * PI / 180);
			break;		

		case 'a': //move camera one step left
			cameraX += -sin((cameraAngleY+90) * PI / 180);
			cameraZ += cos((cameraAngleY+90) * PI / 180);
			break;	
	
		case 'd': //move camera one step right
			cameraX += -sin((cameraAngleY-90) * PI / 180);
			cameraZ += cos((cameraAngleY-90) * PI / 180);
			break;

		case 'q': //move camera one step up
			cameraY += 0.5f;
			break;	
	
		case 'e': //move camera one step down
			cameraY -= 0.5f;
			break;

		case 'n': //next obj
			env_index++;
			env_index %= NUM_OF_ENVS;
			break;

		case 'm': //last obj
			env_index--;
			if(env_index == -1) env_index = NUM_OF_ENVS - 1;
//			obj_id %= NUM_OF_OBJS;

			break;
	}
}

//Called when a special key is pressed
void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT: //rotate camera to right
			cameraAngleY += 1.0f;
			if(cameraAngleY >= 360)
				cameraAngleY -= 360;
			break;

		case GLUT_KEY_LEFT: //rotate camera to left
			cameraAngleY -= 1.0f;
			if(cameraAngleY <= 0)
				cameraAngleY += 360;
			break;

		case GLUT_KEY_DOWN: //rotate camera downside
			cameraAngleX += 1.0f;
			if(cameraAngleX >= 360)
				cameraAngleX -= 360;
			break;

		case GLUT_KEY_UP: //rotate camera to upside
			cameraAngleX -= 1.0f;
			if(cameraAngleX <= 0)
				cameraAngleX += 360;
			break;
	}
}

//Initializes 3D rendering
void initRendering() {
//	glEnable(GL_COLOR_MATERIAL); //Enable color
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glDepthFunc(GL_LESS);
//	glEnable(GL_MATERIAL);
//	glShadeModel(GL_SMOOTH); //Enable smooth shading
	glEnable(GL_TEXTURE_2D);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glClearColor(0.1f, 0.1f, 0.2f, 0.0f); //Change the background

	glEnable(GL_LINE_SMOOTH);
	/* glEnable (GL_POLYGON_SMOOTH); */
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   2000.0);                //The far z clipping coordinate
}

void drawGround(){
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-300.0f, 0.0f, 20.0f);
	glVertex3f(-4.0f, 0.0f, 20.0f);
	glVertex3f(-4.0f, 0.0f, -600.0f);
	glVertex3f(-300.0f, 0.0f, -600.0f);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-4.0f, 0.0f, 20.0f);
	glVertex3f(-2.0f, 0.0f, 20.0f);
	glVertex3f(-2.0f, 0.0f, -600.0f);
	glVertex3f(-4.0f, 0.0f, -600.0f);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-2.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, -600.0f);
	glVertex3f(-2.0f, 0.0f, -600.0f);

	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(2.0f, 0.0f, 20.0f);
	glVertex3f(2.0f, 0.0f, -600.0f);
	glVertex3f(0.0f, 0.0f, -600.0f);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(2.0f, 0.0f, 20.0f);
	glVertex3f(4.0f, 0.0f, 20.0f);
	glVertex3f(4.0f, 0.0f, -600.0f);
	glVertex3f(2.0f, 0.0f, -600.0f);

	glPushMatrix();

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(4.0f, -1.0f, 20.0f);
	glVertex3f(300.0f, -1.0f, 20.0f);
	glVertex3f(300.0f, -1.0f, -600.0f);
	glVertex3f(4.0f, -1.0f, -600.0f);

	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(7.0f, -2.0f, 18.0f);
	for(int i = 0; i < 100; i++){
		glTranslatef(0.0f, 0.0f, -6.0f);
		objects_unit->draw(JETTY);
	}
	glPopMatrix();

}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glRotatef(-cameraAngleX, -1.0f, 0.0f, 0.0f); //Rotate the camera about x-axis
	glRotatef(-cameraAngleY, 0.0f, -1.0f, 0.0f); //Rotate the camera about y-axis
	glTranslatef(-cameraX, -cameraY, -cameraZ); //Set camera position
	
	drawGround();

	glPushMatrix();
	for(int i = 0; i < 5; i++){
		env[(env_index + i) % NUM_OF_ENVS]->draw();
		glTranslatef(0.0f, 0.0f, -60.0f);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslatef(cameraX, 0.0f, cameraZ - 12);
	glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

	objects_unit->draw(ROBOT);
	glPopMatrix();

	glutSwapBuffers(); //Send the 3D scene to the screen
}

//Updates Scene
void update(int value) {

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600); //Set the window size
	
	//Create the window
	glutCreateWindow("env_viewer by MRA"); //set window title
	initRendering(); //Initialize rendering
	glutFullScreen();


	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutReshapeFunc(handleResize);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    objects_unit = new objHandler("../descriptions/obj_descriptions.txt");



    env_index = 0;

    for (int i = 0; i < NUM_OF_ENVS; i++)
    {
    	stringstream ss;
    	ss << "../descriptions/env_" << setw(2) 
    			<< setfill('0') << i << ".txt";
    	env[i] = new environment(ss.str(), objects_unit);
    }

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}

