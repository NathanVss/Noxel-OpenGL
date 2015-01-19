#include "LightManager.h"
#include <Dependecies\EasyBMP\EasyBMP.h>
#include <vector>
#include "Chunk.h"
#include "Container.h"
#include "World.h"
#include "Block.h"
#include "Light.h"
#include "LightSun.h"

LightManager::LightManager(void)
{
}


LightManager::~LightManager(void){
}

void LightManager::setActiveChunksRect() {

	std::vector<Chunk*>* activeChunks = myContainer->getWorld()->getActiveChunks();

	float bottomLeftX = 0;
	float bottomLeftY = 0;
	float topRightX = 0;
	float topRightY = 0;
	for(int i = 0; i < activeChunks->size(); i++) {
		float chunkX = (*activeChunks)[i]->getX();
		float chunkY = (*activeChunks)[i]->getY();
		if(i == 0) {
			bottomLeftX = chunkX;
			bottomLeftY = chunkY;
		}

		if(chunkX < bottomLeftX) {
			bottomLeftX = chunkX;
		}
		if(chunkY < bottomLeftY) {
			bottomLeftY = chunkY;
		}

		if(chunkX > topRightX) {
			topRightX = chunkX;
		}
		if(chunkY > topRightY) {
			topRightY = chunkY;
		}
	}
	bottomLeftX /= Chunk::width*Block::size;
	bottomLeftY /= Chunk::height*Block::size;
	topRightX /= Chunk::width*Block::size;
	topRightY /= Chunk::height*Block::size;
	topRightX += 1;
	topRightY += 1;

	YuEngine::YuBoudingbox rect(bottomLeftX, topRightY, topRightX - bottomLeftX, topRightY - bottomLeftY); 
	activeChunksRect = rect;
}

void LightManager::createBaseMap() {
	setActiveChunksRect();
	precision = Block::size;
	precision = 1;
	baseMap = PixelsMap(activeChunksRect.getWidth() * Chunk::width * precision, activeChunksRect.getHeight() * Chunk::height * precision);
	std::vector<Chunk*>* activeChunks = myContainer->getWorld()->getActiveChunks();

	int mapX, mapY;
	for(int i = 0; i < activeChunks->size(); i++) {

		Chunk* curChunk = (*activeChunks)[i];

		Block*** blocks = curChunk->getBlocks();
		for(int x = 0; x < Chunk::width; x++) {
			for(int y = 0; y < Chunk::height; y++) {
				mapX = blocks[x][y]->getX()/Block::size - activeChunksRect.getX1()*Chunk::width;

				// Pixels Map : 
				// -------
				// |     |
				// -------
				// Il y aura toujours un décalage de 1 car le repere d'un bloc est enbas à gauche
				// Or le TOP de la pixels Map est le bloc du dessus
				mapY = activeChunksRect.getY1()*Chunk::height - blocks[x][y]->getY()/Block::size - 1;
				if(blocks[x][y]->isTransparent()) {
					baseMap.setScale(mapX, mapY, 255,255,255,255);

				} else {
					baseMap.setScale(mapX, mapY, 0,0,0,255);

				}

			}
		}

	}


	convertToBMP(baseMap, "lighting/test.bmp");
}

void LightManager::doSunLighting(LightSunBag &lightSunBag) {
	// Ground level 
	float maxLightable = 50;
	float gradientHeight = 5;
	int bias = 6;
	float sunIndice = lightSunBag.lightSun->getIndice();

	float boxX = activeChunksRect.getX1()*Chunk::width;
	float boxY = activeChunksRect.getY1()*Chunk::height;
	int worldHeight = World::worldHeight;
	for(int x = 0; x < baseMap.getWidth(); x++) {


		int opaqueInCol = 0;

		for(int y = 0; y < baseMap.getHeight(); y++) {

			float yFromSky = y + worldHeight - boxY;
			
			if(yFromSky > maxLightable + gradientHeight) {
				lightSunBag.finalMap.setScale(x, y, 0,0,0,255);
			} else if ( yFromSky > maxLightable && yFromSky <= maxLightable + gradientHeight) {
				float gradientDistance = yFromSky - maxLightable;
				float gradientIndice = 1 - gradientDistance / gradientHeight;

				if(baseMap.isBlack(x, y)) {


						lightSunBag.finalMap.setScale(x, y,0, 0, 0,255);

				} else {
					lightSunBag.finalMap.setScale(x, y, 255*gradientIndice*sunIndice, 255*gradientIndice*sunIndice, 255*gradientIndice*sunIndice,255);

				}
			} else if( yFromSky <= maxLightable ) {

				if(baseMap.isBlack(x, y)) {
					opaqueInCol++;

					if(opaqueInCol < bias) {
						float biasIndice = 1 - opaqueInCol / (float)bias;
						lightSunBag.finalMap.setScale(x, y, 255*sunIndice*biasIndice, 255*sunIndice*biasIndice, 255*sunIndice*biasIndice,255);

						
					} else {

						lightSunBag.finalMap.setScale(x, y, 0,0,0,255);

					}


				} else {
					lightSunBag.finalMap.setScale(x, y, 255*sunIndice,255*sunIndice,255*sunIndice,255*sunIndice);
					
				}

			}


		}

	}

	convertToBMP(lightSunBag.finalMap, "lighting/sun.bmp");
}

