
//file game.h
#include <GL/glut.h>
#include <stdlib.h>	/* srand, rand */
#include <time.h>	/* time (for srand) */
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

#include "objHandler.h"
#include "map.h"
#include "environment.h"
#include "robot.h"

#ifndef GAME_H
#define GAME_H

#define NUM_OF_MAPS 10 //number of maps
#define NUM_OF_ENVS 10 //number of environments
#define B_LEN 60.0f //B_LEN : block length
#define CAM_DIS_Z 12 //camera distance from main character
#define CAM_DIS_Y 4 //camera's higher than main character

enum STATUS {LOADING, STARTING, PLAY, PAUSE, GAMEOVER};

class game
{
public:
	game();
//	~game();
	void update(int);
	void draw();
	void handleSpecialKeypress(int, int, int);
	void handleKeypress(unsigned char, int, int);

private:
	unsigned long score;
//	unsigned int coins;
	int env1_id, env2_id, env3_id, env4_id;
	environment* envs[NUM_OF_ENVS];
	int map1_id, map2_id, map3_id, map4_id;
	map* maps[NUM_OF_MAPS];

	objHandler* central_objs_unit;
	robot* the_robot;
	STATUS game_status;

//	void reset();
	void draw_ground();
	void collision_detect();
	bool enable_collision;
};

#endif
