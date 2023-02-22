#include "objHandler.h"

objHandler::objHandler(string desc_filename){

	//read objects descriptions from file
	ifstream fin(desc_filename.c_str());
	fin.ignore(100, '\n'); //first line is trash!
	fin.ignore(100, '\n'); //so is the second one!
	int p;
	for (int i = 0; i < NUM_OF_OBJS; i++)
	{
		fin >> p;
		fin >> obj_names[i];
		fin >> filenames[i];
		fin >> has_text[i];
		fin >> default_widths[i];
	}

	//load actual models
	GLfloat minMax[6];
	GLfloat trans[3];
	GLfloat scl;
	for(int i = 0; i < NUM_OF_OBJS; i++){
		//read .obj file
		model[i] = glmReadOBJ(filenames[i].c_str());
		glmVertexNormals(model[i], 90.0, GL_TRUE);

		/*normalize the model, so that the y-axis
			will cuts model's center and minimum
			y coordinate will be 0. also scales the 
			model to feat default width*/
		glmMinMax(model[i], minMax);
		trans[0] = -(minMax[0] + minMax[3]) / 2;
		trans[1] = -minMax[1];
		trans[2] = -(minMax[2] + minMax[5]) / 2;
		glmTranslate(model[i], trans);
		scl = default_widths[i] / (minMax[3] - minMax[0]);
		if(scl < 0)  scl *= -1;
		glmScale(model[i], scl);

		//get and store dimentions of the model
		glmDimensions(model[i], dimentions[i]);

		//make display list and store it's ID
		disp_list_ids[i] = glmList(model[i], GLM_SMOOTH|GLM_MATERIAL);
		
		/* in case of no texture, 
			we don"t need the model any more!*/
		if(!has_text[i]){ 
			/*we are done with this model, 
				let's delete it and free memory*/
			glmDelete(model[i]);
		}
	}

}

objHandler::~objHandler(){

}


string objHandler::get_obj_name(int obj_id){
	return obj_names[obj_id];
}

/* dims: array of 3 GLfloats*/
void objHandler::get_dimentions(ObjName OBJ, GLfloat* dims){
	dims[0] = dimentions[OBJ][0];
	dims[1] = dimentions[OBJ][1];
	dims[2] = dimentions[OBJ][2];
}

void objHandler::draw(ObjName OBJ){
	if(has_text[OBJ]){
		glmDraw(model[OBJ], GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE);
	}
	else{
		glCallList(disp_list_ids[OBJ]);
	}
}
