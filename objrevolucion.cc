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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool conTapas) {
   this->vertex = {};
   this->faces = {};
   ply::read_vertices(archivo, this->vertex);
   this->crearMalla(this->vertex, num_instancias, conTapas);
}

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool conTapas, int eje) {
   this->vertex = perfil;
   this->faces = {};

   this->crearMalla(this->vertex, num_instancias, conTapas, eje);
}

// *****************************************************************************
// creacion de la malla a partir de un perfil

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas, int eje) {
   int size = perfil_original.size(); // M
   Tupla3f max, min;
   int northi = 0, southi = 0;
   bool north=false, south=false, order_down=false;

   /* ======================================================================*/
   if ( eje == 0 ) {

      if(perfil_original[0][0] > perfil_original[perfil_original.size()-1][0]){
         order_down = true;
      }

      max = perfil_original[0];
      min = perfil_original[0];
      for(int i=1; i<perfil_original.size(); i++){
         if(perfil_original[i][0] > max[0]){
            max = perfil_original[i];
            northi = i;
         }
         if(perfil_original[i][0] < min[0]){
            min = perfil_original[i];
            southi = i;
         }
      }

      if(max[1]==0 && max[2]==0){ // Y = 0?
         north = true;
         perfil_original.erase(perfil_original.begin()+northi);
      }

      if(min[1]==0 && max[2]==0){ // Y = 0?
         south = true;
         perfil_original.erase(perfil_original.begin()+southi);
      }

      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<perfil_original.size(); j++){
            this->vertex.push_back(this->rotateX(perfil_original[j], 2*M_PI*i/num_instancias));
         }
      }

      size = perfil_original.size();
      this->faces.clear();

      // CARAS
      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<size-1; j++){
            if(order_down){
               this->faces.push_back({
                  size*i+j,
                  size*((i+1)%num_instancias)+j+1,
                  size*((i+1)%num_instancias)+j
               });
               this->faces.push_back({
                  size*i+j,
                  size*i+j+1,
                  size*((i+1)%num_instancias)+j+1
               });
            }else{
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

      if(conTapas){
         // INSERTAMOS POLO SUR Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MAYOR A MENOR
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  min[0],
                  0.0f,
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  max[0],
                  0.0f,
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }
         }else{
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  min[0],
                  0.0f,
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  max[0],
                  0.0f,
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }
         }
      }

   /* ======================================================================*/
   } else if ( eje == 1 ) {
      if(perfil_original[0][1] > perfil_original[perfil_original.size()-1][1]){
         order_down = true;
      }

      max = perfil_original[0];
      min = perfil_original[0];
      for(int i=1; i<perfil_original.size(); i++){
         if(perfil_original[i][1] > max[1]){
            max = perfil_original[i];
            northi = i;
         }
         if(perfil_original[i][1] < min[1]){
            min = perfil_original[i];
            southi = i;
         }
      }

      if(max[0]==0 && max[2]==0){ // x = 0?
         north = true;
         perfil_original.erase(perfil_original.begin()+northi);
      }

      if(min[0]==0 && max[2]==0){ // x = 0?
         south = true;
         perfil_original.erase(perfil_original.begin()+southi);
      }

      // VERTEX
      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<perfil_original.size(); j++){
            this->vertex.push_back(this->rotateY(perfil_original[j], 2*M_PI*i/num_instancias));
         }
      }

      size = perfil_original.size();
      this->faces.clear();

      // CARAS
      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<size-1; j++){
            if(order_down){
               this->faces.push_back({
                  size*i+j,
                  size*((i+1)%num_instancias)+j+1,
                  size*((i+1)%num_instancias)+j
               });
               this->faces.push_back({
                  size*i+j,
                  size*i+j+1,
                  size*((i+1)%num_instancias)+j+1
               });
            }else{
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

      if(conTapas){
         // INSERTAMOS POLO SUR Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MAYOR A MENOR
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  0.0,
                  min[1],
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0,
                  max[1],
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }
         }else{
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  0.0,
                  min[1],
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0,
                  max[1],
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }
         }
      }

   /* ======================================================================*/
   } else if ( eje == 2 ) {
      if(this->vertex[0][2] > this->vertex[this->vertex.size()-1][2]){
         order_down = true;
      }

      max = this->vertex[0];
      min = this->vertex[0];
      for(int i=1; i<this->vertex.size(); i++){
         if(this->vertex[i][2] > max[2]){
            max = this->vertex[i];
            northi = i;
         }
         if(this->vertex[i][2] < min[2]){
            min = this->vertex[i];
            southi = i;
         }
      }

      if(max[0]==0 && max[1]==0){ // x = 0?
         north = true;
         this->vertex.erase(this->vertex.begin()+northi);
      }

      if(min[0]==0 && max[1]==0){ // x = 0?
         south = true;
         this->vertex.erase(this->vertex.begin()+southi);
      }

      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<perfil_original.size(); j++){
            this->vertex.push_back(this->rotateZ(this->vertex[j], 2*M_PI*i/num_instancias));
         }
      }

      size = perfil_original.size();
      this->faces.clear();

      // CARAS
      for(int i=0; i<num_instancias; i++){
         for(int j=0; j<size-1; j++){
            if(order_down){
               this->faces.push_back({
                  size*i+j,
                  size*((i+1)%num_instancias)+j+1,
                  size*((i+1)%num_instancias)+j
               });
               this->faces.push_back({
                  size*i+j,
                  size*i+j+1,
                  size*((i+1)%num_instancias)+j+1
               });
            }else{
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

      if(conTapas){
         // INSERTAMOS POLO SUR Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MAYOR A MENOR
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  0.0f,
                  min[1],
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0f,
                  max[1],
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }
         }else{
            if(south){
               this->vertex.push_back(min);
            }else{
               this->vertex.push_back({
                  0.0f,
                  min[1],
                  min[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*((i+1)%num_instancias),
                  size*(i)
               });
            }

            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0f,
                  max[1],
                  max[2]
               });
            }

            for(int i=0; i<num_instancias; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*((i+1)%num_instancias)+size-1
               });
            }
         }
      }
   }

   // COLORES
   for(int i=0; i<this->vertex.size(); i++){
      colors.push_back({1.0f, 0.0f, 0.0f});
      colors1.push_back({0.0f, 1.0f, 0.0f});
      colors2.push_back({0.0f, 0.0f, 1.0f});
   }
}

Tupla3f ObjRevolucion::rotateX(Tupla3f vertice, double angle){
   Tupla3f out={
      vertice[0],
      vertice[1]*(cos(angle))+vertice[2]*(-sin(angle)),
      vertice[1]*(sin(angle))+vertice[2]*cos(angle)
   };

   return out;
}

Tupla3f ObjRevolucion::rotateY(Tupla3f vertice, double angle){
   Tupla3f out={
      vertice[0]*cos(angle)+vertice[2]*sin(angle),
      vertice[1],
      vertice[0]*(-sin(angle))+vertice[2]*cos(angle)
   };

   return out;
}

Tupla3f ObjRevolucion::rotateZ(Tupla3f vertice, double angle){
   Tupla3f out={
      vertice[0]*cos(angle)+vertice[1]*(-sin(angle)),
      vertice[0]*sin(angle)+vertice[1]*cos(angle),
      vertice[2]
   };

   return out;
}

