#ifndef SEMIESFERA_H_INCLUDED
#define SEMIESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Semiesfera : public ObjRevolucion
{
    public:
        Semiesfera( const int num_vert_perfil, const int num_instancias_perf, const float radio);
} ;

#endif
