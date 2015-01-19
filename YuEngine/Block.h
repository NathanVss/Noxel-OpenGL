#pragma once
#include <gl\glew.h>
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "SpriteRect.h"
#include "Object.h"
#include "Renderable.h"

class Block : public Object, public Renderable
{
public:
	Block(float x, float y);
	~Block(void);
	void init();
	void render();
	void updateVBO(void *datas, int sizeBytes, int offset);
	void update();

private:
	float time;
	float x;
	float y;
	float size;
	SpriteRect* sSprite;
};

