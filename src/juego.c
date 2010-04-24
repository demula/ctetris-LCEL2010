/*
   juego.c
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

#include <stdlib.h>

#include "juego.h"

// ---------------------------------------------------------------------- RAMDOM
char random_pieza(char rango, char update)
{
    static char valor_base_menor = 0;
    static char valor_base_mayor = 0;

    if (update == TRUE)
    {
        valor_base_menor++;
        if (valor_base_menor == rango)
        {
            valor_base_mayor++;
            if (valor_base_mayor == rango)
            {
                valor_base_mayor = 0;
            }
            valor_base_menor = 0;
        }
    }

    return (valor_base_mayor+valor_base_menor) % rango;
}

// ----------------------------------------------------------------------- PIEZA

/*
   Function: pieza_set_posicion

   Cambia las coordenadas de la pieza que le pasemos a las coordenadas indicadas.

   Parameters:

      p_pieza - Puntero a la pieza que queremos cambiar la posicion.
      x - Coordenada x que le queremos asignar a la pieza.
      y - Coordenada y que le queremos asignar a la pieza.

 */
void pieza_set_posicion(Pieza *p_pieza, int x, int y)
{
    p_pieza->x = x;
    p_pieza->y = y;
}

/*
   Function: pieza_get_x

   Devuelve la coordenada x de la pieza que le demos.

   Parameters:

      p_pieza - Puntero a la pieza que queremos cambiar la posicion.

   Returns:

      int con la coordenada x.

 */
int pieza_get_x(Pieza *p_pieza)
{
    return p_pieza->x;
}

/*
   Function: pieza_get_y

   Devuelve la coordenada y de la pieza que le demos.

   Parameters:

      p_pieza - Puntero a la pieza que queremos cambiar la posicion.

   Returns:

      int con la coordenada y.

 */
int pieza_get_y(Pieza *p_pieza)
{
    return p_pieza->y;
}

/*
   Function: rellena_array_forma

   Rellena el array forma del objeto Pieza dependiendo de la clase que le
   pasemos usando como base un string con comas y puntos y comas.

   Necesitamos esta funcion ya que no se pueden asignar cadenas completas ni
   strncpy esta disponible. Ademas necesitamos quitar las comas y puntos y comas
   que pusimos por legibilidad en las constantes.

   Parameters:

      forma - Array multidimensional que queremos rellenar.
      origen - Cadena de caracteres que queremos copiar.
      clase - Clase dentro del array forma que queremos rellenar.

 */
void rellena_array_forma
(
    char forma[NUM_CLASES][ROTACIONES][ANCHO_PIEZA][ALTO_PIEZA],
    char origen[],
    char clase
    )
{
    int posicion_origen;
    int posicion_destino_x = 0;
    int posicion_destino_y = 0;
    int posicion_destino_rotacion = 0;
    for (
        posicion_origen = 0;
        posicion_origen < ANCHO_PIEZA * ALTO_PIEZA * ROTACIONES +
        ALTO_PIEZA * ROTACIONES;
        posicion_origen++
        )
    {
        switch (origen[posicion_origen])
        {
            case '0':
                forma[(int) clase][posicion_destino_rotacion]
                    [posicion_destino_x][posicion_destino_y] = FALSE;
                posicion_destino_x++;
                break;
            case '1':
                forma[(int) clase][posicion_destino_rotacion]
                    [posicion_destino_x][posicion_destino_y] = TRUE;
                posicion_destino_x++;
                break;
            case ',':
                posicion_destino_x = 0;
                posicion_destino_y++;
                break;
            case ';':
                posicion_destino_x = 0;
                posicion_destino_y = 0;
                posicion_destino_rotacion++;
                break;
        }
    }

}

/*
   Function: forma_init

   Rellena el array multidimensional forma por completo con todas sus clases.

   Parameters:

      p_pieza - Puntero a la estructura Pieza que queremos inicializar.
 
 */
