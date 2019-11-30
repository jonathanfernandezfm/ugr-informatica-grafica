#include "aux.h"
#include "luz_direccional.h"

LuzDireccional::LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso )
{
    this->alpha = direccion[0];
    this->beta = direccion[1];
    this->posicion = {}
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}