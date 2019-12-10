// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ventilador.h

//
// #############################################################################

#ifndef VENTILADOR_H_INCLUDED
#define VENTILADOR_H_INCLUDED

#include "aux.h"
#include "paralelepipedo.h"
#include "semiesfera.h"
#include "cilindro.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Ventilador con centro en el origen 

class Ventilador
{
    public:
        Ventilador();

        void draw();
        void girar();
        void balancear();
        void estirar();
    private:
        Paralelepipedo *aspa1 = nullptr;
        Paralelepipedo *aspa2 = nullptr;
        Paralelepipedo *aspa3 = nullptr;
        Paralelepipedo *aspa4 = nullptr;

        Semiesfera *semiesfera = nullptr;

        Cilindro *cilindro = nullptr;

        float giro = 0;
        float incremento = 0, goingUp = 1;
        float balanceo = 0, movingRight = 1;
} ;




#endif
