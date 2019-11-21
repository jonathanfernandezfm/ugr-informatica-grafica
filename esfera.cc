#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf, const float radio )
{
    this->vertex.push_back({
        0.0f, 
        -radio, 
        0.0f
    });

    // -1 por los vertices ya existentes
    float fragment = M_PI / (num_vert_perfil-1);

    Tupla3f start = {
        0.0f, 
        -radio, 
        0.0f
    };

    // empezamos en 1 por los vertices existentes
    for(int i=1; i<num_vert_perfil-1; i++){
        this->vertex.push_back({
            start[0]*cos(i*fragment)-start[1]*sin(i*fragment),
            start[0]*sin(i*fragment)+start[1]*cos(i*fragment),
            0.0f
        });
    }

    this->vertex.push_back({
        0.0f,
        radio, 
        0.0f
    });

    this->crearMalla(this->vertex, num_instancias_perf, true);
    this->generarNormales();
}