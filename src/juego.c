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
    for (posicion_origen = 0; posicion_origen < ANCHO_PIEZA * ALTO_PIEZA * ROTACIONES - ALTO_PIEZA * ROTACIONES; posicion_origen++)
    {
        switch (origen[posicion_origen])
        {
            case '0':
                forma[clase][posicion_destino_rotacion][posicion_destino_x][posicion_destino_y] = 0;
                posicion_destino_x++;
                break;
            case '1':
                forma[clase][posicion_destino_rotacion][posicion_destino_x][posicion_destino_y] = 1;
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


// ----------------------------------------------------------------------- JUEGO
/*
 JUEGO —
 *
 *el nivel, la pieza actual, la pieza siguiente, el tiempo
máximo de permanencia de una pieza en una determinada línea,

 *
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
void juego_init(Juego *juego, int nivel_dificultad)
{
    juego->nivel_dificultad = nivel_dificultad;
    juego->clase_pieza_siguiente = PIEZA_I;
    pieza_init(&juego->pieza_actual);
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
        case 0: return 0;
            break;
        case 1: return VELOCIDAD_NIVEL_1;
            break;
        case 2: return VELOCIDAD_NIVEL_2;
            break;
        case 3: return VELOCIDAD_NIVEL_3;
            break;
    }
    return -1;
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
    } else if (y >= NUM_FILAS_LED)
    {
        return 1;
    } else if (y < 0)
    {
        return 0;
    } else
    {
        return leds->pantalla[x][y];
    }
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
            pieza_ocupacion = juego->pieza_actual.forma[juego->pieza_actual.clase][rotacion][x_temp][y_temp];
            if ((leds_ocupacion == 1) && (pieza_ocupacion == 1))
            {
                return 1;
            }
        }
    }
    return 0;
}

/*
   Function: juego_fijar_pieza

   Copia la pieza actual en su posicion a la pantalla de leds. NO TIENE EN CUENTA
   SI HAY LEDS OCUPADOS.

   Parameters:

 *leds - Puntero a la estructura Leds que contiene la pantalla.
 *juego - Puntero a la estructura Juego de donde accedemos a la pieza actual.
 */
void juego_fijar_pieza(Leds *leds, Juego *juego)
{
    int x_temp, y_temp;
    char pieza_ocupacion;
    for (y_temp = 0; y_temp < ALTO_PIEZA; y_temp++)
    {
        for (x_temp = 0; x_temp < ANCHO_PIEZA; x_temp++)
        {
            pieza_ocupacion = juego->pieza_actual.forma[juego->pieza_actual.clase][juego->pieza_actual.rotacion][x_temp][y_temp];
            if (pieza_ocupacion == 1)
            {
                leds->pantalla[juego->pieza_actual.x + x_temp][juego->pieza_actual.y + y_temp] = 1;
            }
        }
    }
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
    int x, y;
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
    switch (tecla)
    {
        case TECLA_ROTAR:
        {
            juego_rotar_pieza(leds, juego);
            break;
        }
        case TECLA_IZQUIERDA:
        {
            juego_mover_pieza(leds, juego, IZQUIERDA);
            break;
        }
        case TECLA_ABAJO:
        {
            juego_mover_pieza(leds, juego, ABAJO);
            break;
        }
        case TECLA_DERECHA:
        {
            juego_mover_pieza(leds, juego, DERECHA);
            break;
        }
        case TECLA_ARRIBA:
        {
            juego_mover_pieza(leds, juego, ARRIBA);
            break;
        }
        case TECLA_SALIDA:
        {
            //_exit(0);
            break;
        }
    }
}