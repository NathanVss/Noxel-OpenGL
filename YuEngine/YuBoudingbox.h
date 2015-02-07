#pragma once

#include "Object.h"

namespace YuEngine {
class YuBoudingbox : public Object
{
public:
	YuBoudingbox(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	YuBoudingbox(int x1, int y1, int width, int height);
	YuBoudingbox() {};
	~YuBoudingbox(void);
	int getX1();
	int getX2();
	int getX3();
	int getX4();
	int getY1();
	int getY2();
	int getY3();
	int getY4();
	void render(Container* container);
	void changePos(int x1, int y1);

	void setColor(int red, int green, int blue);

	bool isInside(float _x, float _y);
	bool isInsideRight(float _x, float _y);
	bool isInsideLeft(float _x, float _y);

	bool doesCollideTopRightOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideBottomLeftOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideBottomRightOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideTopLeftOf(YuBoudingbox &yuBoudingbox);

	bool doesCollideBottomOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideTopOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideLeftOf(YuBoudingbox &yuBoudingbox);
	bool doesCollideRightOf(YuBoudingbox &yuBoudingbox);
	int getWidth();
	int getHeight();

private:
	int red;
	int green;
	int blue;

	int x1;
	int y1;

	int x2;
	int y2;

	int x3;
	int y3;

	int x4;
	int y4;

	int width;
	int height;
};

}