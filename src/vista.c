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


#include "m5272lcd.c"
#include "m5272gpio.c"
#include "vista.h"


// ------------------------------------------------------------------------- LCD
/*
   Function: lcd_init
   Inicializa el lcd.
*/
void lcd_init(void)
{
    LCD_reset();	// Reseteamos el LCD
    LCD_init();	// e inicializamos el display
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
    while(*mensaje)
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
void leds_init (Leds *leds)
{
    int x, y;
    for (x=0; x<NUM_COLUMNAS_LED; x++)
    {
        for (y=0; y<NUM_FILAS_LED; y++)
        {
            leds->pantalla[x][y] = 0;
        }
    }
    leds->columna_a_refrescar = 0;
}


/*
   Function: paso_de_fila_a_int
   
   Coniverte una fila de leds dada (array de 0 y 1) a un entero para usar en el
   puerto de salida a la hora de imprimir los leds en la pantalla.
  
   Parameters:

      fila[] - Array con los datos de una fila de leds.

   Returns:

      Un entero para pasar al puerto de salida.
 */
int paso_de_fila_a_int(char fila[])
{
    int salida = 0;
    int y;
    int activo = 1;
    for (y=0; y<NUM_FILAS_LED; y++)
    {
        salida += (activo*fila[y])<< y;
    }
    return salida;
}


/*
   Function: mux_columna
   
   Coniverte el numero de columna en la columna de salida que queremos iluminar
   teniendo en cuenta que la esquina superior izquierda es la coordenada (0,0)
   Ej:(con 4 columnas) columna 3 => 0b0001
  
   Parameters:

      columna - Numero de la columna a iluminar.

   Returns:

      Un entero para pasar al puerto de salida.
 */
int mux_columna(int columna)
{
    int salida = 1;
    if (columna >= NUM_COLUMNAS_LED)
    {
        output("Columna fuera del rango de la configuracion actual.");
        return 0;
    }
    salida = salida << (NUM_COLUMNAS_LED - 1 - columna);//el -1 es por que comenzamos a contar por 0
    return salida;
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
int pintar_pieza(Pieza *pieza, int columna)
{

}


/*
   Function: refrescar_columna_leds

   Ilumina la columna de leds con los datos de fila dados.
  
   Parameters:

      salida_fila - Entero con los datos de una fila de leds.
      columna - Numero de la columna que queremos iluminar
 */
void refrescar_columna_leds(int salida_fila, int columna)
{
    int salida = 0;
    salida = mux_columna(columna) << NUM_FILAS_LED; //Para 4x8 es como *2^8
    salida += salida_fila;
    set16_puertoS(salida);
}


/*
   Function: refrescar_leds

   Cada vez que llamamos a esta funcion refrescara la la columna de leds que
   toque tenienddo en cuanta la pieza activa y acutalizara la la informacion de
   columna_a_refrescar en el struct leds.

   Parameters:
  
      leds - Entero con los datos de una fila de leds.
      columna - Numero de la columna que queremos iluminar
 */
void refrescar_leds(Leds *leds, Pieza *pieza)
{
    int salida = 0;
    salida = paso_de_fila_a_int(leds->pantalla[leds->columna_a_refrescar]);
    refrescar_columna_leds(salida, leds->columna_a_refrescar);
    leds->columna_a_refrescar++;
    if (leds->columna_a_refrescar == NUM_COLUMNAS_LED)
    {
        leds->columna_a_refrescar = 0;
    }
}