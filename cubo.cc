#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
     // inicializar la tabla de vértices

     vertex = {
         {0.0f, 0.0f, 1.0f},   // 001
         {1.0f, 0.0f, 1.0f},  // 101
         {1.0f, 1.0f, 1.0f}, // 111
         {0.0f, 1.0f, 1.0f},  // 011
         {1.0f, 0.0f, 0.0f},   // 100
         {1.0f, 1.0f, 0.0f},  // 110
         {0.0f, 0.0f, 0.0f},    // 000
         {0.0f, 1.0f, 0.0f}    // 010
     };

     // inicializar la tabla de caras o triángulos:

     faces = {
         {0, 2, 3}, {0, 1, 2},// CARA A
         {1, 5, 2}, {1, 4, 5}, // CARA B
         {4, 7, 5}, {6, 7, 4}, // CARA C
         {6, 3, 7}, {0, 3, 6}, // CARA D
         {3, 5, 7}, {2, 5, 3}, // CARA E
         {1, 0, 6}, {1, 6, 4} // CARA F
     };

     // inicializar la tabla de colores:

     colors = {
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f},
         {1.0f, 0.0f, 0.0f}};

     colors1 = {
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 1.0f, 0.0f}};

     colors2 = {
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f},
         {0.0f, 0.0f, 1.0f}};
}
