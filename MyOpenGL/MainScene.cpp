#include "MainScene.h"
#include <YuEngine\FpsCounter.h>
#include <YuEngine\Utils.h>
#include <YuEngine\DebugOverlay.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Container.h>
#include <YuEngine\Input.h>
#include <YuEngine\Camera2D.h>
#include "BlockGrass.h"
#include "BlockAir.h"
#include "Chunk.h"
#include "World.h"
#include "Container.h"
#include "LightManager.h"
#include "PixelsMap.h"
#include "LightSun.h"
#include "LightRadius.h"
#include "Player.h"
#include <YuEngine\DDAHelper.h>
#include <YuEngine\Vertex.h>
#include <Dependecies\EasyBMP\EasyBMP.h>
#include <YuEngine\EventTimer.h>
#include <YuEngine\Shader.h>
#include <YuEngine\Spritesheet.h>
#include <YuEngine\FrameBuffer.h>
//using namespace YuEngine;

MainScene::MainScene() : YuEngine::OpenGlScene(1280,720, "YuEngine Infdev") {
	frameRate = ( 1000 / 60 );
	
	container = new Container;
	init(container);
	loop();
}


MainScene::~MainScene(void)
{
}

void MainScene::loop() {

	bool mustFinish = false;
	glm::mat4 cameraMatrix;

	YuEngine::FpsCounter fpsCounter;

	//Container container;

	gameRenderer->init();

	YuEngine::Shader *lightingShader = new YuEngine::Shader("Shaders/lighting.vert", "Shaders/lighting.frag");
	lightingShader->charger();
	container->setLightingShader(lightingShader);

	YuEngine::Shader *blurShader = new YuEngine::Shader("Shaders/blur2D.vert", "Shaders/blur2D.frag");
	blurShader->charger();
	container->setBlurShader(blurShader);
	
	World* world = new World();
	world->setMyContainer(container);
	container->setWorld(world);

	LightManager lightManager(width, height);
	lightManager.setMyContainer(container);

	Player player;
	player.setMyContainer(container);
	player.teleport(Block::size * 2, Block::size * 75);
	//player.teleport(Block::size * 0, Block::size * 0);

	world->init();
	world->generate();


	LightSun lightSun;
	lightManager.setLightSun(&lightSun);

	container->getCamera()->setPosition(glm::vec2(0,80*Block::size)); 

	YuEngine::EventTimer eTimer(60);


	GLuint texId = 0;

	YuEngine::FrameBuffer frameBuffer(width, height);
	frameBuffer.load();

	YuEngine::FrameBuffer frameBufferBlur(width, height);
	frameBufferBlur.load();

	YuEngine::FrameBuffer frameBufferBlurVert(width, height);
	frameBufferBlurVert.load();
			YuEngine::Spritesheet spritesheetLight("textures/voidblank.png", 1);

	while(!mustFinish) {
		beginIteration();

		//lightSun.setSeconds(lightSun.getSeconds() + 300);
		lightSun.setSeconds(3600*14);


		container->getInput()->update();
		debugOverlay->update();
		fpsCounter.update();
		world->update();


		eTimer.update();
		if(eTimer.isOver()) {
			if(container->getInput()->getLeftClick()) {
				glm::vec2 cameraPos = container->getCamera()->getPosition();

				cameraPos.x = cameraPos.x - width/2;
				cameraPos.y = cameraPos.y + height/2;
				std::cout << "CLICK" << std::endl;
				std::cout <<  cameraPos.x+container->getInput()->getMouseX() << ";" << cameraPos.y - container->getInput()->getMouseY() << std::endl;
				LightRadius* lightRadius = new LightRadius(7*Block::size);
				lightRadius->setPosition(cameraPos.x+container->getInput()->getMouseX(), cameraPos.y - container->getInput()->getMouseY());
				lightManager.addLightRadius(lightRadius);
			}
			pixelsToBmp(frameBuffer.getColorBufferId(0));

			eTimer.reset();
		}
		player.update();
		container->getCamera()->setPosition(glm::vec2(player.getX(), player.getY()));
		container->getCamera()->update();
		YuEngine::YuBoudingbox cameraBox = container->getCamera()->getCameraBox();
		lightManager.update();


		lightManager.renderLighting();

		//frameBuffer.bind();

		//	// RENDU AVEC LUMIERE
		//	
		//	clear();
		//	

		//	gameRenderer->begin();
		//	gameRenderer->addGlyph(cameraBox.getX1(),cameraBox.getY1(), width, height, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, &spritesheetLight, 0,0,1,1);

		//	container->getLightingShader()->use();
		//	container->getLightingShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		//	lightManager.render();

		//	gameRenderer->end();

		//	gameRenderer->render(container->getLightingShader()->getProgramID());
		//	container->getLightingShader()->unuse();

		//frameBuffer.unbind();

#pragma region blur

		// DEUXIEME PASSE
		// BLUR

		//frameBufferBlur.bind();
		//
		//	clear();
		//	gameRenderer->begin();

		//	gameRenderer->addGlyph(cameraBox.getX1(),cameraBox.getY1(), width, height, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, &spritesheetLight, 0,0,1,1);
		//	container->getBlurShader()->use();
		//	container->getBlurShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		//	container->getBlurShader()->sendInt("screenWidth", width);
		//	container->getBlurShader()->sendInt("screenHeight", height);
		//	container->getBlurShader()->sendInt("vertical", 0);
		//
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, frameBuffer.getColorBufferId(0));
		//	container->getBlurShader()->sendInt("screenTexture", 0);
		//
		//
		//	gameRenderer->end();
		//	gameRenderer->render(container->getBlurShader()->getProgramID());
		//
		//	container->getBlurShader()->unuse();

		//frameBufferBlur.unbind();

		//frameBufferBlurVert.bind();

		//	clear();
		//	gameRenderer->begin();

		//	gameRenderer->addGlyph(cameraBox.getX1(),cameraBox.getY1(), width, height, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, &spritesheetLight, 0,0,1,1);
		//	container->getBlurShader()->use();
		//	container->getBlurShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		//	container->getBlurShader()->sendInt("screenWidth", width);
		//	container->getBlurShader()->sendInt("screenHeight", height);
		//	container->getBlurShader()->sendInt("vertical", 1);
		//
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, frameBufferBlur.getColorBufferId(0));
		//	container->getBlurShader()->sendInt("screenTexture", 0);
		//
		//
		//	gameRenderer->end();
		//	gameRenderer->render(container->getBlurShader()->getProgramID());
		//
		//	container->getBlurShader()->unuse();	

		//frameBufferBlurVert.unbind();

