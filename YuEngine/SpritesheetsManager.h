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
	
private:
	Spritesheet* FontSpritesheet;
	Spritesheet* blocksSpritesheet;
	Spritesheet* miscSpritesheet;
	Spritesheet* mobsSpritesheet;
};

}