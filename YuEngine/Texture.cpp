#include "Texture.h"
#include <iostream>
namespace YuEngine {

Texture::Texture(std::string textureFile){
	this->id = 0;
	this->textureFile = textureFile;
}


Texture::~Texture(void)
{
}

SDL_Surface* Texture::invertPixels(SDL_Surface *imageSource) const
{
    // Copie conforme de l'image source sans les pixels

    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask, 
                                                         imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);


	std::cout << "Width : " << imageSource->w << std::endl;
    // Tableau intermédiaires permettant de manipuler les pixels

    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;


    // Inversion des pixels

    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
            pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }


    // Retour de l'image inversée

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


    // Génération de l'ID

    glGenTextures(1, &this->id);


    // Verrouillage

    glBindTexture(GL_TEXTURE_2D, this->id);


    // Format de l'image

    GLenum internalFormat(0);
    GLenum format(0);


    // Détermination du format et du format interne pour les images à 3 composantes

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


    // Détermination du format et du format interne pour les images à 4 composantes

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


    // Dans les autres cas, on arrête le chargement

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


    // Déverrouillage

    glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(invertedImage);
	return true;
}

}