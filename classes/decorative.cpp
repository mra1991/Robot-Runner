#include "decorative.h"

decorative::decorative(ObjName OBJ, objHandler* o_h){
	body = OBJ;
	objs_unit = o_h;
	pos[0] = pos[1] = pos[2] = 0; 
	rot[0] = rot[1] = rot[2] = 0;
}

void decorative::setPos(GLfloat x, GLfloat y, GLfloat z){
	pos[0] = x; pos[1] = y; pos[2] = z;
}

void decorative::setRot(GLfloat x, GLfloat y, GLfloat z){
	rot[0] = x; rot[1] = y; rot[2] = z;
}

void decorative::draw(){
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	objs_unit->draw(body);

	glPopMatrix(); 
}