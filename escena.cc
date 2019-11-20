

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
   tetraedro = new Tetraedro();
   ply = new ObjPLY("./plys/beethoven.ply");
   objrev = new ObjRevolucion("./plys/peon.ply", 20, true);
   
   // std::vector<Tupla3f> vector;

   // y
   // vector.push_back({0.0f, 1.0f, 0.0f});
   // vector.push_back({1.0f, 1.0f, 0.0f});

   // z
   // vector.push_back({1.0f, 0.0f, 0.0f});
   // vector.push_back({1.0f, 0.0f, 1.0f}); 

   // z con polos
   // vector.push_back({0.0f, 0.0f, -2.0f});
   // vector.push_back({1.0f, 0.0f, -1.0f}); 
   // vector.push_back({1.0f, 0.0f, 0.0f}); 
   // vector.push_back({0.0f, 0.0f, 1.0f}); 

   //objrev = new ObjRevolucion(vector, 10, true, 2);
   
   cilindro = new Cilindro(10, 100, 1, 1);
   cono = new Cono(10, 100, 1, 1);
   esfera = new Esfera(100, 100, 0.5);
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

   if(chess){
      glPolygonMode(GL_FRONT, GL_FILL);
      if(showTetraedro)
         tetraedro->draw(CHESS, dibujado_vbo);
      glPushMatrix();
      glTranslatef(2, 0, 0);
      if(showCubo)
         cubo->draw(CHESS, dibujado_vbo);
      glPopMatrix();
      glPushMatrix();
      glTranslatef(-3,0,0);
      if(showPly)
         ply->draw(CHESS, dibujado_vbo);
      glPopMatrix();
      
      if(showRevolucion){
         glPushMatrix();
            glTranslatef(4,0,0);
            objrev->draw(CHESS, dibujado_vbo);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,0,2);
            cilindro->draw(CHESS, dibujado_vbo);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(0,0,4);
            cono->draw(CHESS, dibujado_vbo);
         glPopMatrix();
         glPushMatrix();
            glTranslatef(2,0,2);
            esfera->draw(CHESS, dibujado_vbo);
         glPopMatrix();
      }
   }else{
      if (points){
         glPointSize(5);
         glPolygonMode(GL_FRONT, GL_POINT);
         if(showTetraedro)
            tetraedro->draw(POINTS, dibujado_vbo);
         glPushMatrix();
         glTranslatef(2, 0, 0);
         if(showCubo)
            cubo->draw(POINTS, dibujado_vbo);         
         glPopMatrix();
         glPushMatrix();
         glTranslatef(-3,0,0);
         if(showPly)
            ply->draw(POINTS, dibujado_vbo);
         glPopMatrix();
         if(showRevolucion){
            glPushMatrix();
               glTranslatef(4,0,0);
               objrev->draw(POINTS, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,2);
               cilindro->draw(POINTS, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,4);
               cono->draw(POINTS, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(2,0,2);
               esfera->draw(POINTS, dibujado_vbo);
            glPopMatrix();
         }
      }

      if (solid){
         glPolygonMode(GL_FRONT, GL_FILL);
         if(showTetraedro)
            tetraedro->draw(SOLID, dibujado_vbo);
         glPushMatrix();
         glTranslatef(2, 0, 0);
         if(showCubo)
            cubo->draw(SOLID, dibujado_vbo);         
         glPopMatrix();
         glPushMatrix();
         glTranslatef(-3,0,0);
         if(showPly)
            ply->draw(SOLID, dibujado_vbo);
         glPopMatrix();
         if(showRevolucion){
            glPushMatrix();
               glTranslatef(4,0,0);
               objrev->draw(SOLID, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,2);
               cilindro->draw(SOLID, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,4);
               cono->draw(SOLID, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(2,0,2);
               esfera->draw(SOLID, dibujado_vbo);
            glPopMatrix();
         }
      }

      if (lines){
         glLineWidth(3);
         glPolygonMode(GL_FRONT, GL_LINE);
         if(showTetraedro)
            tetraedro->draw(LINES, dibujado_vbo);
         glPushMatrix();
         glTranslatef(2, 0, 0);
         if(showCubo)
            cubo->draw(LINES, dibujado_vbo);         
         glPopMatrix();
         glPushMatrix();
         glTranslatef(-3,0,0);
         if(showPly)
            ply->draw(LINES, dibujado_vbo);
         glPopMatrix();
         if(showRevolucion){
            glPushMatrix();
               glTranslatef(4,0,0);
               objrev->draw(LINES, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,2);
               cilindro->draw(LINES, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(0,0,4);
               cono->draw(LINES, dibujado_vbo);
            glPopMatrix();
            glPushMatrix();
               glTranslatef(2,0,2);
               esfera->draw(LINES, dibujado_vbo);
            glPopMatrix();
         }
      }
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
   string menuVisualizacion = "***SELECCION DE MODO DE VISUALIZACION***\n\t'P': Puntos\n\t'L': Lineas\n\t'S': Solido\n\t'A': Ajedrez\n\t'Q': Salir";
   string menuDibujado = "***SELECCION DE MODO DE DIBUJADO***\n\t'1': glDrawElements\n\t'2': VBOs\n\t'Q': Salir";
   string menuSeleccion = "***Menu***\n\t'O': SELECION DE OBJETO\n\t'V': SELECCION MODO VISUALIZACION\n\t'D': SELECCION MODO DIBUJADO\n\t'Q': Salir";

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
         // COMPLETAR con los diferentes opciones de teclado
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
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      Observer_angle_y--;
      Observer_angle_y--;
      break;
   case GLUT_KEY_RIGHT:
      Observer_angle_y++;
      Observer_angle_y++;
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