void LightManager::enableFinalMap() {
	finalMap = PixelsMap(baseMap.getWidth(), baseMap.getHeight());
	for(int x = 0; x < baseMap.getWidth(); x++) {
		for(int y = 0; y < baseMap.getHeight(); y++) {
			unsigned char red = 0;
			unsigned char green = 0;
			unsigned char blue = 0;
			unsigned char alpha = 0;

			for(int i = 0; i < lightSunBags.size(); i++) {
				red += lightSunBags[i].finalMap.getRed(x, y);
				green += lightSunBags[i].finalMap.getGreen(x, y);
				blue += lightSunBags[i].finalMap.getBlue(x, y);
				alpha += lightSunBags[i].finalMap.getAlpha(x, y);
			}
			if(red > 255) {
				red = 255;
			}
			if(green > 255) {
				green = 255;
			}
			if(blue > 255) {
				blue = 255;
			}
			if(alpha > 255) {
				alpha = 255;
			}

			finalMap.setScale(x, y, red, green, blue, alpha);

		}

	}
}

void LightManager::assignIndices() {
	std::vector<Chunk*>* activeChunks = myContainer->getWorld()->getActiveChunks();
	for(int i = 0; i < activeChunks->size(); i++) {

		Chunk* curChunk = (*activeChunks)[i];

		Block*** blocks = curChunk->getBlocks();
		for(int x = 0; x < Chunk::width; x++) {
			for(int y = 0; y < Chunk::height; y++) {

				int mapX = blocks[x][y]->getX()/Block::size - activeChunksRect.getX1()*Chunk::width;
				int mapY = activeChunksRect.getY1()*Chunk::height - blocks[x][y]->getY()/Block::size - 1;

				YuEngine::Color indice;
				indice.r = finalMap.getRed(mapX, mapY);
				indice.g = finalMap.getGreen(mapX, mapY);
				indice.b = finalMap.getBlue(mapX, mapY);
				indice.a = finalMap.getAlpha(mapX, mapY);
				
				blocks[x][y]->setLightIndice(indice);
			}

		}

	}
}

void LightManager::update() {
	createBaseMap();

	lightSunBags.clear();
	for(int i = 0; i < lightsSun.size(); i++) {
		LightSunBag lightSunBag;

		PixelsMap _finalMap(baseMap.getWidth(), baseMap.getHeight());
		lightSunBag.finalMap = _finalMap;
		lightSunBag.lightSun = lightsSun[i];
		doSunLighting(lightSunBag);
		lightSunBags.push_back(lightSunBag);
	}
	
	enableFinalMap();
	assignIndices();

}

void LightManager::convertToBMP(PixelsMap &s, std::string filename) {
	return;
	BMP* curBMP = new BMP();

		curBMP->SetSize(s.getWidth(),s.getHeight());

		curBMP->SetBitDepth(32);

			
		for(int x=0; x < s.getWidth(); x++) {

			for(int y = 0; y < s.getHeight(); y++) {
	
				(*curBMP)(x, y)->Red = s.getRed(x, y);
				(*curBMP)(x, y)->Alpha = s.getAlpha(x, y);
				(*curBMP)(x, y)->Green = s.getGreen(x, y);
				(*curBMP)(x, y)->Blue = s.getBlue(x, y);

			}
		}

		curBMP->WriteToFile(filename.c_str());
	delete curBMP;
}
