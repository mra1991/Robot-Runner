#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "objHandler.h"
#include "obstacle.h"

#ifndef MAP_H
#define MAP_H

class map
{
public:
	map(string, objHandler*);
	~map();
	void draw();
	void reset();
	void update();
	void get_pos_i(int, GLfloat*);
	void get_dims_i(int, GLfloat*);
	char get_type_i(int);
	int num_of_obss();
private:
	std::vector<obstacle*> obss;
};

#endif
