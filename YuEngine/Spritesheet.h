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
	Spritesheet(int _textureId, int _size);
	~Spritesheet(void);

	void setCurSprite(int x, int y);
	void setCurArea(int x1, int y1, int x2, int y2);
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
	int textureId;

	bool areaMode;

	int curAreaX1;
	int curAreaY1;
	int curAreaX2;
	int curAreaY2;
};

}