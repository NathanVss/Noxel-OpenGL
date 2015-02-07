#pragma once
class Config
{
public:
	Config(void) {
		lighting = true;
	};
	~Config(void) {

	};

	void setLighting(bool _flag) {
		lighting = _flag;
	}
	bool getLighting() {
		return lighting;
	}

	void setScreenDimensions(float _w, float _h) {
		screenWidth = _w;
		screenHeight = _h;
	}

	float getScreenWidth() {
		return screenWidth;
	}
	float getScreenHeight() {
		return screenHeight;
	}

private:
	bool lighting;
	float screenWidth;
	float screenHeight;
};

