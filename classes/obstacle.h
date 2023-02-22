#include <GL/glut.h>
#include "objHandler.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class obstacle
{
public:
	obstacle(char, objHandler*);
	~obstacle();
	void set_pos(GLfloat, GLfloat, GLfloat);
	void get_pos(GLfloat*);
	void get_dims(GLfloat*);
	char get_type();
	void draw();
	void reset();
	void update();
	const GLfloat noh = 2.4f; //normal obstacle height

private:
	objHandler* objs_unit;
	char type; /* 'l' for lift_truck, 'b' for box,
						 'o' for normal obsracles*/
	GLfloat pos[3];
	GLfloat delta_z; //for lift trucks
};

#endif
