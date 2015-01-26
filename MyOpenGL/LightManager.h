#pragma once

#include "PixelsMap.h"
#include <string>
#include "Object.h"
#include <YuEngine\Vertex.h>
#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\EventTimer.h>
#include "Block.h"

class LightSun;
class LightRadius;


class LightManager: public Object
{
public:
	LightManager(int _screenWidth, int _screenHeight);
	~LightManager(void);

	void resetScreenPixels();
	void pixelsToBmp();
	void refreshScreenPixels();
	void update();
	void render();



	void setLightSun(LightSun* l) {
		lightSun = l;
	}
	void addLightRadius(LightRadius* s) {
		lightsRadius.push_back(s);
	}
	GLuint getTexture() {
		return texture;
	}

private:
	GLubyte *screenPixels;
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
};

