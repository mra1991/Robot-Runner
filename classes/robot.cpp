#include "robot.h"

robot::robot(objHandler* o_h){
	objs_unit = o_h;
	objs_unit->get_dimentions(ROBOT_HEAD, parts_dims[0]);
	objs_unit->get_dimentions(ROBOT_NECK, parts_dims[1]);
	objs_unit->get_dimentions(ROBOT_BODY, parts_dims[2]);
	objs_unit->get_dimentions(ROBOT_BACK, parts_dims[3]);
	objs_unit->get_dimentions(ROBOT_WHEEL, parts_dims[4]);

	stretch = 1.0f;
	lane = 1.0f;
	isGrounded = true;
	sit_delay = jump_delay = 0;
	pos[1] = pos[2] = 0;
	pos[0] = lane;
}

void robot::reset(){
	stretch = 1.0f;
	lane = 1.0f;
	isGrounded = true;
	sit_delay = jump_delay = 0;
	pos[1] = pos[2] = 0;
	pos[0] = lane;
}

void robot::resetPosZ(){
	pos[2] = 0;
}

void robot::get_dims(GLfloat* dims){
	dims[0] = parts_dims[2][2]; //width = body's depth
	dims[2] = parts_dims[2][0]; //depth = body's width
	dims[1] = parts_dims[0][1] + parts_dims[2][1] + parts_dims[4][1]
				+  stretch * (parts_dims[1][1] + parts_dims[3][1]) + bfp;
}

GLfloat robot::getPosX(){
	return pos[0];
}

GLfloat robot::getPosY(){
	return pos[1];
}

GLfloat robot::getPosZ(){
	return pos[2];
}

void robot::grounded_signal(bool is_it, GLfloat heigth){
	isGrounded = is_it;
	if(is_it) pos[1] = heigth;
}

void robot::signal_sit(){
	if(isGrounded){
		stretch = 0.5f;
		sit_delay = 20;
	}
}

void robot::signal_jump(){
	if(isGrounded){
		stretch = 1.5f;
		jump_delay = 8;
	}
	isGrounded = false;
}

void robot::signal_move_right(){
	if(lane == -3.0f || lane == -1.0f || lane == 1.0f) 
		lane += 2.0f;
}

void robot::signal_move_left(){
	if(lane == -1.0f || lane == 1.0f || lane == 3.0f)
		lane -= 2.0f;
}

void robot::draw(){
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

	objs_unit->draw(ROBOT_WHEEL);
	glTranslatef(0.0f, parts_dims[4][1], 0.0f);

	glPushMatrix();
		glScalef(1.0f, stretch, 1.0f);
		objs_unit->draw(ROBOT_BACK);
	glPopMatrix();

	glTranslatef(0.0f, parts_dims[3][1]* stretch, 0.0f);

	glTranslatef(0.0f, bfp, 0.0f);
	glPushMatrix();
		glTranslatef(bfp, 0.0f, 0.0f);
		objs_unit->draw(ROBOT_BODY);
	glPopMatrix();

	glTranslatef(0.0f, parts_dims[2][1], 0.0f);

	glPushMatrix();
		glScalef(1.0f, stretch, 1.0f);
		objs_unit->draw(ROBOT_NECK);
	glPopMatrix();

	glTranslatef(0.0f, parts_dims[1][1] * stretch, 0.0f);

	objs_unit->draw(ROBOT_HEAD);
	glPopMatrix();
}

void robot::update(){
	pos[2] -= 1.0f;
	if(sit_delay <= 0){
		sit_delay = 0;
	}
	else{
		sit_delay--;
	}

	if(jump_delay <= 0){
		jump_delay = 0;
		if(!isGrounded){
			pos[1] -= 0.5;
		}
	}
	else{
		pos[1] += 0.5;
		jump_delay--;
	}

	if(sit_delay <= 0 && jump_delay <= 0)
		stretch = 1.0f;

	if((pos[0] - lane) < 0.2f && (pos[0] - lane) > -0.2f)
		pos[0] = lane;
	if(pos[0] < lane){
		pos[0] += 0.2f;
	}
	else if(pos[0] > lane){
		pos[0] -= 0.2f;
	}
}