#include "FrameBuffer.h"
#include <iostream>

namespace YuEngine {
FrameBuffer::FrameBuffer(void){
}


FrameBuffer::~FrameBuffer(void){
	glDeleteFramebuffers(1, &id);
	glDeleteRenderbuffers(1, &depthBufferId);

	colorBuffers.clear();
}

FrameBuffer::FrameBuffer(int _width, int _height) {

	id = 0;
	width = _width;
	height = _height;

}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}
void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



bool FrameBuffer::load() {

	if(glIsFramebuffer(id) == GL_TRUE) {
		glDeleteFramebuffers(1, &id);

			colorBuffers.clear();
	}
	glGenFramebuffers(1, &id);

	glBindFramebuffer(GL_FRAMEBUFFER, id);



	Texture colorBuffer(width, height);
	colorBuffer.loadEmpty();

	colorBuffers.push_back(colorBuffer);

	createRenderBuffer();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffers[0].getId(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);



    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // Libération des buffers

        glDeleteFramebuffers(1, &id);
        glDeleteRenderbuffers(1, &depthBufferId);

        colorBuffers.clear();


        // Affichage d'un message d'erreur et retour de la valeur false

        std::cout << "Erreur : le FBO est mal construit" << std::endl;

        return false;
    }


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void FrameBuffer::createRenderBuffer() {

    if(glIsRenderbuffer(depthBufferId) == GL_TRUE)
        glDeleteRenderbuffers(1, &depthBufferId);

    glGenRenderbuffers(1, &depthBufferId);

    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);


    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}


}