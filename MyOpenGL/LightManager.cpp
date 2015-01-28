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

LightManager::LightManager(int _screenWidth, int _screenHeight) {
	texture = 0;
	sunBias = 127;
	offset = sunBias;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	textureWidth = screenWidth + offset * 2;
	textureHeight = screenHeight + offset * 2;

	screenPixels = new GLubyte[textureWidth*textureHeight*4];
	resetScreenPixels();
	eTimer = YuEngine::EventTimer(60);

	frameBufferHorizBlur = new YuEngine::FrameBuffer(textureWidth, textureHeight);
	frameBufferHorizBlur->load();

	frameBufferObstacle = new YuEngine::FrameBuffer(textureWidth, textureHeight);
	frameBufferObstacle->load();

	frameBufferVertBlur = new YuEngine::FrameBuffer(screenWidth, screenHeight);
	frameBufferVertBlur->load();
	
	lightSpritesheet = YuEngine::Spritesheet("textures/voidblank.png", 1);
}

LightManager::~LightManager(void){
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

void LightManager::update() {

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
		myContainer->getBlurShader()->sendInt("invertY",0);
		myContainer->getBlurShader()->sendFloat("offset",offset);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, frameBufferHorizBlur->getColorBufferId(0));
		myContainer->getBlurShader()->sendInt("screenTexture", 0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		myContainer->getGameRenderer()->render(myContainer->getBlurShader()->getProgramID());

		myContainer->getBlurShader()->unuse();



	frameBufferVertBlur->unbind();


	eTimer.update();

	if(eTimer.isOver()){
	//pixelsToBmp(frameBufferVertBlur->getColorBufferId(0), "lighting/Vert.bmp", screenWidth, screenHeight);
	//pixelsToBmp(frameBufferHorizBlur->getColorBufferId(0), "lighting/Horiz.bmp", textureWidth, textureHeight);
	//pixelsToBmp(texture, "lighting/blocks.bmp", textureWidth, textureHeight);
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

void LightManager::render() {


	myContainer->getLightingShader()->sendInt("screenWidth", screenWidth);
	myContainer->getLightingShader()->sendInt("screenHeight", screenHeight);


	myContainer->getLightingShader()->sendFloat("offset", offset);
	myContainer->getLightingShader()->sendFloat("sunBias", sunBias);

	myContainer->getLightingShader()->sendInt("shadowCasterWidth", textureWidth);
	myContainer->getLightingShader()->sendInt("shadowCasterHeight", textureHeight);

	myContainer->getLightingShader()->sendFloat("screenTopY", cameraBox.getY1());
	myContainer->getLightingShader()->sendFloat("textureTopY", textureBox.getY1());


	myContainer->getLightingShader()->sendFloat("worldHeight", World::worldHeight);
	myContainer->getLightingShader()->sendFloat("blockSize", Block::size);
	myContainer->getLightingShader()->sendFloat("maxDepthLightable", 50);
	myContainer->getLightingShader()->sendFloat("depthGradient", 200);
	myContainer->getLightingShader()->sendFloat("hourIndice", lightSun->getIndice());
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	myContainer->getLightingShader()->sendInt("lightTexture", 0);

}



void LightManager::resetScreenPixels() {

	for(int x = 0; x < textureWidth ; x++) {
		for(int y = 0; y < textureHeight; y++) {

			screenPixels[y*textureWidth*4 + x*4] = 255;
			screenPixels[y*textureWidth*4 + x*4 + 1] = 255;
			screenPixels[y*textureWidth*4 + x*4 + 2] = 255;
			screenPixels[y*textureWidth*4 + x*4 + 3] = 255;
		}

	}

}
void LightManager::pixelsToBmp() {

	BMP* curBMP = new BMP();
	curBMP->SetSize(textureWidth,textureHeight);
	curBMP->SetBitDepth(32);
	for(int x=0; x < textureWidth; x++) {
		for(int y = 0; y < textureHeight; y++) {
			(*curBMP)(x, y)->Red = screenPixels[y*textureWidth*4  + x * 4];
			(*curBMP)(x, y)->Green = screenPixels[y*textureWidth*4  + x * 4 + 1];
			(*curBMP)(x, y)->Blue = screenPixels[y*textureWidth*4  + x * 4 + 2];
			(*curBMP)(x, y)->Alpha = screenPixels[y*textureWidth*4  + x * 4 + 3];
		}
	}
	curBMP->WriteToFile("lighting/pixels.bmp");
	delete curBMP;

}

