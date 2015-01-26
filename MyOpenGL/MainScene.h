#pragma once

#include <YuEngine\OpenGlScene.h>
class Container;
class MainScene: public YuEngine::OpenGlScene
{
public:
	MainScene();
	virtual ~MainScene(void);
	void loop();
	void pixelsToBmp(GLuint textureId);
	void resetPixels(GLubyte *pixels);


protected:
	Container* container;
};

