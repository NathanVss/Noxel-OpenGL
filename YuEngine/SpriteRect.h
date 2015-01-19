#pragma once

#include <gl\glew.h>
#include "Object.h"
#include <string>
#include "Vertex.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

namespace YuEngine {

class Texture;
class Shader;
class Spritesheet;

class SpriteRect : public Object
{
public:
	SpriteRect(float x, float y, float width, float height, float r, float g, float b, float a, Spritesheet* sSpritesheet, int spriteX, int spriteY);
	SpriteRect(float x, float y, float width, float height, float r, float g, float b, float a);
	void init(float x, float y, float width, float height, float r, float g, float b, float a);
	~SpriteRect(void);
	void load();
	void setVerticesFromCoords();
	void updateVbo(void *datas, int sizeBytes, int offset);

	void update(float x, float y);
	void update();
	void render();

private:
	float x;
	float y;
	float width;
	float height;
	float spriteX;
	float spriteY;

	Spritesheet* sSpritesheet;
	Color* cColor;

	GLuint vboId;
	GLuint vaoId;

	float vertices[12];
	float colors[24];
	float textureCoords[12];
	int colorsSizeBytes;
	int textureCoordsSizeBytes;
	int verticesSizeBytes;
};

}