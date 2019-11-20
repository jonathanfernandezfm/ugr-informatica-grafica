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
   this->crearMalla(this->vertex, num_instancias, conTapas);

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

      if(this->vertex[0][0] > this->vertex[this->vertex.size()-1][0]){
         order_down = true;
      }

      max = this->vertex[0];
      min = this->vertex[0];
      for(int i=1; i<this->vertex.size(); i++){
         if(this->vertex[i][0] > max[0]){
            max = this->vertex[i];
            northi = i;
         }
         if(this->vertex[i][0] < min[0]){
            min = this->vertex[i];
            southi = i;
         }
      }

      if(max[1]==0 && max[2]==0){ // Y = 0?
         north = true;
         this->vertex.erase(this->vertex.begin()+northi);
      }

      if(min[1]==0 && max[2]==0){ // Y = 0?
         south = true;
         this->vertex.erase(this->vertex.begin()+southi);
      }

      size = this->vertex.size(); // NEW M

      for(int i=1; i<=num_instancias; i++){
         //std::cout << "perfil " << i << std::endl;
         for(int j=0; j<size; j++){
            this->vertex.push_back(this->rotateX(this->vertex[j], 2*M_PI*i/num_instancias));
         }
      }

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

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*i-1
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
                  size*(i+1),
                  size*(i)
               });
            }
         }
         

         // INSERTAMOS POLO NORTE Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MAYOR A MENOR
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
                  size*(i),
                  size*(i+1)
               });
            }
         }else{
            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  max[0],
                  0.0f,
                  max[2]
               });
            }

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*i-1,
                  size*(i+1)-1
               });
            }
         }

         // COLORES
         for(int i=0; i<this->vertex.size(); i++){
            colors.push_back({1.0f, 0.0f, 0.0f});
            colors1.push_back({0.0f, 1.0f, 0.0f});
            colors2.push_back({0.0f, 0.0f, 1.0f});
         }
      }
   /* ======================================================================*/
   } else if ( eje == 1 ) {
      if(this->vertex[0][1] > this->vertex[this->vertex.size()-1][1]){
         order_down = true;
      }

      max = this->vertex[0];
      min = this->vertex[0];
      for(int i=1; i<this->vertex.size(); i++){
         if(this->vertex[i][1] > max[1]){
            max = this->vertex[i];
            northi = i;
         }
         if(this->vertex[i][1] < min[1]){
            min = this->vertex[i];
            southi = i;
         }
      }

      if(max[0]==0 && max[2]==0){ // x = 0?
         north = true;
         this->vertex.erase(this->vertex.begin()+northi);
      }

      if(min[0]==0 && max[2]==0){ // x = 0?
         south = true;
         this->vertex.erase(this->vertex.begin()+southi);
      }

      size = this->vertex.size(); // NEW M

      for(int i=1; i<=num_instancias; i++){
         //std::cout << "perfil " << i << std::endl;
         for(int j=0; j<size; j++){
            this->vertex.push_back(this->rotateY(this->vertex[j], 2*M_PI*i/num_instancias));
         }
      }

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

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*i-1
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
                  size*(i+1),
                  size*(i)
               });
            }
         }
         

         // INSERTAMOS POLO NORTE Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MAYOR A MENOR
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
                  size*(i),
                  size*(i+1)
               });
            }
         }else{
            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0,
                  max[1],
                  max[2]
               });
            }

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*i-1,
                  size*(i+1)-1
               });
            }
         }

         // COLORES
         for(int i=0; i<this->vertex.size(); i++){
            colors.push_back({1.0f, 0.0f, 0.0f});
            colors1.push_back({0.0f, 1.0f, 0.0f});
            colors2.push_back({0.0f, 0.0f, 1.0f});
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

      size = this->vertex.size(); // NEW M

      for(int i=1; i<=num_instancias; i++){
         //std::cout << "perfil " << i << std::endl;
         for(int j=0; j<size; j++){
            this->vertex.push_back(this->rotateZ(this->vertex[j], 2*M_PI*i/num_instancias));
         }
      }

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

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*(i+1)-1,
                  size*i-1
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
                  size*(i+1),
                  size*(i)
               });
            }
         }
         

         // INSERTAMOS POLO NORTE Y CREAMOS SUS CARAS
         if(order_down){ // SI EL PERFIL ES DE MENOR A MAYOR
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
                  size*(i),
                  size*(i+1)
               });
            }
         }else{
            if(north){
               this->vertex.push_back(max);
            }else{
               this->vertex.push_back({
                  0.0f,
                  max[1],
                  max[2]
               });
            }

            for(int i=1; i<num_instancias+1; i++){
               this->faces.push_back({
                  this->vertex.size()-1,
                  size*i-1,
                  size*(i+1)-1
               });
            }
         }

         // COLORES
         for(int i=0; i<this->vertex.size(); i++){
            colors.push_back({1.0f, 0.0f, 0.0f});
            colors1.push_back({0.0f, 1.0f, 0.0f});
            colors2.push_back({0.0f, 0.0f, 1.0f});
         }
      }
   }

   // for(int i=0; i<this->vertex.size(); i++){
   //    std::cout << this->vertex[i] << std::endl;
   // }

   

   // PRINTF VERTICES
   // for(int i=0; i<this->vertex.size(); i++){
   //    std::cout << this->vertex[i] << std::endl;
   // }

   // PRINTF CARAS
   // for(int i=0; i<this->faces.size(); i++){
   //    std::cout << this->faces[i] << std::endl;
   // }
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

