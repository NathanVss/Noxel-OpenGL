#include "Player.h"
#include "EntityManager.h"
#include "Block.h"
#include "Container.h"
#include "BlockAir.h"
#include "World.h"
#include "FocusManager.h"
#include "QuickInventory.h"
#include "ItemWoodPickaxe.h"
#include "ItemGrassBlock.h"
#include "RendererPlayer.h"
#include "HealthBuffer.h"
#include "GuiPlayerHealth.h"
#include "GuiManager.h"
#include "BlockTorch.h"
#include "ItemBlock.h"

#include <YuEngine\Container.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Input.h>


#include "PlayerOverlay.h"
#include <math.h>


Player::Player(): EntityLiving(){


}

Player::Player(Container* c) : EntityLiving() {
	myContainer = c;
	rendererPlayer = new RendererPlayer(myContainer, this);
	quickInventory = new QuickInventory(myContainer);
	healthBuffer = new HealthBuffer(20,20);

	guiHealth = new GuiPlayerHealth(myContainer);
	guiHealth->setHealthBuffer(healthBuffer);
	myContainer->getGuiManager()->handleGui(guiHealth, true);
	myContainer->getPlayerOverlay()->setGuiPlayerHealth(guiHealth);

	pixelSize = rendererPlayer->getPixelSize();
	switchMode = 1;
	textureOffsetX = 0;
	textureOffsetY = 4;
	width = pixelSize * 2 * 8;
	height = pixelSize * 4 * 8;
	jumpHeight = 10;
	speedX = 15;
	isDigging = false;
	ticks = 0;
	fallingTicks = 0;
	fallingHeight = 0;
	affectedByFallingDamages = true;
	fallingDamagesMutliplicator = 0.5f;

	movingState = MovingStates::WALK;

	BlockTorch* btorch = new BlockTorch();
	ItemBlock* iblock = new ItemBlock(myContainer, btorch);
	quickInventory->addItem(iblock);

	// Bounding Box
	updateOffsets();
	boundingBox = YuEngine::YuBoudingbox(0, 0, width-pixelSize*9, height-pixelSize*4);
	placeBoundingBox();

	leftClickEvent = YuEngine::KeyEvent(YuEngine::KeyName::mouseLeft, myContainer->getInput());
	rightClickEvent = YuEngine::KeyEvent(YuEngine::KeyName::mouseRight, myContainer->getInput());
	switchEvent = YuEngine::KeyEvent(YuEngine::KeyName::w, myContainer->getInput());
}

Player::~Player(void)
{
}

void Player::teleport(float _x, float _y) {
	x = _x;
	y = _y;
	placeBoundingBox();
}

/* Refresh offsets of boundingbox relative to texture */
void Player::updateOffsets() {
	
	if(goingLeft) {
		bboxOffsetX = 3;
		bboxOffsetY = 4;
	} else if(goingRight) {
		bboxOffsetX = 2;
		bboxOffsetY = 4;
	}
}

void Player::placeBoundingBox() {
		boundingBox.changePos(x + bboxOffsetX*pixelSize,y - bboxOffsetY*pixelSize);
}
void Player::transposeBBoxPosToPlayer(glm::vec2 boundingBoxPos) {
	x = boundingBoxPos.x - bboxOffsetX*pixelSize;
	y = boundingBoxPos.y + bboxOffsetY*pixelSize;
}

void Player::giveItem(Item* item) {

	quickInventory->addItem(item);
}


void Player::render() {
	rendererPlayer->render();
	quickInventory->render();
}

void Player::update() {

	EntityLiving::update();

	ticks++;

	//if(ticks % 5 == 0) {

		//if(healthBuffer->getHealth() == 0) {
		//	healthBuffer->setHealth(21);
		//}
		//	
		//healthBuffer->hit(1);

	//}




	if(movingState == MovingStates::FLY) {
		handleFlyMoving();
	} else {
		handleMoving();
		handleFalling();
	}

	handleDigging();
	
	updateOffsets();


	switchEvent.update();
	if(switchEvent.getEvent()) {
		if(switchMode == 0) {
			switchMode = 1;
		} else if(switchMode == 1) {
			switchMode = 0;
		}

		ItemWoodPickaxe* woodPickaxe = new ItemWoodPickaxe(myContainer);
		quickInventory->addItem(woodPickaxe);
	}

	heldItem = quickInventory->getSelectedItem();

	quickInventory->update();
	handleAction();

}


