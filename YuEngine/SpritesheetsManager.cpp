#include "SpritesheetsManager.h"
#include "Spritesheet.h"
namespace YuEngine {

SpritesheetsManager::SpritesheetsManager(){

	FontSpritesheet = new Spritesheet("textures/font.png", 16);
	blocksSpritesheet = new Spritesheet("textures/blocks.png", 16);
	miscSpritesheet = new Spritesheet("textures/misc.png", 16);
	mobsSpritesheet = new Spritesheet("textures/mobs.png", 32);
	guiSpritesheet = new Spritesheet("textures/gui.png", 32);
	itemsSpritesheet = new Spritesheet("textures/items.png", 32);

}


SpritesheetsManager::~SpritesheetsManager(void){
	delete this->FontSpritesheet;
}
}
