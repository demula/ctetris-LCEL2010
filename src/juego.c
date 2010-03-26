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


#include "juego.h"


// ----------------------------------------------------------------------- PIEZA

/*
   Function: nueva_pieza

   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.

   Parameters:

      clase - Caracter con la clase de la que queremos la pieza.

   Returns:

      Pieza colocada en coordenadas de inicio superiores al marco de la pantalla.
 */
void pieza_set_posicion(Pieza *pieza, int x, int y)
{
    pieza->x = x;
    pieza->y = y;
}

int pieza_get_x(Pieza *pieza)
{
    return pieza->x;
}

int pieza_get_y(Pieza *pieza)
{
    return pieza->y;
}

/*
   Function: copia_texto_forma

   Copia caracteres de una cadena a otra.

   Necesitamos esta funcion ya que no se pueden asignar cadenas completas ni
   strncpy esta disponible. Ademas necesitamos quitar las comas y puntos y comas
   que pusimos por legibilidad en las constantes.

   Parameters:

 *destino - Puntero a la cadena que queremos copiar los carecteres de origen.
      origen - Cadena de caracteres que queremos copiar.
 */
void rellena_array_forma(char forma[NUM_CLASES][ROTACIONES][ANCHO_PIEZA][ALTO_PIEZA], char origen[], char clase)
{
    int posicion_origen;
    int posicion_destino_x = 0;
    int posicion_destino_y = 0;
    int posicion_destino_rotacion = 0;
    for (posicion_origen = 0; posicion_origen < ANCHO_PIEZA * ALTO_PIEZA * ROTACIONES + ALTO_PIEZA * ROTACIONES; posicion_origen++)
    {
        switch (origen[posicion_origen])
        {
            case '0':
                forma[(int) clase][posicion_destino_rotacion][posicion_destino_x][posicion_destino_y] = 0;
                posicion_destino_x++;
                break;
            case '1':
                forma[(int) clase][posicion_destino_rotacion][posicion_destino_x][posicion_destino_y] = 1;
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

   Parameters:

 *pieza - Puntero a la estructura Pieza que queremos inicializar.
 */
void forma_init(Pieza *pieza)
{
    rellena_array_forma(pieza->forma, FORMA_O, PIEZA_O);
    rellena_array_forma(pieza->forma, FORMA_I, PIEZA_I);
    rellena_array_forma(pieza->forma, FORMA_T, PIEZA_T);
    rellena_array_forma(pieza->forma, FORMA_L, PIEZA_L);
    rellena_array_forma(pieza->forma, FORMA_J, PIEZA_J);
    rellena_array_forma(pieza->forma, FORMA_S, PIEZA_S);
    rellena_array_forma(pieza->forma, FORMA_Z, PIEZA_Z);
}

/*
   Function: posiciones_comienzo_init

   Parameters:

 *pieza - Puntero a la estructura Pieza que queremos inicializar.
 */
void posiciones_comienzo_init(Pieza *pieza)
{
    pieza->x_comienzo[PIEZA_O] = O_X;
    pieza->y_comienzo[PIEZA_O] = O_Y;
    pieza->x_comienzo[PIEZA_I] = I_X;
    pieza->y_comienzo[PIEZA_I] = I_Y;
    pieza->x_comienzo[PIEZA_T] = T_X;
    pieza->y_comienzo[PIEZA_T] = T_Y;
    pieza->x_comienzo[PIEZA_L] = L_X;
    pieza->y_comienzo[PIEZA_L] = L_Y;
    pieza->x_comienzo[PIEZA_J] = J_X;
    pieza->y_comienzo[PIEZA_J] = J_Y;
    pieza->x_comienzo[PIEZA_S] = S_X;
    pieza->y_comienzo[PIEZA_S] = S_Y;
    pieza->x_comienzo[PIEZA_Z] = Z_X;
    pieza->y_comienzo[PIEZA_Z] = Z_Y;
}

/*
   Function: pieza_init
 
   Inicializa una estructura pieza con la pieza de clase O.

   Parameters:

 *pieza - Puntero a la estructura Pieza que queremos inicializar.
 */
void pieza_init(Pieza *pieza)
{
    pieza->clase = PIEZA_O; //Notice the equal to and the comma
    pieza->rotacion = 0;
    pieza->x = O_X;
    pieza->y = O_Y;
    forma_init(pieza);
    posiciones_comienzo_init(pieza);
}


// ------------------------------------------------------------------------ LEDS

/*
   Function: leds_init

   Inicializa una estructura Leds con lo valores por defecto (0).(Ahora mismo es
   como leds_borra_pantalla pero en el caso de añadir una variable mas a la
   estructura esto cambiaria)

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
}

/*
   Function: leds_borrar_pantalla

   Borra la pantalla.

   Parameters:

 *leds - Puntero a estructura leds que queremos inicializar.
 */
void leds_borrar_pantalla(Leds *leds)
{
    int x, y;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            leds->pantalla[x][y] = 0;
        }
    }
}

/*
   Function: leds_fila_a_int

   Traduce la columna del array a un entero que se le entregara al puerto para
   excitar la columna de leds correspondiente y la escribe en fila_leds.

   Parameters:

 *leds - Puntero a la pantalla de leds que vamos a usar.
      columna - Numero de la columna que queremos iluminar
      fila_leds - Entero donde se guardara la traduccion
 */
void leds_fila_a_int(Leds *leds, int columna, int *fila_leds)
{
    int posicion;
    *fila_leds = 0;
    for (posicion = 0; posicion < NUM_FILAS_LED; posicion++)
    {
        if (leds->pantalla[columna][posicion] == 1)
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

 *leds - Puntero a la estructura Leds de donde accedemos a la pantalla.
   x - Posicion x que queremos
   y - Posicion y que queremos
 */
char leds_get_posicion(Leds *leds, int x, int y)
{
    if ((x < 0) || (x >= NUM_COLUMNAS_LED))
    {
        return 1;
    }
    else if (y >= NUM_FILAS_LED)
    {
        return 1;
    }
    else if (y < 0)
    {
        return 0;
    }
    else
    {
        return leds->pantalla[x][y];
    }
}

/*
   Function: leds_set_posicion

   Escribe los leds teniendo en cuenta el tamaño de la pantalla.

   Parameters:

 *leds - Puntero a la estructura Leds de donde accedemos a la pantalla.
   x - Posicion x que queremos
   y - Posicion y que queremos
   valor - Valor a escribir en la posicion
 */
void leds_set_posicion(Leds *leds, int x, int y, int valor)
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
        leds->pantalla[x][y] = valor;
    }
}

/*
   Function: leds_pintar_pieza

   Copia la pieza actual en su posicion a la pantalla de leds. NO TIENE EN CUENTA
   SI HAY LEDS OCUPADOS.

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
void leds_pintar_pieza(Leds *leds, Juego *juego)
{
    int x_temp, y_temp;
    char pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            pieza_ocupacion = juego->pieza_actual.forma[(int) juego->pieza_actual.clase][juego->pieza_actual.rotacion][x_temp][y_temp];
            if (pieza_ocupacion == 1)
            {
                leds_set_posicion(leds, juego->pieza_actual.x + x_temp, juego->pieza_actual.y + y_temp, 1);
            }
        }
    }
}

/*
   Function: leds_borrar_pieza

   DES-Copia la pieza actual en su posicion a la pantalla de leds. NO TIENE EN CUENTA
   SI HAY LEDS OCUPADOS.

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
void leds_borrar_pieza(Leds *leds, Juego *juego)
{
    int x_temp, y_temp;
    char pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            pieza_ocupacion = juego->pieza_actual.forma[(int) juego->pieza_actual.clase][juego->pieza_actual.rotacion][x_temp][y_temp];
            if (pieza_ocupacion == 1)
            {
                leds_set_posicion(leds, juego->pieza_actual.x + x_temp, juego->pieza_actual.y + y_temp, 0);
            }
        }
    }
}

/*
   Function: leds_actualiza_area_superior

   Corre un numero_filas dado todas las filas superiores desde la fila_comienzo(incluida).

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
void leds_actualiza_area_superior(Leds *leds, int fila_comienzo, int numero_filas)
{
    int x, y;
    char valor_led;

    //Cortamos y pegamos la parte superior
    for (y = fila_comienzo; y > DEATH_LINE; y--)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            valor_led = leds_get_posicion(leds, x, y - numero_filas);
            leds_set_posicion(leds, x, y, valor_led);
        }
    }

    //Borramos el cacho superior de pantalla que falta con ceros
    for (y = 0; y < numero_filas; y++)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            leds_set_posicion(leds, x, y, 0);
        }
    }



}

/*
   Function: leds_fila_completa

   Devuelve 1 si la fila esta totalmente completa, 0 en caso contrario.

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
int leds_fila_completa(Leds *leds, int fila)
{
    int x;
    char valor_led;
    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        valor_led = leds_get_posicion(leds, x, fila);
        if (valor_led == 0)
        {
            return 0;
        }
    }

    return 1;
}

/*
   Function: leds_borrar_filas_completadas

   Borra todas la filas que se hayan podido completar y baja las superiores

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
void leds_borrar_filas_completadas(Leds *leds, Juego *juego)
{
    int fila;
    int numero_filas, fila_comienzo, fila_completa;
    numero_filas = 0;

    for (fila = juego->pieza_actual.y; fila < ALTO_PIEZA + juego->pieza_actual.y; fila++)
    {
        fila_completa = leds_fila_completa(leds, fila);
        if (fila_completa)
        {
            if (!numero_filas)
            {
                fila_comienzo = fila;
            }
            numero_filas++;
        }
    }

    leds_actualiza_area_superior(leds, fila_comienzo, numero_filas);
}


// ----------------------------------------------------------------------- JUEGO
/*
 JUEGO — el nivel, la pieza actual, la pieza siguiente, el tiempo máximo de
 permanencia de una pieza en una determinada línea,

– init
– mover
– rotar
– colision
– tiempo_caida_pieza
 */

/*
   Function: juego_init

   Inicializa una estructura juego.

   Parameters:

 *juego - Puntero a la estructura Juego que queremos inicializar.
   nivel_dificultad - Dificultad inicial del juego antes de ser elegida.
 */
void juego_init(Juego *juego)
{
    juego->nivel_dificultad = -1;
    juego->clase_pieza_siguiente = PIEZA_I;
    pieza_init(&juego->pieza_actual);
}

/*
   Function: juego_siguiente_pieza

   Inicializa una estructura juego.

   Parameters:

 *juego - Puntero a la estructura Juego que queremos inicializar.
   nivel_dificultad - Dificultad inicial del juego antes de ser elegida.
 */
void juego_siguiente_pieza(Juego *juego)
{
    char siguiente_pieza = juego->pieza_actual.clase;
    siguiente_pieza++;
    if (siguiente_pieza == NUM_CLASES) siguiente_pieza = 0;
    juego->clase_pieza_siguiente = siguiente_pieza;
}

/*
   Function: juego_tiempo_caida_pieza

   Devuelve el tiempo de caida de la pieza dependiendo del nivel actual.

   Parameters:

 *juego - Puntero a la estructura Juego de donde accedemos al nivel actual.
 */
int juego_tiempo_caida_pieza(Juego *juego)
{
    switch (juego->nivel_dificultad)
    {
        case -1: return 0;
            break;
        case 0: return VELOCIDAD_NIVEL_1;
            break;
        case 1: return VELOCIDAD_NIVEL_2;
            break;
        case 2: return VELOCIDAD_NIVEL_3;
            break;
    }
    return -1;
}

/*
   Function: juego_colision

   Devuelve 0 si no hay colisiones dado la posicion siguiente de la pieza y los
   leds de pantalla ocupados (Se ignora la posicion actual de la pieza).

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
   x_pos - Posicion x de la pieza donde queremos hacer la deteccion de colision.
   y_pos - Posicion y de la pieza donde queremos hacer la deteccion de colision.
   rotacion - Rotacion de la pieza donde queremos hacer la deteccion de colision.
 */
int juego_colision(Leds *leds, Juego *juego, int rotacion, int x_pos, int y_pos)
{
    int x_temp, y_temp;
    char leds_ocupacion, pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            leds_ocupacion = leds_get_posicion(leds, x_temp + x_pos, y_temp + y_pos);
            pieza_ocupacion = juego->pieza_actual.forma[(int) juego->pieza_actual.clase][rotacion][x_temp][y_temp];
            if ((leds_ocupacion == 1) && (pieza_ocupacion == 1))
            {
                return 1;
            }
        }
    }
    return 0;
}

