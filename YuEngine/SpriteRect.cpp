#include "SpriteRect.h"
#include <string>
#include "Texture.h"
#include "Shader.h"
#include "Container.h"
#include "Camera2D.h"
#include "Spritesheet.h"


namespace YuEngine {



void SpriteRect::init(float x, float y, float width, float height, float r, float g, float b, float a) {

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->vaoId = 0;
	this->vboId = 0;
	this->cColor = new Color();
	this->cColor->a = a;
	this->cColor->r = r;
	this->cColor->g = g;
	this->cColor->b = b;



	float colorCoordsTmp[] = {this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a,    this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a,   this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a, 
								this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a,    this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a,     this->cColor->r,this->cColor->g,this->cColor->b,this->cColor->a};



	for(int i= 0; i<24;i++) {
		this->colors[i] = colorCoordsTmp[i];
	}

	this->setVerticesFromCoords();

	this->colorsSizeBytes = (24*sizeof(float));
	
	this->verticesSizeBytes = (12*sizeof(float));
}

SpriteRect::SpriteRect(float x, float y, float width, float height, float r, float g, float b, float a, Spritesheet* sSpritesheet, int spriteX, int spriteY) {
	this->init(x, y, width, height, r, g, b, a);
	this->spriteX = spriteX;
	this->spriteY = spriteY;
	this->sSpritesheet = sSpritesheet;

	this->sSpritesheet->setCurSprite(this->spriteX, this->spriteY);


	//
	//this->textureCoordsSizeBytes = (12*sizeof(float));
	//for(int i = 0; i<12; i++) {
	//	this->textureCoords[i] = textureCoordsTmp[i];
	//}
	
}
SpriteRect::SpriteRect(float x, float y, float width, float height, float r, float g, float b, float a) {
	this->init(x, y, width, height, r, g, b, a);
}

SpriteRect::~SpriteRect() {
	delete this->cColor;
	glDeleteBuffers(1, &vboId);
	glDeleteVertexArrays(1, &vaoId);
}

void SpriteRect::setVerticesFromCoords() {

	float verticesTmp[] = {x, y,  x+width, y,   x, y+height,
							x, y+height, x+width, y,  x+width, y+height};	

	for(int i=0;i<12;i++) {
		this->vertices[i] = verticesTmp[i];
	}

	if(glIsBuffer(vboId) == GL_TRUE) {
		this->updateVbo(this->vertices, 12*sizeof(float), 0);
	}

}

void SpriteRect::load() {
	if(glIsBuffer(vboId) == GL_TRUE) {
		glDeleteBuffers(1, &vboId);
	}

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	glBufferData(GL_ARRAY_BUFFER, (this->verticesSizeBytes + this->colorsSizeBytes + this->textureCoordsSizeBytes), 0, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, this->verticesSizeBytes, this->vertices);
		glBufferSubData(GL_ARRAY_BUFFER, this->verticesSizeBytes, this->colorsSizeBytes, this->colors);
		glBufferSubData(GL_ARRAY_BUFFER, this->verticesSizeBytes+this->colorsSizeBytes, this->textureCoordsSizeBytes, this->textureCoords);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(glIsVertexArray(vaoId)) {
		glDeleteVertexArrays(1, &vaoId);
	}

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);


		glBindBuffer(GL_ARRAY_BUFFER, vboId);


			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(this->verticesSizeBytes));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(this->verticesSizeBytes+this->colorsSizeBytes));
			glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void SpriteRect::update(float x, float y) {

	if(x != this->x ||  y != this->y) {
		
		this->x = x;
		this->y = y;
		this->setVerticesFromCoords();

	}
	this->update();

}

void SpriteRect::update() {

}

void SpriteRect::updateVbo(void *datas, int sizeBytes, int offset)
{
    // Verrouillage du VBO

    glBindBuffer(GL_ARRAY_BUFFER,vboId);


        // Récupération de l'adresse du VBO

        void *vboAdress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);


        // Si l'adresse retournée est nulle alors on arrête le transfert

        if(vboAdress == NULL)
        {
            std::cout << "Erreur au niveau de la récupération du VBO" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return; 
        }


        // Mise à jour des données

        memcpy((char*)vboAdress + offset, datas, sizeBytes);


        // Annulation du pointeur

        glUnmapBuffer(GL_ARRAY_BUFFER);
        vboAdress = 0;


    // Déverrouillage du VBO

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRect::render() {

	

	glUseProgram(this->cContainer->getClassicShader()->getProgramID());

		glBindVertexArray(vaoId);

		glUniformMatrix4fv(glGetUniformLocation(this->cContainer->getClassicShader()->getProgramID(), "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(this->cContainer->getCamera()->getCameraMatrix()));

			this->sSpritesheet->bind();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			this->sSpritesheet->unbind();


		glBindVertexArray(0);

	glUseProgram(0);


}


}