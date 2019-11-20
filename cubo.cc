#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
     // inicializar la tabla de vértices

     vertex = {
<<<<<<< HEAD
         {0.0f, 0.0f, 1.0f},   // 001
         {1.0f, 0.0f, 1.0f},  // 101
         {1.0f, 1.0f, 1.0f}, // 111
         {0.0f, 1.0f, 1.0f},  // 011
         {1.0f, 0.0f, 0.0f},   // 100
         {1.0f, 1.0f, 0.0f},  // 110
         {0.0f, 0.0f, 0.0f},    // 000
         {0.0f, 1.0f, 0.0f}    // 010
=======
         {0.0f, 0.0f, 50.0f},   // 001
         {50.0f, 0.0f, 50.0f},  // 101
         {50.0f, 50.0f, 50.0f}, // 111
         {0.0f, 50.0f, 50.0f},  // 011
         {50.0f, 0.0f, 0.0f},   // 100
         {50.0f, 50.0f, 0.0f},  // 110
         {0.0f, 0.0f, 0.0f},    // 000
         {0.0f, 50.0f, 0.0f}    // 010
>>>>>>> master
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

<<<<<<< HEAD
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
=======
     /* Las caras estan definidas de forma que la primera mitad del vector
          son aquellas que se pintarán de un color en modo ajedrez, y la otra
          mitad de otro color, de esta forma ahorramos comprobaciones para
          este pintado simplemente pasando la mitad del vector para un
          color y la otra mitad para el otro OPCIONAL*/

     /*faces = {
          {0,2,3},
          {1,5,2},
          {4,7,5},
          {6,3,7},
          {3,5,7},
          {1,0,6},
          {0,1,2},
          {1,4,5},
          {6,7,4},
          {0,3,6},
          {2,5,3},
          {1,6,4}
     };*/

     // inicializar la tabla de colores:

     colors = {
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f},
         {50.0f, 0.0f, 0.0f}};

     colors1 = {
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f},
         {0.0f, 50.0f, 0.0f}};

     colors2 = {
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f},
         {0.0f, 0.0f, 50.0f}};
>>>>>>> master
}
