#include "aux.h"
#include "malla.h"
#include "semiesfera.h"

Semiesfera::Semiesfera( const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
    std::vector<Tupla3f> perfil;

    perfil.push_back({
        0.0f, 
        -radio, 
        0.0f
    });

    // -1 por los vertices ya existentes
    float fragment = (M_PI / 2) / (num_vert_perfil-1);

    Tupla3f start = {
        0.0f, 
        -radio, 
        0.0f
    };

    // empezamos en 1 por los vertices existentes
    for(int i=1; i<num_vert_perfil-1; i++){
        perfil.push_back({
            start[0]*cos(i*fragment)-start[1]*sin(i*fragment),
            start[0]*sin(i*fragment)+start[1]*cos(i*fragment),
            0.0f
        });
    }

    perfil.push_back({
        0.0f,
        0.0f, 
        0.0f
    });

    this->crearMalla(perfil, num_instancias_perf, true);
    this->generarNormales();
}