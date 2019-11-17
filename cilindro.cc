#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio )
{
    this->vertex.push_back({
        radio, 
        0.0f, 
        0.0f
    });
    this->vertex.push_back({
        radio, 
        altura, 
        0.0f
    });

    this->crearMalla(this->vertex, num_instancias_perf, true);
}