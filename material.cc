#include "aux.h"
#include "material.h"

Material::Material(){}

Material::Material( Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo )
{
    this->difuso = mdifuso;
    this->especular = mespecular;
    this->ambiente = mambiente;
    this->brillo = brillo;
}

void Material::aplicar()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *) & ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *) & difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) & especular);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo);
}
