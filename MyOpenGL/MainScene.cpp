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
	
	World* world = new World();
	world->setMyContainer(container);
	container->setWorld(world);

	LightManager lightManager(width, height);
	lightManager.setMyContainer(container);

	Player player;
	player.setMyContainer(container);
	player.teleport(Block::size * 2, Block::size * 80);

	world->init();
	world->generate();
	int cx = 0;
	int cy = 0;

	YuEngine::DDAHelper helper(1504,2414,1514,2402);
	YuEngine::coords crds;
	crds.x = 0;
	crds.y = 0;
	float a = -1.5;
	std::cout << floor(a) << ";" << ceil(a) << std::endl;
	while(true) {

		crds = helper.getNextCoords();
		if(crds.x == 1514 && crds.y == 2402) {
			break;
		}
	}



	BlockGrass* bg = new BlockGrass(Block::size* 1, Block::size*16*4+5*Block::size);
	world->setBlock(bg);

	LightSun lightSun;

	lightManager.addLightSun(&lightSun);


	container->getCamera()->setPosition(glm::vec2(0,80*Block::size)); 

	YuEngine::EventTimer eTimer(60);


	GLuint texId = 0;


	while(!mustFinish) {
		beginIteration();

		//lightSun.setSeconds(lightSun.getSeconds() + 50);
		lightSun.setSeconds(3600*14);

		cx++;
		cy++;

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

			eTimer.reset();
		}


		player.update();

		container->getCamera()->setPosition(glm::vec2(player.getX(), player.getY()));
		container->getCamera()->update();

		lightManager.update();


		gameRenderer->begin();

		int size = 0;
		for(int i = 0; i < size; i++) {
			for(int y = 0; y < size; y++) {

				int index = container->getGameRenderer()->addGlyph(100+i*11, 100+y*11, 10,10, 10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
			}
		}

		world->render();
		player.render();

		debugOverlay->addDebugString(std::string("Memory Usage : ") + YuEngine::Utils::getMemoryUsage() + std::string("Mo"));
		debugOverlay->addDebugString(std::string("FPS : ") + fpsCounter.getLastFps());
		debugOverlay->addDebugString(std::string("Sprites : ") + gameRenderer->getGlyphsNumber());
		
		debugOverlay->render();

		
		glUseProgram(container->getClassicShader()->getProgramID());
		glUniformMatrix4fv(glGetUniformLocation(container->getClassicShader()->getProgramID(), "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(container->getCamera()->getCameraMatrix()));

		lightManager.render();
		gameRenderer->end();
		clear();


		gameRenderer->render();

		glUseProgram(0);


		endIteration();

	}

	delete world;
}
