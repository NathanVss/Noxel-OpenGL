#include "Block.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Container.h>

#include <iostream>
#include "Container.h"
#include "World.h"

#include <YuEngine\ParticlesRenderer.h>

float Block::size = 32;
int Block::AirId = 0;
int Block::GrassId = 1;
int Block::DirtId = 2;
int Block::StoneId = 3;
int Block::SandId = 4;

void Block::onDestroy() {


	if(emitParticlesOnDestroy) {


		for(int _x = 0; _x < 4; _x++) {
			for(int _y = 0; _y < 4; _y++) {

				float velX = (double)rand() / RAND_MAX ;
				float velY = (double)rand() / RAND_MAX ;
				float neg = (double)rand() / RAND_MAX;
				float r = (double)rand() / RAND_MAX * 2 - 1;
				float g = (double)rand() / RAND_MAX * 2 - 1;
				float b = (double)rand() / RAND_MAX * 2 - 1;

				r *= 0.1;
				g *= 0.1;
				b *= 0.1;

				if(neg < 0.5) {
					neg = -1;
				} else {
					neg = 1;
				}

				YuEngine::Particle particle(x + _x * Block::size / 4 , y + _y * Block::size / 4 , 4, velX*neg,velY,particlesColors.r + r, particlesColors.g + g,particlesColors.b + b,particlesColors.a);
				particle.age = 0;
				particle.deathAge = 120*2;
				particle.useColors = true;
				particle.gravity = 0.1f;
				myContainer->getParticlesRenderer()->addParticle(particle);

			}

		}
	}

}

void Block::render(bool obstacles) {

	if(obstacles) {
		myContainer->getGameRenderer()->addGlyph(x,y+Block::size,Block::size, Block::size, 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 0, 1);

	} else {
		myContainer->getGameRenderer()->addGlyph(x,y+Block::size,Block::size, Block::size, 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), textX, textY);
		
		if(maxWaterQuantity > 0 && waterQuantity > 0) {
			float waterLevel = Block::size * (waterQuantity / maxWaterQuantity);
			//myContainer->getGameRenderer()->addGlyph(x,y+Block::size,Block::size, Block::size, 16.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f * (waterQuantity / maxWaterQuantity),myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 6, 0);
			myContainer->getGameRenderer()->addGlyph(x,y+waterLevel,Block::size, waterLevel, 16.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 6, 0);

		}
		//myContainer->getGameRenderer()->addGlyph(boundingBox.getX1(),boundingBox.getY1(),boundingBox.getWidth(), boundingBox.getHeight(), 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),0.4f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), textX, textY);
		
	}

	YuEngine::Color c;
	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;
	lightIndice = c;

	if(!hasBoundingbox) {
		return;
	}
	//container->getGameRenderer()->addGlyph(boundingBox.getX1(), boundingBox.getY1(), Block::size, Block::size, 18.0f, 1.0f, 1.0f, 1.0f, 1.0f, container->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);

}
void Block::update() {

	if(waterQuantity > 0) {
		Block* bottomBlock = myContainer->getWorld()->getBlock(x, y - Block::size);
		if(bottomBlock) {
			float quantityCanTake = bottomBlock->getWaterQuantityCanTake();
			if(quantityCanTake > 0) {
				if(quantityCanTake >= waterQuantity) {

					// DONNER TOUT
					bottomBlock->addWaterQuantity(waterQuantity);
					waterQuantity = 0;
				} else {
					bottomBlock->addWaterQuantity(quantityCanTake);
					waterQuantity -= quantityCanTake;
					// DONNER ASSEZ POUR FULL
				}
			}
		}

		Block* leftBlock = myContainer->getWorld()->getBlock(x - Block::size, y);
		if(leftBlock && leftBlock->getWaterQuantityCanTake() != 0) {
			float hisWaterQuantity = leftBlock->getWaterQuantity();
			if(hisWaterQuantity < waterQuantity) {
				float amoutToGive = (waterQuantity - hisWaterQuantity) / 2;
				leftBlock->addWaterQuantity(amoutToGive);
				waterQuantity -= amoutToGive;
			}
		}


		Block* rightBlock = myContainer->getWorld()->getBlock(x + Block::size, y);
		if(rightBlock  && rightBlock->getWaterQuantityCanTake() != 0) {
			float hisWaterQuantity = rightBlock->getWaterQuantity();
			if(hisWaterQuantity < waterQuantity) {
				float amoutToGive = (waterQuantity - hisWaterQuantity) / 2;
				rightBlock->addWaterQuantity(amoutToGive);
				waterQuantity -= amoutToGive;
			}
		}
	}
}