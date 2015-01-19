#include "PixelsMap.h"


PixelsMap::PixelsMap(void): width(0), height(0), red(nullptr), blue(nullptr), green(nullptr), alpha(nullptr) {
}

PixelsMap::PixelsMap(int _width, int _height) : width(_width), height(_height), red(nullptr), blue(nullptr), green(nullptr), alpha(nullptr){
	initArrays();

}

void PixelsMap::initArrays() {

	red = new unsigned char*[width];
	for(int x = 0; x < width; x++) {
		red[x] = new unsigned char[height];
		
	}

	green = new unsigned char*[width];
	for(int x = 0; x < width; x++) {
		green[x] = new unsigned char[height];
	}

	blue = new unsigned char*[width];
	for(int x = 0; x < width; x++) {
		blue[x] = new unsigned char[height];
	}

	alpha = new unsigned char*[width];
	for(int x = 0; x < width; x++) {
		alpha[x] = new unsigned char[height];
	}
}

bool PixelsMap::setScale(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	if( x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
	red[x][y] = r;
	green[x][y] = g;
	blue[x][y] = b;
	alpha[x][y] = a;
	return true;
}


void PixelsMap::destroyArrays() {
	for(int x = 0; x < width; x++) {
		if(this->red) {
			delete[] this->red[x];

		}
		if(this->green) {
			delete[] this->green[x];

		}
		if(this->blue) {
			delete[] this->blue[x];
	
		}
		if(this->alpha) {
			delete[] this->alpha[x];

		}
	}
	if(this->red) {
		delete[] this->red;
	}
	if(this->green) {
		delete[] this->green;
	}
	if(this->blue) {
		delete[] this->blue;
	}
	if(this->alpha) {
		delete[] this->alpha;
	}

}
PixelsMap::~PixelsMap(void){
	destroyArrays();
}
