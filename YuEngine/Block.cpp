#include "Block.h"
#include "SpriteRect.h"
#include "Spritesheet.h"
#include "Container.h"
#include "SpritesheetsManager.h"


Block::Block(float x, float y){
	this->time = 0.0f;
	this->x = x;
	this->y = y;
	this->size = 200.0f;
	this->sSprite = nullptr;
}

Block::~Block(void){
	if(this->sSprite) {
		delete this->sSprite;
	}
}


void Block::init() {

	this->sSprite = new SpriteRect(x, y, size, size, 1.0f, 1.0f, 1.0f, 1.0f, this->cContainer->getSpritesheetsManager()->getFontSpritesheet(), 0, 0);
	this->sSprite->setContainer(this->cContainer);
	this->sSprite->load();
}

void Block::update() {
	this->time += 0.5f;
	this->x += 0.5f;

	this->sSprite->update(this->x, this->y);

}

void Block::render() {

	this->sSprite->render();

}