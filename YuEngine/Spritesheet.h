#pragma once
#include <gl\glew.h>
#include <string>

namespace YuEngine {
class Texture;
class TexturingRectangle;

class Spritesheet
{
public:
	Spritesheet(std::string textureFile, int size);
	~Spritesheet(void);

	void setCurSprite(int x, int y);
	void bind();
	void unbind();
	GLuint getTextureId();
	TexturingRectangle getCoords();

	int getCurX() {
		return this->curX;
	}
	int getCurY() {
		return this->curY;
	}

private:
	Texture* tTexture;
	int size;
	int curX;
	int curY;
};

}