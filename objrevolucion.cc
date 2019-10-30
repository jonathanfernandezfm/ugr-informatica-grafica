#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <math.h>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   this->vertex = {};
   this->faces = {};
   ply::read_vertices(archivo, this->vertex);
   this->crearMalla(this->vertex, num_instancias, true);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas) {
   int size = perfil_original.size(); // M
   Tupla3f max, min;
   int northi, southi;
   bool north=false, south=false;

   max = this->vertex[0];
   min = this->vertex[0];
   for(int i=1; i<size; i++){
      if(this->vertex[i][1] > max[1]){
         max = this->vertex[i];
         northi = i;
      }
      if(this->vertex[i][1] < min[1]){
         min = this->vertex[i];
         southi = i;
      }
   }

   if(max[1]==0){
      north = true;
      this->vertex.erase(this->vertex.begin()+northi);
   }

   if(min[1]==0){
      south = true;
      this->vertex.erase(this->vertex.begin()+southi);
   }

   for(int i=0; i<size; i++){
      std::cout << this->vertex[i] << std::endl;
   }

   //VERTICES
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<size; j++){
         this->vertex.push_back(this->rotateX(this->vertex[j], 2*M_PI*i/num_instancias));
      }
   }

   // CARAS
   for(int i=0; i<num_instancias; i++){
      for(int j=0; j<size-1; j++){
         this->faces.push_back({
            size*i+j,
            size*((i+1)%num_instancias)+j,
            size*((i+1)%num_instancias)+j+1
         });
         this->faces.push_back({
            size*i+j,
            size*((i+1)%num_instancias)+j+1,
            size*i+j+1
         });
      }
   }

}

Tupla3f ObjRevolucion::rotateX(Tupla3f vertice, double angle){
   Tupla3f out={
      vertice[0]*cos(angle)+vertice[2]*sin(angle),
      vertice[1],
      vertice[0]*(-sin(angle))+vertice[2]*cos(angle)
   };

   return out;
}

