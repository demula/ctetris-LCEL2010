/*
   prueba_leds.c

   Archivo de prueba de algoritmos para el objeto Leds.

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

#include <stdio.h>
#include <stdlib.h>

/* Omitimos las librerias del Coldfire */
#define __M5272LIB_H__
#define	m5272_h

// ---------------------------------------------------------------------- HEADER
#include "../ctetris/src/juego.c"


// ------------------------------------------------------------ SETUPS & RESULTS
//Setup leds_fila_a_int
#define COLUMNA_PRUEBA_LEDS_FILA_A_INT 2
#define FILA_PRUEBA_LEDS_FILA_A_INT "01001001"

//Salida leds_fila_a_int
#define SALIDA_PRUEBA_LEDS_FILA_A_INT 73

//Setup leds_get_posicion
#define COLUMNA_PRUEBA_LEDS_GET_POSICION 2
#define FILA_PRUEBA_LEDS_GET_POSICION "01001001"
#define XP1_PRUEBA_LEDS_GET_POSICION 0
#define YP1_PRUEBA_LEDS_GET_POSICION -1
#define XP2_PRUEBA_LEDS_GET_POSICION -1
#define YP2_PRUEBA_LEDS_GET_POSICION 0
#define XP3_PRUEBA_LEDS_GET_POSICION 4
#define YP3_PRUEBA_LEDS_GET_POSICION 4
#define XP4_PRUEBA_LEDS_GET_POSICION 0
#define YP4_PRUEBA_LEDS_GET_POSICION 8
#define XP5_PRUEBA_LEDS_GET_POSICION 2
#define YP5_PRUEBA_LEDS_GET_POSICION 1
#define XP6_PRUEBA_LEDS_GET_POSICION 2
#define YP6_PRUEBA_LEDS_GET_POSICION 6

//Salidas leds_get_posicion
#define SALIDA_PRUEBA_LEDS_GET_POSICION_0_m1 0
#define SALIDA_PRUEBA_LEDS_GET_POSICION_m1_0 1
#define SALIDA_PRUEBA_LEDS_GET_POSICION_4_4 1
#define SALIDA_PRUEBA_LEDS_GET_POSICION_0_8 1
#define SALIDA_PRUEBA_LEDS_GET_POSICION_2_1 1
#define SALIDA_PRUEBA_LEDS_GET_POSICION_2_6 0


// --------------------------------------------------------------------- GLOBALS
/*
   Esta parte solo es necesaria si necesitamos que se guarden los valores entre
   tests.
 */
//Leds leds;
//Juego juego;


// --------------------------------------------------------------------- TARGETS
/* Ya incluidos en juego.c */


// --------------------------------------------------------------------- HELPERS

void print_pantalla(Leds *leds)
{
    int x, y;

    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        printf("         ");
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            printf("%i",leds->pantalla[x][y]);
        }
        printf("\n");
    }
}

void print_pieza(Juego *juego, char clase, int rotacion)
{
    int x, y;

    for (y = 0; y < ALTO_PIEZA; y++)
    {
        printf("         ");
        for (x = 0; x < ANCHO_PIEZA; x++)
        {
            printf("%i",juego->pieza_actual.forma[(int)clase][rotacion][x][y]);
        }
        printf("\n");
    }
}

// ----------------------------------------------------------------------- TESTS

int prueba_leds_init()
{
    Leds leds;
    int x, y;

    leds_init(&leds);

    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            if (leds.pantalla[x][y] != 0) return 1;
        }
    }
    return 0;
}

int prueba_leds_borrar_pantalla()
{
    Leds leds;
    int x, y;

    leds_init(&leds);

    //Cambiamos algunos bits
    leds.pantalla[NUM_COLUMNAS_LED - 2][NUM_FILAS_LED - 1] = 1;
    leds.pantalla[0][0] = 1;

    leds_borrar_pantalla(&leds);

    for (x = 0; x < NUM_COLUMNAS_LED; x++)
    {
        for (y = 0; y < NUM_FILAS_LED; y++)
        {
            if (leds.pantalla[x][y] != 0) return 1;
        }
    }
    return 0;
}

