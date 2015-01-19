#pragma once

#include <gl\glew.h>
#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
#include <string>


namespace YuEngine {

class YuWindow;
class Container;
class GameRenderer;
class Shader;
class SpritesheetsManager;
class DebugOverlay;

class OpenGlScene
{
public:
	OpenGlScene(void) {};
	OpenGlScene(int _width, int _height, std::string title);
	virtual ~OpenGlScene(void) {
		delete yuWindow;
		//delete container;
	}
	//void looop();
	void beginIteration();
	void endIteration();
	void clear();
	void init(Container* container);
protected:
	int width;
	int height;

	int startTime;
	int elapsedTime;
	int endTime;
	unsigned int frameRate;

	GameRenderer* gameRenderer;
	Shader* classicShader;
	SpritesheetsManager* spritesheetsManager;
	DebugOverlay* debugOverlay;

	YuWindow* yuWindow;
	//Container* container;
};


}