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
	
private:
	Spritesheet* FontSpritesheet;
	Spritesheet* blocksSpritesheet;
};

}