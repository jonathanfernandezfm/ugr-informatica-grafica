#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(modes mode)
{
	std::vector<Tupla3i> faceschess1, faceschess2;
	int cont = 0;

	if(mode == CHESS){
		for(Tupla3i tupla: faces){
			if(cont%2==0){
				faceschess1.push_back(tupla);
			}else{
				faceschess2.push_back(tupla);
			}
			cont++;
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertex.data());
		glEnableClientState(GL_COLOR_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, colors1.data());
		glDrawElements(GL_TRIANGLES, faceschess1.size() * 3, GL_UNSIGNED_INT, faceschess1.data());
		glColorPointer(3, GL_FLOAT, 0, colors2.data());
		glDrawElements(GL_TRIANGLES, faceschess2.size() * 3, GL_UNSIGNED_INT, faceschess2.data());

		// glColorPointer(3, GL_FLOAT, 0, colors1.data());
		// glDrawElements(GL_TRIANGLES, faces.size()/2 * 3, GL_UNSIGNED_INT, faces.data());
		// glColorPointer(3, GL_FLOAT, 0, colors2.data());
		// glDrawElements(GL_TRIANGLES, faces.size()/2 * 3, GL_UNSIGNED_INT, faces.data()+faces.size()/2);
		glDisableClientState(GL_VERTEX_ARRAY);
	}else{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertex.data());
		glEnableClientState(GL_COLOR_ARRAY);

		switch (mode)
		{
		case SOLID:
			glColorPointer(3, GL_FLOAT, 0, colors.data());
			break;
		case LINES:
			glColorPointer(3, GL_FLOAT, 0, colors1.data());
			break;
		case POINTS:
			glColorPointer(3, GL_FLOAT, 0, colors2.data());
			break;
		default:
			break;
		}

		glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, faces.data());
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(modes mode)
{
    if (id_vbo_ver == 0)
        id_vbo_ver = crearVBO(GL_ARRAY_BUFFER, 3 * vertex.size() * sizeof(float), vertex.data());
    if (id_vbo_faces == 0)
        id_vbo_faces = crearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * faces.size() * sizeof(unsigned int), faces.data());
    if (id_vbo_colors == 0)
        id_vbo_colors = crearVBO(GL_ARRAY_BUFFER, 3 * colors.size() * sizeof(float), colors.data());
    if (id_vbo_colors1 == 0)
        id_vbo_colors1 = crearVBO(GL_ARRAY_BUFFER, 3 * colors1.size() * sizeof(float), colors1.data());
    if (id_vbo_colors2 == 0)
        id_vbo_colors2 = crearVBO(GL_ARRAY_BUFFER, 3 * colors2.size() * sizeof(float), colors2.data());


    /* VERTICES */
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    /* COLORES */
	if(mode == SOLID) {
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colors);
	} else if(mode == POINTS) {
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colors1);
	} else if(mode == LINES) {
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colors2);
	} else if(mode == CHESS) {
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colors1);
	}
	glColorPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* CARAS */
	
	if(mode == CHESS){
		std::vector<Tupla3i> faceschess1, faceschess2;
		int cont = 0;

		for(Tupla3i tupla: faces){
			if(cont%2==0){
				faceschess1.push_back(tupla);
			}else{
				faceschess2.push_back(tupla);
			}
			cont++;
		}

		if (id_vbo_faceschess1 == 0)
        	id_vbo_faceschess1 = crearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * faceschess1.size() * sizeof(unsigned int), faceschess1.data());
		if (id_vbo_faceschess2 == 0)
        	id_vbo_faceschess2 = crearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * faceschess2.size() * sizeof(unsigned int), faceschess2.data());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_faceschess1);
		glDrawElements(GL_TRIANGLES, 3 * faceschess1.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colors2);
		glColorPointer(3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_faceschess2);
		glDrawElements(GL_TRIANGLES, 3 * faceschess2.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
	} else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_faces);
		glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
	}   
}

void Malla3D::draw_ModoSmooth()
{
	m->aplicar();

	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex.data());
	// glEnableClientState(GL_COLOR_ARRAY);
	// glColorPointer(3, GL_FLOAT, 0, colors.data());
	glEnableClientState( GL_NORMAL_ARRAY );
	glNormalPointer(GL_FLOAT, 0, normalsv.data() );
	glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, faces.data());

	// glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Malla3D::draw_ModoFlat()
{

}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(modes mode, bool dibujado_vbo)
{
	m = new Material(Tupla4f( 0.8, 0.6, 0.8, 1.0), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(1.0, 0.0, 0.5, 1.0), 128*0.6);
	draw_ModoSmooth();
	// if(dibujado_vbo){
	// 	draw_ModoDiferido(mode);
	// }else{
	// 	draw_ModoInmediato(mode);
	// }
	
}

GLuint Malla3D::crearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(tipo_vbo, id_vbo);
    glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
    glBindBuffer(tipo_vbo, 0);

    return id_vbo;
}

void Malla3D::generarNormales() 
{
	Tupla3f vector1, vector2;
	Tupla3f prod;
	float module=0;

	for(int i=0; i<faces.size(); i++){
		vector1 = vertex[faces[i][1]] - vertex[faces[i][0]]; // q-p
		vector2 = vertex[faces[i][2]] - vertex[faces[i][0]]; // r-p

		prod = vector1.cross(vector2).normalized();

		normalsf.push_back(prod);
	}

	normalsv.resize(vertex.size());
	for(int i=0; i<normalsv.size(); i++){
		normalsv[i]={0,0,0};
	}

	for(int i=0; i<faces.size(); i++){
		normalsv[faces[i][0]] = normalsv[faces[i][0]] + normalsf[i];
		normalsv[faces[i][1]] = normalsv[faces[i][1]] + normalsf[i];
		normalsv[faces[i][2]] = normalsv[faces[i][2]] + normalsf[i];
	}

	for(int i=0; i<normalsv.size(); i++){
		normalsv[i] = normalsv[i].normalized();
	}
}
