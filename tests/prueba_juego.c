/*
   prueba_juego.c

   Archivo de prueba de algoritmos para el objeto Juego.

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
#define __M5272LCD_C__
#define	_HARDWARE_CONF_H
#define	_HARDWARE_CONF_C


// ---------------------------------------------------------------------- HEADER
/* Declaramos las funciones usadas de las libs del Coldfire para que se queje */
#define NUM_FILAS_TECLADO 4
#define NUM_COLS_TECLADO 4
#define RET_OPTOACOPLADORES 1150
#define RET_REBOTES 1150
#define SIN_SIGNO 1	// Flag para las funciones outNum y outNumDec
#define TRUE 1
#define FALSE 0
#define KEY_LEFT 'a'//"\0x14b"
#define KEY_UP 'w'//"\0x148"
#define KEY_DOWN 's'//"\0x150"
#define KEY_RIGHT 'd'//"\0x14d"

void set16_puertoS(unsigned short int valor)
{
}

void habilitar_interrupciones(void)
{
}

void deshabilitar_interrupciones(void)
{
}

int lee_puertoE(void)
{
}

void retardo(int ms)
{
    usleep(ms * 1000);
}

void output(char string[])
{
    printf("%s", string);
}

void outNum(int base, int numero, int opciones)
{
    char numero_string [5];
    sprintf(numero_string, "%i", numero);
    output(numero_string);
}

#include "../src/control.c"


// ------------------------------------------------------------ SETUPS & RESULTS
#define PRUEBA_EXITO 0
#define PRUEBA_FALLO 1

//Setup juego_colision
#define COLUMNA_PRUEBA_LEDS_FILA_A_INT 2
#define FILA_PRUEBA_LEDS_FILA_A_INT "01001001"

//Salida juego_colision
#define SALIDA_PRUEBA_JUEGO_COLISION_PARED 1
#define SALIDA_PRUEBA_JUEGO_COLISION_ABAJO 1
#define SALIDA_PRUEBA_JUEGO_COLISION_INTERMEDIA 1
#define SALIDA_PRUEBA_JUEGO_COLISION_ROTACION 1
#define SALIDA_PRUEBA_JUEGO_COLISION_SIN 0


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
            printf("%i", leds->pantalla[x][y]);
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
            printf("%i", juego->pieza_actual.forma[(int) clase][rotacion][x][y]);
        }
        printf("\n");
    }
}

// ----------------------------------------------------------------------- TESTS

