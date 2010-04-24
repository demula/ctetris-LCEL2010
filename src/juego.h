/*
   juego.h
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


#ifndef _JUEGO_H
#define	_JUEGO_H

//#include "hardware.c"
#include "hardware.h"

/*
   Constants: Valor de las teclas en el juego

   TECLA_ROTAR - Valor de la tecla del teclado matricial para rotar la pieza activa
   TECLA_IZQUIERDA - Valor de la tecla del teclado matricial para mover izquierda
   TECLA_ABAJO - Valor de la tecla del teclado matricial para mover abajo
   TECLA_DERECHA - Valor de la tecla del teclado matricial para mover derecha
   TECLA_ARRIBA - Valor de la tecla del teclado matricial para mover arriba
   TECLA_SALIDA - Valor de la tecla del teclado matricial para salir del programa

 */
#define TECLA_ROTAR 'A'
#define TECLA_IZQUIERDA '1'
#define TECLA_ABAJO '4'
#define TECLA_DERECHA '7'
#define TECLA_ARRIBA '5' //Para pruebas
#define TECLA_SALIDA '3' //Para pruebas

/*
   Constants: Valor de las direciones en el juego (por legibilidad)

   ARRIBA - Valor del swicth como arriba
   IZQUIERDA - Valor del swicth como izquierda
   ABAJO - Valor del swicth como abajo
   DERECHA - Valor del swicth como derecha

 */
#define ARRIBA 'U'
#define IZQUIERDA 'L'
#define ABAJO 'D'
#define DERECHA 'R'

/*
   Constants: Configuración del hardware del teclado

   ANCHO_PIEZA - Altura en casillas que ocupa.
   ALTO_PIEZA - Número de columnas en el teclado matricial.
   ROTACIONES - Rotaciones posibles de una pieza.
   NUM_CLASES - Número de piezas posibles en el juego.
   PIEZA_O - Numero identificador para el switch de la pieza O
   PIEZA_I - Numero identificador para el switch de la pieza I
   PIEZA_T - Numero identificador para el switch de la pieza T
   PIEZA_L - Numero identificador para el switch de la pieza L
   PIEZA_J - Numero identificador para el switch de la pieza J
   PIEZA_S - Numero identificador para el switch de la pieza S
   PIEZA_Z - Numero identificador para el switch de la pieza Z

 */
#define ANCHO_PIEZA 4
#define ALTO_PIEZA 4
#define ROTACIONES 4
#define NUM_CLASES 7
#define PIEZA_O 0
#define PIEZA_I 1
#define PIEZA_T 2
#define PIEZA_L 3
#define PIEZA_J 4
#define PIEZA_S 5
#define PIEZA_Z 6

/*
   Constants: Definiciones de los leds que ocupan cada pieza

   Son cadenas de 0 y 1 donde las filas van separadas por comas y las rotaciones
   por punto y coma (Al iniciar el struct son IGNORADAS).

   Ej: Una ficha T con ancho 4, alto 4 y 4 rotaciones en sentido antihorario
       como esta

    Rotacion 0 -> 0100,  Rotacion 1 -> 0100,  Rotacion 2 -> 0100,  Rotacion 3 -> 0000,
                  0110,                1110,                1100,                1110,
                  0100,                0000,                0100,                0100,
                  0000;                0000;                0000;                0000;

   Seria => "0100,0110,0100,0000;0100,1110,0000,0000;0100,1100,0100,0000;0000,1110,0100,0000;"

   OCUPACION_O - Leds de ocupacion de la pieza O.
   OCUPACION_I - Leds de ocupacion de la pieza I.
   OCUPACION_T - Leds de ocupacion de la pieza T.
   OCUPACION_L - Leds de ocupacion de la pieza L.
   OCUPACION_J - Leds de ocupacion de la pieza J.
   OCUPACION_S - Leds de ocupacion de la pieza S.
   OCUPACION_Z - Leds de ocupacion de la pieza Z.

 */
#define FORMA_O "1100,1100,0000,0000;1100,1100,0000,0000;1100,1100,0000,0000;1100,1100,0000,0000;"
#define FORMA_I "0100,0100,0100,0100;0000,1111,0000,0000;0100,0100,0100,0100;0000,1111,0000,0000;"
#define FORMA_T "0100,0110,0100,0000;0100,1110,0000,0000;0100,1100,0100,0000;0000,1110,0100,0000;"
#define FORMA_L "0100,0100,0110,0000;0010,1110,0000,0000;1100,0100,0100,0000;0000,1110,1000,0000;"
#define FORMA_J "0100,0100,1100,0000;0000,1110,0010,0000;0110,0100,0100,0000;1000,1110,0000,0000;"
#define FORMA_S "0000,0110,1100,0000;1000,1100,0100,0000;0000,0110,1100,0000;1000,1100,0100,0000;"
#define FORMA_Z "0000,1100,0110,0000;0010,0110,0100,0000;0000,1100,0110,0000;0010,0110,0100,0000;"

