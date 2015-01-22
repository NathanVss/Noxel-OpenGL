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
				// Si il est entier alors la distance sera forcément "lui + 1"
				if(floor(lastX) == lastX || ceil(lastX) == lastX) {
					nextXAxisDist = 1;
				// Sinon lui + "ce qu'il faut" pour que = ceil(lastX)
				} else {
					nextXAxisDist = ceil(lastX) - lastX;
				}
				
			} else {
				if(floor(lastX) == lastX || ceil(lastX) == lastX) {
					nextXAxisDist = -1;
				} else {
					// floor(-1.5) = -2
					// ceil(-1.5) = -1

					// De 15.6 => 15
					// floor(15.6) = 15
					// 15 - 15.6 = -0.6

					// De -1.6 => -2
					// floor(-1.6) = -2
					// -2 - ( - 1.6 ) = -0.6
					nextXAxisDist = floor(lastX) - lastX;
				}
			}

			if(this->ey > this->sy) {
				if(floor(lastY) == lastY || ceil(lastY) == lastY) {
					nextYAxisDist = 1;
				} else {

					nextYAxisDist = ceil(lastY) - lastY;

				}
			} else {
				if(floor(lastY) == lastY || ceil(lastY) == lastY) {
					nextYAxisDist = -1;
				} else {

					nextYAxisDist = floor(lastY) - lastY;

				}
			}
			// revoir nextXAxis dist qui peut être diff de 1 ou -1 ( c'est plutôt la distance entre lastX et Ceil lastX
			float yOfIntersectXAxis = a*(nextXAxisDist + this->lastX)  + b;
			float xOfIntersectYAxis = ((nextYAxisDist + this->lastY) - b) / a;

			float XdeltaToNextYAxis = xOfIntersectYAxis - this->sx;
			float XdeltaToNextXAxis = nextXAxisDist;

			float YdeltaToNextYAxis = nextYAxisDist;
			float YdeltaToNextXAxis = yOfIntersectXAxis - this->sy;

			// NEXT X AXIS = [dx+nextXAxisDist;yOfIntersectXAxis]
			// NEXT Y AXIS = [xOfIntersectYAxis;py+nextYAxisDist]
			float distToNextXAxisIntersect1 = (pow((lastX - (lastX+nextXAxisDist)), 2) + pow((lastY - yOfIntersectXAxis), 2));
			float distToNextYAxisIntersect1 = (pow((lastX - xOfIntersectYAxis), 2) + pow((lastY - ( lastY + nextYAxisDist)), 2));

			float distToNextXAxisIntersect = (pow((XdeltaToNextXAxis),2) + pow((YdeltaToNextXAxis), 2));
			float distToNextYAxisIntersect = (pow((XdeltaToNextYAxis),2) + pow((YdeltaToNextYAxis), 2));


			if(distToNextXAxisIntersect1 > distToNextYAxisIntersect1) {
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
	pt.y = ceil(this->lastY);
	return pt;
}

DDAHelper::~DDAHelper(void)
{
}

}