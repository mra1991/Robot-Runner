#include "obstacle.h"

obstacle::obstacle(char t, objHandler* o_h){
	objs_unit = o_h;
	type = t;
	delta_z = 0;
}

void obstacle::set_pos(GLfloat x, GLfloat y, GLfloat z){
	pos[0] = x; pos[1] = y; pos[2] = z;
}

void obstacle::get_pos(GLfloat* p){
	p[0] = pos[0]; p[1] = pos[1]; p[2] = pos[2]; 
}

void obstacle::get_dims(GLfloat* d){
	switch(type){
		case 'b':
			objs_unit->get_dimentions(SOFT_BOX, d);
			break;
		case 'l':
			objs_unit->get_dimentions(LIFT_TRUCK, d);
			break;
		case 'o':
			objs_unit->get_dimentions(OBSTACLE_TOP, d);
			d[1] += noh;
			break;
	}
}

char obstacle::get_type(){
	return type;
}

void obstacle::draw(){
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	switch(type){
		case 'b':
			objs_unit->draw(SOFT_BOX);
			break;
		case 'l':
			glTranslatef(0.0f, 0.0f, delta_z);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			objs_unit->draw(LIFT_TRUCK);
			break;
		case 'o':
			glPushMatrix();
			glScalef(1.0f, noh + 0.2f, 1.0f);
			objs_unit->draw(OBSTACLE_LOW);
			glPopMatrix();
			glTranslatef(0.0f, noh, 0.0f);
			objs_unit->draw(OBSTACLE_TOP);
			break;
	}
	glPopMatrix();
}

void obstacle::reset(){
	delta_z = 0;
}

void obstacle::update(){
	delta_z += 0.5f;
}