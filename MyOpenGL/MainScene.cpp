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
#include "Player.h"
#include <YuEngine\DDAHelper.h>
#include <YuEngine\Vertex.h>
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
	world->setContainer(container);
	container->setWorld(world);

	LightManager lightManager;
	lightManager.setMyContainer(container);

	Player player;
	player.setMyContainer(container);
	player.teleport(Block::size * 2, Block::size * 80);

	world->init();
	world->generate();
	int cx = 0;
	int cy = 0;

	//Block* b = world->getBlock(Block::size * 3, Block::size * 64);

	LightSun lightSun;

	BlockGrass* bg = new BlockGrass(Block::size* 1, Block::size*5*16-1);
	world->setBlock(bg);

	lightManager.addLightSun(&lightSun);
	container->getCamera()->setPosition(glm::vec2(0,80*Block::size)); 
	while(!mustFinish) {
		beginIteration();

		//lightSun.setSeconds(lightSun.getSeconds() + 100);
		lightSun.setSeconds(3600*2);
		//std::cout << "Il est : " << lightSun.getSeconds() / 3600 << "h" << std::endl;

		cx++;
		cy++;

		container->getInput()->update();
		debugOverlay->update();
		fpsCounter.update();
		world->update();

		lightManager.update();


		player.update();

		//std::cout << "player : [" <<  player.getX() << ";" << player.getY() << std::endl;
		container->getCamera()->setPosition(glm::vec2(player.getX(), player.getY()));
		container->getCamera()->update();

		if(container->getInput()->getKeySpace()) {
			player.teleport(Block::size * 3, Block::size * 84);
		}

		gameRenderer->begin();

		//PixelsMap px(1280, 720);
	
		int size = 0;
		for(int i = 0; i < size; i++) {
			for(int y = 0; y < size; y++) {

				BlockGrass blockGrass(i*Block::size,y*Block::size);
				blockGrass.setContainer(container);
				blockGrass.render();
				//int index = container->getGameRenderer()->addGlyph(100+i*11, 100+y*11, 10,10, 1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
			}
		}
		container->getGameRenderer()->addGlyph(0, 0, 10,10, 2.0f ,1.0f,  1.0f, 1.0f, 1.0f, spritesheetsManager->getFontSpritesheet(), 0,1);
		world->render();
		player.render();

		debugOverlay->addDebugString(std::string("Memory Usage : ") + YuEngine::Utils::getMemoryUsage() + std::string("Mo"));
		debugOverlay->addDebugString(std::string("FPS : ") + fpsCounter.getLastFps());
		debugOverlay->addDebugString(std::string("Sprites : ") + gameRenderer->getGlyphsNumber());
		
		debugOverlay->render();

		gameRenderer->end();
		clear();
		
		gameRenderer->render();



		endIteration();

	}

	delete world;
}