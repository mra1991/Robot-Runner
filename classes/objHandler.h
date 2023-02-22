#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <GL/glut.h>

#include "../glmwithtexture/glm.h"

using namespace std;

#ifndef OBJ_HANDLER
#define OBJ_HANDLER

enum ObjName {OLD_BOX, SOFT_BOX,
				COIN, MAGNET, 
				CONTAINER_SHIP, CRUISE_SHIP,
				JETTY, T_CRANE, LIFT_TRUCK,
				BLUE_TRUCK, YELLOW_TRUCK,
				OBSTACLE_LOW, OBSTACLE_TOP,
				PIPE, PIPE_L,
				CONTAINER_RED, CONTAINER_BLUE,
				TOW_TRACTOR_B, TOW_TRACTOR_W,
				ROBOT, ROBOT_HEAD, ROBOT_NECK,
				ROBOT_BODY, ROBOT_BACK,
				ROBOT_WHEEL,
				/*add other obj names here*/
				NUM_OF_OBJS
				};

class objHandler
{
public:
	objHandler(string);
	~objHandler();
	string get_obj_name(int);
	void get_dimentions(ObjName, GLfloat*);
	void draw(ObjName);

private:
	GLMmodel* model[NUM_OF_OBJS];
	string obj_names[NUM_OF_OBJS];
	string filenames[NUM_OF_OBJS];
	bool has_text[NUM_OF_OBJS];
	GLfloat default_widths[NUM_OF_OBJS];
	GLfloat dimentions[NUM_OF_OBJS][3];
	GLuint disp_list_ids[NUM_OF_OBJS];

};

#endif
