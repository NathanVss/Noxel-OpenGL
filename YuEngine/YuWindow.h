#pragma once

#include <gl\glew.h>
#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
#include <string>

namespace YuEngine {

class YuWindow
{
public:
	YuWindow(void) {
	};
	YuWindow(int _width, int _height, std::string _title) {
		width = _width;
		height = _height;
		title = _title;
	};
	~YuWindow(void) {
	}
	bool initWindow();
	bool initOpenGl();
	void swap();

private:
	int height;
	int width;
	std::string title;
	SDL_Window* sdlWindow;
	SDL_GLContext* openGlContext;
};

}