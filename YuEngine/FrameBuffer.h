#pragma once


#include <gl\glew.h>
#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include <Dependecies\SDL2-2.0.3\include\SDL_image.h>
#include <vector>
#include "Texture.h"

namespace YuEngine {


class FrameBuffer
{
public:
	FrameBuffer(void);
	FrameBuffer(int _width, int _height);
	~FrameBuffer(void);

	void bind();
	void unbind();

	bool load();
	void createRenderBuffer();

	GLuint getId() const {
		return id; 
	}
	GLuint getColorBufferId(int index) const {
		return colorBuffers[index].getId();
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}

private:
	int width;
	int height;
	GLuint id;
	GLuint depthBufferId;
	std::vector<Texture> colorBuffers;
};

}