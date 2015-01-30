#pragma once

#include <gl\glew.h>
#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include <Dependecies\SDL2-2.0.3\include\SDL_image.h>
#include <string>
namespace YuEngine {

class Texture
{
public:
	Texture() {

	};
	Texture(std::string textureFile);
	Texture(int _width, int _height);
	Texture(Texture const &textureToCopy);
	Texture& operator=(Texture const &textureToCopy);
	~Texture(void);



	SDL_Surface* invertPixels(SDL_Surface *imageSource) const;
	bool load();
	bool loadEmpty();
	GLuint getId() const { return this->id; }
	void setTextureFile(const std::string &textureFile) { this->textureFile = textureFile; }
	std::string getTextureFile() const { return textureFile; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	bool getEmptyTexture() const { return emptyTexture; }

private:
	GLuint id;
	std::string textureFile;
	bool emptyTexture;
	int width;
	int height;
};

}