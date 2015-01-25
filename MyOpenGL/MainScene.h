#pragma once

#include <YuEngine\OpenGlScene.h>
class Container;
class MainScene: public YuEngine::OpenGlScene
{
public:
	MainScene();
	virtual ~MainScene(void);
	void loop();
	void pixelsToBmp(GLubyte *pixels);
	void resetPixels(GLubyte *pixels);


protected:
	Container* container;
};

