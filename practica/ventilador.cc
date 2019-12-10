#include "aux.h"
#include "malla.h"
#include "ventilador.h"

Ventilador::Ventilador()
{
    aspa1 = new Paralelepipedo(5, 1, 0.1);
    aspa2 = new Paralelepipedo(5, 1, 0.1);
    aspa3 = new Paralelepipedo(5, 1, 0.1);
    aspa4 = new Paralelepipedo(5, 1, 0.1);
    aspa1->setMaterial(new Material(Tupla4f( 1.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
    aspa2->setMaterial(new Material(Tupla4f( 1.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
    aspa3->setMaterial(new Material(Tupla4f( 1.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
    aspa4->setMaterial(new Material(Tupla4f( 1.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    semiesfera = new Semiesfera(50, 50, 0.75);
    semiesfera->setMaterial(new Material(Tupla4f( 0.0, 1.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    cilindro = new Cilindro(50, 50, 1, 0.25);
    cilindro->setMaterial(new Material(Tupla4f( 1.0, 0.0, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
}

void Ventilador::draw()
{
    glPushMatrix();
        glTranslatef(0, -incremento, 0);
        glPushMatrix();
            glTranslatef(0, -0.1, 0);
            glScalef(1, 1+incremento, 1);
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
            aspa1->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa2->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa3->draw(LIGHT, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(270, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa4->draw(LIGHT, false);
        glPopMatrix();
    glPopMatrix();
}

void Ventilador::girar()
{
    giro += 0.5;    
}

void Ventilador::balancear()
{
    if(movingRight) {
        balanceo += 0.1;
        if(balanceo >= 10) {
            movingRight = 0;
        }
    } else {
        balanceo -= 0.1;
        if(balanceo <= -10) {
            movingRight = 1;
        }
    }
}

void Ventilador::estirar()
{
    if(goingUp) {
        incremento += 0.001;
        if(incremento >= 1) {
            goingUp = 0;
        }
    } else {
        incremento -= 0.001;
        if(incremento <= -0.5) {
            goingUp = 1;
        }
    }
    
}
