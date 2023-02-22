#include "game.h"

game::game(){
	env1_id = env2_id = env3_id = env4_id = 0;
	map1_id = map2_id = map3_id = map4_id = 0;

	//set game status
	game_status = LOADING;

	/* let the objHandler [central_objs_unit] deal
							 with objects data */
	central_objs_unit = 
		new objHandler("../descriptions/obj_descriptions.txt");

	//build enviroments according to description files
    for (int i = 0; i < NUM_OF_ENVS; i++)
    {
    	stringstream ss;
    	ss << "../descriptions/env_" << setw(2) 
    			<< setfill('0') << i << ".txt";
    	envs[i] = new environment(ss.str(), central_objs_unit);
    }

    //build maps according to description files
    for (int i = 0; i < NUM_OF_MAPS; i++)
    {
    	stringstream ss;
    	ss << "../descriptions/map_" << setw(2) 
    			<< setfill('0') << i << ".txt";
    	maps[i] = new map(ss.str(), central_objs_unit);
    }

    the_robot = new robot(central_objs_unit);

//}

//void game::reset(){
	//reset coins and score
//	coins = 0;
	score = 0;

	//reset main character
	the_robot->reset();

	/*make sure to undo all the changes applied 
		to used maps before we get rid of them*/ 
	maps[map1_id]->reset();
	maps[map2_id]->reset();
	maps[map3_id]->reset();

	srand(time(NULL)); // seed random func

	//choose new maps and environments
	env1_id = rand() % NUM_OF_ENVS;
	env2_id = rand() % NUM_OF_ENVS;
	env3_id = rand() % NUM_OF_ENVS;
	env4_id = rand() % NUM_OF_ENVS;

	map1_id = rand() % NUM_OF_MAPS;
	map2_id = rand() % NUM_OF_MAPS;
	map3_id = rand() % NUM_OF_MAPS;
	map4_id = rand() % NUM_OF_MAPS;

	//srart new game
	game_status = PLAY;

	enable_collision = false;
}

void game::update(int value){
	if(game_status == PLAY){
		score++;
		maps[map1_id]->update();
		the_robot->update();
		collision_detect();

		/*in case we've reached the end of block, we should
			get rid of the first block and choose a new one
								 to be added to the end*/
		if(-the_robot->getPosZ() >= B_LEN){
			//reset first map before getting rid of it
			maps[map1_id]->reset();

			map1_id = map2_id;
			map2_id = map3_id;
			map3_id = map4_id;
			map4_id = rand() % NUM_OF_MAPS;

			env1_id = env2_id;
			env2_id = env3_id;
			env3_id = env4_id;
			env4_id = rand() % NUM_OF_ENVS;	

			//now main character should get back to the beginnig of block
			the_robot->resetPosZ();
		}	
	}
}

void game::draw(){
	switch(game_status){
		case PLAY:
			//set the camera
			glTranslatef(0.0f, -the_robot->getPosY() - CAM_DIS_Y,
								-the_robot->getPosZ() - CAM_DIS_Z);

			draw_ground();

			glPushMatrix();
			maps[map1_id]->draw();
			envs[env1_id]->draw();

			//move to beginning of second block		
			glTranslatef(0,0,-B_LEN);

			maps[map2_id]->draw();
			envs[env2_id]->draw();

			//move to beginning of third block		
			glTranslatef(0,0,-B_LEN);

			maps[map3_id]->draw();
			envs[env3_id]->draw();

			//move to beginning of third block		
			glTranslatef(0,0,-B_LEN);

			maps[map3_id]->draw();
			envs[env4_id]->draw();

			glPopMatrix();

			glPushMatrix();
			the_robot->draw();
			glPopMatrix();

			break;

		case PAUSE:
			glTranslatef(0.0f, -2.0f, -5.0f);
			glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
			central_objs_unit->draw(ROBOT);
			break;

		case LOADING:
			//...
			break;

		case GAMEOVER:
			//...
			break;

		default:
			break;
	}
}

void game::handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;

		case '\r': //Enter key
			if(game_status == PLAY)
				game_status = PAUSE;
			else if(game_status == PAUSE)
				game_status = PLAY;	
			break;

		case 'p':
			enable_collision = !enable_collision;
			break;

//		case ' ': //space bar
//			the_robot->signal_shoot();				
	}
}

//Called when a special key is pressed
void game::handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT:
			the_robot->signal_move_right();
			break;

		case GLUT_KEY_LEFT:
			the_robot->signal_move_left();
			break;

		case GLUT_KEY_DOWN:
			the_robot->signal_sit();
			break;

		case GLUT_KEY_UP:
			the_robot->signal_jump();
			break;
	}
}

void game::collision_detect(){
	if(the_robot->getPosY() <= 0)
		the_robot->grounded_signal(true, 0.0f);
	if(enable_collision){
		GLfloat r_dims[3];
		the_robot->get_dims(r_dims);
		GLfloat r_pos[3];
		r_pos[0] = the_robot->getPosX();
		r_pos[1] = the_robot->getPosY();
		r_pos[2] = the_robot->getPosZ();
		for(int i=0; i < maps[map1_id]->num_of_obss(); i++){
			char obs_type = maps[map1_id]->get_type_i(i);
			GLfloat dims_i[3], pos_i[3];
			maps[map1_id]->get_dims_i(i, dims_i);
			maps[map1_id]->get_pos_i(i, pos_i);
			if(obs_type == 'o'){
				if(r_pos[0] == pos_i[0] && 
					(r_pos[1] + r_dims[1]) >= 2.4f &&
					r_pos[2] - pos_i[2] <= 0.8){
						game_status = GAMEOVER;
					break;
				}
			}
		}
	}
}

void game::draw_ground(){
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-300.0f, 0.0f, 20.0f);
	glVertex3f(-4.0f, 0.0f, 20.0f);
	glVertex3f(-4.0f, 0.0f, -600.0f);
	glVertex3f(-300.0f, 0.0f, -600.0f);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(-4.0f, 0.0f, 20.0f);
	glVertex3f(-2.0f, 0.0f, 20.0f);
	glVertex3f(-2.0f, 0.0f, -600.0f);
	glVertex3f(-4.0f, 0.0f, -600.0f);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-2.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, -600.0f);
	glVertex3f(-2.0f, 0.0f, -600.0f);

	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(2.0f, 0.0f, 20.0f);
	glVertex3f(2.0f, 0.0f, -600.0f);
	glVertex3f(0.0f, 0.0f, -600.0f);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(2.0f, 0.0f, 20.0f);
	glVertex3f(4.0f, 0.0f, 20.0f);
	glVertex3f(4.0f, 0.0f, -600.0f);
	glVertex3f(2.0f, 0.0f, -600.0f);

	glPushMatrix();

	glColor3f(0.0f, 0.1f, 0.4f);
	glVertex3f(4.0f, -1.0f, 20.0f);
	glVertex3f(300.0f, -1.0f, 20.0f);
	glVertex3f(300.0f, -1.0f, -600.0f);
	glVertex3f(4.0f, -1.0f, -600.0f);

	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(7.0f, -2.0f, 18.0f);
	for(int i = 0; i < 100; i++){
		glTranslatef(0.0f, 0.0f, -6.0f);
		central_objs_unit->draw(JETTY);
	}
	glPopMatrix();

}