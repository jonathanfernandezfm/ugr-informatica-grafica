#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->vertex, this->faces );

   for(int i=0; i<this->vertex.size(); i++){
      colors.push_back({50.0f, 0.0f, 0.0f});
      colors1.push_back({0.0f, 50.0f, 0.0f});
      colors2.push_back({0.0f, 0.0f, 50.0f});
   }
}


