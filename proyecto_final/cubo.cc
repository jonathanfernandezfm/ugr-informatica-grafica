#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado, bool reverse)
{
    // inicializar la tabla de vértices

    vertex = {
        {0.0f, 0.0f, lado}, // 001
        {lado, 0.0f, lado}, // 101
        {lado, lado, lado}, // 111
        {0.0f, lado, lado}, // 011
        {lado, 0.0f, 0.0f}, // 100
        {lado, lado, 0.0f}, // 110
        {0.0f, 0.0f, 0.0f}, // 000
        {0.0f, lado, 0.0f}  // 010
    };

    // inicializar la tabla de caras o triángulos:

    if(reverse) {
        faces = {
            {0, 3, 2}, 
            {0, 2, 1}, // CARA A
            {1, 2, 5},
            {1, 5, 4}, // CARA B
            {4, 5, 7},
            {6, 4, 7}, // CARA C
            {6, 7, 3},
            {0, 6, 3}, // CARA D
            {3, 7, 5},
            {2, 3, 5}, // CARA E
            {1, 6, 0},
            {1, 4, 6} // CARA F
        };
    } else {
        faces = {
            {0, 2, 3}, 
            {0, 1, 2}, // CARA A
            {1, 5, 2},
            {1, 4, 5}, // CARA B
            {4, 7, 5},
            {6, 7, 4}, // CARA C
            {6, 3, 7},
            {0, 3, 6}, // CARA D
            {3, 5, 7},
            {2, 5, 3}, // CARA E
            {1, 0, 6},
            {1, 6, 4} // CARA F
        };
    }
    

    // inicializar la tabla de colores:

    for(int i=0; i<vertex.size(); i++){
        colors.push_back({1.0f, 0.0f, 0.0f});
        colors1.push_back({0.0f, 1.0f, 0.0f});
        colors2.push_back({0.0f, 0.0f, 1.0f});
    }

    this->generarNormales();
}
