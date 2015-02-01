#include "YuBoudingbox.h"
#include "Container.h"
#include "GameRenderer.h"
#include "SpritesheetsManager.h"

namespace YuEngine {

YuBoudingbox::YuBoudingbox(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->x3 = x3;
	this->y3 = y3;
	this->x4 = x4;
	this->y4 = y4;

	this->red = 0;
	this->green = 255;
	this->blue = 0;
}

void YuBoudingbox::render(Container* container) {
	container->getGameRenderer()->addGlyph(x1, x2, width, height, 18.0f, 1.0f, 1.0f, 1.0f, 1.0f, container->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);
}

void YuBoudingbox::changePos(int x1, int y1) {
	this->x1 = x1;
	this->y1 = y1;
}

void YuBoudingbox::setColor(int red, int green,int blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

YuBoudingbox::YuBoudingbox(int x1, int y1, int width, int height) {
	this->x1 = x1;
	this->y1 = y1;
	this->width = width;
	this->height = height;

	this->red = 0;
	this->green = 255;
	this->blue = 0;
}

int YuBoudingbox::getHeight() {
	return this->height;
}

int YuBoudingbox::getWidth() {
	return this->width;
}

/*
[ RECT 1 ]
		  [ RECT 2 ]
*/
bool YuBoudingbox::doesCollideTopLeftOf(YuBoudingbox &Rect2) {
	if(this->x1 + this->width == Rect2.getX1() && this->y1 - this->height == Rect2.getY1()) {
		return true;
	}
	return false;
}


/*
[ RECT 2 ]
		  [ RECT 1 ]
*/
bool YuBoudingbox::doesCollideBottomRightOf(YuBoudingbox &Rect2) {
	if(Rect2.getX1() + Rect2.getWidth() == this->x1 && Rect2.getY1() - Rect2.getHeight() == this->y1) {
		return true;
	}
	return false;
}

/*
		  [ RECT 2 ]
[ RECT 1 ]
*/
bool YuBoudingbox::doesCollideBottomLeftOf(YuBoudingbox &Rect2) {
	if(Rect2.getX1() == this->x1 + this->width && this->y1 == Rect2.getY1() - Rect2.getHeight()) {
		return true;
	}
	return false;
}

/*
		  [ RECT 1 ]
[ RECT 2 ]

*/
bool YuBoudingbox::doesCollideTopRightOf(YuBoudingbox &Rect2)  {

	if(Rect2.getX1() + Rect2.getWidth() == this->x1 && Rect2.getY1() == this->y1 - this->height) {
		return true;
	}

	return false;
}

/*

[ RECT 2 ][ RECT 1 ]

*/
bool YuBoudingbox::doesCollideRightOf(YuBoudingbox &Rect2) {
	if(Rect2.getX1() + Rect2.getWidth() == x1) {


		if((Rect2.getY1() > y1 - height && y1 - height > Rect2.getY1() - Rect2.getHeight()) ||
			(y1  < Rect2.getY1() && y1 > Rect2.getY1() - Rect2.getHeight()) ||
			(Rect2.getY1() < y1 && Rect2.getY1() > y1 - height) ||
			(y1 < Rect2.getY1() && y1 > Rect2.getY1() - Rect2.getHeight()) ||
			(y1 == Rect2.getY1())) {
			return true;
		}

	}

	return false;
}

/*

[ RECT 1 ][ RECT 2 ]

*/
bool YuBoudingbox::doesCollideLeftOf(YuBoudingbox &Rect2) {

	if(this->x1 + this->width == Rect2.getX1()) {
		if((Rect2.getY1() > y1 - height && y1 - height > Rect2.getY1() - Rect2.getHeight()) ||
			(y1  < Rect2.getY1() && y1 > Rect2.getY1() - Rect2.getHeight()) ||
			(Rect2.getY1() < y1 && Rect2.getY1() > y1 - height) ||
			(y1 < Rect2.getY1() && y1 > Rect2.getY1() - Rect2.getHeight()) ||
			(y1 == Rect2.getY1())
			) {
			return true;
		}


	}

	return false;
}

/*

[ RECT 2]
[ RECT 1]

*/
bool YuBoudingbox::doesCollideBottomOf(YuBoudingbox &Rect2) {


	if(Rect2.getY1()-Rect2.getHeight() == y1) {

		if ((Rect2.getX1() > this->x1 && Rect2.getX1() < this->x1 + this->width) || 
			(Rect2.getX1() + Rect2.getWidth() > this->x1 && Rect2.getX1() + Rect2.getWidth() < this->x1 + this->width) ||
			(this->x1 > Rect2.getX1() && this->x1 < Rect2.getX1() + Rect2.getWidth()) || 
			(this->x1 + this->width > Rect2.getX1() && this->x1 + this->width < Rect2.getX1() + Rect2.getWidth()) ||
			(this->x1 == Rect2.getX1() && this->x1 + this->width == Rect2.getX1() + Rect2.getWidth())) {

		//std::cout << "TOUCH BOTTOM" << std::endl;
		return true;
		}
	}
	return false;
}


/*

[ RECT 1]
[ RECT 2]

*/
bool YuBoudingbox::doesCollideTopOf(YuBoudingbox &Rect2) {
	int is = this->y1 - this->height;
	if(this->y1 - this->height == Rect2.getY1()) {


		if ((Rect2.getX1() > this->x1 && Rect2.getX1() < this->x1 + this->width) || 
			(Rect2.getX1() + Rect2.getWidth() > this->x1 && Rect2.getX1() + Rect2.getWidth() < this->x1 + this->width) ||
			(this->x1 > Rect2.getX1() && this->x1 < Rect2.getX1() + Rect2.getWidth()) || 
			(this->x1 + this->width > Rect2.getX1() && this->x1 + this->width < Rect2.getX1() + Rect2.getWidth()) ||
			(this->x1 == Rect2.getX1() && this->x1 + this->width == Rect2.getX1() + Rect2.getWidth())) {

		return true;
		}
	}
	return false;
}

int YuBoudingbox::getX1() {
	return this->x1;
}
int YuBoudingbox::getX4() {
	return this->x4;
}
int YuBoudingbox::getX3() {
	return this->x3;
}
int YuBoudingbox::getX2() {
	return this->x2;
}
int YuBoudingbox::getY1() {
	return this->y1;
}
int YuBoudingbox::getY2() {
	return this->y2;
}

int YuBoudingbox::getY3() {
	return this->y3;
}

int YuBoudingbox::getY4() {
	return this->y4;
}


YuBoudingbox::~YuBoudingbox(void)
{
}

}