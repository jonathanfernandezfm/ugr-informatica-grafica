// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz_direccional.h

//
// #############################################################################

#ifndef LUZ_DIRECCIONAL_H_INCLUDED
#define LUZ_DIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
    protected:
        float alpha;
        float beta;
    public:
        LuzDireccional( Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso );

        void variarAnguloAlpha( float incremento );

        void variarAnguloBeta( float incremento );
} ;


#endif
