#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara
{
    public:
        Camara( );
        Camara( Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, int tipo );
        void setObserver();
        void setObserver(float angulo_x, float angulo_y);
        void setProyeccion(float left, float right, float bottom, float top, float near, float far);
        void mover(float x, float y, float z);
        void zoom(float factor);

        void rotarXExaminar(float angulo_x, float angulo_y);
        void rotarYExaminar(float angulo_x, float angulo_y);
        void rotarZExaminar(float angulo_x, float angulo_y);
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        void rotarZFirstPerson(float angle);

        void setAt(Tupla3f at);
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;

        int tipo;
        float left, right, bottom, top, near, far;
        float radio;

        
        
} ;

#endif
