#pragma once

#include <YuEngine\OpenGlScene.h>
class Container;
class MainScene: public YuEngine::OpenGlScene
{
public:
	MainScene();
	~MainScene(void);
	void loop();


protected:
	Container* container;
};

