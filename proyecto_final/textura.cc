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

void Textura::activar(std::vector<Tupla2f> cf, std::vector<Tupla3f> vertex) {    
    // glColor3f(1.0,1.0,1.0); 
    // glBindTexture(GL_TEXTURE_2D, idTex);

    // glActiveTexture(GL_TEXTURE0);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, texels);

    // glEnable(GL_TEXTURE_2D);
    // glEnableClientState (GL_TEXTURE_COORD_ARRAY);

    // glActiveTexture(GL_TEXTURE0);

    // glTexCoordPointer(2, GL_FLOAT, 0, cf.data());

    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_TEXTURE_2D);


    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, idTex);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // TRASFIERE LOS DATOS A GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, idTex);

    glVertexPointer(3, GL_FLOAT, 0, vertex.data());
    glTexCoordPointer(2, GL_FLOAT, 0, cf.data());

    glDrawArrays(GL_QUADS, 0, (vertex.size()/3));

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glDeleteTextures(1, &idTex);
    std::cout << "cargado" << std::endl;
}