int prueba_leds_fila_a_int()
{
    Leds leds;
    int y, salida;
    char fila_prueba[NUM_FILAS_LED] = FILA_PRUEBA_LEDS_FILA_A_INT;

    leds_init(&leds);

    //Rellenamos los leds con la fila que queremos
    printf("    Valor de la entrada para leds_fila_a_int: ");
    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        leds.pantalla[COLUMNA_PRUEBA_LEDS_FILA_A_INT][y] = fila_prueba[y] - 48;
        printf("%i", fila_prueba[y] - 48);
    }
    printf("\n");

    salida = 0;
    leds_fila_a_int(&leds, COLUMNA_PRUEBA_LEDS_FILA_A_INT, &salida);

    printf("    Valor de la salida para leds_fila_a_int: %i\n", salida);

    if (salida != SALIDA_PRUEBA_LEDS_FILA_A_INT) return 1;

    return 0;
}

int prueba_leds_get_posicion()
{
    Leds leds;
    int y, salida;
    char fila_prueba[NUM_FILAS_LED] = FILA_PRUEBA_LEDS_GET_POSICION;

    leds_init(&leds);

    //Rellenamos los leds con la fila que queremos
    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        leds.pantalla[COLUMNA_PRUEBA_LEDS_GET_POSICION][y] = fila_prueba[y] - 48;
    }

    salida = 0;
    salida = leds_get_posicion(&leds, XP1_PRUEBA_LEDS_GET_POSICION, YP1_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP1_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP1_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_0_m1) return 1;

    salida = leds_get_posicion(&leds, XP2_PRUEBA_LEDS_GET_POSICION, YP2_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP2_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP2_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_m1_0) return 1;

    salida = leds_get_posicion(&leds, XP3_PRUEBA_LEDS_GET_POSICION, YP3_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP3_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP3_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_4_4) return 1;

    salida = leds_get_posicion(&leds, XP4_PRUEBA_LEDS_GET_POSICION, YP4_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP4_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP4_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_0_8) return 1;

    salida = leds_get_posicion(&leds, XP5_PRUEBA_LEDS_GET_POSICION, YP5_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP5_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP5_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_2_1) return 1;

    salida = leds_get_posicion(&leds, XP6_PRUEBA_LEDS_GET_POSICION, YP6_PRUEBA_LEDS_GET_POSICION);
    printf("    Valor de la salida para leds_get_posicion en ");
    printf("%i, ", XP6_PRUEBA_LEDS_GET_POSICION);
    printf("%i es: ", YP6_PRUEBA_LEDS_GET_POSICION);
    printf("%i\n", salida);
    if (salida != SALIDA_PRUEBA_LEDS_GET_POSICION_2_6) return 1;

    return 0;
}

int prueba_leds_set_posicion()
{
    Leds leds;
    leds_init(&leds);

    printf("    Valor de la pantalla antes de leds_set_posicion un cuadrado hueco:\n");
    print_pantalla(&leds);
    //Pintamos un cuadrado hueco en el centro de la pantalla
    leds_set_posicion(&leds, 0, 2, 1);
    leds_set_posicion(&leds, 1, 2, 1);
    leds_set_posicion(&leds, 2, 2, 1);
    leds_set_posicion(&leds, 3, 2, 1);
    leds_set_posicion(&leds, 0, 3, 1);
    leds_set_posicion(&leds, 0, 4, 1);
    leds_set_posicion(&leds, 3, 3, 1);
    leds_set_posicion(&leds, 3, 4, 1);
    leds_set_posicion(&leds, 0, 5, 1);
    leds_set_posicion(&leds, 1, 5, 1);
    leds_set_posicion(&leds, 2, 5, 1);
    leds_set_posicion(&leds, 3, 5, 1);
    
    printf("    Valor de la pantalla despues de leds_set_posicion un cuadrado hueco:\n");
    print_pantalla(&leds);

    leds_borrar_pantalla(&leds);
    leds_set_posicion(&leds, 0, 5, 1);
    leds_set_posicion(&leds, 1, 5, 1);
    leds_set_posicion(&leds, 2, 5, 1);
    leds_set_posicion(&leds, 3, 5, 1);
    leds_set_posicion(&leds, -1, 5, 1);
    leds_set_posicion(&leds, 4, 5, 1);


    printf("    Valor de la pantalla despues de leds_set_posicion una linea dentro y fuera de la pantalla:\n");
    print_pantalla(&leds);

    return 0;
}