int prueba_juego_colision()
{
    //Setup general
    Juego juego;
    Leds leds;
    int salida;
    juego_init(&juego);
    leds_init(&leds);

    //Colision pared izquierda
    juego.pieza_actual.clase = 0;
    juego.pieza_actual.rotacion = 0;
    juego.pieza_actual.x = -1;
    juego.pieza_actual.y = 3;

    salida = juego_colision(
        &leds,
        &juego,
        juego.pieza_actual.rotacion,
        juego.pieza_actual.x,
        juego.pieza_actual.y
        );

    printf("    Valor de la entrada para juego_colision pared izquierda:\n");
    printf("        Pieza\n");
    print_pieza(
        &juego,
        juego.pieza_actual.clase,
        juego.pieza_actual.rotacion
        );
    printf("        Pantalla\n");
    print_pantalla(&leds);
    printf("        Pantalla + Pieza\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);
    printf("    Valor de la salida para juego_colision pared izquierda: %i\n",salida);
    if (salida != SALIDA_PRUEBA_JUEGO_COLISION_PARED) return PRUEBA_FALLO;


    //Colision por la parte de abajo de la pieza
    leds_set_posicion(&leds, 0, 5, 1);
    leds_set_posicion(&leds, 1, 5, 1);
    leds_set_posicion(&leds, 2, 5, 1);
    leds_set_posicion(&leds, 3, 5, 1);

    juego.pieza_actual.clase = 6;
    juego.pieza_actual.rotacion = 0;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 3;

    salida = juego_colision(
        &leds,
        &juego,
        juego.pieza_actual.rotacion,
        juego.pieza_actual.x,
        juego.pieza_actual.y
        );

    printf("    Valor de la entrada para juego_colision parte de abajo:\n");
    printf("        Pieza\n");
    print_pieza(
        &juego,
        juego.pieza_actual.clase,
        juego.pieza_actual.rotacion
        );
    printf("        Pantalla\n");
    print_pantalla(&leds);
    printf("        Pantalla + Pieza\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);
    printf("    Valor de la salida para juego_colision parte de abajo: %i\n",salida);
    if (salida != SALIDA_PRUEBA_JUEGO_COLISION_ABAJO) return PRUEBA_FALLO;


    //Colision por una esquina intermedia de la pieza
    leds_set_posicion(&leds, 3, 7, 1);
    leds_set_posicion(&leds, 3, 6, 1);
    leds_set_posicion(&leds, 3, 5, 1);
    leds_set_posicion(&leds, 3, 4, 1);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    salida = juego_colision(
        &leds,
        &juego,
        juego.pieza_actual.rotacion,
        juego.pieza_actual.x,
        juego.pieza_actual.y
        );

    printf("    Valor de la entrada para juego_colision esquina intermedia:\n");
    printf("        Pieza\n");
    print_pieza(
        &juego,
        juego.pieza_actual.clase,
        juego.pieza_actual.rotacion
        );
    printf("        Pantalla\n");
    print_pantalla(&leds);
    printf("        Pantalla + Pieza\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);
    printf("    Valor de la salida para juego_colision esquina intermedia: %i\n",salida);
    if (salida != SALIDA_PRUEBA_JUEGO_COLISION_INTERMEDIA) return PRUEBA_FALLO;

    //Sin colision
    juego.pieza_actual.clase = 1;
    juego.pieza_actual.rotacion = 0;
    juego.pieza_actual.x = 2;
    juego.pieza_actual.y = 2;

    salida = juego_colision(
        &leds,
        &juego,
        juego.pieza_actual.rotacion,
        juego.pieza_actual.x,
        juego.pieza_actual.y
        );

    printf("    Valor de la entrada para juego_colision sin colision:\n");
    printf("        Pieza\n");
    print_pieza(
        &juego,
        juego.pieza_actual.clase,
        juego.pieza_actual.rotacion
        );
    printf("        Pantalla\n");
    print_pantalla(&leds);
    printf("        Pantalla + Pieza\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);
    printf("    Valor de la salida para juego_colision sin colision: %i\n",salida);
    if (salida != SALIDA_PRUEBA_JUEGO_COLISION_SIN) return PRUEBA_FALLO;

    return PRUEBA_EXITO;
}

int prueba_juego_mover_pieza()
{
    //Setup general
    Juego juego;
    Leds leds;
    Resultados resultados;
    Estado estado;
    juego_init(&juego);
    leds_init(&leds);
    resultados_init(&resultados);
    estado_init(&estado);

    //Con posibilidad de movimiento
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza con posibilidad de movimiento a la izquierda:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_mover_pieza(&leds, &juego, &resultados, &estado, IZQUIERDA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //Contra la pared
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza SIN posibilidad de movimiento a la derecha:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_mover_pieza(&leds, &juego, &resultados, &estado, DERECHA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //Contra restos de piezas CON posibilidad de movimiento
    leds_set_posicion(&leds, 3, 7, 1);
    leds_set_posicion(&leds, 3, 6, 1);
    leds_set_posicion(&leds, 3, 5, 1);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza con posibilidad de movimiento a la derecha:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_mover_pieza(&leds, &juego, &resultados, &estado, DERECHA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //Contra restos de piezas SIN posibilidad de movimiento
    leds_set_posicion(&leds, 3, 7, 1);
    leds_set_posicion(&leds, 3, 6, 1);
    leds_set_posicion(&leds, 3, 5, 1);
    leds_set_posicion(&leds, 2, 6, 1);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza SIN posibilidad de movimiento a la derecha:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_mover_pieza(&leds, &juego, &resultados, &estado, DERECHA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);
    return PRUEBA_EXITO;
}

int prueba_juego_rotar_pieza()
{
    //Setup general
    Juego juego;
    Leds leds;
    juego_init(&juego);
    leds_init(&leds);

    //Con posibilidad de rotacion
    leds_set_posicion(&leds, 3, 7, 1);
    leds_set_posicion(&leds, 3, 6, 1);
    leds_set_posicion(&leds, 3, 5, 1);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza con posibilidad de rotar:\n");
    printf("        Pantalla antes de rotar\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de rotar la pieza\n");
    juego_rotar_pieza(&leds, &juego);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //Contra la pared
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 0;
    juego.pieza_actual.x = 2;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza SIN posibilidad de rotar por la pared:\n");
    printf("        Pantalla antes de rotar\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de rotar la pieza\n");
    juego_rotar_pieza(&leds, &juego);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //Contra restos de piezas
    leds_set_posicion(&leds, 3, 7, 1);
    leds_set_posicion(&leds, 3, 5, 1);

    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_mover_pieza SIN posibilidad de rotar:\n");
    printf("        Pantalla antes de rotar\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de rotar la pieza\n");
    juego_rotar_pieza(&leds, &juego);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    return PRUEBA_EXITO;
}

int prueba_juego_tecla_pulsada()
{
    //Setup general
    Juego juego;
    Leds leds;
    Resultados resultados;
    Estado estado;
    juego_init(&juego);
    leds_init(&leds);
    resultados_init(&resultados);
    estado_init(&estado);

    //DERECHA
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 0;
    juego.pieza_actual.y = 4;
    printf("    Valor de la entrada para juego_tecla_pulsada DERECHA:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_DERECHA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //IZQUIERDA
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_tecla_pulsada IZQUIERDA:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_IZQUIERDA);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //ABAJO
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_tecla_pulsada ABAJO:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de mover la pieza\n");
    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_ABAJO);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    //ROTAR
    juego.pieza_actual.clase = 4;
    juego.pieza_actual.rotacion = 2;
    juego.pieza_actual.x = 1;
    juego.pieza_actual.y = 4;

    printf("    Valor de la entrada para juego_tecla_pulsada ROTAR:\n");
    printf("        Pantalla antes de mover\n");
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pieza(&leds,&juego);
    printf("        Pantalla despues de rotar la pieza\n");
    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_ROTAR);
    leds_pintar_pieza(&leds, &juego);
    print_pantalla(&leds);
    leds_borrar_pantalla(&leds);

    return PRUEBA_EXITO;
}


// ------------------------------------------------------------------------ MAIN

int main(int argc, char** argv)
{
    int p_juego_colision, p_juego_mover_pieza,
        p_juego_rotar_pieza, p_juego_tecla_pulsada;
    printf("Comienzo de pruebas del objeto Juego:\n");

    p_juego_colision = prueba_juego_colision();
    if (!p_juego_colision)
    {
        printf("Pasa prueba_juego_colision\n");
    }
    else
    {
        printf("FAIL prueba_juego_colision\n");
    }
    p_juego_mover_pieza = prueba_juego_mover_pieza();
    if (!p_juego_mover_pieza)
    {
        printf("Pasa prueba_juego_mover_pieza\n");
    }
    else
    {
        printf("FAIL prueba_juego_mover_pieza\n");
    }
    p_juego_rotar_pieza = prueba_juego_rotar_pieza();
    if (!p_juego_rotar_pieza)
    {
        printf("Pasa prueba_juego_rotar_pieza\n");
    }
    else
    {
        printf("FAIL prueba_juego_rotar_pieza\n");
    }
    p_juego_tecla_pulsada = prueba_juego_tecla_pulsada();
    if (!p_juego_tecla_pulsada)
    {
        printf("Pasa prueba_juego_tecla_pulsada\n");
    }
    else
    {
        printf("FAIL prueba_juego_tecla_pulsada\n");
    }
    if (!(p_juego_colision || p_juego_mover_pieza || p_juego_rotar_pieza || p_juego_tecla_pulsada))
    {
        printf("\nTODAS LAS PRUEBAS SE HAN PASADO CON EXITO.\n");
    }
    return (EXIT_SUCCESS);
}

