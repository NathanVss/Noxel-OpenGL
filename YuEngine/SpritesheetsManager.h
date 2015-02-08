#pragma once
namespace YuEngine {


class Spritesheet;


class SpritesheetsManager
{
public:
	SpritesheetsManager();
	~SpritesheetsManager(void);
	Spritesheet* getFontSpritesheet() {
		return this->FontSpritesheet;
	}
	Spritesheet* getBlocksSpritesheet() {
		return blocksSpritesheet;
	}
	Spritesheet* getMiscSpritesheet() {
		return miscSpritesheet;
	}
	Spritesheet* getMobsSpritesheet() {
		return mobsSpritesheet;
	}
	Spritesheet* getGuiSpritesheet() {
		return guiSpritesheet;
	}
	Spritesheet* getItemsSpritesheet() {
		return itemsSpritesheet;
	}
private:
	Spritesheet* FontSpritesheet;
	Spritesheet* blocksSpritesheet;
	Spritesheet* miscSpritesheet;
	Spritesheet* mobsSpritesheet;
	Spritesheet* guiSpritesheet;
	Spritesheet* itemsSpritesheet;
};

}