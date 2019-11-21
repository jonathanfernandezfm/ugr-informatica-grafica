#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio )
{
    std::vector<Tupla3f> perfil;

    perfil.push_back({
        radio, 
        0.0f, 
        0.0f
    });

    // -1 por los vertices ya existentes
    float fragment = altura / (num_vert_perfil-1);

    // empezamos en 1 por los vertices existentes
    for(int i=1; i<num_vert_perfil; i++){
        perfil.push_back({
            radio,
            i*fragment,
            0.0f
        });
    }

    this->crearMalla(perfil, num_instancias_perf, true);

    // for(int i=0; i<faces.size(); i++){
    //     std::cout << "Faces: " << faces[i] << std::endl;
    // }

    // 	std::cout << std::endl << std::endl;

    // for(int i=0; i<vertex.size(); i++){
    //     std::cout << "vertex: " << vertex[i] << std::endl;
    // }

    //this->generarNormales();
}