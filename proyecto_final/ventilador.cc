#include "aux.h"
#include "malla.h"
#include "ventilador.h"

Ventilador::Ventilador()
{
    aspa = new Paralelepipedo(5, 1, 0.1);
    aspa->setMaterial(new Material(Tupla4f( 1.0, 0.5, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
    
    semiesfera = new Semiesfera(50, 50, 0.75);
    semiesfera->setMaterial(new Material(Tupla4f( 0.3, 0.6, 0.3, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    semiesferaPequena = new Semiesfera(50, 50, 0.4);
    semiesferaPequena->setMaterial(new Material(Tupla4f( 0.3, 0.6, 0.3, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    cilindro = new Cilindro(50, 50, 1, 0.25);
    cilindro->setMaterial(new Material(Tupla4f( 0.7, 0.6, 0.3, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

    luzVentilador = new LuzPosicional(
      {0.0, 0.0, 0.0},
      GL_LIGHT3,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );
}

void Ventilador::draw(modes mode)
{
    glPushMatrix();
        glPushMatrix();
            semiesferaPequena->draw(mode, false);
        glPopMatrix();

        glTranslatef(0, -1-altura, 0);
        glPushMatrix();
            glTranslatef(0, -0.1, 0);
            glScalef(1, 1+altura, 1);
            cilindro->draw(mode, false);
        glPopMatrix();

        glRotatef(balanceoAlpha, 1, 0, 0);
        glRotatef(balanceoBeta, 0, 1, 0);
        glRotatef(giro, 0, 1, 0);
        glTranslatef(0, -0.75, 0);

        glPushMatrix();
            glRotatef(180, 1, 0, 0);
            semiesfera->draw(mode, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(mode, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(mode, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(180, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(mode, false);
        glPopMatrix();
        glPushMatrix();
            glRotatef(270, 0, 1, 0);
            glRotatef(10, 1, 0, 0);
            glTranslatef(0.1, 0.15, -0.5);
            aspa->draw(mode, false);
        glPopMatrix();
        
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -3, 0.0);
        if(luz)
            luzVentilador->activar(); 
        else
            luzVentilador->desactivar(); 
    glPopMatrix();
}

void Ventilador::girar()
{
    giro += incrementoGiro;    
}

void Ventilador::balancear()
{
    if(movingRight) {
        balanceoAlpha += incrementoBalanceo;
        balanceoBeta += incrementoBalanceo;
        if(balanceoAlpha >= 10) {
            movingRight = 0;
        }
    } else {
        balanceoAlpha -= incrementoBalanceo;
        balanceoBeta -= incrementoBalanceo;
        if(balanceoAlpha <= -10) {
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
