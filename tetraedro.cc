#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

	// inicializar la tabla de vértices

	vertex = {
<<<<<<< HEAD
		{0.0f, 0.0f, 1.0f}, // 001
		{1.0f, 0.0f, 0.0f}, // 100
		{0.0f, 1.0f, 0.0f}, // 010
=======
		{0.0f, 0.0f, 50.0f}, // 001
		{50.0f, 0.0f, 0.0f}, // 100
		{0.0f, 50.0f, 0.0f}, // 010
>>>>>>> master
		{0.0f, 0.0f, 0.0f}   // 000
	};

	// inicializar la tabla de caras o triángulos:

	faces = {
		{0, 1, 2}, // CARA A
		{1, 3, 2}, // CARA B
		{3, 0, 2}, // CARA C
		{3, 1, 0}  // CARA D
	};

	// inicializar la tabla de colores:

	colors = {
<<<<<<< HEAD
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}};

	colors1 = {
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f}};

	colors2 = {
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f}};
=======
		{50.0f, 0.0f, 0.0f},
		{50.0f, 0.0f, 0.0f},
		{50.0f, 0.0f, 0.0f},
		{50.0f, 0.0f, 0.0f}};

	colors1 = {
		{0.0f, 50.0f, 0.0f},
		{0.0f, 50.0f, 0.0f},
		{0.0f, 50.0f, 0.0f},
		{0.0f, 50.0f, 0.0f}};

	colors2 = {
		{0.0f, 0.0f, 50.0f},
		{0.0f, 0.0f, 50.0f},
		{0.0f, 0.0f, 50.0f},
		{0.0f, 0.0f, 50.0f}};
>>>>>>> master
}