int prueba_leds_pintar_pieza()
{
    Leds leds;
    Juego juego;
    leds_init(&leds);
    juego_init(&juego);
    printf("    Valor de la pantalla antes de leds_pintar_pieza:\n");
    print_pantalla(&leds);

    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 3;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza O:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 1;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza I:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza T:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 3;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza L:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza J:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 5;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza S:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    juego.pieza_actual.clase = 6;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    printf("    Valor de la pantalla despues de leds_pintar_pieza Z:\n");
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    return 0;
}

int prueba_leds_borrar_pieza()
{
    Leds leds;
    Juego juego;
    leds_init(&leds);
    juego_init(&juego);


    printf("    Valor de la pantalla antes de leds_borrar_pieza 0:\n");
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 3;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza O:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza I:\n");
    juego.pieza_actual.clase = 1;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza I:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza T:\n");
    juego.pieza_actual.clase = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza T:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza L:\n");
    juego.pieza_actual.clase = 3;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza L:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza J:\n");
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza J:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza S:\n");
    juego.pieza_actual.clase = 5;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza S:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);


    printf("    Valor de la pantalla antes de leds_borrar_pieza Z:\n");
    juego.pieza_actual.clase = 6;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 2;
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);

    printf("    Valor de la pantalla despues de leds_borrar_pieza Z:\n");
    leds_borrar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    return 0;
}

int prueba_leds_borrar_filas_completadas()
{
    return 0;
}





// ------------------------------------------------------------------------ MAIN

int main(int argc, char** argv)
{
    int p_leds_init, p_leds_borrar_pantalla, p_leds_fila_a_int,
        p_leds_get_posicion, p_leds_set_posicion, p_leds_pintar_pieza,
        p_leds_borrar_pieza, p_leds_borrar_filas_completadas;
    printf("Comienzo de pruebas del objeto Leds:\n");

    p_leds_init = prueba_leds_init();
    if (!p_leds_init)
    {
        printf("Pasa prueba_leds_init\n");
    } else
    {
        printf("FAIL prueba_leds_init\n");
    }

    p_leds_borrar_pantalla = prueba_leds_borrar_pantalla();
    if (!p_leds_borrar_pantalla)
    {
        printf("Pasa prueba_leds_borrar_pantalla\n");
    } else
    {
        printf("FAIL prueba_leds_borrar_pantalla\n");
    }

    p_leds_fila_a_int = prueba_leds_fila_a_int();
    if (!p_leds_fila_a_int)
    {
        printf("Pasa prueba_leds_fila_a_int\n");
    } else
    {
        printf("FAIL prueba_leds_fila_a_int\n");
    }

    p_leds_get_posicion = prueba_leds_get_posicion();
    if (!p_leds_get_posicion)
    {
        printf("Pasa prueba_leds_get_posicion\n");
    } else
    {
        printf("FAIL prueba_leds_get_posicion\n");
    }

    p_leds_set_posicion = prueba_leds_set_posicion();
    if (!p_leds_set_posicion)
    {
        printf("Pasa prueba_leds_set_posicion\n");
    } else
    {
        printf("FAIL prueba_leds_set_posicion\n");
    }

    p_leds_pintar_pieza = prueba_leds_pintar_pieza();
    if (!p_leds_pintar_pieza)
    {
        printf("Pasa prueba_leds_pintar_pieza\n");
    } else
    {
        printf("FAIL prueba_leds_pintar_pieza\n");
    }

    p_leds_borrar_pieza = prueba_leds_borrar_pieza();
    if (!p_leds_borrar_pieza)
    {
        printf("Pasa prueba_leds_borrar_pieza\n");
    } else
    {
        printf("FAIL prueba_leds_borrar_pieza\n");
    }

    p_leds_borrar_filas_completadas = prueba_leds_borrar_filas_completadas();
    if (!p_leds_borrar_filas_completadas)
    {
        printf("Pasa prueba_leds_borrar_filas_completadas\n");
    } else
    {
        printf("FAIL prueba_leds_borrar_filas_completadas\n");
    }

    if (!(p_leds_init || p_leds_borrar_pantalla || p_leds_fila_a_int ||
        p_leds_get_posicion || p_leds_set_posicion || p_leds_pintar_pieza ||
        p_leds_borrar_pieza || p_leds_borrar_filas_completadas))
    {
        printf("\nTODAS LAS PRUEBAS SE HAN PASADO CON EXITO.\n");
    }
    return (EXIT_SUCCESS);
}

