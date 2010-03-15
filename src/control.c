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


#include "vista.h"
#include "control.h"

/*
   Function: menu
   
   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.

   Parameters:

 *estado - Puntero a el estado global.
      tecla - char con el valor de la tecla pulsada.
 */
void menu(Estado *estado, char tecla)
{
    switch (tecla)
    {
        case TECLA_NIVEL_1:
        {
            estado->nivel_dificultad = 0;
        }
            break;
        case TECLA_NIVEL_2:
        {
            estado->nivel_dificultad = 1;
        }
            break;
        case TECLA_NIVEL_3:
        {
            estado->nivel_dificultad = 2;
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

/*
   Function: estado_init
   Inicializa una estructura Estado con lo valores que se le dan.
   
   Parameters:

 *estado - Puntero a la estructura Estado que queremos inicializar.
      nivel_dificultad - int con el nivel dificultad para la partida.
 */
void estado_init(Estado *estado, int nivel_dificultad)
{
    estado->nivel_dificultad = nivel_dificultad;
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
    reloj->columna_led = TASA_REFRESCO; //Dependiendo de la rutina de atencio puede que lo iniciemos a 0
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


