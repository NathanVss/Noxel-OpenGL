#include "Entity.h"
#include "Block.h"
#include <YuEngine\DDAHelper.h>
#include <vector>

Entity::Entity(void){
	x = 0;
	y = 0;
	gravity = 50;
	velocityX = 0;
	velocityY = 0;
	width = 0;
	height = 0;
	collideOnBottom = false;
	collideOnLeft = false;
	collideOnRight = false;
	collideOnTop = false;
	collideOnTopLeft = false;
	collideOnTopRight = false;
	collideOnBottomRight = false;
	collideOnBottomLeft = false;
}

void Entity::checkCollisions(float destX, float destY) {

	bool verticalToTopMov = false;
	bool verticalToBottomMov = false;
	bool transvToLeftMov = false;
	bool transvToRightMov = false;
	bool diagToTopRightMov = false;
	bool diagToTopLeftMov = false;
	bool diagToBottomLeftMov = false;
	bool diagToBottomRightMov = false;
	bool idleMov = false;

	bool canPass = false;
	while(canPass == false) {
		verticalToTopMov = false;
		verticalToBottomMov = false;
		transvToLeftMov = false;
		transvToRightMov = false;
		diagToTopRightMov = false;
		diagToTopLeftMov = false;
		diagToBottomLeftMov = false;
		diagToBottomRightMov = false;
		idleMov = false;


		if(this->x > destX && destY < this->y) {
			diagToTopLeftMov = true;
		}
		if(this->x < destX && this->y > destY) {
			diagToTopRightMov = true;
		}
		if(this->x > destX && destY > this->y) {
			diagToBottomLeftMov = true;
		}
		if(this->x < destX && destY > this->y) {
			diagToBottomRightMov = true;
		}
		if(this->x == destX && destY > this->y) {
			verticalToBottomMov = true;
		}
		if(this->x == destX && destY < this->y) {
			verticalToTopMov = true;
		}
		if(destY == this->y && this->x < destX) {
			transvToRightMov = true;
		}
		if(destY == this->y && this->x > destX) {
			transvToLeftMov = true;
		}
		if(destY == this->y && this->x == destX) {
			idleMov = true;
		}

		if(diagToBottomLeftMov && this->collideOnBottom) {
			destY = this->y;
		} else if(diagToBottomRightMov && this->collideOnBottom) {
			destY = this->y;
		} else if(diagToTopLeftMov && this->collideOnTop) {
			destY = this->y;
		} else if(diagToTopRightMov && this->collideOnTop) {
			destY = this->y;
		} else if (diagToBottomLeftMov && this->collideOnLeft) {
			destX = this->x;
		} else if (diagToBottomRightMov && this->collideOnRight) {
			destX = this->x;
		} else if (diagToTopRightMov && this->collideOnRight) {
			destX = this->x;
		} else if (diagToTopLeftMov && this->collideOnLeft) {
			destX = this->x;
		} else {
			canPass = true;
		}
	}
	// Conversion des coords en block unit
	int buX = floor(x / Block::size);
	int buY = floor(y / Block::size);
	int destBuX = floor((destX / Block::size));
	int destBuY = floor(destY / Block::size);
	std::cout << "BlockUnit [" << buX << ";" << buY << "]" << std::endl;
	std::cout << "BlockUnit Dest [" << destBuX << ";" << destBuY << "]" << std::endl;

	YuEngine::DDAHelper ddaHelper(buX, buY, destBuX, destBuY);
	YuEngine::coords coords;
	coords.x = buX;
	coords.y = buY;

	std::vector<Block*> blocksToCheck;

	while(!(coords.x == destBuX && coords.y == destBuY)) {
		coords = ddaHelper.getNextCoords();
		std::cout << "[" << coords.x << ";" << coords.y << "]" << std::endl;

	}

}



Entity::~Entity(void)
{
}
