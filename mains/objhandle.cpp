#include <iostream>
#include <string>

#include <GL/glut.h>

#include "../classes/objHandler.h"

using namespace std;

objHandler* objects_unit;
int obj_id;
GLfloat dims[3];

float cameraR = 10.0f; //camera radius
float cameraH = 1.0f; //camera height
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

		case '-': //zoom in
			if(cameraR > 0)
				cameraR -= 1.0f;
			break;	
	
		case '=': //zoom out
			cameraR += 1.0f;
			break;

		case '9':
			cameraH -= 1.0f;
			break;	
	
		case '0':
			cameraH += 1.0f;
			break;

		case 'n':
			cameraAngleX = cameraAngleY = 0.0f;
			obj_id++;
			obj_id %= NUM_OF_OBJS;
			objects_unit->get_dimentions((ObjName)obj_id, dims);
			cout << setw(2) << setfill('0') << obj_id 
				<< setw(20) << setfill(' ') << objects_unit->get_obj_name(obj_id) 
				<< "\t\t" << dims[0] << "\t\t" << dims[1] << "\t\t" << dims[2] << '\n'; 
			break;
	}
}

//Called when a special key is pressed
void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT:
			cameraAngleY += 1.0f;
			if(cameraAngleY >= 360)
				cameraAngleY -= 360;
			break;

		case GLUT_KEY_LEFT:
			cameraAngleY -= 1.0f;
			if(cameraAngleY <= 0)
				cameraAngleY += 360;
			break;

		case GLUT_KEY_DOWN:
			if(cameraAngleX < 90)
				cameraAngleX += 1.0f;
			break;

		case GLUT_KEY_UP:
			if(cameraAngleX > -90)
				cameraAngleX -= 1.0f;
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

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glTranslatef(0.0f, -cameraH, -cameraR); //Set camera position
	glRotatef(-cameraAngleX, -1.0f, 0.0f, 0.0f); //Rotate the camera about x-axis
	glRotatef(-cameraAngleY, 0.0f, -1.0f, 0.0f); //Rotate the camera about y-axis

	objects_unit->draw((ObjName)obj_id);

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
	glutCreateWindow(".obj Loader/Normalizer by MRA"); //set window title
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
    	obj_id = 0;
	objects_unit->get_dimentions((ObjName)obj_id, dims);

	cout << "ID" << setw(20) << "NAME" << "\t\t" 
		<< "X_dimention" << '\t' << "Y_dimention" << '\t' << "Z_dimention" << '\n'; 
	cout << setw(60) << setfill('-') << '\n';	

	cout << setw(2) << setfill('0') << obj_id 
		<< setw(20) << setfill(' ') << objects_unit->get_obj_name(obj_id) 
		<< "\t\t" << dims[0] << "\t\t" << dims[1] << "\t\t" << dims[2] << '\n'; 

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}

