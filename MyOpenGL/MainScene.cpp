#include "MainScene.h"
#include <YuEngine\FpsCounter.h>
#include <YuEngine\Utils.h>
#include <YuEngine\DebugOverlay.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Container.h>
#include <YuEngine\Input.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\ParticlesRenderer.h>
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
#include "Config.h"

#include "GameConsole.h"
#include "Commander.h"
#include "FocusManager.h"

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


	Config config;
	container->setConfig(&config);

	gameRenderer->init();

	std::vector<std::string> locations;
	locations.push_back("vertexPosition");
	locations.push_back("vertexColor");
	locations.push_back("vertexUV");

	YuEngine::Shader *lightingShader = new YuEngine::Shader("Shaders/lighting.vert", "Shaders/lighting.frag");
	lightingShader->charger(locations);
	container->setLightingShader(lightingShader);

	YuEngine::Shader *blurShader = new YuEngine::Shader("Shaders/blur2D.vert", "Shaders/blur2D.frag");
	blurShader->charger(locations);
	container->setBlurShader(blurShader);

	YuEngine::Shader *lightRadiusShader = new YuEngine::Shader("Shaders/classic2D.vert", "Shaders/lightRadius.frag");
	lightRadiusShader->charger(locations);
	container->setLightRadiusShader(lightRadiusShader);

	std::vector<std::string> particlesLocations;
	particlesLocations.push_back("particlePos");
	particlesLocations.push_back("particleSize");
	YuEngine::Shader *particlesShader = new YuEngine::Shader("Shaders/particles.vert", "Shaders/particles.frag");
	particlesShader->charger(particlesLocations);
	container->setParticlesShader(particlesShader);


	particlesShader->use();
	container->getParticlesRenderer()->init();
	particlesShader->unuse();



	World* world = new World();
	world->setMyContainer(container);
	container->setWorld(world);

	LightManager lightManager(width, height);
	lightManager.setMyContainer(container);

	Player player;
	player.setMyContainer(container);
	player.teleport(Block::size * -20, Block::size * 80);
	container->setPlayer(&player);

	world->init();
	world->generate();

	LightRadius lightplayer(2000, 0.4);
	lightManager.addLightRadius(&lightplayer);

	LightSun lightSun;
	lightManager.setLightSun(&lightSun);

	container->getCamera()->setPosition(glm::vec2(0,80*Block::size)); 

	YuEngine::EventTimer eTimer(10);

	FocusManager focusManager;
	focusManager.setPlayerFocus();
	container->setFocusManager(&focusManager);

	Commander commander;
	commander.setMyContainer(container);
	container->setCommander(&commander);

	GameConsole gameConsole;
	gameConsole.setMyContainer(container);
	container->setGameConsole(&gameConsole);
	gameConsole.newEntry("YuEngine InfDev");

	std::vector<YuEngine::Vertex> verts;
	std::vector<YuEngine::Vertex> copyverts;
	std::vector<YuEngine::Vertex> alverts;

		for(int i = 0; i < 100000;i++) {
			YuEngine::Vertex vert;
			
			verts.push_back(vert);

		}

	while(!mustFinish) {
		beginIteration();

		//lightSun.setSeconds(lightSun.getSeconds() +150);
		lightSun.setSeconds(3600*14);

		//lightplayer.setPosition(1280/2, 720/2);
		//lightplayer.setPosition(player.getX(), player.getY());

		container->getInput()->update();
		debugOverlay->update();
		fpsCounter.update();
		world->update();

		//alverts.clear();
		//for(int i = 0; i < verts.size(); i++) {

		//	int a = 1;
		//	int b = 4;
		//	if(b > a) {
		//		float b = 5;
		//	}

		//	alverts.push_back(verts[i]);

		//}
		//copyverts.clear();
		//copyverts = alverts;

		//std::cout << "size : " << alverts.size() << std::endl;

		eTimer.update();
		if(eTimer.isOver()) {
			if(container->getInput()->getRightClick()) {
				glm::vec2 cameraPos = container->getCamera()->getPosition();

				cameraPos.x = cameraPos.x - width/2;
				cameraPos.y = cameraPos.y + height/2;
				std::cout << "CLICK" << std::endl;
				std::cout <<  cameraPos.x+container->getInput()->getMouseX() << ";" << cameraPos.y - container->getInput()->getMouseY() << std::endl;
				LightRadius* lightRadius = new LightRadius(200, 0.01);
				lightRadius->setPosition(cameraPos.x+container->getInput()->getMouseX(), cameraPos.y - container->getInput()->getMouseY());
				lightManager.addLightRadius(lightRadius);
			}
			//pixelsToBmp(frameBuffer.getColorBufferId(0));

			eTimer.reset();
		}
		player.update();
		container->getCamera()->setPosition(glm::vec2(player.getX(), player.getY()));
		container->getCamera()->update();
		gameConsole.update();


		container->getParticlesRenderer()->update();
		
		glm::vec2 cameraPos = container->getCamera()->getPosition();
		YuEngine::YuBoudingbox cameraBox = container->getCamera()->getCameraBox();

		lightplayer.setPosition(container->getInput()->getMouseX() + cameraBox.getX1(),cameraBox.getY1() - container->getInput()->getMouseY());
		if(container->getInput()->getKeySpace()) {
			lightplayer.setRadius(lightplayer.getRadius() + 30);
		}

		if(config.getLighting()) {
			lightManager.update();
			lightManager.renderLighting();
		}
		glViewport(0, 0, width, height);

		// RENDU DU MONDE
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//clear();


		gameRenderer->begin();

			world->render(false);
			player.render();



			container->getClassicShader()->use();
			container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
			gameRenderer->end();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			gameRenderer->render(container->getClassicShader()->getProgramID());
			container->getClassicShader()->unuse();

		particlesShader->use();
		particlesShader->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		container->getParticlesRenderer()->render();
		particlesShader->unuse();


		 //LIGHT

		if(config.getLighting()) {

			gameRenderer->begin();

			YuEngine::Spritesheet spritesheet(lightManager.getLastFrameBufferLightsRadius()->getColorBufferId(0), 1);
			//YuEngine::Spritesheet spritesheet(lightManager.getFrameBufferVertBlur()->getColorBufferId(0), 1);
			gameRenderer->addGlyph(cameraBox.getX1(),cameraBox.getY1(), width, height, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, &spritesheet, 0,0,1,1);
			container->getClassicShader()->use();
			container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
		
			gameRenderer->end();
			// Blending multiplicatif
			// Ce qui est devant est égal au fond multiplé par la lumiere normalisée
			glBlendFunc(GL_DST_COLOR, GL_SRC1_COLOR);
			gameRenderer->render(container->getClassicShader()->getProgramID());
			container->getClassicShader()->unuse();
		}





		// RENDU SANS LUMIERE
		gameRenderer->begin();

			debugOverlay->addDebugString(std::string("Memory Usage : ") + YuEngine::Utils::getMemoryUsage() + std::string("Mo"));
			debugOverlay->addDebugString(std::string("FPS : ") + fpsCounter.getLastFps());
			debugOverlay->addDebugString(std::string("Sprites : ") + gameRenderer->getGlyphsNumber());
			debugOverlay->addDebugString(std::string("Total Sprites : ") + gameRenderer->getTotalGlyphsNumber());
			debugOverlay->addDebugString(std::string("Total Particles : ") + container->getParticlesRenderer()->getParticlesNbr());

			gameRenderer->resetTotalGlyphsNumber();
			debugOverlay->render();

			gameConsole.render();


			container->getClassicShader()->use();
			container->getClassicShader()->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());
			gameRenderer->end();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			gameRenderer->render(container->getClassicShader()->getProgramID());
		container->getClassicShader()->unuse();

		//


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