#include "Entity.h"
#include "Block.h"
#include <YuEngine\DDAHelper.h>
#include <vector>
#include "World.h"
#include "Container.h"

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


		if(this->x > destX && destY > this->y) {
			diagToTopLeftMov = true;
		}

		if(this->x < destX && this->y < destY) {
			diagToTopRightMov = true;
		}
		if(this->x > destX && destY < this->y) {
			diagToBottomLeftMov = true;
		}
		if(this->x < destX && destY < this->y) {
			diagToBottomRightMov = true;
		}


		if(this->x == destX && destY < this->y) {
			verticalToBottomMov = true;
		}
		if(this->x == destX && destY > this->y) {
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
			std::cout << "CORRECTION" << std::endl;
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


	std::vector<YuEngine::coords> traj;
	YuEngine::DDAHelper trajHelper(x, y, destX, destY);
	YuEngine::coords trajCoords;
	trajCoords.x = x;
	trajCoords.y = y;
	while(true) {

		YuEngine::coords curCoords;
		curCoords = trajCoords;
		traj.push_back(curCoords);
		if((trajCoords.x == destX && trajCoords.y == destY)) {
			break;
		}
		
		trajCoords = trajHelper.getNextCoords();
	}

	if(!idleMov) {
	std::cout << "Player [" << x << ";" << y << "] => [" << destX << ";" << destY << "]" << std::endl;

	}
	if(diagToBottomLeftMov) {
		std::cout << "DIAG TO BOTTOM LEFT" << std::endl;
	}
	if(diagToBottomRightMov) {
		std::cout << "DIAG TO BOTTOM RIGHT" << std::endl;
	}
	if(diagToTopLeftMov) {
		std::cout << "DIAG TO TOP LEFT" << std::endl;
	}
	if(diagToTopRightMov) {
		std::cout << "DIAG TO TOP RIGHT" << std::endl;
	}
	if(verticalToBottomMov) {
		std::cout << "VERTICAL TO BOTTOM" << std::endl;
	}
	if(verticalToTopMov) {
		std::cout << "VERTICAL TO TOP" << std::endl;
	}
	if(transvToLeftMov) {
		std::cout << "TRANSV TO LEFT" << std::endl;
	}
	if(transvToRightMov) {
		std::cout << "TRANSV TO RIGHT" << std::endl;
	}
	// Conversion des coords en block unit
	int buX = floor(x / Block::size);
	int buY = floor(y / Block::size);
	int destBuX = floor((destX / Block::size));
	int destBuY = floor(destY / Block::size);
	//std::cout << "BlockUnit [" << buX << ";" << buY << "]" << std::endl;
	//std::cout << "BlockUnit Dest [" << destBuX << ";" << destBuY << "]" << std::endl;

	YuEngine::DDAHelper ddaHelper(buX, buY, destBuX, destBuY);
	YuEngine::coords coords;
	coords.x = buX;
	coords.y = buY;

	std::vector<Block*> blocksToCheck;

	bool first = true;
	while(true) {
		//std::cout << "[" << coords.x << ";" << coords.y << "]" << std::endl;
		std::vector<Block*> curBlocks;

		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size, coords.y * Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size, coords.y * Block::size + 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size, coords.y * Block::size - 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size, coords.y * Block::size - 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size, coords.y * Block::size + 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 1 * Block::size, coords.y*Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y*Block::size));

		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 1 * Block::size, coords.y*Block::size + 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 1 * Block::size, coords.y*Block::size - 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 1 * Block::size, coords.y*Block::size + 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 1 * Block::size, coords.y*Block::size - 2 *Block::size));
		
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y*Block::size + 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y*Block::size - 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y*Block::size + 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y*Block::size - 2 *Block::size));


		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 2*Block::size, coords.y*Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 2 * Block::size, coords.y*Block::size + 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 2 * Block::size, coords.y*Block::size - 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 2 * Block::size, coords.y*Block::size - 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size - 2 * Block::size, coords.y*Block::size + 2 *Block::size));
		
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 2*Block::size, coords.y*Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 2 * Block::size, coords.y*Block::size + 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 2 * Block::size, coords.y*Block::size - 1 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 2 * Block::size, coords.y*Block::size - 2 *Block::size));
		curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 2 * Block::size, coords.y*Block::size + 2 *Block::size));

		//curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y * Block::size));
		//curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y + 1 *Block::size));
		//curBlocks.push_back(myContainer->getWorld()->getBlock(coords.x * Block::size + 1 * Block::size, coords.y - 1 *Block::size));

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
	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;

	collideOnRight = false;
	collideOnTop = false;
	collideOnBottom = false;
	collideOnLeft = false;
	collideOnTopLeft = false;
	collideOnTopRight = false;
	collideOnBottomLeft = false;
	collideOnBottomRight = false;

	for(int j = 0; j < traj.size(); j++) {

		if(!idleMov)
			std::cout << "Checking [" << traj[j].x << ";" << traj[j].y << std::endl;

		boundingBox.changePos(traj[j].x, traj[j].y);

		for(int i = 0; i < blocksToCheck.size(); i++) {
			blocksToCheck[i]->setLightIndice(c);
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
				std::cout << "BOTTOM" << std::endl;
			}

			/*
			[ BLOCK ]
			[ ME ]
			*/
			if(boundingBox.doesCollideBottomOf(CurBoundingBox)) {
				this->collideOnTop = true;
				std::cout << "TOP" << std::endl;
			}

			/*
			[ BLOCK ][ ME ]
			*/
			if(boundingBox.doesCollideRightOf(CurBoundingBox)) {
				this->collideOnLeft = true;
						
				std::cout << "LEFT" << std::endl;
			}

			/*
			[ ME ][ BLOCK ]
			*/
			if(boundingBox.doesCollideLeftOf(CurBoundingBox)) {
				this->collideOnRight = true;
				std::cout << "RIGHT" << std::endl;	
			}

			/*
			[ ME ] <-
					[ BLOCK ]
			*/
			if(boundingBox.doesCollideTopLeftOf(CurBoundingBox)) {
				this->collideOnBottomRight = true;
				std::cout << "BOTTOM RIGHT" << std::endl;
			}

			/*
						[ ME ] <-
			[ BLOCK ]
			*/
			if(boundingBox.doesCollideTopRightOf(CurBoundingBox)) {
				this->collideOnBottomLeft = true;
				std::cout << "BOTTOM LEFT" << std::endl;
			}

			/*
					[ BLOCK ]
			[ ME ] <-
			*/
			if(boundingBox.doesCollideBottomLeftOf(CurBoundingBox)) {
				this->collideOnTopRight = true;
				std::cout << "TOP RIGHT" << std::endl;
			}
					
			/*
			[ BLOCK ]
						[ ME ] <-
			*/
			if(boundingBox.doesCollideBottomRightOf(CurBoundingBox)) {
				std::cout << "TOP LEFT" << std::endl;
				this->collideOnTopLeft = true;
			}


		}


		if(transvToLeftMov && this->collideOnLeft){
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(transvToRightMov && this->collideOnRight){
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(verticalToBottomMov && this->collideOnBottom) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(verticalToTopMov && this->collideOnTop) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(diagToTopLeftMov && (this->collideOnLeft || this->collideOnTop || this->collideOnTopLeft)) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(diagToTopRightMov && (this->collideOnRight || this->collideOnTop || this->collideOnTopRight)) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(diagToBottomLeftMov && (this->collideOnLeft || this->collideOnBottom || this->collideOnBottomLeft)) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}
		if(diagToBottomRightMov && (this->collideOnRight || this->collideOnBottom || this->collideOnBottomRight)) {
			this->x = traj[j].x;
			this->y = traj[j].y;
			return;
		}

	}

	this->x = traj[traj.size()-1].x;
	this->y = traj[traj.size()-1].y;

}



Entity::~Entity(void)
{
}
