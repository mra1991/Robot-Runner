#define PI (3.141592653589793)

#include <vector>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glut.h>

#include "../classes/objHandler.h"
#include "../classes/decorative.h"

using namespace std;

ofstream fout("../descriptions/map_new.txt");

objHandler* objects_unit;
vector<decorative*> decors;
decorative* decor;

ObjName obj_id;

GLfloat pos[3];


//camera position
float cameraX = 0.0f;
float cameraY = 1.0f;
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

		//------------------------------------------------

		case 't': //move object forward
			pos[2] -= 1.0f;
			break;

		case 'g': //move object backward
			pos[2] += 1.0f;
			break;

		case 'f': //move object left
			pos[0] -= 1.0f;
			break;

		case 'h': //move object right
			pos[0] += 1.0f;
			break;

		case 'r': //move object up
			pos[1] += 1.0f;
			break;

		case 'y': //move object down
			pos[1] -= 1.0f;
			break;


		case 'n': //next obj
			if(obj_id == SOFT_BOX) obj_id = OBSTACLE_LOW;
			else if(obj_id == OBSTACLE_LOW) obj_id = LIFT_TRUCK;
			else if(obj_id == LIFT_TRUCK) obj_id = SOFT_BOX;
			break;

		case '\r': //Enter Key: write object
			if(obj_id == SOFT_BOX) fout << 'b';
			if(obj_id == OBSTACLE_LOW) fout << 'o';
			if(obj_id == LIFT_TRUCK) fout << 'l';

			fout << '\t'<< pos[0] << '\t' << pos[1] << '\t' << pos[2] << '\n';
			decor = new decorative(obj_id, objects_unit);
			decor->setPos(pos[0], pos[1], pos[2]);
			decors.push_back(decor);
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
	glVertex3f(-20.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, -60.0f);
	glVertex3f(-20.0f, 0.0f, -60.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, -60.0f);
	glVertex3f(-4.0f, 0.0f, -60.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -60.0f);
	glVertex3f(-2.0f, 0.0f, -60.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, -60.0f);
	glVertex3f(0.0f, 0.0f, -60.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, -60.0f);
	glVertex3f(2.0f, 0.0f, -60.0f);

	glPushMatrix();

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(4.0f, -1.0f, 0.0f);
	glVertex3f(20.0f, -1.0f, 0.0f);
	glVertex3f(20.0f, -1.0f, -60.0f);
	glVertex3f(4.0f, -1.0f, -60.0f);

	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(7.0f, -2.0f, 3.0f);
	for(int i = 0; i < 10; i++){
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
	for(int i = 0; i < (int)decors.size(); i++){
		decors[i]->draw();
	}

	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	if(obj_id == LIFT_TRUCK)
		glRotatef(90,0,1,0);

	objects_unit->draw(obj_id);
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
	glutCreateWindow("environment builder by MRA"); //set window title
	initRendering(); //Initialize rendering


	
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

    obj_id = SOFT_BOX;

	pos[0] = pos[1] = pos[2] = 0; 

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}

