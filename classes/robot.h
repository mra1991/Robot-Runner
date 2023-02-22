#include <GL/glut.h>

#include "objHandler.h"

#include <iostream>
using namespace std;

#ifndef ROBOT_H
#define ROBOT_H

class robot
{
public:
	robot(objHandler*);
	~robot();
	void reset();
	void resetPosZ();
	void get_dims(GLfloat*);
	GLfloat getPosX();
	GLfloat getPosY();
	GLfloat getPosZ();
	void grounded_signal(bool, GLfloat);
	void signal_sit();
	void signal_jump();
	void signal_move_right();
	void signal_move_left();
	void draw();
	void update();

private:
	objHandler* objs_unit;
	GLfloat pos[3];
	GLfloat parts_dims[5][3]; //head, neck, body, back, wheel
	bool isGrounded;
	GLfloat lane; //rememter it should always be an integer
	GLfloat stretch;

	int sit_delay, jump_delay;

	const GLfloat bfp = -0.31f; //body fixing parameter

};

#endif
