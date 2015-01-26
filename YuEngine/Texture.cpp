#include "Texture.h"
#include <iostream>
namespace YuEngine {

Texture::Texture(std::string textureFile){
	this->id = 0;
	this->textureFile = textureFile;
	emptyTexture = false;
}
Texture::Texture(int _width, int _height) {
	width = _width;
	height = _height;
	emptyTexture = true;
	id = 0;
}
Texture::Texture(Texture const &textureToCopy) {
	textureFile = textureToCopy.getTextureFile();
	width = textureToCopy.getWidth();
	height = textureToCopy.getHeight();
	emptyTexture = textureToCopy.getEmptyTexture();

	if(emptyTexture && glIsTexture(textureToCopy.getId()) == GL_TRUE) {
		loadEmpty();
	} else if(glIsTexture(textureToCopy.getId() == GL_TRUE)) {
		load();
	}
};
Texture& Texture::operator=(Texture const &textureToCopy) {
	textureFile = textureToCopy.getTextureFile();
	width = textureToCopy.getWidth();
	height = textureToCopy.getHeight();
	emptyTexture = textureToCopy.getEmptyTexture();

	if(emptyTexture && glIsTexture(textureToCopy.getId()) == GL_TRUE) {
		loadEmpty();
	} else if(glIsTexture(textureToCopy.getId() == GL_TRUE)) {
		load();
	}

	return *this;
};



Texture::~Texture(void)
{
	glDeleteTextures(1, &id);
}


bool Texture::loadEmpty() {

	if(glIsTexture(id) == GL_TRUE) {
		glDeleteTextures(1, &id);
	}

	glGenTextures(1, &id);


	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;

}

SDL_Surface* Texture::invertPixels(SDL_Surface *imageSource) const
{
    // Copie conforme de l'image source sans les pixels

    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask, 
                                                         imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


    // Tableau interm�diaires permettant de manipuler les pixels

    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;


    // Inversion des pixels

    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }


    // Retour de l'image invers�e

    return imageInversee;
}

bool Texture::load()
{
    // Chargement de l'image dans une surface SDL

	SDL_Surface *SdlImage = IMG_Load(this->textureFile.c_str());

    if(SdlImage == 0)
    {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        return false;
    }
	SDL_Surface *invertedImage = this->invertPixels(SdlImage);
	SDL_FreeSurface(SdlImage);


    // G�n�ration de l'ID

    glGenTextures(1, &this->id);


    // Verrouillage

    glBindTexture(GL_TEXTURE_2D, this->id);


    // Format de l'image

    GLenum internalFormat(0);
    GLenum format(0);


    // D�termination du format et du format interne pour les images � 3 composantes

    if(invertedImage->format->BytesPerPixel == 3)
    {
        // Format interne

        internalFormat = GL_RGB;


        // Format

        if(invertedImage->format->Rmask == 0xff)
            format = GL_RGB;

        else
            format = GL_BGR;
    }


    // D�termination du format et du format interne pour les images � 4 composantes

    else if(invertedImage->format->BytesPerPixel == 4)
    {    
        // Format interne
        
        internalFormat = GL_RGBA;


        // Format

        if(invertedImage->format->Rmask == 0xff)
            format = GL_RGBA;

        else
            format = GL_BGRA;
    }


    // Dans les autres cas, on arr�te le chargement

    else
    {
        std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
        SDL_FreeSurface(invertedImage);

        return false;
    }


    // Copie des pixels
	
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, invertedImage->w, invertedImage->h, 0, format, GL_UNSIGNED_BYTE, invertedImage->pixels);


    // Application des filtres

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    // D�verrouillage

    glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(invertedImage);
	return true;
}

}