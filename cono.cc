#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono( const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio )
{
    this->vertex.push_back({
        radio, 
        0.0f, 
        0.0f
    });

    // -1 por los vertices ya existentes
    float fragmentX = radio / (num_vert_perfil-1);
    float fragmentY = altura / (num_vert_perfil-1);

    // empezamos en 1 por los vertices existentes
    for(int i=1; i<num_vert_perfil; i++){
        this->vertex.push_back({
            radio-(i*fragmentX),
            i*fragmentY,
            0.0f
        });
    }

    this->vertex.push_back({
        0.0f, 
        altura,
        0.0f
    });

    this->crearMalla(this->vertex, num_instancias_perf, true);
}