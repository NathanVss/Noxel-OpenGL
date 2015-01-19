#include "OpenGlScene.h"

#include <iostream>
#include "Shader.h"
#include "Camera2D.h"
#include "Input.h"
#include "Container.h"
#include "Texture.h"
#include "SpritesheetsManager.h"
#include "FontRenderer.h"
#include "DebugOverlay.h"
#include "FpsCounter.h"
#include "Utils.h"
#include "GameRenderer.h"
#include <random>
#include <time.h>
#include "YuWindow.h"


namespace YuEngine {


OpenGlScene::OpenGlScene(int _width, int _height, std::string title) {
	width = _width;
	height = _height;
	yuWindow = new YuWindow(width,height,title);
	yuWindow->initWindow();
	yuWindow->initOpenGl();

	frameRate = ( 1000 / 60 );
	//init();
	//this->loop();
}
void OpenGlScene::beginIteration() {

	startTime = SDL_GetTicks();
}
void OpenGlScene::endIteration() {
	yuWindow->swap();
	endTime = SDL_GetTicks();
	elapsedTime = endTime - startTime;

	if(elapsedTime < frameRate) {
		SDL_Delay(frameRate - elapsedTime);
	}
	
}

void OpenGlScene::clear() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(119/255.0f,181/255.0f,254/255.0f,1);
}

void OpenGlScene::init(Container* container) {
	//container = new Container();

	classicShader = new Shader("Shaders/classic2D.vert", "Shaders/classic2D.frag");
	classicShader->charger();
	container->setClassicShader(classicShader);

	gameRenderer = new GameRenderer();
	gameRenderer->setContainer(container);
	container->setGameRenderer(gameRenderer);

	spritesheetsManager = new SpritesheetsManager();
	container->setSpritesheetsManager(spritesheetsManager);

	FontRenderer* fontRenderer = new FontRenderer();
	fontRenderer->setContainer(container);
	container->setFontRenderer(fontRenderer);

	debugOverlay = new DebugOverlay();
	debugOverlay->setContainer(container);


	Input *input = new Input();
	container->setInput(input);
	input->setContainer(container);

	Camera2D* camera = new Camera2D();
	container->setCamera(camera);
	camera->setContainer(container);
	camera->init(this->width, this->height);

}

//void OpenGlScene::looop() {
//	FpsCounter* fpsCounter = new FpsCounter();
//
//	bool mustFinish = false;
//
//	glm::mat4 cameraMatrix;
//
//	gameRenderer->init();
//
//	while(!mustFinish) {
//
//
//		beginIteration();
//		
//
//		container->getCamera()->update();
//		debugOverlay->update();
//		container->getInput()->update();
//		fpsCounter->update();
//
//		int size = 50;
//		int posX = 0;
//		int posY = 0;
//		gameRenderer->begin();
//
//
//		for(int x = posX - size/2; x <= posX + size/2; x++) {
//			container->getGameRenderer()->addGlyph(x*10, posY - size/2*10, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
//			container->getGameRenderer()->addGlyph(x*10, posY + size/2*10, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
//
//		}
//		for(int y = posY - size/2; y <= posY + size/2; y++) {
//			container->getGameRenderer()->addGlyph(posX - size/2*10, y*10, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
//			container->getGameRenderer()->addGlyph(posX + size/2*10, y*10, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
//
//		}
//
//
//		//for(int i = 0; i <= size; i++) {
//
//		//	for(int y = 0; y <= size; y++) {
//
//		//		int index = cContainer->getGameRenderer()->addGlyph(100+i*11, 100+y*11, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, sSpritesheetsManager->getFontSpritesheet(), 0,1);
//		//		//std::cout << index << std::endl;
//		//	}
//
//
//		//}
//
//		debugOverlay->addDebugString(std::string("Memory Usage : ") + Utils::getMemoryUsage() + std::string("Mo"));
//		debugOverlay->addDebugString(std::string("FPS : ") + fpsCounter->getLastFps());
//		debugOverlay->render();
//
//		gameRenderer->end();	
//		clear();
//
//
//		gameRenderer->render();
//
//
//		cameraMatrix = container->getCamera()->getCameraMatrix();
//
//	
//		endIteration();
//	}
//
//}



}