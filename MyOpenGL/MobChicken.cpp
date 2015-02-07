#include "MobChicken.h"
#include "Block.h"
#include <iostream>
#include <YuEngine\Container.h>
#include "Container.h"
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <random>
#include <YuEngine\Utils.h>

MobChicken::MobChicken(void) : EntityMob(){

	width = Block::size*2;
	height = Block::size*2;

	x = Block::size * 50;
	y = Block::size * 80;

	speedX = 2;
	knockbackX = 5;
	knockbackY = 10;
	jumpVel = 10;

	YuEngine::YuBoudingbox _boudingBox(x, y, width, height);
	_boudingBox.setContainer(container);
	boundingBox = _boudingBox;

	legsAnimationTimer = YuEngine::EventTimer(0);
	walkSpeed = 7;

	health = 15 + (YuEngine::Utils::getRandom() * 10);
	maxHealth = health;

}

void MobChicken::update() {

	EntityMob::update();
}

void MobChicken::render() {

	//
	//myContainer->getGameRenderer()->addGlyph(x, y, width, height, 14.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);
	//myContainer->getGameRenderer()->addGlyph(boundingBox.getX1(), boundingBox.getY1(),boundingBox.getWidth(), boundingBox.getHeight(), 15.5f, 1.0f, 1.0f, 1.0f, 1.0f,myContainer->getSpritesheetsManager()->getBlocksSpritesheet(), 3,0);
	moving = true;
	legsAnimationTimer.update();
	if(goingRight) {

		if(moving) {
			if(legsAnimationTimer.isUnder(0, walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 2,0,4,2);

			} else if(legsAnimationTimer.isUnder(walkSpeed, 2*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,0,2,2);

			} else if(legsAnimationTimer.isUnder(2*walkSpeed, 3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 4,0,6,2);

			} else if(legsAnimationTimer.isOver(3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,0,2,2);
				if(legsAnimationTimer.isOver(4*walkSpeed)) {
					legsAnimationTimer.reset();
				}
			}
		} else {
			myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,0,2,2);

		}

	} else if(goingLeft) {
		if(moving) {
			if(legsAnimationTimer.isUnder(0, walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 4,2,6,4);

			} else if(legsAnimationTimer.isUnder(walkSpeed, 2*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,2,2,4);

			} else if(legsAnimationTimer.isUnder(2*walkSpeed, 3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 2,2,4,4);

			} else if(legsAnimationTimer.isOver(3*walkSpeed)) {
				myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,2,2,4);
				if(legsAnimationTimer.isOver(4*walkSpeed)) {
					legsAnimationTimer.reset();
				}
			}
		} else {
			myContainer->getGameRenderer()->addGlyph(x, y, width, height, 16.0f, 1.0f, 1.0f, 1.0f, 1.0f, myContainer->getSpritesheetsManager()->getMobsSpritesheet(), 0,2,2,4);

		}
	}

}

MobChicken::~MobChicken(void){
}
