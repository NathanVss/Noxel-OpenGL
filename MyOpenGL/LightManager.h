#pragma once

#include "PixelsMap.h"
#include <string>
#include "Object.h"
#include <YuEngine\YuBoudingbox.h>

class LightSun;

class LightBag {
public:
	LightBag() { 
		
	};
	LightBag(const LightBag &other) {
		finalMap = other.finalMap;
	};
	virtual ~LightBag() { };
	PixelsMap finalMap;
};
class LightSunBag : public LightBag {
public:
	LightSunBag() { };
	~LightSunBag() { };
	LightSun* lightSun;
};

class LightManager: public Object
{
public:
	LightManager(void);
	~LightManager(void);
	void convertToBMP(PixelsMap &s, std::string filename);
	void createBaseMap();
	void update();
	void setActiveChunksRect();

	void enableFinalMap();
	void assignIndices();

	void doSunLighting(LightSunBag &lightSunBag);
	void addLightSun(LightSun* s) {
		lightsSun.push_back(s);
	}
private:
	std::vector<LightSunBag> lightSunBags;
	std::vector<LightSun*> lightsSun;
	PixelsMap baseMap;
	PixelsMap finalMap;
	YuEngine::YuBoudingbox activeChunksRect;
	int precision;
};