void forma_init(Pieza *p_pieza)
{
    rellena_array_forma(p_pieza->forma, FORMA_O, PIEZA_O);
    rellena_array_forma(p_pieza->forma, FORMA_I, PIEZA_I);
    rellena_array_forma(p_pieza->forma, FORMA_T, PIEZA_T);
    rellena_array_forma(p_pieza->forma, FORMA_L, PIEZA_L);
    rellena_array_forma(p_pieza->forma, FORMA_J, PIEZA_J);
    rellena_array_forma(p_pieza->forma, FORMA_S, PIEZA_S);
    rellena_array_forma(p_pieza->forma, FORMA_Z, PIEZA_Z);
}

/*
   Function: posiciones_comienzo_init

   Parameters:

      p_pieza - Puntero a la estructura Pieza que queremos inicializar.
 
 */
void posiciones_comienzo_init(Pieza *p_pieza)
{
    p_pieza->x_comienzo[PIEZA_O] = O_X;
    p_pieza->y_comienzo[PIEZA_O] = O_Y;
    p_pieza->x_comienzo[PIEZA_I] = I_X;
    p_pieza->y_comienzo[PIEZA_I] = I_Y;
    p_pieza->x_comienzo[PIEZA_T] = T_X;
    p_pieza->y_comienzo[PIEZA_T] = T_Y;
    p_pieza->x_comienzo[PIEZA_L] = L_X;
    p_pieza->y_comienzo[PIEZA_L] = L_Y;
    p_pieza->x_comienzo[PIEZA_J] = J_X;
    p_pieza->y_comienzo[PIEZA_J] = J_Y;
    p_pieza->x_comienzo[PIEZA_S] = S_X;
    p_pieza->y_comienzo[PIEZA_S] = S_Y;
    p_pieza->x_comienzo[PIEZA_Z] = Z_X;
    p_pieza->y_comienzo[PIEZA_Z] = Z_Y;
}

/*
   Function: pieza_init
 
   Inicializa una estructura pieza con la pieza de clase O.

   Parameters:

      p_pieza - Puntero a la estructura Pieza que queremos inicializar.
 
 */
void pieza_init(Pieza *p_pieza)
{
    p_pieza->clase = random_pieza(NUM_CLASES,FALSE); //Notice the equal to and the comma
    p_pieza->rotacion = 0;
    p_pieza->x = O_X;
    p_pieza->y = O_Y;
    forma_init(p_pieza);
    posiciones_comienzo_init(p_pieza);
}

// ------------------------------------------------------------------ RESULTADOS

/*
   Function: resultados_init

   Inicializa la estructura Resultados a 0.

   Parameters:

      p_resultados - Puntero al objeto Resultados que queremos inicializar.

 */
void resultados_init(Resultados *p_resultados)
{
    p_resultados->lineas = 0;
    p_resultados->tiempo_partida = 0;
    p_resultados->tetris_conseguidos = 0;
    p_resultados->puntuacion = 0;
}

/*
   Function: resultados_nueva_partida

   Reinicia los campos necesarios de Resultados para una nueva partida.

   Parameters:

      p_resultados - Puntero al objeto  Resultados que queremos inicializar.
 
 */
void resultados_nueva_partida(Resultados *p_resultados)
{
    p_resultados->lineas = 0;
    p_resultados->tiempo_partida = 0;
    p_resultados->tetris_conseguidos = 0;
    p_resultados->puntuacion = 0;
}

/*
   Function: resultados_linea_completada

   Añade una linea completada a los resultados.

   Parameters:

      p_resultados - Puntero a estructura Resultados que queremos sumar la linea.
 
 */
void resultados_linea_completada(Resultados *p_resultados)
{
    p_resultados->lineas++;
}

/*
   Function: resultados_ms_transcurrido

   Añade un milisegundo al tiempo transcurrido de la partida.

   Parameters:

      p_resultados - Puntero a estructura Resultados que queremos sumar el ms.

 */