/*
   Function: juego_game_over

   Devuelve 0 si la pieza actual no tiene ninguna parte por encima de la pantalla.

   Parameters:

 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
int juego_game_over(Juego *juego)
{
    int x;
    char pieza_ocupacion;

    for (x = 0; x < ANCHO_PIEZA; x++)
    {
        pieza_ocupacion = juego->pieza_actual.forma[(int) juego->pieza_actual.clase][juego->pieza_actual.rotacion][x][DEATH_LINE];
        if (pieza_ocupacion == 1)
        {
            return 1;
        }
    }

    return 0;
}

/*
   Function: juego_nueva_pieza

   Pinta la pieza antigua en la pantalla, coloca la nueva en posicion de salida y
   calcula la siguiente pieza.

   Parameters:

 *leds - Puntero a la estructura Leds para pintar la pieza con la que se estaba jugando.
 *juego - Puntero a la estructura Juego de donde accedemos a las piezas.
 */
void juego_nueva_pieza(Juego *juego)
{
    juego->pieza_actual.clase = juego->clase_pieza_siguiente;
    juego->pieza_actual.x = juego->pieza_actual.x_comienzo[(int) juego->pieza_actual.clase];
    juego->pieza_actual.y = juego->pieza_actual.y_comienzo[(int) juego->pieza_actual.clase];
    juego_siguiente_pieza(juego);
}

