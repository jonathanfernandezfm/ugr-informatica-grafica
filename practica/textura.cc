#include "aux.h"
#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(){  }

Textura::Textura(std::string archivo)
{
    jpg::Imagen *pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();

    texels = pimg->leerPixels();
    glGenTextures(1, &idTex);
}

void Textura::activar() {    
    glBindTexture(GL_TEXTURE_2D, idTex);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, texels);

    glEnable(GL_TEXTURE_2D);

    
    glDisable(GL_TEXTURE_2D);

    std::cout << "cargado" << std::endl;
}