#pragma endregion

		// TROISIEME PASSE
		clear();
		gameRenderer->begin();

		world->render();
		player.render();

		container->getClassicShader()->use();
		
		container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		gameRenderer->end();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		gameRenderer->render(container->getClassicShader()->getProgramID());
		container->getClassicShader()->unuse();


		// LIGHT
		gameRenderer->begin();
		YuEngine::Spritesheet spritesheet(lightManager.getFrameBufferHorizBlur()->getColorBufferId(0), 1);
		//YuEngine::Spritesheet spritesheet(frameBufferBlurVert.getColorBufferId(0), 1);
		gameRenderer->addGlyph(cameraBox.getX1(),cameraBox.getY1(), width, height, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, &spritesheet, 0,0,1,1);
		
		container->getClassicShader()->use();
		container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		
		
		gameRenderer->end();
		// Blending multiplicatif
		// Ce qui est devant est égal au fond multiplé par la lumiere normalisée
		glBlendFunc(GL_DST_COLOR, GL_SRC1_COLOR);
		gameRenderer->render(container->getClassicShader()->getProgramID());
		
		container->getClassicShader()->unuse();


		// RENDU SANS LUMIERE
		gameRenderer->begin();

		debugOverlay->addDebugString(std::string("Memory Usage : ") + YuEngine::Utils::getMemoryUsage() + std::string("Mo"));
		debugOverlay->addDebugString(std::string("FPS : ") + fpsCounter.getLastFps());
		debugOverlay->addDebugString(std::string("Sprites : ") + gameRenderer->getGlyphsNumber());
		debugOverlay->render();

		container->getClassicShader()->use();
		container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		
		gameRenderer->end();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		gameRenderer->render(container->getClassicShader()->getProgramID());
		
		container->getClassicShader()->unuse();


		
		

		endIteration();

	}

	delete world;
}


void MainScene::pixelsToBmp(GLuint textureId) {

	GLubyte *pixels =  new GLubyte[1280*720*4];
	glBindTexture(GL_TEXTURE_2D, textureId);

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	BMP* curBMP = new BMP();

	int textureWidth = 1280;
	int textureHeight = 720;

	curBMP->SetSize(textureWidth,textureHeight);
	curBMP->SetBitDepth(32);
	for(int x=0; x < textureWidth; x++) {
		for(int y = 0; y < textureHeight; y++) {
			(*curBMP)(x, y)->Red = pixels[y*textureWidth*4  + x * 4];
			(*curBMP)(x, y)->Green = pixels[y*textureWidth*4  + x * 4 + 1];
			(*curBMP)(x, y)->Blue = pixels[y*textureWidth*4  + x * 4 + 2];
			//(*curBMP)(x, y)->Alpha = pixels[y*textureWidth*4  + x * 4 + 3];
			(*curBMP)(x, y)->Alpha = 0;
		}
	}
	curBMP->WriteToFile("lighting/FBO.bmp");
	delete curBMP;
	delete[] pixels;

}