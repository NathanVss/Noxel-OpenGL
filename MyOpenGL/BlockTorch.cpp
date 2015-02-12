#include "BlockTorch.h"
#include "LightRadius.h"
#include "LightManager.h"
#include "Container.h"
#include "World.h"
#include <YuEngine\ParticlesRenderer.h>
#include <YuEngine\Utils.h>

BlockTorch::BlockTorch(void) : Block() {
	construct();
};
BlockTorch::BlockTorch(float _x, float _y, float _z) : Block(_x,_y, _z) {
	construct();
};
BlockTorch::~BlockTorch(void) {

};

void BlockTorch::onDestroy() {
	Block::onDestroy();

	light->setDestroy(true);
}

void BlockTorch::update() {
	Block::update();

	if(age % 5 == 0) {

		

		Block* attachedlock; 

		if(position == 0) {
			attachedlock = myContainer->getWorld()->getBlock(x, y-Block::size, Block::landZ);
		} else if(position == 1) {
			attachedlock = myContainer->getWorld()->getBlock(x + Block::size, y, Block::landZ);

		} else if(position == 2) {
			attachedlock = myContainer->getWorld()->getBlock(x - Block::size, y, Block::landZ);

		}

		if(attachedlock->getId() == Block::AirId) {
			onDestroy();
			myContainer->getWorld()->deleteBlock(this);
		}
	}
}

void BlockTorch::construct() {
	z = Block::frontZ;
	
	textX1 = 7;
	textY1 = 0;
	textX2 = 8;
	textY2 = 1;

	transparent = true;

	hasBoundingbox = false;

	particlesColors.r = 128.0f / 255;
	particlesColors.g = 64.0f / 255;
	particlesColors.b = 0.0f / 255;
	particlesColors.a = 1.0f;

	maxWaterQuantity = 0;
	waterQuantity = 0;

	id = Block::TorchId;
}

void BlockTorch::onPlacing() {

	light = new LightRadius(200, 0.01);
	light->setPosition(x, y);
	myContainer->getLightManager()->addLightRadius(light);

	if(position == 0) {
		textX1 = 7;
		textY1 = 0;
		textX2 = 8;
		textY2 = 1; 
	} else if(position == 1) {
		textX1 = 9;
		textY1 = 0;
		textX2 = 10;
		textY2 = 1;
	} else if(position == 2) {
		textX1 = 8;
		textY1 = 0;
		textX2 = 9;
		textY2 = 1;
	}

}

bool BlockTorch::canBePlaced(float _x, float _y) {
	Block* bottomBlock = myContainer->getWorld()->getBlock(_x, _y-Block::size, Block::landZ);
	Block* leftBlock = myContainer->getWorld()->getBlock(_x - Block::size, _y, Block::landZ);
	Block* rightBlock = myContainer->getWorld()->getBlock(_x + Block::size, _y, Block::landZ);

	if(bottomBlock->getId() != Block::AirId) {
		position = 0;
		return true;
	}
	if(rightBlock->getId() != Block::AirId) {
		position = 1;
		return true;

	}
	if(leftBlock->getId() != Block::AirId) {
		position = 2;
		return true;

	}

	return false;

}


void BlockTorch::render(bool flag) {
	Block::render(flag);

	if(!flag) {


		if(age%30 == 0) {
			YuEngine::Color partColor;

			float colorRand = YuEngine::Utils::getRandom();

			if(colorRand <= 0.3f) {
				partColor.r = 223 / 255.0f;
				partColor.g = 0 / 255.0f;
				partColor.b = 0 / 255.0f;
				partColor.a = 1.0f;

			} else if(colorRand <= 0.6) {
				partColor.r = 236 / 255.0f;
				partColor.g = 139 / 255.0f;
				partColor.b = 51 / 255.0f;
				partColor.a = 1.0f;
			} else {
				partColor.r = 227 / 255.0f;
				partColor.g = 196 / 255.0f;
				partColor.b = 17 / 255.0f;
				partColor.a = 1.0f;
			}


			float velX = YuEngine::Utils::getRandom();
			float velY = YuEngine::Utils::getRandom();
			float neg = YuEngine::Utils::getRandom();

			float r = YuEngine::Utils::getRandom() * 2 - 1;
			float g = YuEngine::Utils::getRandom() * 2 - 1;
			float b = YuEngine::Utils::getRandom() * 2 - 1;
			r *= 0.1;
			g *= 0.1;
			b *= 0.1;

			partColor.r += r;
			partColor.g += g;
			partColor.b += b;

			if(neg < 0.5) {
				neg = -1;
			} else {
				neg = 1;
			}

			YuEngine::Particle particle(x + Block::size / 2 , y + Block::size, 4, velX*neg, velY, partColor.r, partColor.g, partColor.b,partColor.a);
			particle.age = 0;
			particle.deathAge = 60;
			particle.useColors = true;
			particle.gravity = 0.01f;
			myContainer->getParticlesRenderer()->addParticle(particle);


		}
	}


}