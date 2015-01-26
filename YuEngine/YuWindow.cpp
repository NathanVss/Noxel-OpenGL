#include "YuWindow.h"
#include "Errors.h"

namespace YuEngine{

void YuWindow::swap() {
		SDL_GL_SwapWindow(sdlWindow);
	
}

bool YuWindow::initWindow() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
		YuFatalError("Error while initialising SDL : " + std::string( SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(sdlWindow == 0) {
		YuFatalError("Error while creating window : " + std::string(SDL_GetError()));
    }

	SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);
	openGlContext = &context;

	if((*openGlContext) == 0) {
		YuFatalError("Error while creating OpenGL context : " + std::string(SDL_GetError()));
    }
    return true;

}

bool YuWindow::initOpenGl() {


    GLenum glewInit( glewInit() );

    if(glewInit != GLEW_OK)
    {
		YuFatalError("Error while initialising glew : " + std::string((const char*)glewGetErrorString(glewInit)));
    }
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_ONE,  GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);







	



	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	//glBlendFunc (GL_ONE, GL_ONE);

    return true;
}

};