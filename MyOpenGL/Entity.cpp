#include "Entity.h"
#include "Block.h"
#include <YuEngine\DDAHelper.h>
#include <vector>
#include "World.h"
#include "Container.h"

Entity::Entity(void){
	x = 0;
	y = 0;
	gravity = 1.0f;
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
	destroy = false;
}

void Entity::update() {

}

void Entity::applyGravity() {
	if(!affectedByGravity) {
		return;
	}
	if(!collideOnBottom) {

		if(velocityY >= - 100) {
			velocityY -= gravity;
		}
	} else {
		velocityY = 0;
	}

}


void Entity::handleMoving() {


	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;


	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	boundingBox.changePos(endLocation.x, endLocation.y);
	x = endLocation.x;
	y = endLocation.y;
}

glm::vec2 Entity::checkCollisions(float startX, float startY, float destX, float destY) {

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


		if(startX > destX && destY > startY) {
			diagToTopLeftMov = true;
		}

		if(startX < destX && startY < destY) {
			diagToTopRightMov = true;
		}
		if(startX > destX && destY < startY) {
			diagToBottomLeftMov = true;
		}
		if(startX < destX && destY < startY) {
			diagToBottomRightMov = true;
		}


		if(startX == destX && destY < startY) {
			verticalToBottomMov = true;
		}
		if(startX == destX && destY > startY) {
			verticalToTopMov = true;
		}
		if(destY == startY && startX < destX) {
			transvToRightMov = true;
		}
		if(destY == startY && startX > destX) {
			transvToLeftMov = true;
		}
		if(destY == startY && startX == destX) {
			idleMov = true;
		}

		if(diagToBottomLeftMov && this->collideOnBottom) {
			destY = startY;
		} else if(diagToBottomRightMov && this->collideOnBottom) {
			destY = startY;
		} else if(diagToTopLeftMov && this->collideOnTop) {
			destY = startY;
		} else if(diagToTopRightMov && this->collideOnTop) {
			destY = startY;
		} else if (diagToBottomLeftMov && this->collideOnLeft) {
			destX = startX;
		} else if (diagToBottomRightMov && this->collideOnRight) {
			destX = startX;
		} else if (diagToTopRightMov && this->collideOnRight) {
			destX = startX;
		} else if (diagToTopLeftMov && this->collideOnLeft) {
			destX = startX;
		} else {
			canPass = true;
		}
	}


	std::vector<YuEngine::coords> traj;
	destX = (int)destX;
	destY = (int)destY;
	YuEngine::DDAHelper trajHelper(startX, startY, destX, destY);
	YuEngine::coords trajCoords;
	trajCoords.x = startX;
	trajCoords.y = startY;
	while(true) {

		YuEngine::coords curCoords;
		curCoords = trajCoords;
		traj.push_back(curCoords);
		if((trajCoords.x == destX && trajCoords.y == destY)) {
			break;
		}
		
		trajCoords = trajHelper.getNextCoords();
	}
	// Conversion des coords en block unit
	int buX = floor(startX / Block::size);
	int buY = floor(startY / Block::size);
	int destBuX = floor((destX / Block::size));
	int destBuY = floor(destY / Block::size);

	YuEngine::DDAHelper ddaHelper(buX, buY, destBuX, destBuY);
	YuEngine::coords coords;
	coords.x = buX;
	coords.y = buY;

	std::vector<Block*> blocksToCheck;

	bool first = true;
	while(true) {
		std::vector<Block*> curBlocks;

		glm::vec2 centerCurCoords(floor(((coords.x *Block::size + boundingBox.getWidth()/2) / Block::size)), floor((coords.y *Block::size - boundingBox.getHeight()/2) / Block::size));
		int size = 3;
		for(int fx = -size+1; fx <= size; fx++) {
			for(int fy = -size+1; fy <= size; fy++) {
				curBlocks.push_back(myContainer->getWorld()->getBlock(centerCurCoords.x * Block::size + fx * Block::size, centerCurCoords.y * Block::size + fy * Block::size));

			}
		}

		for(int i = 0; i < curBlocks.size(); i++) {
			if(curBlocks[i] && std::find(blocksToCheck.begin(), blocksToCheck.end(), curBlocks[i]) == blocksToCheck.end()) {
				blocksToCheck.push_back(curBlocks[i]);
			}
		}
		if((coords.x == destBuX && coords.y == destBuY)) {

			break;
		}
		coords = ddaHelper.getNextCoords();
	}
	YuEngine::Color c;
	c.r = 50;
	c.g = 50;
	c.b = 50;
	c.a = 255;

	collideOnRight = false;
	collideOnTop = false;
	collideOnBottom = false;
	collideOnLeft = false;
	collideOnTopLeft = false;
	collideOnTopRight = false;
	collideOnBottomLeft = false;
	collideOnBottomRight = false;


	glm::vec2 endLocation(startX, startY);
	for(int j = 0; j < traj.size(); j++) {


		boundingBox.changePos(traj[j].x, traj[j].y);

		for(int i = 0; i < blocksToCheck.size(); i++) {
			//blocksToCheck[i]->setLightIndice(c);
			if(!(blocksToCheck[i]->getHasBoudingbox())) {
				continue;
			}
		
			Block* CurBlock = blocksToCheck[i];
			YuEngine::YuBoudingbox CurBoundingBox = CurBlock->getBoundingbox();

			/* 
			[ ME ]
			[ BLOCK ]
			*/
			if(boundingBox.doesCollideTopOf(CurBoundingBox)) {
				this->collideOnBottom = true;
				//std::cout << "BOTTOM" << std::endl;
			}

			/*
			[ BLOCK ]
			[ ME ]
			*/
			if(boundingBox.doesCollideBottomOf(CurBoundingBox)) {
				this->collideOnTop = true;
				//std::cout << "TOP" << std::endl;
			}

			/*
			[ BLOCK ][ ME ]
			*/
			if(boundingBox.doesCollideRightOf(CurBoundingBox)) {
				this->collideOnLeft = true;
						
				//std::cout << "LEFT" << std::endl;
			}

			/*
			[ ME ][ BLOCK ]
			*/
			if(boundingBox.doesCollideLeftOf(CurBoundingBox)) {
				this->collideOnRight = true;
				//std::cout << "RIGHT" << std::endl;	
			}
			/*
			[ ME ] <-
					[ BLOCK ]
			*/
			if(boundingBox.doesCollideTopLeftOf(CurBoundingBox)) {
				this->collideOnBottomRight = true;
				//std::cout << "BOTTOM RIGHT" << std::endl;
			}

			/*
						[ ME ] <-
			[ BLOCK ]
			*/
			if(boundingBox.doesCollideTopRightOf(CurBoundingBox)) {
				this->collideOnBottomLeft = true;
				//std::cout << "BOTTOM LEFT" << std::endl;
			}

			/*
					[ BLOCK ]
			[ ME ] <-
			*/
			if(boundingBox.doesCollideBottomLeftOf(CurBoundingBox)) {
				this->collideOnTopRight = true;
				//std::cout << "TOP RIGHT" << std::endl;
			}
					
			/*
			[ BLOCK ]
						[ ME ] <-
			*/
			if(boundingBox.doesCollideBottomRightOf(CurBoundingBox)) {
				//std::cout << "TOP LEFT" << std::endl;
				this->collideOnTopLeft = true;
			}


		}


		if(transvToLeftMov && this->collideOnLeft){
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);
			return endLocation;
		}
		if(transvToRightMov && this->collideOnRight){
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(verticalToBottomMov && this->collideOnBottom) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(verticalToTopMov && this->collideOnTop) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(diagToTopLeftMov && (this->collideOnLeft || this->collideOnTop || this->collideOnTopLeft)) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(diagToTopRightMov && (this->collideOnRight || this->collideOnTop || this->collideOnTopRight)) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(diagToBottomLeftMov && (this->collideOnLeft || this->collideOnBottom || this->collideOnBottomLeft)) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if(diagToBottomRightMov && (this->collideOnRight || this->collideOnBottom || this->collideOnBottomRight)) {
			//this->x = traj[j].x;
			//this->y = traj[j].y;
			endLocation = glm::vec2(traj[j].x, traj[j].y);

			return endLocation;
		}
		if( j != traj.size() - 1) {
			collideOnBottom = false;
			collideOnLeft = false;
			collideOnRight = false;
			collideOnTop = false;
			collideOnTopLeft = false;
			collideOnTopRight = false;
			collideOnBottomRight = false;
			collideOnBottomLeft = false;
		}

	}
	endLocation = glm::vec2(traj[traj.size() -1].x, traj[traj.size() - 1].y);
	return endLocation;
	//this->x = traj[traj.size()-1].x;
	//this->y = traj[traj.size()-1].y;

}


Entity::~Entity(void)
{
}
