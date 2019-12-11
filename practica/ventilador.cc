#include "aux.h"
#include "malla.h"
#include "ventilador.h"

Ventilador::Ventilador()
{
    aspa = new Paralelepipedo(5, 1, 0.1);
    aspa->setMaterial(new Material(Tupla4f( 1.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
    
    semiesfera = new Semiesfera(50, 50, 0.75);
    semiesfera->setMaterial(new Material(Tupla4f( 0.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    cilindro = new Cilindro(50, 50, 1, 0.25);
    cilindro->setMaterial(new Material(Tupla4f( 1.0, 0.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
}

void Ventilador::draw()
{
    glPushMatrix();
        glTranslatef(0, -altura, 0);
        glPushMatrix();
            glTranslatef(0, -0.1, 0);
            glScalef(1, 1+altura, 1);
            cilindro->draw(LIGHT, false);
        glPopMatrix();

        glRotatef(balanceo, 1, 0, 0);
        glRotatef(giro, 0, 1, 0);
        glTranslatef(0, -0.75, 0);

        glPushMatrix();
            glRotatef(180, 1, 0, 0);
            semiesfera->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(270, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(LIGHT, false);
        glPopMatrix();
    glPopMatrix();
}

void Ventilador::girar()
{
    giro += incrementoGiro;    
}

void Ventilador::balancear()
{
    if(movingRight) {
        balanceo += incrementoBalanceo;
        if(balanceo >= 10) {
            movingRight = 0;
        }
    } else {
        balanceo -= incrementoBalanceo;
        if(balanceo <= -10) {
            movingRight = 1;
        }
    }
}

void Ventilador::estirar()
{
    if(goingUp) {
        altura += incrementoEstirar;
        if(altura >= 1) {
            goingUp = 0;
        }
    } else {
        altura -= incrementoEstirar;
        if(altura <= -0.5) {
            goingUp = 1;
        }
    }
    
}

void Ventilador::modificarVelocidadGiro(float incremento)
{
    incrementoGiro += incremento;
    if(incrementoGiro < 0) incrementoGiro = 0;
}

void Ventilador::modificarVelocidadEstiramiento(float incremento)
{
    incrementoEstirar += incremento;
    if(incrementoEstirar < 0) incrementoEstirar = 0;
}

void Ventilador::modificarVelocidadBalanceo(float incremento)
{
    incrementoBalanceo += incremento;
    if(incrementoBalanceo < 0) incrementoBalanceo = 0;
}
