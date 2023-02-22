#include "environment.h"

/*inputs a description file and a pointer to an objHandeler 
	(which has already loaded all the models and knows how to 
	draw them) and creates decorative objecs according to file 
	data and stores them in a vector*/
environment::environment(string filename, objHandler* objs_unit){
	ifstream fin(filename.c_str());
	decorative* new_decor;
	int obj_id;
	GLfloat x, y, z;
	while(fin >> obj_id){
		new_decor = new decorative((ObjName)obj_id, objs_unit);
		fin >> x >> y >> z;
		new_decor->setPos(x, y, z);
		fin >> x >> y >> z;
		new_decor->setRot(x, y, z);
		decors.push_back(new_decor);
	}
}

void environment::draw(){
	for(int i = 0; i < (int)decors.size(); i++)
		decors[i]->draw();
}