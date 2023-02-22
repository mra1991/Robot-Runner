#include "map.h"

map::map(string filename, objHandler* objs_unit){
	ifstream fin(filename.c_str());
	obstacle* new_obs;
	char obs_type;
	GLfloat x, y, z;
	while(fin >> obs_type){
		new_obs = new obstacle(obs_type, objs_unit);
		fin >> x >> y >> z;
		new_obs->set_pos(x, y, z);
		obss.push_back(new_obs);
	}
}

void map::draw(){
	for(int i = 0; i < (int)obss.size(); i++)
		obss[i]->draw();
}

void map::reset(){
	for(int i = 0; i < (int)obss.size(); i++)
		obss[i]->reset();
}

void map::update(){
	for(int i = 0; i < (int)obss.size(); i++)
		obss[i]->update();
}

void map::get_pos_i(int ni, GLfloat* po){
	obss[ni]->get_pos(po);
}

void map::get_dims_i(int ni, GLfloat* di){
	obss[ni]->get_dims(di);
}

char map::get_type_i(int ni){
	return obss[ni]->get_type();
}

int map::num_of_obss(){
	return (int)obss.size();
}