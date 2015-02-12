#include "LightManager.h"
#include <Dependecies\EasyBMP\EasyBMP.h>
#include <vector>
#include "Chunk.h"
#include "Container.h"
#include "World.h"
#include "Block.h"
#include "Light.h"
#include "LightSun.h"
#include "LightRadius.h"
#include "Block.h"
#include <YuEngine\Camera2D.h>
#include <YuEngine\Shader.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\Input.h>

LightManager::LightManager(int _screenWidth, int _screenHeight) {
	texture = 0;
	sunBias = 127;
	offset = sunBias;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	textureWidth = screenWidth + offset * 2;
	textureHeight = screenHeight + offset * 2;

	eTimer = YuEngine::EventTimer(60);

	frameBufferHorizBlur = new YuEngine::FrameBuffer(textureWidth, textureHeight);
	frameBufferHorizBlur->load();

	frameBufferObstacle = new YuEngine::FrameBuffer(textureWidth, textureHeight);
	frameBufferObstacle->load();

	frameBufferVertBlur = new YuEngine::FrameBuffer(screenWidth, screenHeight);
	frameBufferVertBlur->load();

	frameBufferLightsRadius1 = new YuEngine::FrameBuffer(screenWidth, screenHeight);
	frameBufferLightsRadius1->load();	
	
	frameBufferLightsRadius2 = new YuEngine::FrameBuffer(screenWidth, screenHeight);
	frameBufferLightsRadius2->load();
	
	lightSpritesheet = YuEngine::Spritesheet("textures/voidblank.png", 1);
}

LightManager::~LightManager(void){

	//lightsRadius.clear();

}






void LightManager::update() {

	std::vector<LightRadius*> temp;
	for(int i = 0; i < lightsRadius.size(); i++) {
		if(lightsRadius[i]->getDestroy()) {
			delete lightsRadius[i];
		} else {
			temp.push_back(lightsRadius[i]);
		}
	}
	lightsRadius = temp;

	glm::vec2 cameraPos = myContainer->getCamera()->getPosition();
	cameraBox = YuEngine::YuBoudingbox(cameraPos.x - screenWidth/2, cameraPos.y + screenHeight/2, screenWidth, screenHeight);
	textureBox = YuEngine::YuBoudingbox(cameraBox.getX1() - offset, cameraBox.getY1() + offset, cameraBox.getWidth() + offset*2, cameraBox.getHeight() + offset*2);
	
	refreshScreenPixels();

}

