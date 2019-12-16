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
#include "luz_posicional.h"

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

        void draw(modes mode);
        void toggleLuz();

        void girar();
        void balancear();
        void estirar();
        void modificarVelocidadGiro(float incremento);
        void modificarVelocidadBalanceo(float incremento);
        void modificarVelocidadEstiramiento(float incremento);

        LuzPosicional *luzVentilador = nullptr;
    private:
        Paralelepipedo *aspa = nullptr;

        Semiesfera *semiesfera = nullptr;
        Semiesfera *semiesferaPequena = nullptr;

        Cilindro *cilindro = nullptr;

        float giro = 0, incrementoGiro = 0.5;
        float altura = 0, goingUp = 1, incrementoEstirar = 0.001;
        float balanceo = 0, movingRight = 1, incrementoBalanceo = 0.1;
        float balanceoAlpha = 0, balanceoBeta = 0;

        bool luz = false;
} ;




#endif
