#ifndef CCUBE_H
#define CCUBE_H

class ccube
{
public:
	ccube(float = 0, float = 0, float = 0, 
		float = 0, float = 0, float = 0);
	void set(float , float , float, float, float, float);
	void setUP(float);
	void setDOWN(float);
	void setLEFT(float);
	void setRIGHT(float);
	void setFRONT(float);
	void setBACK(float);
	~ccube();
private:
	float up, down, left, right, front, back;
};

#endif

ccube::ccube(float u, float d, float l,
	float r, float f, float b){

	up = u;
	down = d;
	left = l;
	right = r;
	front = f;
	back = b;
}

ccube::set(float u, float d, float l,
	float r, float f, float b){

	up = u;
	down = d;
	left = l;
	right = r;
	front = f;
	back = b;
}

void ccube::setUP(float u){
	up = u;
}

void ccube::setDOWN(float d){ 
	down = d;
}

void ccube::setLEFT(float l){
	left = l;
}

void ccube::setRIGHT(float r){
	right = r;
}

void ccube::setFRONT(float f){
	front = f;
}

void ccube::setBACK(float b){
	back = b;
}