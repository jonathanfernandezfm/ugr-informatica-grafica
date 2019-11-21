// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "enums.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
public:
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(modes mode);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(modes mode);

   void draw_ModoSmooth();

   void draw_ModoFlat();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(modes mode, bool dibujado_vbo);

   GLuint crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram);

   void generarNormales();

protected:
   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

   GLuint id_vbo_ver, id_vbo_faces, id_vbo_colors, id_vbo_colors1, id_vbo_colors2, 
         id_vbo_colorschess1, id_vbo_colorschess2, id_vbo_faceschess1, id_vbo_faceschess2;

   std::vector<Tupla3f> vertex; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> faces;  // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> colors;
   std::vector<Tupla3f> colors1;
   std::vector<Tupla3f> colors2;
   std::vector<Tupla3f> normalsf;
   std::vector<Tupla3f> normalsv;
};

#endif
