#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz_direccional.h"
#include "luz_posicional.h"
#include "enums.h"
#include "semiesfera.h"
#include "ventilador.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELANIMACIONES
} menu;

class Escena
{
    private:
        // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

        // variables que definen la posicion de la camara en coordenadas polares
        GLfloat Observer_distance;
        GLfloat Observer_angle_x;
        GLfloat Observer_angle_y;

        // variables que controlan la ventana y la transformacion de perspectiva
        GLfloat Width, Height, Front_plane, Back_plane;

        // Transformación de cámara
        void change_projection(const float ratio_xy);
        void change_observer();

        void clear_window();

        bool showCubo = false;
        bool showTetraedro = false;
        bool showRevolucion = false;
        bool showPly = false;
        bool points = false, lines = false, solid = false, chess = false, iluminacion = false;
        bool panelIluminacion = false;
        std::vector<bool> luces = {false, false, false, false, false, false, false};
        LuzPosicional *luz1 = nullptr, *luz3 = nullptr, *luz4 = nullptr, *luz5 = nullptr, *luz6 = nullptr, *luz7 = nullptr;
        LuzDireccional *luz2 = nullptr;
        bool movingAlpha = false, movingBeta = false;
        float alphaAngle = 0, betaAngle = 0;
        bool dibujado_vbo = false;
        bool animar = true;
        bool modificandoGiro = false, modificandoBalanceo = false, modificandoEstiramiento = false;

        menu modoMenu = NADA;
        modes modoDraw = SOLID;

        // Objetos de la escena
        Ejes ejes;
        Cubo *cubo = nullptr;           // es importante inicializarlo a 'nullptr'
        Tetraedro *tetraedro = nullptr; // es importante inicializarlo a 'nullptr'
        ObjPLY *ply = nullptr;
        ObjRevolucion *objrev = nullptr, *objrev1 = nullptr;
        Cilindro *cilindro = nullptr;
        Cono *cono = nullptr;
        Esfera *esfera = nullptr;
        Semiesfera *semiesfera = nullptr;
        Ventilador *ventilador = nullptr;

        LuzDireccional *luzDireccional = nullptr;
        LuzPosicional *luzPosicional = nullptr;

    public:
        Escena();
        void inicializar(int UI_window_width, int UI_window_height);
        void redimensionar(int newWidth, int newHeight);

        // Dibujar
        void dibujar();

        // Interacción con la escena
        bool teclaPulsada(unsigned char Tecla1, int x, int y);
        void teclaEspecial(int Tecla1, int x, int y);
        void animarVentilador();
};
#endif