void Player::handleFalling() {

	if(!lastCollideOnBottom && !lastCollideOnBottomLeft && !lastCollideOnBottomRight) {

		if(velocityY < 0) {
			fallingTicks++;

			fallingHeight += ( lastY - y ) ;
		}
	} else {
		fallingTicks = 0;
		fallingHeight = 0;
	}

	float damageLimit = 2;

	// Obligé de verifier qu'il collide avec le sol sinon le dégat sont appliqués plusieurs fois
	if(fallingHeight > Block::size * damageLimit && movingState == MovingStates::WALK && (collideOnBottom || collideOnBottomLeft || collideOnBottomRight) && affectedByFallingDamages) {
		float damage = (fallingHeight-damageLimit*Block::size) / Block::size;
		damage *= fallingDamagesMutliplicator;
		std::cout << "TICKS : " << fallingTicks << ", DAMAGE : " << damage << std::endl;
		healthBuffer->hit(damage);
	}
}

void Player::handleAction() {
	rightClickEvent.update();
	if(rightClickEvent.getEvent()) {

		if(heldItem) {

			ItemStack* selectedItemStack = quickInventory->getSelectedItemStack();
			heldItem->onUse(selectedItemStack);
		}
	}

}

void Player::handleFlyMoving() {
	affectedByGravity = false;
	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;
	velocityY = 0;
	if(myContainer->getFocusManager()->getPlayerFocus()) {

		if(input->getKeyZ()) {
			velocityY = speedX;
		}
		if(input->getKeyS()) {
			velocityY = -speedX;
		}
		if(input->getKeyQ()) {
			velocityX = -speedX;
		}
		if(input->getKeyD()) {
			velocityX = speedX;
		}
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;


	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	boundingBox.changePos(endLocation.x, endLocation.y);
	transposeBBoxPosToPlayer(endLocation);
}

void Player::handleMoving() {
	affectedByGravity = true;

	YuEngine::Input* input = myContainer->getInput();

	velocityX = 0;
	if(myContainer->getFocusManager()->getPlayerFocus()) {

		if(input->getKeyS()) {
			velocityY = -speedX;
		}
		if(input->getKeySpace() && !jumping) {

			jumping = true;
			velocityY = jumpHeight;
		}
		if(input->getKeyQ()) {
			velocityX = -speedX;
		}
		if(input->getKeyD()) {
			velocityX = speedX;
		}

	}


	if(jumping && collideOnBottom) {
		jumping = false;
	}

	float destX = boundingBox.getX1() + velocityX;
	float destY = boundingBox.getY1() + velocityY;

	// On simule le déplacement de la BBox
	glm::vec2 endLocation = checkCollisions(boundingBox.getX1(), boundingBox.getY1(), destX, destY);
	// On la mets à l'endroit final
	boundingBox.changePos(endLocation.x, endLocation.y);
	// On place le joueur en fonction de placement final de la BBox
	transposeBBoxPosToPlayer(endLocation);

}

void Player::handleDigging() {

	leftClickEvent.update();
	if(leftClickEvent.getEvent()) {
		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());

		myContainer->getEntityManager()->hit(mousePos.x, mousePos.y);
	}
	if(myContainer->getInput()->getLeftClick()) {
		YuEngine::Position mousePos = myContainer->getCamera()->getMouseAbsPos(myContainer->getInput()->getMouseX(), myContainer->getInput()->getMouseY());
		glm::vec2 mouseWorld;
		mouseWorld.x = floor(mousePos.x / Block::size) * 32;
		mouseWorld.y = floor(mousePos.y / Block::size) * 32;
		Block* curBlock = myContainer->getWorld()->getBlock(mouseWorld.x, mouseWorld.y, Block::landZ);

		if(switchMode == 0) {
			curBlock->setWaterQuantity(100);

		} else if(switchMode == 1) {

			if(curBlock->getId() != Block::AirId) {

				curBlock->addDestructStateAmount(10);
				if(curBlock->getDestructState() > 5) {

					curBlock->onDestroy();

					BlockAir* blockAir = new BlockAir(mouseWorld.x, mouseWorld.y, Block::landZ);
					myContainer->getWorld()->setBlock(blockAir);

				}


				isDigging = true;
			}
		}

	} else {
		isDigging = false;
	}

}


