#include "aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "enums.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane = 0.1;
   Back_plane = 2000.0;
   Observer_distance = 2.0;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;
   ejes.changeAxisSize(5000);
   cubo = new Cubo();
   cubo->setMaterial(new Material(Tupla4f( 1.0, 0.0, 0.0, 1.0), Tupla4f(1.0, 0.0, 0.0, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
   // cubo->setTextura(new Textura("assets/text-madera.jpg"));
   tetraedro = new Tetraedro();
   ply = new ObjPLY("./plys/beethoven.ply");
   objrev = new ObjRevolucion("./plys/peon.ply", 100, true);
   objrev->setMaterial(new Material(Tupla4f( 1, 1, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
   objrev1 = new ObjRevolucion("./plys/peon.ply", 100, true);
   objrev1->setMaterial(new Material(Tupla4f( 1.0, 0.2, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
   semiesfera = new Semiesfera(100, 100, 1);
   semiesfera->setMaterial(new Material(Tupla4f( 1.0, 0.2, 0.1, 0.1), Tupla4f(0.0, 0.0, 1, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));
   ventilador = new Ventilador();

   paredes = new Paralelepipedo(50, 50, 10, true);
   paredes->setMaterial(new Material(Tupla4f( 1, 0.8, 0.8, 1.0), Tupla4f(0.0, 0.0, 0.0, 0.0), Tupla4f(0.0, 0.0, 0.0, 0.0), 128*0.6));

   // std::vector<Tupla3f> vector;

   // // y
   // vector.push_back({0.0f, 1.0f, 0.0f});
   // vector.push_back({1.0f, 1.0f, 0.0f});

   // // z
   // vector.push_back({1.0f, 0.0f, 0.0f});
   // vector.push_back({1.0f, 0.0f, 1.0f}); 

   // // z con polos
   // vector.push_back({0.0f, 0.0f, -2.0f});
   // vector.push_back({1.0f, 0.0f, -1.0f}); 
   // vector.push_back({1.0f, 0.0f, 0.0f}); 
   // vector.push_back({0.0f, 0.0f, 1.0f}); 

   // objrev = new ObjRevolucion(vector, 10, true, 2);
   
   cilindro = new Cilindro(10, 10, 1, 1);
   cono = new Cono(10, 10, 1, 1);
   esfera = new Esfera(100, 100, 1);


   luz1 = new LuzPosicional(
      {2.0, 2.0, 2.0},
      GL_LIGHT1,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );

   luz2 = new LuzDireccional(
      {20*M_PI/180, 20*M_PI/180},
      GL_LIGHT2,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );

   // LUZ3 VENTILADOR

   luz4 = new LuzPosicional(
      {2.0, 2.0, 2.0},
      GL_LIGHT4,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );

   luz5 = new LuzPosicional(
      {2.0, 2.0, 2.0},
      GL_LIGHT5,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );

   luz6 = new LuzPosicional(
      {2.0, 2.0, 2.0},
      GL_LIGHT6,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );

   luz7 = new LuzPosicional(
      {2.0, 2.0, 2.0},
      GL_LIGHT7,
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 1.0f, 1.0f}
   );
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
   glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
   glEnable(GL_CULL_FACE);  // Habilitar CULL_FACE
   glEnable(GL_NORMALIZE); // Habilitar Normalizacion

   Width = UI_window_width / 10;
   Height = UI_window_height / 10;

   change_projection(float(UI_window_width) / float(UI_window_height));
   glViewport(0, 0, UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();
   glLineWidth(1);
   ejes.draw();
   
   // luzDireccional->activar();
   // luzPosicional->activar();

   // ******** PR3 **************
   
   // ******** PR3 **************

   // ******** PR4 **************
   // glPolygonMode(GL_FRONT, GL_FILL);
   
   // cubo->draw(SOLID, dibujado_vbo);

   // ******** PR4 **************
   
   if(iluminacion){
      //glEnable(GL_LIGHT0);
      if(luces[0]) luz1->activar(); else luz1->desactivar();
      if(luces[1]) luz2->activar(); else luz2->desactivar();
      if(luces[2]) ventilador->luzVentilador->activar(); else ventilador->luzVentilador->desactivar();
      if(luces[3]) luz4->activar(); else luz4->desactivar();
      if(luces[4]) luz5->activar(); else luz5->desactivar(); 
      if(luces[5]) luz6->activar(); else luz6->desactivar();
      if(luces[6]) luz7->activar(); else luz7->desactivar();

      pintar(LIGHT);      
   } else {
      if(chess){
         pintar(CHESS);
      }else{
         if (points){
            pintar(POINTS);
         }
         if (solid){
            pintar(SOLID);
         }
         if (lines){
            pintar(LINES);
         }
      }
   }
}

void Escena::pintar(modes modo)
{
   switch(modo){
      case CHESS:
         glPolygonMode(GL_FRONT, GL_FILL);
         break;
      case SOLID:
         glPolygonMode(GL_FRONT, GL_FILL);
         break;
      case POINTS:
         glPointSize(5);
         glPolygonMode(GL_FRONT, GL_POINT);
         break;
      case LINES:
         glLineWidth(3);
         glPolygonMode(GL_FRONT, GL_LINE);
         break;
      case LIGHT:
         glPolygonMode(GL_FRONT, GL_FILL);
         break;
      default:
         break;
   }

   glPushMatrix();
      glTranslatef(-25, 0, -25);
      paredes->draw(modo, dibujado_vbo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0, 10, 0);
      ventilador->draw(modo);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(4, 1.4, 0);
      objrev->draw(modo, dibujado_vbo);
      glTranslatef(2, 0, 0);
      objrev1->draw(modo, dibujado_vbo);
   glPopMatrix();
   
   if(showTetraedro)
      tetraedro->draw(modo, dibujado_vbo);
   glPushMatrix();
   glTranslatef(2, 0, 0);
   if(showCubo)
      cubo->draw(modo, dibujado_vbo);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-3,0,0);
   if(showPly)
      ply->draw(modo, dibujado_vbo);
   glPopMatrix();
   
   if(showRevolucion){
      glPushMatrix();
         glTranslatef(4,0,0);
         objrev->draw(modo, dibujado_vbo);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,2);
         cilindro->draw(modo, dibujado_vbo);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0,0,4);
         cono->draw(modo, dibujado_vbo);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(2,0,2);
         esfera->draw(modo, dibujado_vbo);
      glPopMatrix();
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
   using namespace std;
   bool salir = false;
   string clear = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   string menuObjeto = "***SELECCION DE OBJETO***\n\t'C': Cubo\n\t'T': Tetraedro\n\t'R': Revolucion\n\t'P': PLY\n\t'Q': Salir";
   string menuVisualizacion = "***SELECCION DE MODO DE VISUALIZACION***\n\t'P': Puntos\n\t'L': Lineas\n\t'S': Solido\n\t'A': Ajedrez\n\t'I': Iluminacion\n\t'J': Animacion\n\t'+': +Velocidad\n\t'-': -Velocidad\n\t'Q': Salir";
   string menuAnimacion = "***SELECCION DE ANIMACIONES***\n\t'1': Giro Ventilador\n\t'2': Balanceo Ventilador\n\t'3': Estiramiento Ventilador\n\t'Q': Salir";
   string menuDibujado = "***SELECCION DE MODO DE DIBUJADO***\n\t'1': glDrawElements\n\t'2': VBOs\n\t'Q': Salir";
   string menuSeleccion = "***Menu***\n\t'O': SELECION DE OBJETO\n\t'V': SELECCION MODO VISUALIZACION\n\t'D': SELECCION MODO DIBUJADO\n\t'A': ANIMACIONES\n\t'Q': Salir (PROGRAMA)";
   string menuIluminacion = "***ILUMINACION***\n\t'I': Activar luces\n\t'1'...'7': Activar luz i\n\t'A': Variar alpha\n\t'B': Variar beta\n\t'Q': Salir";
   string menuAnimacionMod = "***MODIFICANDO ANIMACION***\n\t'+': + velocidad\n\t'-': - velocidad\n\t'Q': Salir";

   if (modoMenu == SELOBJETO)
   {
      switch (toupper(tecla))
      {
         case 'C':
            showCubo = !showCubo;
            cout << ">>>>>>>> CUBO: " << showCubo << " <<<<<<<<" << endl;
            break;
         case 'T':
            showTetraedro = !showTetraedro;
            cout << ">>>>>>>> TETRAEDRO: " << showTetraedro << " <<<<<<<<" << endl;
            break;
         case 'R':
            showRevolucion = !showRevolucion;
            cout << ">>>>>>>> REVOLUCION: " << showRevolucion << " <<<<<<<<" << endl;
            break;
         case 'P':
            showPly = !showPly;
            cout << ">>>>>>>> PLY: " << showPly << " <<<<<<<<" << endl;
            break;
         case 'Q':
            modoMenu = NADA;
            cout << clear;
            cout << menuSeleccion << endl;
            break;
         default:
            cout << clear;
            cout << menuObjeto << endl;
            break;
      }
   }
   else if (modoMenu == SELVISUALIZACION)
   {
      if(panelIluminacion){
         switch (toupper(tecla))
         {
            case '1':
               luces[0] = !luces[0];
               cout << ">> LUZ 1 " << luces[0] << " <<" << endl;
               break;
            case '2':
               luces[1] = !luces[1];
               cout << ">> LUZ 2 " << luces[1] << " <<" << endl;
               break;
            case '3':
               luces[2] = !luces[2];
               cout << ">> LUZ 3 " << luces[2] << " <<" << endl;
               break;
            case '4':
               luces[3] = !luces[3];
               cout << ">> LUZ 4 " << luces[3] << " <<" << endl;
               break;
            case '5':
               luces[4] = !luces[4];
               cout << ">> LUZ 5 " << luces[4] << " <<" << endl;
               break;
            case '6':
               luces[5] = !luces[5];
               cout << ">> LUZ 6 " << luces[5] << " <<" << endl;
               break;
            case '7':
               luces[6] = !luces[6];
               cout << ">> LUZ 7 " << luces[6] << " <<" << endl;
               break;
            case 'I':
               iluminacion = !iluminacion;
               cout << ">>>>>>>> ILUMINACION: " << iluminacion << "<<<<<<<<" << endl;
               break;
            case 'A':
               movingAlpha = !movingAlpha;
               movingBeta = false;
               break;
            case 'B':
               movingBeta = !movingBeta;
               movingAlpha = false;
               break;
            case 'Q':
               modoMenu = SELVISUALIZACION;
               panelIluminacion = false;
               movingAlpha = false;
               movingBeta = false;
               cout << clear;
               cout << menuVisualizacion << endl;
               break;
            default:
               cout << clear << menuIluminacion << endl;
               break;
         }
      } else {
         switch (toupper(tecla))
         {
            case 'P':
               points = !points;
               cout << ">>>>>>>> PUNTOS: " << points << "<<<<<<<<" << endl;
               break;
            case 'L':
               lines = !lines;
               cout << ">>>>>>>> LINEAS: " << lines << "<<<<<<<<" << endl;
               break;
            case 'S':
               solid = !solid;
               cout << ">>>>>>>> SOLIDO: " << solid << "<<<<<<<<" << endl;
               break;
            case 'A':
               chess = !chess;
               cout << ">>>>>>>> AJEDREZ: " << chess << "<<<<<<<<" << endl;
               break;
            case 'I':
               panelIluminacion = !panelIluminacion;
               cout << clear << menuIluminacion << endl;
               break;
            case 'J':
               animar = !animar;
               cout << clear;
               cout << menuVisualizacion << endl;
               break;
            case '+':
               ventilador->modificarVelocidadGiro(0.1);
               ventilador->modificarVelocidadBalanceo(0.1);
               ventilador->modificarVelocidadEstiramiento(0.001);
               break;
            case '-':
               ventilador->modificarVelocidadGiro(-0.1);
               ventilador->modificarVelocidadBalanceo(-0.1);
               ventilador->modificarVelocidadEstiramiento(-0.001);
               break;
            case 'Q':
               modoMenu = NADA;
               cout << clear;
               cout << menuSeleccion << endl;
               break;
            default:
               cout << clear;
               cout << menuVisualizacion << endl;
               break;
         }
      }
   }
   else if (modoMenu == SELDIBUJADO)
   {
      switch (toupper(tecla))
      {
         case '1':
            dibujado_vbo = false;
            cout << ">>>>>>>> INMEDIATO <<<<<<<<" << endl;
            break;
         case '2':
            dibujado_vbo = true;
            cout << ">>>>>>>> DIFERIDO <<<<<<<<" << endl;
            break;
         case 'Q':
            modoMenu = NADA;
            cout << clear;
            cout << menuSeleccion << endl;
            break;
         default:
            cout << clear;
            cout << menuDibujado << endl;
            break;
      }
   }
   else if (modoMenu == SELANIMACIONES)
   {
      if(modificandoGiro || modificandoBalanceo || modificandoEstiramiento) {
         switch (toupper(tecla))
         {
            case '+':
               if(modificandoGiro) ventilador->modificarVelocidadGiro(0.1);
               if(modificandoBalanceo) ventilador->modificarVelocidadBalanceo(0.1);
               if(modificandoEstiramiento) ventilador->modificarVelocidadEstiramiento(0.001);
               cout << clear;
               cout << menuAnimacionMod << endl;
               break;
            case '-':
               if(modificandoGiro) ventilador->modificarVelocidadGiro(-0.1);
               if(modificandoBalanceo) ventilador->modificarVelocidadBalanceo(-0.1);
               if(modificandoEstiramiento) ventilador->modificarVelocidadEstiramiento(-0.001);
               cout << clear;
               cout << menuAnimacionMod << endl;
               break;
            case 'Q':
               modificandoGiro = false;
               modificandoBalanceo = false;
               modificandoEstiramiento = false;
               cout << clear;
               cout << menuAnimacion << endl;
               break;
            default:
               cout << clear;
               cout << menuAnimacionMod << endl;
         }
      }else{
         switch (toupper(tecla))
         {
            case '1':
               modificandoGiro = !modificandoGiro;
               cout << clear;
               cout << menuAnimacionMod << endl;
               break;
            case '2':
               modificandoBalanceo = !modificandoBalanceo;
               cout << clear;
               cout << menuAnimacionMod << endl;
               break;
            case '3':
               modificandoEstiramiento = !modificandoEstiramiento;
               cout << clear;
               cout << menuAnimacionMod << endl;
               break;
            case 'Q':
               modoMenu = NADA;
               cout << clear;
               cout << menuSeleccion << endl;
               break;
            default:
               cout << clear;
               cout << menuAnimacion << endl;
         }
      }
   }
   else if (modoMenu == NADA)
   {
      switch (toupper(tecla))
      {
         case 'Q':
            salir = true;
            break;
         case 'O':
            // ESTAMOS EN MODO SELECCION DE OBJETO
            modoMenu = SELOBJETO;
            cout << clear;
            cout << menuObjeto << endl;
            break;
         case 'V':
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            modoMenu = SELVISUALIZACION;
            cout << clear;
            cout << menuVisualizacion << endl;
            break;
         case 'D':
            // ESTAMOS EN MODO SELECCION DE DIBUJADO
            modoMenu = SELDIBUJADO;
            cout << clear;
            cout << menuDibujado << endl;
            break;
         case 'A':
            modoMenu = SELANIMACIONES;
            cout << clear;
            cout << menuAnimacion << endl;
            break;
         default:
            cout << clear;
            cout << menuSeleccion << endl;
      }
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   using namespace std;
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      if(movingAlpha) {
         luz2->variarAnguloAlpha(-10.0f);
         cout << endl << "-Alpha" << endl;
      } else if(movingBeta) {
         luz2->variarAnguloBeta(-10.0f);
         cout << endl << "-Beta" << endl;
      } else {
         Observer_angle_y--;
         Observer_angle_y--;
      }
      break;
   case GLUT_KEY_RIGHT:
      if(movingAlpha) {
         luz2->variarAnguloAlpha(10.0f);
         cout << endl << "+Alpha" << endl;
      } else if(movingBeta) {
         luz2->variarAnguloBeta(10.0f);
         cout << endl << "-Beta" << endl;
      } else {
         Observer_angle_y++;
         Observer_angle_y++;
      }
      break;
   case GLUT_KEY_UP:
      Observer_angle_x--;
      Observer_angle_x--;
      break;
   case GLUT_KEY_DOWN:
      Observer_angle_x++;
      Observer_angle_x++;
      break;
   case GLUT_KEY_PAGE_UP:
      Observer_distance *= 1.2;
      break;
   case GLUT_KEY_PAGE_DOWN:
      Observer_distance /= 1.2;
      break;
   }

   //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane ,
   wx = ratio_xy*wy;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   Width = newWidth;
   Height = newHeight;
   change_projection(float(newHeight) / float(newWidth));
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -Observer_distance);
   glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
   glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}

void Escena::animarVentilador()
{
   if(animar){
      ventilador->girar();
      ventilador->balancear();
      ventilador->estirar();
   }
}