void resultados_ms_transcurrido(Resultados *p_resultados)
{
    p_resultados->tiempo_partida++;
}

/*
   Function: resultados_tetris_conseguido

   Añade una "tetris" a los resultados.

   Parameters:

      p_resultados - Puntero a estructura Resultados que queremos sumar el tetris.

 */
void resultados_tetris_conseguido(Resultados *p_resultados)
{
    p_resultados->tetris_conseguidos++;
}

/*
   Function: resultados_actualizar_puntuacion

   Actualiza la puntuacion dependiendo del numero de lineas completadas (ya que
   suman distinto) y del nivel en que se despejen las lineas.

   Cada linea completada en el nivel 1 vale 10 puntos. Tenemos un multiplicador
   por nivel y otro por numero de lineas conseguidas. Quedando la formula tal
   que asi:

        Puntuacion = [Nivel*Mul_Nivel*Puntiacion_base*Num_lineas]*
                            (Mul_Lineas*Num_lineas)

   Parameters:

      p_resultados - Puntero a estructura Resultados que queremos sumar la linea.
      lineas - Numero de lineas conseguidas.
      nivel - Nivel actual

 */
void resultados_actualizar_puntuacion(Resultados *p_resultados, int lineas, int nivel)
{
    p_resultados->puntuacion += nivel*MULTIPLICADOR_NIVEL*PUNTUACION_BASE_LINEA*lineas*MULTIPLICADOR_LINEAS*lineas;
}

// ------------------------------------------------------------------------ LEDS

/*
   Function: leds_init

   Inicializa una estructura Leds con lo valores por defecto (0).(Ahora mismo es
   como leds_borra_pantalla pero en el caso de añadir una variable mas a la
   estructura esto cambiaria).

   Parameters:

      p_leds - Puntero a estructura leds que queremos inicializar.
 
 */
void leds_init(Leds *p_leds)
{
    int x, y;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            p_leds->pantalla[x][y] = LED_OFF;
        }
    }
}

/*
   Function: leds_borrar_pantalla

   Borra la pantalla.

   Parameters:

      p_leds - Puntero a estructura leds que queremos inicializar.

 */
void leds_borrar_pantalla(Leds *p_leds)
{
    int x, y;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            p_leds->pantalla[x][y] = LED_OFF;
        }
    }
}

/*
   Function: leds_fila_a_int

   Traduce la columna del array a un entero que se le entregara al puerto para
   excitar la columna de leds correspondiente y la escribe en fila_leds.

   Parameters:

      p_leds - Puntero a la pantalla de leds que vamos a usar.
      columna - Numero de la columna que queremos iluminar.
      fila_leds - Entero donde se guardara la traduccion.
 
 */
void leds_fila_a_int(Leds *p_leds, int columna, int *fila_leds)
{
    int posicion;
    *fila_leds = 0;
    for (posicion = 0; posicion < NUM_FILAS_LED; posicion++)
    {
        if (p_leds->pantalla[columna][posicion] == LED_ON)
        {
            *fila_leds += 1 << (NUM_FILAS_LED - 1 - posicion);
        }
    }
}

/*
   Function: leds_get_posicion

   Devuelve si la posicion de la pantalla esta ocupada o no. Si se le pide una
   posicion fuera de la pantalla devolvera que esta ocupada a no ser que sea por
   parte superior donde aparecen las piezas.

   Parameters:

      p_leds - Puntero a la estructura Leds de donde accedemos a la pantalla.
      x - Posicion x que queremos saber.
      y - Posicion y que queremos saber.

   Returns:
  
      Un char 1 o 0 dependiendo de si esta ocupada la casilla o no.
 
 */
char leds_get_posicion(Leds *p_leds, int x, int y)
{
    if ((x < 0) || (x >= NUM_COLUMNAS_LED))
    {
        return LED_ON;
    }
    else if (y >= NUM_FILAS_LED)
    {
        return LED_ON;
    }
    else if (y < 0)
    {
        return LED_OFF;
    }
    else
    {
        return p_leds->pantalla[x][y];
    }
}