/*
   Constants: Puntos de inicio de las piezas

   O_X - Coordenada x inicial de la pieza O.
   O_Y - Coordenada y inicial de la pieza O.
   I_X - Coordenada x inicial de la pieza I.
   I_Y - Coordenada y inicial de la pieza I.
   T_X - Coordenada x inicial de la pieza T.
   T_Y - Coordenada y inicial de la pieza T.
   L_X - Coordenada x inicial de la pieza L.
   L_Y - Coordenada y inicial de la pieza L.
   J_X - Coordenada x inicial de la pieza J.
   J_Y - Coordenada y inicial de la pieza J.
   S_X - Coordenada x inicial de la pieza S.
   S_Y - Coordenada y inicial de la pieza S.
   Z_X - Coordenada x inicial de la pieza Z.
   Z_Y - Coordenada y inicial de la pieza Z.

 */
#define O_X 1
#define O_Y -2
#define I_X 0
#define I_Y -4
#define T_X 0
#define T_Y -3
#define L_X 0
#define L_Y -3
#define J_X 1
#define J_Y -3
#define S_X 0
#define S_Y -2
#define Z_X 0
#define Z_Y -2

/*
   Constants: Configuración de la matriz de leds

   NUM_FILAS_LED - Numero de filas en la matriz de leds.
   NUM_COLUMNAS_LED - Numero de columnas en la matriz de leds.
   TASA_REFRESCO - Tiempo que permance encendida cada columna de leds.
   DEATH_LINE - Linea en la que si una pieza ha colisionado y tiene partes sobre
                ella nos da game over.
   LED_ON - Valor del array leds que consideramos como encendido.
   LED_OFF - Valor del array leds que consideramos como apagado.

 */
#define NUM_FILAS_LED 8
#define NUM_COLUMNAS_LED 4
#define TASA_REFRESCO 10
#define DEATH_LINE -1
#define LED_ON 1
#define LED_OFF 0

/*
   Constants: Configuración de la velocidad de caida de las piezas segun nivel

   VELOCIDAD_NIVEL_1 - Velocidad de caida en ms de cada paso en la pantalla a nv1
   VELOCIDAD_NIVEL_2 - Velocidad de caida en ms de cada paso en la pantalla a nv2
   VELOCIDAD_NIVEL_3 - Velocidad de caida en ms de cada paso en la pantalla a nv3

 */
#define VELOCIDAD_NIVEL_1 1000
#define VELOCIDAD_NIVEL_2 800
#define VELOCIDAD_NIVEL_3 600

/*
   Constants: Valores del nivel de dificultad

   Valores que se le asignan al nivel de dificultad.

 */
#define NUM_NIVELES 3
#define VALOR_NIVEL_1 0
#define VALOR_NIVEL_2 1
#define VALOR_NIVEL_3 2
#define VALOR_NIVEL_NO_DEFINIDO -1

/*
   Constants: Valores para puntuacion y resultados

 */
#define PUNTUACION_BASE_LINEA 10
#define MULTIPLICADOR_NIVEL 1
#define MULTIPLICADOR_LINEAS 1
#define TETRIS 4

/*
   Constants: Configuración del game over y sus textos

   TEXTO_GAME_OVER - Velocidad de caida en ms de cada paso en la pantalla a nv1
   TEXTO_FILAS_COMPLETADAS - Velocidad de caida en ms de cada paso en la pantalla a nv2
   TIEMPO_GAME_OVER - Tiempo en ms que se muestran los resultados en pantalla.

 */
#define TEXTO_GAME_OVER "GAME OVER\n"
#define TEXTO_FILAS_COMPLETADAS "   Filas completadas  "
#define TEXTO_DURACION_PARTIDA "   Duracion de la partida  "
#define TEXTO_SEGUNDOS " segundos"
#define TEXTO_FILAS_MINUTO "   Filas por minuto  "
#define TEXTO_TETRIS_CONSEGUIDOS "   Tetris conseguidos  "
#define TEXTO_PUNTUACION_FINAL "   Puntuacion final  "
#define BASE_10 10
#define MS_A_S 1000
#define MS_A_MIN 60000
#define TIEMPO_GAME_OVER 3000

/*
   Struct: Leds de la pantalla de juego

   Estructura con la informacion de lo que se debe mostrar en la pantalla de
   leds. Contiene la informacion de que led debe estar encendido (menos la pieza
   en juego) y de la siguiente columna a refrescar.

   Movida a juego.h para evitar importacion recursiva.

   pantalla - Matriz con la informacion de los leds encencidos.

 */
typedef struct
{
    char pantalla[NUM_COLUMNAS_LED][NUM_FILAS_LED];
} Leds;

