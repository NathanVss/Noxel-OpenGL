#pragma once

#include <gl\glew.h>
#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include <Dependecies\SDL2-2.0.3\include\SDL_image.h>
#include <string>
namespace YuEngine {

class Texture
{
public:
	Texture(std::string textureFile);
	~Texture(void);
	SDL_Surface* invertPixels(SDL_Surface *imageSource) const;
	bool load();
	GLuint getId() const { return this->id; }
	void setTextureFile(const std::string &textureFile) { this->textureFile = textureFile; }


private:
	GLuint id;
	std::string textureFile;
};

}