#include "Block.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Container.h>

#include <iostream>
float Block::size = 32;


void Block::render() {

	container->getGameRenderer()->addGlyph(x,y,Block::size, Block::size, 15.0f, 1.0f*(lightIndice.r/255.0f),1.0f*(lightIndice.g/255.0f),1.0f*(lightIndice.b/255.0f),1.0f,container->getSpritesheetsManager()->getBlocksSpritesheet(), textX, textY);
	
	if(!hasBoundingbox) {
		return;
	}
	//container->getGameRenderer()->addGlyph(boundingBox.getX1(), boundingBox.getY1(), Block::size, Block::size, 18.0f, 1.0f, 1.0f, 1.0f, 1.0f, container->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);

}
void Block::update() {

}