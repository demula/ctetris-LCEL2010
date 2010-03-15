/*
   vista.c
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


#include "vista.h"


// ------------------------------------------------------------------------- LCD

/*
   Function: lcd_init
   Inicializa el lcd.
 */
void lcd_init(void)
{
    LCD_reset(); // Reseteamos el LCD
    LCD_init(); // e inicializamos el display
}

/*
   Function: imprimir_en_lcd
   Imprime una cadena de caracteres por el lcd.

   Parameters:

      mensaje - Cadena de caracteres  imprimir.
 */
void imprimir_en_lcd(char* mensaje)
{
    LCD_inst(LIN_1LCD);
    while (*mensaje)
    {
        LCD_dato(*mensaje++);
    }
}

/*
   Function: limpiar_lcd
   Borrar todo lo escrito en el lcd y vuelve a poner el cursor en la 1a linea.
 */
void limpiar_lcd(void)
{
    LCD_inst(CLR_DISP);
    LCD_inst(LIN_1LCD);
}


// ------------------------------------------------------------------------ LEDS

/*
   Function: leds_init
 
   Inicializa una estructura Leds con lo valores por defecto (0).

   Parameters:

 *leds - Puntero a estructura leds que queremos inicializar.
 */
void leds_init(Leds *leds)
{
    int x, y;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            leds->pantalla[x][y] = 0;
        }
    }
    leds->columna_a_refrescar = 0;
}


/*
   Function: ocupacion_pieza

   Devuelve la informacion de la columna indicada de leds con los datos de una
   pieza dada para su posterior suma con la salida de leds iluminados.

   Parameters:

      pieza - Puntero a la pieza que quermos pintar.
      columna - Numero de la columna que queremos iluminar

   Returns:

      Un entero para pasar al puerto de salida.
 */
int ocupacion_pieza (int x, int y, Pieza *pieza)
{
    if ((x < pieza->x) || (y < pieza->y))
    {
        return 0;
    }
    if ((x >= pieza->x+ANCHO_PIEZA) || (y >= pieza->y+ALTO_PIEZA))
    {
        return 0;
    }
    char salida;
    int x_temp = x - pieza->x;//Posicion del cursor dentro de la pieza
    int y_temp = y - pieza->y;
    int posicion_en_forma = (pieza->rotacion*ANCHO_PIEZA*ALTO_PIEZA)+(y_temp*ANCHO_PIEZA)+x_temp;
    salida = pieza->forma[pieza->clase][posicion_en_forma];
    if ( '1' == salida)
    {
        return 1;
    }
    return 0;
}


/*
   Function: pintar_pieza

   Devuelve la informacion de la columna indicada de leds con los datos de una
   pieza dada para su posterior suma con la salida de leds iluminados.

   Parameters:

      pieza - Puntero a la pieza que quermos pintar.
      columna - Numero de la columna que queremos iluminar
  
   Returns:

      Un entero para pasar al puerto de salida.
 */
void pintar_pieza_sobre_leds(Leds *leds, Pieza *pieza, int columna, char *fila_leds[])
{
    int posicion;
    for (posicion = 0; posicion < NUM_FILAS_LED; posicion++)
    {
        if ((leds->pantalla[columna][posicion] == 1) || (ocupacion_pieza(columna, posicion, pieza) == 1))
        {
            fila_leds[posicion] = '1';
        }
        else
        {
            fila_leds[posicion] = '0';
        }
    }
}


/*
   Function: refrescar_leds

   Cada vez que llamamos a esta funcion refrescara la la columna de leds que
   toque tenienddo en cuanta la pieza activa y acutalizara la la informacion de
   columna_a_refrescar en el struct leds.

   Parameters:

      puerto - Puntero a la estructura de manejo de puertoł
      leds - Entero con los datos de una fila de leds.
      columna - Numero de la columna que queremos iluminar
 */
void refrescar_leds(Puerto *puerto, Leds *leds, Pieza *pieza)
{
    char fila_leds[NUM_FILAS_LED];
    pintar_pieza_sobre_leds(leds, pieza, leds->columna_a_refrescar, &fila_leds[]);
    puerto_excita_columna(puerto, leds->columna_a_refrescar, fila_leds);
    leds->columna_a_refrescar++;
    if (leds->columna_a_refrescar == NUM_COLUMNAS_LED)
    {
        leds->columna_a_refrescar = 0;
    }
}