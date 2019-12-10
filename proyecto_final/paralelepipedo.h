// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Paralelepipedo.h

//
// #############################################################################

#ifndef PARALELEPIPEDO_H_INCLUDED
#define PARALELEPIPEDO_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Paralelepipedo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Paralelepipedo : public Malla3D
{
   public:
   Paralelepipedo(float ancho=1, float largo=1, float a=1, bool reverse=false) ;

} ;




#endif
