#include "aux.h"
#include "luz.h"

void Luz::activar()
{
	glLightfv(id, GL_AMBIENT, (GLfloat*) & colorAmbiente);
	glLightfv(id, GL_DIFFUSE, (GLfloat*) & colorDifuso);
	glLightfv(id, GL_SPECULAR, (GLfloat*) & colorEspecular);
	glLightfv(id, GL_POSITION, (GLfloat*) & posicion);
    glEnable(id);

}