void LightManager::renderLighting() {


	frameBufferHorizBlur->bind();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, textureWidth, textureHeight);

		myContainer->getGameRenderer()->begin();
		myContainer->getGameRenderer()->addGlyph(cameraBox.getX1() - offset, cameraBox.getY1() + offset, textureWidth, textureHeight, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, &lightSpritesheet, 0,0,1,1);
		myContainer->getGameRenderer()->end();


		myContainer->getBlurShader()->use();
		myContainer->getBlurShader()->sendMatrix4("cameraMatrix", myContainer->getCamera()->getCameraMatrix());
		myContainer->getBlurShader()->sendInt("screenWidth", screenWidth);
		myContainer->getBlurShader()->sendInt("screenHeight", screenHeight);
		myContainer->getBlurShader()->sendInt("screenTextureHeight", textureHeight);
		myContainer->getBlurShader()->sendInt("screenTextureWidth", textureWidth);
		myContainer->getBlurShader()->sendInt("vertical", 0);
		myContainer->getBlurShader()->sendInt("invertY", 0);
		myContainer->getBlurShader()->sendFloat("offset", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frameBufferObstacle->getColorBufferId(0));
		myContainer->getBlurShader()->sendInt("screenTexture", 0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		myContainer->getGameRenderer()->render(myContainer->getBlurShader()->getProgramID());

		myContainer->getBlurShader()->unuse();

	frameBufferHorizBlur->unbind();


	frameBufferVertBlur->bind();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, screenWidth, screenHeight);


		myContainer->getGameRenderer()->begin();
		myContainer->getGameRenderer()->addGlyph(cameraBox.getX1(), cameraBox.getY1(), cameraBox.getWidth(), cameraBox.getHeight(), 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, &lightSpritesheet, 0,0,1,1);
		myContainer->getGameRenderer()->end();


		myContainer->getBlurShader()->use();
		myContainer->getBlurShader()->sendMatrix4("cameraMatrix", myContainer->getCamera()->getCameraMatrix());
		myContainer->getBlurShader()->sendInt("screenWidth", screenWidth);
		myContainer->getBlurShader()->sendInt("screenHeight", screenHeight);
		myContainer->getBlurShader()->sendInt("screenTextureHeight", textureHeight);
		myContainer->getBlurShader()->sendInt("screenTextureWidth", textureWidth);
		myContainer->getBlurShader()->sendInt("vertical", 1);
		myContainer->getBlurShader()->sendFloat("sunIndice", lightSun->getIndice());
		myContainer->getBlurShader()->sendFloat("cameraBoxY", cameraBox.getY1());
		myContainer->getBlurShader()->sendFloat("darkDepthY", Block::size * 40);
		myContainer->getBlurShader()->sendFloat("darkDepthGradient", Block::size * 20);
		myContainer->getBlurShader()->sendInt("invertY",0);
		myContainer->getBlurShader()->sendFloat("offset",offset);





		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frameBufferHorizBlur->getColorBufferId(0));
		myContainer->getBlurShader()->sendInt("screenTexture", 0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		myContainer->getGameRenderer()->render(myContainer->getBlurShader()->getProgramID());

		myContainer->getBlurShader()->unuse();



	frameBufferVertBlur->unbind();

	YuEngine::Texture lastTexture;

	YuEngine::FrameBuffer *lastFrameBuffer = frameBufferVertBlur;
	YuEngine::FrameBuffer *curFrameBuffer = frameBufferLightsRadius1;


	for(int i = 0; i < lightsRadius.size(); i++) {
		
		
		curFrameBuffer->bind();

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, screenWidth, screenHeight);


			myContainer->getGameRenderer()->begin();
			myContainer->getGameRenderer()->addGlyph(cameraBox.getX1(), cameraBox.getY1(), cameraBox.getWidth(), cameraBox.getHeight(), 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, &lightSpritesheet, 0,0,1,1);
			myContainer->getGameRenderer()->end();

			myContainer->getLightRadiusShader()->use();
			myContainer->getLightRadiusShader()->sendMatrix4("cameraMatrix", myContainer->getCamera()->getCameraMatrix());

			myContainer->getLightRadiusShader()->sendFloat("lightX", lightsRadius[i]->getX() - cameraBox.getX1());
			myContainer->getLightRadiusShader()->sendFloat("lightY", cameraBox.getY1() - lightsRadius[i]->getY());
			myContainer->getLightRadiusShader()->sendFloat("lightRadius", lightsRadius[i]->getRadius());
			myContainer->getLightRadiusShader()->sendFloat("lightIntensity", lightsRadius[i]->getIntensity());
			myContainer->getLightRadiusShader()->sendInt("screenTextureWidth", screenWidth);
			myContainer->getLightRadiusShader()->sendInt("screenTextureHeight", screenHeight);


			glActiveTexture(GL_TEXTURE0);
			int lastId = lastFrameBuffer->getColorBufferId(0);

			glBindTexture(GL_TEXTURE_2D, lastId);
			myContainer->getLightRadiusShader()->sendInt("screenTexture", 0);
			myContainer->getGameRenderer()->render(myContainer->getLightRadiusShader()->getProgramID());

			myContainer->getLightRadiusShader()->unuse();



		curFrameBuffer->unbind();

		lastFrameBuffer = curFrameBuffer;
		lastFrameBufferLightsRadius = lastFrameBuffer;
		//pixelsToBmp(curFrameBuffer->getColorBufferId(0), "lighting/radius" + std::to_string(i) + ".bmp", screenWidth, screenHeight);

		if(curFrameBuffer == frameBufferLightsRadius2) {
			curFrameBuffer = frameBufferLightsRadius1;
		} else {
			curFrameBuffer = frameBufferLightsRadius2;

		}
		

	}

	glViewport(0, 0, screenWidth, screenHeight);



		int lightsRadiusNumber = 0;
		for(int i = 0; i < lightsRadius.size(); i++) {
			lightsRadiusNumber++;
			myContainer->getBlurShader()->sendFloat("mousePosX", myContainer->getInput()->getMouseX());
			myContainer->getBlurShader()->sendFloat("mousePosY", myContainer->getInput()->getMouseY());
			myContainer->getBlurShader()->sendFloat("lightsRadius[" + std::to_string(i) + "].position.x",lightsRadius[i]->getX() - cameraBox.getX1());
			myContainer->getBlurShader()->sendFloat("lightsRadius[" + std::to_string(i) + "].position.y",lightsRadius[i]->getY() - cameraBox.getY1());
			myContainer->getBlurShader()->sendFloat("lightsRadius[" + std::to_string(i) + "].radius",lightsRadius[i]->getRadius());

		}
		myContainer->getBlurShader()->sendInt("lightsRadiusNumber",lightsRadiusNumber);


	eTimer.update();
	if(eTimer.isOver()){
		//pixelsToBmp(frameBufferVertBlur->getColorBufferId(0), "lighting/Vert.bmp", screenWidth, screenHeight);
		//pixelsToBmp(frameBufferHorizBlur->getColorBufferId(0), "lighting/Horiz.bmp", textureWidth, textureHeight);
		//pixelsToBmp(frameBufferObstacle->getColorBufferId(0), "lighting/obstacle.bmp", textureWidth, textureHeight);


		eTimer.reset();
	}

}


void LightManager::refreshScreenPixels() {

	frameBufferObstacle->bind();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, textureWidth, textureHeight);

		myContainer->getGameRenderer()->begin();

		myContainer->getWorld()->render(true);

		myContainer->getGameRenderer()->end();


		myContainer->getClassicShader()->use();


		YuEngine::Camera2D camBox;
		camBox.setContainer(myContainer);
		camBox.init(textureWidth, textureHeight);
		glm::vec2 position = myContainer->getCamera()->getPosition();
		camBox.setPosition(position);
		camBox.update();

		myContainer->getClassicShader()->sendMatrix4("cameraMatrix", camBox.getCameraMatrix());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		myContainer->getGameRenderer()->render(myContainer->getClassicShader()->getProgramID());

		myContainer->getClassicShader()->unuse();


	frameBufferObstacle->unbind();

}

void LightManager::pixelsToBmp(GLuint textureId, std::string file, int width, int height) {
	GLubyte *pixels =  new GLubyte[width*height*4];
	glBindTexture(GL_TEXTURE_2D, textureId);

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	BMP* curBMP = new BMP();


	curBMP->SetSize(width,height);
	curBMP->SetBitDepth(32);
	for(int x=0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			(*curBMP)(x, y)->Red = pixels[y*width*4  + x * 4];
			(*curBMP)(x, y)->Green = pixels[y*width*4  + x * 4 + 1];
			(*curBMP)(x, y)->Blue = pixels[y*width*4  + x * 4 + 2];
			(*curBMP)(x, y)->Alpha = 0;
		}
	}
	curBMP->WriteToFile(file.c_str());
	delete curBMP;
	delete[] pixels;

}