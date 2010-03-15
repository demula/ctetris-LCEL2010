/*
   vista.h
   Tetris para Motorola Coldfire 5242 sobre la plataforma de desarrollo
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


#ifndef _VISTA_H
#define	_VISTA_H


#include "juego.h"
#include "control.h"
#include "m5272lcd.c"


/*
   Constants: Configuración de la matriz de leds

   NUM_FILAS_LED - Numero de filas en la matriz de leds.
   NUM_COLUMNAS_LED - Numero de columnas en la matriz de leds.
   TASA_REFRESCO - Cada cuanto se refresca la pantalla led en Hz
*/
#define NUM_FILAS_LED 8
#define NUM_COLUMNAS_LED 4
#define TASA_REFRESCO 20 // TODO: hay que cambiarla para que coincida con las specs de la practica


/*
   Struct: Leds de la pantalla de juego

   Estructura con la informacion de lo que se debe mostrar en la pantalla de
   leds. Contiene la informacion de que led debe estar encendido (menos la pieza
   en juego) y de la siguiente columna a refrescar.
 
   pantalla - Matriz con la informacion de los leds encencidos.
   columna_a_refrescar - Siguiente columna a refrescar.
*/
typedef struct
{
    char pantalla[NUM_COLUMNAS_LED][NUM_FILAS_LED];
    char columna_a_refrescar;
} Leds;


// ------------------------------------------------------------------------- LCD
/*
   Functions: Declaracion de las funciones para el uso de la pantalla lcd.

   Funciones contenidas en vista.c para mas informacion acceder a ellas.
*/
void lcd_init(void);
void imprimir_en_lcd(char* mensaje);
void limpiar_lcd(void);


// ------------------------------------------------------------------------ LEDS
/*
   Functions: Declaracion de las funciones para el uso de la pantalla de leds.

   Funciones contenidas en vista.c para mas informacion acceder a ellas.
*/
void leds_init(Leds *leds);
void refrescar_leds(Puerto *puerto, Leds *leds, Pieza *pieza);


#endif	/* _VISTA_H */

