#include "aux.h"
#include "luz_direccional.h"

LuzDireccional::LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso )
{
    this->alpha = direccion[0];
    this->beta = direccion[1];
    this->posicion = {cos(this->alpha), sin(this->beta), 1, 0};
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
}

void LuzDireccional::variarAnguloAlpha(float incremento)
{
    this->alpha += incremento*M_PI/180;
    this->posicion = {cos(this->alpha), sin(this->beta), 1, 0};
}

void LuzDireccional::variarAnguloBeta(float incremento)
{
    this->beta += incremento*M_PI/180;
    this->posicion = {cos(this->alpha), sin(this->beta), 1, 0};
}