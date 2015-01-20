#include "DDAHelper.h"
#include <math.h>

namespace YuEngine {

DDAHelper::DDAHelper(float sx, float sy, float ex, float ey){

	this->sx = sx;
	this->sy = sy;
	this->ex = ex;
	this->ey = ey;

	float divizor = ex - sx;
	if( divizor == 0) { divizor = 1; }
	this->a = (ey - sy) / divizor;
	this->b = ey - ex * a;
	this->isFirst = true;

	this->lastX = sx;
	this->lastY = sy;
}

coords DDAHelper::getNextCoords() {
	
	if(!this->isFirst) {

		if(this->sx == this->ex) {

			if(this->sy > this->ey) {
				this->lastY -= 1;
			} else {
				this->lastY += 1;
			}
		} else {



			float nextYAxisDist;
			float nextXAxisDist;
			if(this->ex > this->sx) {
				nextXAxisDist = 1;
			} else {
				nextXAxisDist = -1;
			}

			if(this->ey > this->sy) {
				nextYAxisDist = 1;
			} else {
				nextYAxisDist = -1;
			}

			float yOfIntersectXAxis = a*(nextXAxisDist + this->lastX)  + b;
			float xOfIntersectYAxis = ((nextYAxisDist + this->lastY) - b) / a;

			float XdeltaToNextYAxis = xOfIntersectYAxis - this->sx;
			float XdeltaToNextXAxis = nextXAxisDist;

			float YdeltaToNextYAxis = nextYAxisDist;
			float YdeltaToNextXAxis = yOfIntersectXAxis - this->sy;

			// NEXT X AXIS = [dx+nextXAxisDist;yOfIntersectXAxis]
			// NEXT Y AXIS = [xOfIntersectYAxis;py+nextYAxisDist]
			float distToNextXAxisIntersect = (pow((XdeltaToNextXAxis),2) + pow((YdeltaToNextXAxis), 2));
			float distToNextYAxisIntersect = (pow((XdeltaToNextYAxis),2) + pow((YdeltaToNextYAxis), 2));


			if(distToNextXAxisIntersect > distToNextYAxisIntersect) {
				// On prend la prochaine Y
				this->lastX = xOfIntersectYAxis;
				this->lastY += nextYAxisDist;
			} else {
				// Prochainn X
				this->lastX += nextXAxisDist;
				this->lastY = yOfIntersectXAxis;
			}



		}

	}

	if(this->isFirst) {
		this->isFirst = false;
	}

	coords pt;
	pt.x = floor(this->lastX);
	pt.y = floor(this->lastY);
	return pt;
}

DDAHelper::~DDAHelper(void)
{
}

}