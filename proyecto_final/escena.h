#ifndef _ESCENA_H
#define _ESCENA_H

#include <map>
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
#include "paralelepipedo.h"
#include "cuadro.h"
#include "camara.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELANIMACIONES,
    SELCAMARA
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
        bool animar = false;
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
        Paralelepipedo *paredes = nullptr;
        Cuadro *cuadro = nullptr;

        Cubo *cubo_aux = nullptr;
        // LUCES
        LuzDireccional *luzDireccional = nullptr;
        LuzPosicional *luzPosicional = nullptr;

        // CAMARAS
        Camara camara_ort;
        Camara camara_pers;
        Camara camara_aux;
        int camaraActiva = 0;
        std::vector<Camara> camaras = {};
        int seleccionado = -1;
    public:
        Escena();
        void inicializar(int UI_window_width, int UI_window_height);
        void redimensionar(int newWidth, int newHeight);

        // Dibujar
        void dibujar();
        void pintar(modes modo);

        // Interacción con la escena
        bool teclaPulsada(unsigned char Tecla1, int x, int y);
        void teclaEspecial(int Tecla1, int x, int y);
        void animarVentilador();

        // CAMARAS
        void moverCamara(int x, int y);
        void zoomPositivo(float zoom);
        void zoomNegativo(float zoom);
        void escogerColor(int x, int y);

        void procesarPixel(unsigned char*);
};
#endif
