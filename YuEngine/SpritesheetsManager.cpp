#include "SpritesheetsManager.h"
#include "Spritesheet.h"
namespace YuEngine {

SpritesheetsManager::SpritesheetsManager(){

	FontSpritesheet = new Spritesheet("textures/font.png", 16);
	blocksSpritesheet = new Spritesheet("textures/blocks.png", 16);

}


SpritesheetsManager::~SpritesheetsManager(void){
	delete this->FontSpritesheet;
}
}
