// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool conTapas=true) ;
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool conTapas=true, int eje=1) ;
    private:
        Tupla3f rotateX(Tupla3f vertice, double angle);
        Tupla3f rotateY(Tupla3f vertice, double angle);
        Tupla3f rotateZ(Tupla3f vertice, double angle);
    protected:
        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas=true, int eje=1);
} ;

#endif
