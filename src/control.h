/*
   control.h
   Control de ctetris para Motorola Coldfire 5242 sobre la plataforma de desarrollo
   ENT2004CF.

   Copyright (C) 2010 Jorge Bravo Jimenez fbravos45@gmail.com
   Copyright (C) 2010 Jesus de Mula Cano demula@gmail.com

   License:
   Este programa es software libre; usted puede redistruirlo y/o modificarlo
   bajo los términos de la Licencia Pública General GNU, tal y como está
   publicada por la Free Software Foundation; ya sea la versión 2 de la Licencia,
   o (a su elección) cualquier versión posterior.

   Este programa se distribuye con la intención de ser útil, pero SIN NINGUNA
   GARANTÍA; incluso sin la garantía implícita de USABILIDAD O UTILIDAD PARA UN
   FIN PARTICULAR. Vea la Licencia Pública General GNU para más detalles.

   Usted debería haber recibido una copia de la Licencia Pública General GNU
   junto a este programa; si no es así, escriba a la Free Software Foundation,
   Inc. 675 Mass Ave, Cambridge, MA 02139, EEUU.
 */


#ifndef _CONTROL_H
#define	_CONTROL_H


/*
   Constants: Textos de los menus del juego

   TEXTO_BIENVENIDA - Texto a poner en el inicio del juego o al equivocarse de
                      tecla al elegir nivel
   TEXTO_NIVEL_1 - Texto para elegir el nivel 1
   TEXTO_NIVEL_2 - Texto para elegir el nivel 2
   TEXTO_NIVEL_3 - Texto para elegir el nivel 3
   NUM_NIVELES_MENU - Numero de niveles elegibles en el menu (ojo funcion menu())
*/
#define TEXTO_BIENVENIDA "ELije nivel:"
#define TEXTO_NIVEL_1 "Nivel 1"
#define TEXTO_NIVEL_2 "Nivel 2"
#define TEXTO_NIVEL_3 "Nivel 3"
#define NUM_NIVELES_MENU 3


/*
   Constants: Valor de las teclas de los menus del juego

   TECLA_COMIENZO - Valor de la tecla del teclao matricial para comenzar el juego
   TECLA_NIVEL_1 - Valor de la tecla del teclao matricial para nivel 1
   TECLA_NIVEL_2 - Valor de la tecla del teclao matricial para nivel 2
   TECLA_NIVEL_3 - Valor de la tecla del teclao matricial para nivel 3
*/
#define TECLA_COMIENZO 'A'
#define TECLA_NIVEL_1 '1'
#define TECLA_NIVEL_2 '4'
#define TECLA_NIVEL_3 '7'


/*
   Struct: Estado del juego
  
   Contiene todas las variables que hacen falta para definir el juego antes de
   su comienzo.

   nivel_dificultad - Numero de filas en la matriz de leds.
   jugando - Numero de columnas en la matriz de leds.
   texto_niveles - Numero de columnas en la matriz de leds.
*/
typedef struct
{
    int nivel_dificultad;
    int jugando;
    char* texto_niveles[NUM_NIVELES_MENU];
} Estado;


/*
   Struct: Relojes del juego

   Contiene todos que se usan en el juego.

   columna_led - Tiempo que lleva escitada la columna en ms.
   refresco - Tiempo de refresco que queremos en la pantalla lcd.
   nota - Tiempo que lleva una nota sonando.
*/
typedef struct
{
    int columna_led;
    int refresco;
    int nota;
} Reloj;


/*
   Functions: Declaracion de las funciones contenidas en control.c

   Funciones contenidas en control.c para mas informacion acceder a ellas.
*/
void menu (Estado *estado, char tecla);
void estado_init (Estado *estado, int nivel_dificultad);
void reloj_init (Reloj *reloj);


#endif	/* _CONTROL_H */

