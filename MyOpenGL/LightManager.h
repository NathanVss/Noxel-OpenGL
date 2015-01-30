#pragma once

#include "PixelsMap.h"
#include <string>
#include "Object.h"
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\EventTimer.h>
#include <YuEngine\FrameBuffer.h>
#include <YuEngine\Spritesheet.h>


#include "Block.h"

class LightSun;
class LightRadius;


class LightManager: public Object
{
public:
	LightManager(int _screenWidth, int _screenHeight);
	~LightManager(void);

	void refreshScreenPixels();
	void update();

	void pixelsToBmp(GLuint texture, std::string, int, int);
	void renderLighting();



	void setLightSun(LightSun* l) {
		lightSun = l;
	}
	void addLightRadius(LightRadius* s) {
		lightsRadius.push_back(s);
	}
	GLuint getTexture() {
		return texture;
	}
	YuEngine::FrameBuffer* getFrameBufferHorizBlur() {
		return frameBufferHorizBlur;
	}
	YuEngine::FrameBuffer* getFrameBufferVertBlur() {
		return frameBufferVertBlur;
	}
	YuEngine::FrameBuffer* getFrameBufferLightsRadius(int index) {
		if(index == 1) {
			return frameBufferLightsRadius1;

		} else if (index == 2) {
			return frameBufferLightsRadius2;

		}
	}
	YuEngine::FrameBuffer* getLastFrameBufferLightsRadius() {
		return lastFrameBufferLightsRadius;
	}

private:
	int screenWidth;
	int screenHeight;

	int textureWidth;
	int textureHeight;
	YuEngine::EventTimer eTimer;
	YuEngine::YuBoudingbox cameraBox;
	YuEngine::YuBoudingbox textureBox;
	float sunBias;
	float offset;

	GLuint texture;
	
	LightSun* lightSun;

	std::vector<LightSun*> lightsSun;
	std::vector<LightRadius*> lightsRadius;

	YuEngine::FrameBuffer* frameBufferHorizBlur;
	YuEngine::FrameBuffer* frameBufferVertBlur;
	YuEngine::FrameBuffer* frameBufferObstacle;
	YuEngine::FrameBuffer* frameBufferLightsRadius1;
	YuEngine::FrameBuffer* frameBufferLightsRadius2;
	YuEngine::FrameBuffer* lastFrameBufferLightsRadius;

	YuEngine::Spritesheet lightSpritesheet;
};

