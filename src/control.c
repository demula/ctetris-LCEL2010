/*
   control.c
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


#include "control.h"


/*
   Function: menu

   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.

   Parameters:

 *estado - Puntero a el estado global.
      tecla - char con el valor de la tecla pulsada.
 */
void menu(Estado *estado, Juego *juego, char tecla)
{
    switch (tecla)
    {
        case TECLA_NIVEL_1:
        {
            juego->nivel_dificultad = 0;
        }
            break;
        case TECLA_NIVEL_2:
        {
            juego->nivel_dificultad = 1;
        }
            break;
        case TECLA_NIVEL_3:
        {
            juego->nivel_dificultad = 2;
        }
            break;
        case TECLA_COMIENZO:
        {
            estado->jugando = 1; //TRUE
        }
            break;
        default:
        {

        }
            break;
    }
}


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
void lcd_imprimir(char* mensaje)
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
void lcd_limpiar(void)
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
int ocupacion_pieza(int x, int y, Pieza *pieza)
{
    if ((x < pieza->x) || (y < pieza->y))
    {
        return 0;
    }
    if ((x >= pieza->x + ANCHO_PIEZA) || (y >= pieza->y + ALTO_PIEZA))
    {
        return 0;
    }
    char salida;
    int x_temp = x - pieza->x; //Posicion del cursor dentro de la pieza
    int y_temp = y - pieza->y;
    int posicion_en_forma = (pieza->rotacion * ANCHO_PIEZA * ALTO_PIEZA)+(y_temp * ANCHO_PIEZA) + x_temp;
    salida = pieza->forma[pieza->clase][posicion_en_forma];
    if ('1' == salida)
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
void pintar_pieza_sobre_leds(Leds *leds, Pieza *pieza, int columna, char *fila_leds)
{
    int posicion;
    for (posicion = 0; posicion < NUM_FILAS_LED; posicion++)
    {
        if ((leds->pantalla[columna][posicion] == 1) || (ocupacion_pieza(columna, posicion, pieza) == 1))
        {
            fila_leds[posicion] = '1';
        } else
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
void leds_refrescar(Puerto *puerto, Leds *leds, Pieza *pieza)
{
    char fila_leds[NUM_FILAS_LED];
    pintar_pieza_sobre_leds(leds, pieza, leds->columna_a_refrescar, fila_leds);
    puerto_excita_columna(puerto, leds->columna_a_refrescar, fila_leds);
    leds->columna_a_refrescar++;
    if (leds->columna_a_refrescar == NUM_COLUMNAS_LED)
    {
        leds->columna_a_refrescar = 0;
    }
}


/*
   Function: estado_init
   Inicializa una estructura Estado con lo valores que se le dan.
   
   Parameters:

 *estado - Puntero a la estructura Estado que queremos inicializar.
      nivel_dificultad - int con el nivel dificultad para la partida.
 */
void estado_init(Estado *estado)
{
    estado->jugando = 0;
    estado->texto_menu[0] = TEXTO_NIVEL_1;
    estado->texto_menu[1] = TEXTO_NIVEL_2;
    estado->texto_menu[2] = TEXTO_NIVEL_3;
}

/*
   Function: reloj_init
   Inicializa una estructura Reloj con valores a 0.

   Parameters:

 *reloj - Puntero a la estructura Reloj que queremos inicializar.
 */
void reloj_init(Reloj *reloj)
{
    reloj->columna_led = TASA_REFRESCO; //Dependiendo de la rutina de atencion puede que lo iniciemos a 0
    reloj->nota = 0;
}

/*
   Function: puerto_init
   Inicializa una estructura Puerto con valores a 0.

   Parameters:

 *puerto - Puntero a la estructura Puerto que queremos inicializar.
 */
void puerto_init(Puerto *puerto)
{
    puerto->situacion_puerto = 0;
}

/*
   Function: columna_a_puerto
   
   Convierte el valor numerico que representa a la columna al valor de salida 
   en el puerto. Recordamos que la columna tiene que estar a nivel alto para
   encenderse.

   Parameters:

      columna - valor numerico de la columna de leds que queremos excitar
 */
int columna_a_puerto(char columna)
{
    int salida = 0;
    salida = EXCITACION << columna;
    salida = salida << POS_COLUMNA;
    return salida;
}

/*
   Function: fila_a_puerto
   
   Coniverte el string que representa a la fila a el valor que necesitamos en el
   puerto de salida.

   Parameters:

      fila_leds - String con la informacion de los leds que se vana encender.
 */
int fila_a_puerto(char* fila_leds)
{
    int posicion;
    int salida = 0;
    for (posicion = 0; posicion < NUM_FILAS_LED; posicion++)
    {
        if (fila_leds[posicion] == '1')
        {
            salida += EXCITACION << posicion;
        }
    }
    salida = !salida; //Para encender los leds tienen que estar a nivel bajo en fila
    salida = salida << POS_FILA;
    return salida;
}

/*
   Function: puerto_excita_columna
   
   Excita la columna de leds que queremos con la informacion de fila dados.

   Parameters:

 *puerto - Puntero a la estructura Puerto que queremos inicializar.
      columna - Columna que queremos excitar.
      fila_leds - Informacion de los leds encendidos de dicha columna.
 */
void puerto_excita_columna(Puerto *puerto, char columna, char* fila_leds)
{
    //Colocamos la columna en su posicion correspondiente en el puerto de salida
    int columna_en_puerto = 0;
    columna_en_puerto = columna_a_puerto(columna);
    columna_en_puerto = MASCARA_COLUMNA_LEDS & columna_en_puerto; //aplica mascara
    puerto->situacion_puerto = puerto->situacion_puerto & !MASCARA_COLUMNA_LEDS; //limpia puerto en columnas
    puerto->situacion_puerto += columna_en_puerto;

    //Colocamos la fila en su posicion correspondiente en el puerto de salida
    int fila_en_puerto = 0;
    fila_en_puerto = fila_a_puerto(fila_leds);
    fila_en_puerto = MASCARA_FILA_LEDS & fila_en_puerto;
    puerto->situacion_puerto = puerto->situacion_puerto & !MASCARA_FILA_LEDS;
    puerto->situacion_puerto += fila_en_puerto;

    set_puertoS(puerto->situacion_puerto);
}

/*
   Function: puerto_excita_teclado
   
   Excita la columna del teclado indicada sin modificar los demas valores del
   puerto de salida.

   Parameters:

 *puerto - Puntero a la estructura Puerto que queremos inicializar.
      columna_teclado - Columna que queremos excitar.
 */
void puerto_excita_teclado(Puerto *puerto, char columna_teclado)
{
    puerto->situacion_puerto = puerto->situacion_puerto & !MASCARA_TECLADO;
    puerto->situacion_puerto += columna_teclado;

    set_puertoS(puerto->situacion_puerto);
}


