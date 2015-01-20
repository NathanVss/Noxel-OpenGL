#pragma once

namespace YuEngine {

struct coords {
	int x;
	int y;
};

class DDAHelper
{
public:
	DDAHelper(float sx, float sy, float ex, float ey);
	~DDAHelper(void);
	coords getNextCoords();

private:
	float a;
	float b;

	float sx;
	float sy;

	float ex;
	float ey;

	float lastX;
	float lastY;

	bool isFirst;
};

}