#include "Block.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Container.h>

#include <iostream>
#include "Container.h"

float Block::size = 32;


void Block::render(bool obstacles) {

	if(obstacles) {
		myContainer->getGameRenderer()->addGlyph(x,y+Block::size,Block::size, Block::size, 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 0, 1);

	} else {
		myContainer->getGameRenderer()->addGlyph(x,y+Block::size,Block::size, Block::size, 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), textX, textY);
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

}