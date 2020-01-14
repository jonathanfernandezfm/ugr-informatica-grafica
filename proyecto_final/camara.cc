#include "aux.h"
#include "camara.h"

Camara::Camara(){ }

Camara::Camara( Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, int tipo )
{
    this->eye = eye;
    this->at = at;
    this->up = up;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
    this->tipo = tipo;

    this->radio=sqrt(pow(eye[0]-at[0],2)+pow(eye[1]-at[1],2)+pow(eye[2]-at[2],2));
}

void Camara::rotarXExaminar(float angulo_x, float angulo_y)
{
    float x = sin((angulo_y*M_PI)/180.0) * cos((angulo_x*M_PI)/180.0)*radio;
    eye[0] = x;
}

void Camara::rotarYExaminar(float angulo_x, float angulo_y)
{
    float y = sin((angulo_x*M_PI)/180.0)*radio;
    eye[1] = y;
}

void Camara::rotarZExaminar(float angulo_x, float angulo_y)
{
    float z = cos((angulo_y*M_PI)/180.0) * cos((angulo_x*M_PI)/180.0)*radio;
    eye[2] = z;
}

void Camara::setObserver()
{
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
}

void Camara::setObserver(float angulo_y, float angulo_x)
{
    float up_temp=1.0;

    int ang_x = angulo_x;
    int ang_y = angulo_y;
    ang_x %=360;
    ang_y %=360;

    rotarXExaminar(angulo_x, angulo_y);
    rotarYExaminar(angulo_x, angulo_y);
    rotarZExaminar(angulo_x, angulo_y);

    if(ang_x<-90 && ang_x>=-270 or ang_x>90 && ang_x<=270){
        up_temp = -1.0;
    }else{
        up_temp = 1.0;
    }

    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up_temp, up[2]);
}

void Camara::setProyeccion(float left, float right, float bottom, float top, float near, float far)
{
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if(tipo==0){ //Camara Ortogonal
        glOrtho(left, right, bottom, top, near, far);
    }else if(tipo==1){  //Camara perspectiva
        glFrustum(left, right, bottom, top, near, far);
    }

    glMatrixMode( GL_MODELVIEW );
}

void Camara::setAt(Tupla3f at)
{
    this->at = at;
}

void Camara::mover(float x, float y, float z)
{

}

void Camara::zoom(float factor)
{

}