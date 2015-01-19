#pragma once

#include <YuEngine\Vertex.h>
#include <vector>

class PixelsMap
{
public:
	PixelsMap(void);
	PixelsMap(int width, int height);
	PixelsMap& operator=(const PixelsMap& copy) {

		destroyArrays();
		height = copy.getHeight();
		width = copy.getWidth();
		initArrays();
		for(int x = 0; x < width; x++)  {
			for(int y = 0; y < height; y++) {
				red[x][y] = copy.getRed(x, y);
				green[x][y] = copy.getGreen(x, y);
				blue[x][y] = copy.getBlue(x, y);
				alpha[x][y] = copy.getAlpha(x, y);
			}
		}
		return *this;
	}

	~PixelsMap(void);

	void initArrays();
	void destroyArrays();

	bool setScale(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	
	bool isBlack(int x, int y) {
		return red[x][y] == 0 && green[x][y] == 0 && blue[x][y] == 0;
	}

	unsigned char getRed(int x, int y) const {
		return red[x][y];
	}
	unsigned char getGreen(int x, int y) const {
		return green[x][y];
	}
	unsigned char getBlue(int x, int y) const {
		return blue[x][y];
	}
	unsigned char getAlpha(int x, int y) const {
		return alpha[x][y];
	}
	YuEngine::Color getColor(int x, int y) {
		YuEngine::Color color;
		color.a = alpha[x][y] / 255.0f;
		color.r = red[x][y] / 255.0f;
		color.g = green[x][y] / 255.0f;
		color.b = blue[x][y] / 255.0f;
		return color;
	}

	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	void setHeight(int _h) {
		height = _h;
	}
	void setWidth(int _w) {
		width = _w;
	}
private:
	int width;
	int height;

	unsigned char** red;
	unsigned char** green;
	unsigned char** blue;
	unsigned char** alpha;
};