/*
   Function: juego_mover_pieza

   Mueve la pieza activa en la direccion indicada teniendo en cuenta si hay 
   colisiones. En caso de colision no hace nada.

   Parameters:

 *leds - Puntero a la estructura Leds para acceder a las colisiones.
 *juego - Puntero a la estructura Juego de donde accedemos al nivel actual.
   direccion - Caracter con la direccion en la que queremos mover la pieza.
 */
void juego_mover_pieza(Leds *leds, Juego *juego, char direccion)
{
    int x, y, game_over;
    x = pieza_get_x(&juego->pieza_actual);
    y = pieza_get_y(&juego->pieza_actual);

    switch (direccion)
    {
        case IZQUIERDA:
        {
            int hay_colision = juego_colision(leds, juego, juego->pieza_actual.rotacion, x - 1, y);
            if (!hay_colision)
            {
                juego->pieza_actual.x = x - 1;
            }
            break;
        }
        case ARRIBA:
        {
            int hay_colision = juego_colision(leds, juego, juego->pieza_actual.rotacion, x, y - 1);
            if (!hay_colision)
            {
                juego->pieza_actual.y = y - 1;
            }
            break;
        }
        case ABAJO:
        {
            int hay_colision = juego_colision(leds, juego, juego->pieza_actual.rotacion, x, y + 1);
            if (!hay_colision)
            {
                juego->pieza_actual.y = y + 1;
            }
            else
            {
                leds_pintar_pieza(leds, juego);
                game_over = juego_game_over(juego);
                if (!game_over)
                {
                    leds_borrar_filas_completadas(leds);
                    juego_nueva_pieza(juego);
                }

            }
            break;
        }
        case DERECHA:
        {
            int hay_colision = juego_colision(leds, juego, juego->pieza_actual.rotacion, x + 1, y);
            if (!hay_colision)
            {
                juego->pieza_actual.x = x + 1;
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

 *leds - Puntero a la estructura Leds para acceder a las colisiones.
 *juego - Puntero a la estructura Juego de donde accedemos al nivel actual.
 */
void juego_rotar_pieza(Leds *leds, Juego *juego)
{
    int hay_colision = juego_colision(
        leds,
        juego,
        juego->pieza_actual.rotacion + 1,
        pieza_get_x(&juego->pieza_actual),
        pieza_get_y(&juego->pieza_actual)
        );
    if (!hay_colision)
    {
        juego->pieza_actual.rotacion++;
    }
}

/*
   Function: juego_caida_timeout

   Gestiona la caida automatica de la pieza

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
    tiempo_caida - Tiempo en milisegundos que tarda en caer la pieza una unidad.
 */
void juego_caida_timeout(Leds *leds, Juego *juego, int tiempo_caida)
{
    static int contador = 0;
    contador++;
    if (contador == tiempo_caida)
    {
        contador = 0;
        leds_borrar_pieza(leds, juego);
        juego_mover_pieza(leds, juego, ABAJO);
        leds_pintar_pieza(leds, juego);

    }
}

/*
   Function: juego_rotar_pieza

   Rota la pieza activa teniendo en cuenta si hay colisiones. En caso de
   colision no hace nada.

   Parameters:

 *leds - Puntero a la estructura Leds para acceder a las colisiones.
 *juego - Puntero a la estructura Juego de donde accedemos al nivel actual.
 * tecla - Tecla pulsada en el teclado matricial
 */
void juego_tecla_pulsada(Leds *leds, Juego *juego, char tecla)
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
            leds_borrar_pieza(leds, juego);
            juego_rotar_pieza(leds, juego);
            leds_pintar_pieza(leds, juego);
            break;
        }
        case TECLA_IZQUIERDA:
        {
            leds_borrar_pieza(leds, juego);
            juego_mover_pieza(leds, juego, IZQUIERDA);
            leds_pintar_pieza(leds, juego);
            break;
        }
        case TECLA_ABAJO:
        {
            leds_borrar_pieza(leds, juego);
            juego_mover_pieza(leds, juego, ABAJO);
            leds_pintar_pieza(leds, juego);
            break;
        }
        case TECLA_DERECHA:
        {
            leds_borrar_pieza(leds, juego);
            juego_mover_pieza(leds, juego, DERECHA);
            leds_pintar_pieza(leds, juego);
            break;
        }
        case TECLA_ARRIBA:
        {
            leds_borrar_pieza(leds, juego);
            juego_mover_pieza(leds, juego, ARRIBA);
            leds_pintar_pieza(leds, juego);
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