/*
   Struct: Pieza del juego

   Contiene la informacion de la pieza activa del juego. Nos valdra para saber
   su localizacion en la pantalla, los leds que ocupa teniendo en cuenta su
   rotacion.

   clase - Identificacion del tipo de la pieza que esta en juego .
   x - Posicion horizontal.
   y - Poscicion vertical.
   rotacion - rotacion en la que esta la pieza.
   x_comienzo - Array con las posiciones x iniciales de cada pieza (i=clase).
   y_comienzo - Array con las posiciones y iniciales de cada pieza (i=clase).
   forma - Array multidimensional que contiene la forma de cada clase de pieza
           con sus rotaciones.

 */
typedef struct
{
    char clase;
    int x;
    int y;
    int rotacion;
    int x_comienzo[NUM_CLASES];
    int y_comienzo[NUM_CLASES];
    char forma[NUM_CLASES][ROTACIONES][ANCHO_PIEZA][ALTO_PIEZA];
} Pieza;

/*
   Struct: Juego

   Contiene la informacion de la pieza activa del juego. Nos valdra para saber
   su localizacion en la pantalla, los leds que ocupa teniendo en cuenta su
   rotacion.

   nivel_dificultad - Nivel de dificultad al que esta el juego.
   clase_pieza_siguiente - Identificacion del tipo de la pieza siguiente.
   pieza _actual - Estructura Pieza para uso del juego.

 */
typedef struct
{
    int nivel_dificultad;
    char clase_pieza_siguiente;
    Pieza pieza_actual;
} Juego;

/*
   Struct: Juego

   Contiene los resultados de la partida jugada (lineas completadas, puntuacion,
   etc...)

   lineas - Numero de lineas completadas.
   tiempo_partida - Duracion de la partida en ms
   tetris_conseguidos - Numero de veces que se ha conseguido despejar 4 filas a la vez
   puntuacion - Numero de puntos obtenidos en la partida.
 
 */
typedef struct
{
    int lineas;
    int tiempo_partida;
    int tetris_conseguidos;
    int puntuacion;
} Resultados;

/*
   Struct: Estado del juego

   Contiene todas las variables que hacen falta para definir el juego antes de
   su comienzo.

   jugando - Indica si se esta jugando (1) o en los menus(0).
   texto_menu - Numero de columnas en la matriz de leds.

 */
typedef struct
{
    char jugando;
    char* texto_menu[NUM_NIVELES];
} Estado;

/*
   Functions: Prototipos de las funciones contenidas en juego.c

   Funciones contenidas en juego.c para mas informacion acceder a ellas.

 */
// ----------------------------------------------------------------------- PIEZA
void pieza_init(Pieza *p_pieza);
void pieza_set_posicion(Pieza *p_pieza, int x, int y);
int pieza_get_x(Pieza *p_pieza);
int pieza_get_y(Pieza *p_pieza);
void rellena_array_forma
(
    char forma[NUM_CLASES][ROTACIONES][ANCHO_PIEZA][ALTO_PIEZA],
    char origen[],
    char clase
    );
void forma_init(Pieza *p_pieza);
void posiciones_comienzo_init(Pieza *p_pieza);
// ------------------------------------------------------------------ RESULTADOS
void resultados_init(Resultados *p_resultados);
void resultados_nueva_partida(Resultados *p_resultados);
void resultados_linea_completada(Resultados *p_resultados);
// ------------------------------------------------------------------------ LEDS
void leds_init(Leds *p_leds);
void leds_borrar_pantalla(Leds *p_leds);
void leds_fila_a_int(Leds *p_leds, int columna, int *fila_leds);
char leds_get_posicion(Leds *p_leds, int x, int y);
void leds_set_posicion(Leds *p_leds, int x, int y, int valor);
void leds_pintar_pieza(Leds *p_leds, Juego *p_juego);
void leds_borrar_pieza(Leds *p_leds, Juego *p_juego);
void leds_actualiza_area_superior
(
    Leds *p_leds,
    int fila_comienzo,
    int numero_filas
    );
int leds_fila_completa(Leds *p_leds, int fila);
void leds_borrar_filas_completadas
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados
    );
// ----------------------------------------------------------------------- JUEGO
void juego_init(Juego *p_juego);
void juego_siguiente_pieza(Juego *p_juego);
int juego_tiempo_caida_pieza(Juego *p_juego);
void juego_nuevo_juego(Leds *p_leds, Juego *p_juego, Resultados *p_resultados);
int juego_colision
(
    Leds *p_leds,
    Juego *p_juego,
    int rotacion,
    int x_pos,
    int y_pos
    );
int juego_comprueba_game_over(Juego *juego);
void juego_nueva_pieza(Juego *p_juego);
void juego_partida_terminada
(
    Leds *leds,
    Juego *juego,
    Resultados *resultados,
    Estado *estado
    );
void juego_mover_pieza
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    char direccion
    );
void juego_rotar_pieza(Leds *p_leds, Juego *p_juego);
void juego_caida_timeout
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    int tiempo_caida
    );
void juego_tecla_pulsada
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    char tecla
    );

#endif	/* _JUEGO_H */

