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

#include "juego.c"
#include "m5272lcd.c"


/*
   Constants: Textos de los menus del juego

   TEXTO_BIENVENIDA - Texto a poner en el inicio del juego o al equivocarse de
                      tecla al elegir nivel
   TEXTO_NIVEL_1 - Texto para elegir el nivel 1
   TEXTO_NIVEL_2 - Texto para elegir el nivel 2
   TEXTO_NIVEL_3 - Texto para elegir el nivel 3
   NUM_NIVELES_MENU - Numero de niveles elegibles en el menu (ojo funcion menu())
 */
#define TEXTO_BIENVENIDA "Bienvenido a ColdtrixTM:\n"
#define TEXTO_NIVEL_1 "Facil"
#define TEXTO_NIVEL_2 "Medio"
#define TEXTO_NIVEL_3 "Dificil"
#define TEXTO_NIVELES_POSIBLES "Por favor pulse: (1) Facil, (4) Medio, (7) Dificil\n"
#define TEXTO_NIVEL_SELECCIONADO "Nivel seleccionado: "
#define TEXTO_COMENZAR_JUEGO ". Pulse A para comenzar la partida...\n"
#define TEXTO_TECLA_ERRONEA "Tecla no valida"
#define TEXTO_NO_NIVEL "No ha seleccionado ningun nivel.\n"
#define NUM_ITEMS_MENU 3


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
   Constants: Constantes de uso para el puerto de salida

   EXCITACION - Valor de excitacion de un bit de salida
   POS_TECLADO - Posicion del bit menos significativo del teclado
   POS_COLUMNA - Posicion del bit menos significativo de la salida a las columnas
   POS_FILA - Posicion del bit menos significativo de la salida a las filas
   MASCARA_TECLADO - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados al teclado (mascara AND y luego sumado)
   MASCARA_COLUMNA_LEDS - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados a la columna de leds (mascara AND...)
   MASCARA_FILA_LEDS - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados a la fila de leds (mascara AND...)
 */
#define EXCITACION 0x0001
#define POS_TECLADO 0
#define POS_COLUMNA 4
#define POS_FILA 8
#define MASCARA_TECLADO 0xFFF0
#define MASCARA_COLUMNA_LEDS 0xFF0F
#define MASCARA_FILA_LEDS 0x00FF


/*
   Struct: Estado del juego
  
   Contiene todas las variables que hacen falta para definir el juego antes de
   su comienzo.

   nivel_dificultad - Numero de filas en la matriz de leds.
   jugando - Indica si se esta jugando (1) o en los menus(0).
   texto_menu - Numero de columnas en la matriz de leds.
 */
typedef struct
{
    char jugando;
    char* texto_menu[NUM_ITEMS_MENU];
} Estado;


/*
   Struct: Relojes del juego

   Contiene todos que se usan en el juego.

   columna_led - Tiempo de refresco por columna MENOS tiempo que lleva escitada 
                la columna en ms.
   nota - Cuenta atras de tiempo que lleva sonando una nota.
 */
typedef struct
{
    int nota;
} Reloj;


/*
   Struct: Relojes del juego

   Contiene todos que se usan en el juego.

   columna_led - Tiempo que lleva escitada la columna en ms.
   refresco - Tiempo de refresco que queremos en la pantalla lcd.
   nota - Tiempo que lleva una nota sonando.
 */
typedef struct
{
    short int situacion_puerto;
} Puerto;


/*
   Functions: Declaracion de las funciones contenidas en control.c

   Funciones contenidas en control.c para mas informacion acceder a ellas.
 */
void menu(Estado *estado, Juego *juego, char tecla);
void estado_init(Estado *estado);
void reloj_init(Reloj *reloj);
void puerto_init(Puerto *puerto);
void puerto_excita_columna(Puerto *puerto, char columna, int fila_leds);
void puerto_excita_teclado(Puerto *puerto, char columna);
void leds_refrescar(Puerto *puerto, Leds *leds);
//void lcd_init(void);
//void lcd_imprimir(char* mensaje);
//void lcd_limpiar(void);


#endif	/* _CONTROL_H */