/*
   Function: leds_set_posicion

   Escribe los leds teniendo en cuenta el tamaño de la pantalla.

   Parameters:

   p_leds - Puntero a la estructura Leds de donde accedemos a la pantalla.
   x - Posicion x que queremos.
   y - Posicion y que queremos.
   valor - Valor a escribir en la posicion.
 
 */
void leds_set_posicion(Leds *p_leds, int x, int y, int valor)
{
    if ((x < 0) || (x >= NUM_COLUMNAS_LED))
    {
    }
    else if (y >= NUM_FILAS_LED)
    {
    }
    else if (y < 0)
    {
    }
    else
    {
        p_leds->pantalla[x][y] = valor;
    }
}

/*
   Function: leds_pintar_pieza

   Copia la pieza actual en su posicion a la pantalla de leds. NO TIENE EN 
   CUENTA SI HAY LEDS OCUPADOS.

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza
                actual.
 
 */
void leds_pintar_pieza(Leds *p_leds, Juego *p_juego)
{
    int x_temp, y_temp;
    char pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            pieza_ocupacion = p_juego->pieza_actual.forma
                [(int) p_juego->pieza_actual.clase]
                [p_juego->pieza_actual.rotacion]
                [x_temp]
                [y_temp];
            if (pieza_ocupacion == TRUE)
            {
                leds_set_posicion(p_leds, p_juego->pieza_actual.x + x_temp,
                    p_juego->pieza_actual.y + y_temp, LED_ON);
            }
        }
    }
}

/*
   Function: leds_borrar_pieza

   DES-Copia la pieza actual en su posicion a la pantalla de leds. NO TIENE EN 
   CUENTA SI HAY LEDS OCUPADOS.

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza
                actual.
 
 */
void leds_borrar_pieza(Leds *p_leds, Juego *p_juego)
{
    int x_temp, y_temp;
    char pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            pieza_ocupacion = p_juego->pieza_actual.forma
                [(int) p_juego->pieza_actual.clase]
                [p_juego->pieza_actual.rotacion]
                [x_temp]
                [y_temp];
            if (pieza_ocupacion == TRUE)
            {
                leds_set_posicion(p_leds, p_juego->pieza_actual.x + x_temp,
                    p_juego->pieza_actual.y + y_temp, LED_OFF);
            }
        }
    }
}

/*
   Function: leds_actualiza_area_superior

   Corre un numero_filas dado todas las filas superiores desde la
   fila_comienzo(incluida).

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      fila_comienzo - Fila por donde vamos a empezar a "mover" el area superior.
      numero_filas - Numero de filas que vamos a mover el area superior.

 */
void leds_actualiza_area_superior
(
    Leds *p_leds,
    int fila_comienzo,
    int numero_filas
    )
{
    int x, y;
    char valor_led;

    //Cortamos y pegamos la parte superior
    /*
      BUG de error al borrar filas completadas solucionado
      y = fila_comienzo + numero_filas - 1 --> ya que la fila de comienzo
      es la primera por arriba y estamos empezando por la primera por abajo.

     */
    for (y = fila_comienzo + numero_filas - 1; y > DEATH_LINE; y--)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            valor_led = leds_get_posicion(p_leds, x, y - numero_filas);
            leds_set_posicion(p_leds, x, y, valor_led);
        }
    }

    //Borramos el cacho superior de pantalla que falta con ceros
    for (y = 0; y < numero_filas; y++)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            leds_set_posicion(p_leds, x, y, LED_OFF);
        }
    }
}

/*
   Function: leds_fila_completa

   Devuelve 1 si la fila esta totalmente completa, 0 en caso contrario.

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      fila - Fila de la que queremos saber si esta completa.

   Returns:

      TRUE(1) o FALSE(0) dependiendo de si esta la fila completa o no.
 */
