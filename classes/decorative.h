#include <GL/glut.h>
#include "objHandler.h"

#ifndef DECORATIVE_H
#define DECORATIVE_H

class decorative
{
public:
	decorative(ObjName, objHandler*);
	~decorative();
	void setPos(GLfloat, GLfloat, GLfloat);
	void setRot(GLfloat, GLfloat, GLfloat);
	void draw();

private:
	ObjName body;
	objHandler* objs_unit;
	GLfloat pos[3]; //position
	GLfloat rot[3]; //rotation
};

#endif
