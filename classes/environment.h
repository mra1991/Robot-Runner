#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "objHandler.h"
#include "decorative.h"

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class environment
{
public:
	environment(string, objHandler*);
	~environment();
	void draw();
private:
	std::vector<decorative*> decors;
};

#endif
