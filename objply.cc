#include "objply.h"
#include "ply_reader.h"

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
// Lee la lista de vertices y caras
	ply::read( nombre_archivo, this->vertex, this->faces );

	//this->generarNormales();

	for(int i=0; i<this->vertex.size(); i++){
		colors.push_back({1.0f, 0.0f, 0.0f});
		colors1.push_back({0.0f, 1.0f, 0.0f});
		colors2.push_back({0.0f, 0.0f, 1.0f});
	}
}


