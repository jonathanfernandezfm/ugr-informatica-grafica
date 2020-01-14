#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro( const float altura, const float ancho )
{
    // // inicializar la tabla de vértices

    // vertex = {
    //     {0.0f, 0.0f, 0.0f}, // 001
    //     {ancho, 0.0f, 0.0f}, // 101
    //     {ancho, altura, 0.0f}, // 111
    //     {0.0f, altura, 0.0f} // 011
    // };

    // // inicializar la tabla de caras o triángulos:

    // faces = {
    //     {0, 1, 2}, 
    //     {2, 3, 0}
    // };

    // // inicializar la tabla de colores:

    // for(int i=0; i<vertex.size(); i++){
    //     colors.push_back({1.0f, 0.0f, 0.0f});
    //     colors1.push_back({0.0f, 1.0f, 0.0f});
    //     colors2.push_back({0.0f, 0.0f, 1.0f});
    // }

    // cf = {
    //     {0.0, 1.0},
    //     {1.0, 1.0},
    //     {1.0, 0.0},
    //     {0.0, 0.0}
    // };

    vertex =  {  { -1.0, 0.0, 0.0 }, // 0
                 { -1.0, 0.5, 0.0 }, // 1
                 { 1.0, 0.5, 0.0 }, // 2
                 { 1.0, 0.0, 0.0 } // 3
            };

    faces = { { 0, 1, 2 }, { 0, 2, 3 }
                } ;

    cf = {{0.0, 1.0},
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0}};

    this->generarNormales();
}