int leds_fila_completa(Leds *p_leds, int fila)
{
    int x;
    char valor_led;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        valor_led = leds_get_posicion(p_leds, x, fila);
        if (valor_led == LED_OFF)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*
   Function: leds_borrar_filas_completadas

   Borra todas la filas que se hallan podido completar y baja las superiores

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza
                actual.
      p_resultados - Puntero a la estructura Resultados para anotar las lineas
                     completadas.
 
 */
void leds_borrar_filas_completadas
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados
    )
{
    int fila;
    int numero_filas, fila_comienzo, fila_completa;
    numero_filas = 0;
    fila_completa = 0;

    for
        (
        fila = 0;
        (fila < ALTO_PIEZA) && (fila + p_juego->pieza_actual.y < NUM_FILAS_LED);
        fila++
        )
    {
        fila_completa = leds_fila_completa(p_leds, fila +
            p_juego->pieza_actual.y);
        if (fila_completa)
        {
            if (!numero_filas)
            {
                fila_comienzo = fila + p_juego->pieza_actual.y;
            }
            numero_filas++;
            resultados_linea_completada(p_resultados);
        }
    }
    //numero_filas da bug , usando otra variable va bien TODO:
    if (numero_filas % TETRIS == 0 && numero_filas != 0)
    {
        resultados_tetris_conseguido(p_resultados);
    }

    //Actualizamos el estado del juego
    resultados_actualizar_puntuacion(p_resultados,
        numero_filas,
        p_juego->nivel_dificultad);
    leds_actualiza_area_superior(p_leds, fila_comienzo, numero_filas);
}

// ----------------------------------------------------------------------- JUEGO

/*
   Function: juego_init

   Inicializa una estructura juego.

   Parameters:

      p_juego - Puntero a la estructura Juego que queremos inicializar.

 */
void juego_init(Juego *p_juego)
{
    p_juego->nivel_dificultad = VALOR_NIVEL_NO_DEFINIDO;
    p_juego->clase_pieza_siguiente = random_pieza(NUM_CLASES,FALSE);
    pieza_init(&p_juego->pieza_actual);
}

/*
   Function: juego_siguiente_pieza

   Coloca en la estructura juego que le pasemos el valor de la siguiente pieza
   que saldra durante el transcurso de la partida.

   Parameters:

      p_juego - Puntero a la estructura Juego para cambiar la siguiente pieza.

 */
void juego_siguiente_pieza(Juego *p_juego)
{
    p_juego->clase_pieza_siguiente = random_pieza(NUM_CLASES,FALSE);
}

/*
   Function: juego_tiempo_caida_pieza

   Devuelve el tiempo de caida de la pieza dependiendo del nivel actual.

   Parameters:

      p_juego - Puntero a la estructura Juego de donde accedemos al nivel actual.

   Returns:

      El valor en ms de cuanto va a tardar en caer una casilla la pieza en juego.
 
 */
int juego_tiempo_caida_pieza(Juego *p_juego)
{
    switch (p_juego->nivel_dificultad)
    {
        case VALOR_NIVEL_NO_DEFINIDO:
            return VALOR_NIVEL_NO_DEFINIDO;
            break;
        case VALOR_NIVEL_1:
            return VELOCIDAD_NIVEL_1;
            break;
        case VALOR_NIVEL_2:
            return VELOCIDAD_NIVEL_2;
            break;
        case VALOR_NIVEL_3:
            return VELOCIDAD_NIVEL_3;
            break;
    }
    return VALOR_NIVEL_NO_DEFINIDO;
}

/*
   Function: juego_nuevo_juego

   Inicia una nueva partida.

   Parameters:

      p_leds - Puntero a la estructura Leds para que sean borrados.
      p_juego - Puntero a la estructura Juego donde resetaeremos lo valores
                necesarios para una nueva partida.
      p_resultados - Puntero a la estructura Resultados donde resetaeremos 
                     lo valores necesarios para una nueva partida.

 */
void juego_nuevo_juego(Leds *p_leds, Juego *p_juego, Resultados *p_resultados)
{
    p_juego->pieza_actual.clase = random_pieza(NUM_CLASES,FALSE);
    juego_siguiente_pieza(p_juego);
    resultados_nueva_partida(p_resultados);
    //p_juego->nivel_dificultad = VALOR_NIVEL_NO_DEFINIDO;//da bug
    //pieza_init(&p_juego->pieza_actual);
    leds_borrar_pantalla(p_leds);
}

/*
   Function: juego_colision

   Devuelve FALSE(0) si no hay colisiones dado la posicion siguiente de la pieza
   y los leds de pantalla ocupados (Se ignora la posicion actual de la pieza).

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza
                actual.
      rotacion - Rotacion de la pieza donde haremos la deteccion de colision.
      x_pos - Posicion x de la pieza donde haremos la deteccion de colision.
      y_pos - Posicion y de la pieza donde haremos la deteccion de colision.

   Returns:

      TRUE(1) or FALSE(0) en caso de que halla o no colision con la pieza.

 */
int juego_colision
(
    Leds *p_leds,
    Juego *p_juego,
    int rotacion,
    int x_pos,
    int y_pos
    )
{
    int x_temp, y_temp;
    char leds_ocupacion, pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            leds_ocupacion = leds_get_posicion(p_leds,
                x_temp + x_pos,
                y_temp + y_pos);
            pieza_ocupacion = p_juego->pieza_actual.forma
                [(int) p_juego->pieza_actual.clase]
                [rotacion]
                [x_temp]
                [y_temp];
            if ((leds_ocupacion == LED_ON) && (pieza_ocupacion == TRUE))
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

/*
   Function: juego_game_over

   Devuelve FALSE(0) si la pieza actual no tiene ninguna parte por encima de la
   pantalla.

   Parameters:

      p_juego - Puntero a la estructura Juego donde accedemos a la pieza actual.

   Returns:

      FALSE cuando la pieza se encuentra completamente en el area de juego, TRUE
      en los demas casos.

 */
int juego_comprueba_game_over(Juego *juego)
{
    int x, y;
    char pieza_ocupacion;

    for (x = 0; x < ANCHO_PIEZA; x++)
    {
        if (juego->pieza_actual.y < 0)
        {
            for (y = 0; y < ALTO_PIEZA; y++)
            {
                if (juego->pieza_actual.y + y == DEATH_LINE)
                    pieza_ocupacion = juego->pieza_actual.forma
                    [(int) juego->pieza_actual.clase]
                    [juego->pieza_actual.rotacion]
                    [x]
                    [y];
                if (pieza_ocupacion == TRUE)
                {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

/*
   Function: juego_nueva_pieza

   Coloca la nueva en posicion de salida y calcula la siguiente pieza.

   Parameters:

      p_juego - Puntero a la estructura Juego de donde accedemos a las piezas.
 
 */
void juego_nueva_pieza(Juego *p_juego)
{
    p_juego->pieza_actual.clase = p_juego->clase_pieza_siguiente;
    p_juego->pieza_actual.x = p_juego->pieza_actual.x_comienzo[
        (int) p_juego->pieza_actual.clase];
    p_juego->pieza_actual.y = p_juego->pieza_actual.y_comienzo[
        (int) p_juego->pieza_actual.clase];
    juego_siguiente_pieza(p_juego);
}

/*
   Function: juego_partida_terminada

   Vuelve al estado de no jugando y nos imprime por pantalla que el juego se ha
   acabado ademas de la filas que hemos completado durante la partida. Pasado un
   tiempo nos volvera a ofrecer si queremos volver a jugar.

   Parameters:

      p_leds - Puntero a la estructura Leds para el borrado de pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a las piezas.
      p_resultados - Puntero a la estructura Resultados para saber las lineas
                     completedas.
      p_estado - Puntero a la estructura Estado para pasar a estado=NO_JUGANDO

 */
void juego_partida_terminada
(
    Leds *leds,
    Juego *juego,
    Resultados *resultados,
    Estado *estado
    )
{
    estado->jugando = FALSE;
    output(TEXTO_GAME_OVER);
    output(TEXTO_FILAS_COMPLETADAS);
    outNum(BASE_10, resultados->lineas, SIN_SIGNO);
    output("\n");
    output(TEXTO_DURACION_PARTIDA);
    outNum(BASE_10, resultados->tiempo_partida/MS_A_S, SIN_SIGNO);//TODO ms a s
    output(TEXTO_SEGUNDOS);
    output("\n");
    output(TEXTO_TETRIS_CONSEGUIDOS);
    outNum(BASE_10, resultados->tetris_conseguidos, SIN_SIGNO);
    output("\n");
    output(TEXTO_FILAS_MINUTO);
    outNum(BASE_10, resultados->tetris_conseguidos*MS_A_MIN/resultados->tiempo_partida, SIN_SIGNO);
    output("\n");
    output(TEXTO_PUNTUACION_FINAL);
    outNum(BASE_10, resultados->puntuacion, SIN_SIGNO);
    output("\n");
    retardo(TIEMPO_GAME_OVER);
    juego_nuevo_juego(leds,juego,resultados);
}

/*
   Function: juego_mover_pieza

   Mueve la pieza activa en la direccion indicada teniendo en cuenta si hay 
   colisiones. En caso de colision no hace nada.

   Parameters:

      p_leds - Puntero a la estructura Leds para acceder a las colisiones.
      p_juego - Puntero a la estructura Juego de donde accedemos al nivel actual.
      p_resultados - Puntero a la estructura Resultados (necesario en caso de
                     completar linea).
      p_estado - Puntero a la estructura Estado (caso fin de partida).
      direccion - Caracter con la direccion en la que queremos mover la pieza.
 
 */
void juego_mover_pieza
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    char direccion
    )
{
    int x, y, game_over;
    x = pieza_get_x(&p_juego->pieza_actual);
    y = pieza_get_y(&p_juego->pieza_actual);

    switch (direccion)
    {
        case IZQUIERDA:
        {
            int hay_colision = juego_colision(p_leds, p_juego,
                p_juego->pieza_actual.rotacion, x - 1, y);
            if (!hay_colision)
            {
                p_juego->pieza_actual.x = x - 1;
            }
            break;
        }
        case ARRIBA:
        {
            int hay_colision = juego_colision(p_leds, p_juego,
                p_juego->pieza_actual.rotacion, x, y - 1);
            if (!hay_colision)
            {
                p_juego->pieza_actual.y = y - 1;
            }
            break;
        }
        case ABAJO:
        {
            int hay_colision = juego_colision(p_leds, p_juego,
                p_juego->pieza_actual.rotacion, x, y + 1);
            if (!hay_colision)
            {
                p_juego->pieza_actual.y = y + 1;
            }
            else
            {
                leds_pintar_pieza(p_leds, p_juego);
                game_over = juego_comprueba_game_over(p_juego);
                if (!game_over)
                {
                    leds_borrar_filas_completadas(p_leds, p_juego, p_resultados);
                    juego_nueva_pieza(p_juego);
                }
                else
                {
                    juego_partida_terminada(p_leds, p_juego,
                        p_resultados, p_estado);
                }

            }
            break;
        }
        case DERECHA:
        {
            int hay_colision = juego_colision(p_leds, p_juego,
                p_juego->pieza_actual.rotacion, x + 1, y);
            if (!hay_colision)
            {
                p_juego->pieza_actual.x = x + 1;
            }
            break;
        }
    }
}

/*
   Function: juego_rotar_pieza

   Rota la pieza activa teniendo en cuenta si hay colisiones. En caso de
   colision no hace nada.

   Parameters:

      p_leds - Puntero a la estructura Leds para acceder a las colisiones.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza.
 
 */
void juego_rotar_pieza(Leds *p_leds, Juego *p_juego)
{
    int hay_colision = juego_colision(
        p_leds,
        p_juego,
        p_juego->pieza_actual.rotacion + 1,
        pieza_get_x(&p_juego->pieza_actual),
        pieza_get_y(&p_juego->pieza_actual)
        );
    if (!hay_colision)
    {
        p_juego->pieza_actual.rotacion++;
        if (p_juego->pieza_actual.rotacion == ROTACIONES)
        {
            p_juego->pieza_actual.rotacion = 0;
        }
    }
}

/*
   Function: juego_caida_timeout

   Gestiona la caida automatica de la pieza mediante un contador interno. Esta
   funcion debe ser llamada cada 1ms para que la caida que le damos sea en ms.

   Parameters:

      p_leds - Puntero a la estructura Leds que contiene la pantalla.
      p_juego - Puntero a la estructura Juego de donde accedemos a la pieza.
      p_resultados - Puntero a la estructura Resultados (necesario en caso de
                     completar linea).
      p_estado - Puntero a la estructura Estado (caso fin de partida).
      tiempo_caida - Tiempo en ms que tarda en caer la pieza una unidad.
 
 */
void juego_caida_timeout
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    int tiempo_caida
    )
{
    static int contador = 0;
    contador++;
    if (contador == tiempo_caida)
    {
        contador = 0;
        leds_borrar_pieza(p_leds, p_juego);
        juego_mover_pieza(p_leds, p_juego, p_resultados, p_estado, ABAJO);
        leds_pintar_pieza(p_leds, p_juego);

    }
}

/*
   Function: juego_tecla_pulsada

   Esta funcion se encarga de mover o rotar la pieza durante el juego
   dependiendo de la tecla que pulsemos.

   Parameters:

      p_leds - Puntero a la estructura Leds para acceder a las colisiones.
      p_juego - Puntero a la estructura Juego.
      p_resultados - Puntero a la estructura Resultados (necesario en caso de
                     completar linea).
      p_estado - Puntero a la estructura Estado (caso fin de partida).
      tecla - Tecla pulsada en el teclado matricial.
 
 */
void juego_tecla_pulsada
(
    Leds *p_leds,
    Juego *p_juego,
    Resultados *p_resultados,
    Estado *p_estado,
    char tecla
    )
{
    /*
       Deshabilitamos y posteriormente habilitamos interrupciones para evitar
       que se corrompan las variables globales. TODO: Implementar locks (mas elegante)
     */
    deshabilitar_interrupciones();
    switch (tecla)
    {
        case TECLA_ROTAR:
        {
            leds_borrar_pieza(p_leds, p_juego);
            juego_rotar_pieza(p_leds, p_juego);
            leds_pintar_pieza(p_leds, p_juego);
            break;
        }
        case TECLA_IZQUIERDA:
        {
            leds_borrar_pieza(p_leds, p_juego);
            juego_mover_pieza(p_leds, p_juego, p_resultados, p_estado, IZQUIERDA);
            leds_pintar_pieza(p_leds, p_juego);
            break;
        }
        case TECLA_ABAJO:
        {
            leds_borrar_pieza(p_leds, p_juego);
            juego_mover_pieza(p_leds, p_juego, p_resultados, p_estado, ABAJO);
            leds_pintar_pieza(p_leds, p_juego);
            break;
        }
        case TECLA_DERECHA:
        {
            leds_borrar_pieza(p_leds, p_juego);
            juego_mover_pieza(p_leds, p_juego, p_resultados, p_estado, DERECHA);
            leds_pintar_pieza(p_leds, p_juego);
            break;
        }
        case TECLA_ARRIBA:
        {
            leds_borrar_pieza(p_leds, p_juego);
            juego_mover_pieza(p_leds, p_juego, p_resultados, p_estado, ARRIBA);
            leds_pintar_pieza(p_leds, p_juego);
            break;
        }
        case TECLA_SALIDA:
        {
            //_exit(0);
            break;
        }
    }
    habilitar_interrupciones();
}
