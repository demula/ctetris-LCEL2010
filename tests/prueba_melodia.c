/*
   prueba_melodia.c

   Archivo de prueba de algoritmos para el objeto Melodia.

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

#define MCFSIM_TMR0 1
#define MCFSIM_TRR0 2
#define MCF_CLK 66000000

static int r_trr0 = 0;
static int r_tmr0 = 0;

#define mbar_writeShort(dir,x) if (dir == MCFSIM_TRR0) r_trr0 = x;if (dir == MCFSIM_TMR0) r_tmr0 = x


// ---------------------------------------------------------------------- HEADER
#include "../ctetris/src/melodia.c"


// ------------------------------------------------------------ SETUPS & RESULTS
//Setup leds_fila_a_int

//Salida leds_fila_a_int

//Setup leds_get_posicion

//Salidas leds_get_posicion

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

void beep(int freq, int length)
{
    fprintf(stdout, "\33[10;%d]\33[11;%d]\a\33[10]\33[11]", freq, length);
    fflush(stdout);
    if (length) usleep(length * 1000L);
}

// ----------------------------------------------------------------------- TESTS
//Prototipos de las funciones de melodia.c

int prueba_melodia_init()
{
    int posicion;
    Melodia melodia;
    int frecuencias_temp[NUMERO_TOTAL_NOTAS] = FRECUENCIAS;
    int tiempos_temp[NUMERO_TOTAL_NOTAS] = TIEMPOS;

    melodia_init(&melodia);

    printf("    Valores de frecuencia despues de melodia_init():\n        ");
    for (posicion = 0; posicion < NUMERO_TOTAL_NOTAS; posicion++)
    {
        printf("%i, ", melodia.frecuencia[posicion]);
        if (melodia.frecuencia[posicion] != frecuencias_temp[posicion])
        {
            return 1;
        }
        if (posicion % 10 == 9)
        {
            printf("\n        ");
        }
    }

    printf("\n");
    printf("    Valores de tiempo despues de melodia_init():\n        ");
    for (posicion = 0; posicion < NUMERO_TOTAL_NOTAS; posicion++)
    {
        printf("%i, ", melodia.tiempo[posicion]);
        if (melodia.tiempo[posicion] != tiempos_temp[posicion])
        {
            return 1;
        }
        if (posicion % 10 == 9)
        {
            printf("\n        ");
        }
    }
    printf("\n");
    return 0;
}

int prueba_melodia_stop()
{
    melodia_stop();
    printf("    Prueba de melodia_stop():\n");
    printf("        Valor del TRR0 %i\n", r_trr0);
    printf("        Valor del TMR0 %i\n", r_tmr0);

    return 0;
}

int prueba_melodia_set_frecuencia()
{
    //melodia_set_frecuencia(int frecuencia);
    return 0;
}

int prueba_melodia_play()
{
    /*
    int nota;
    for (nota = 0; nota < NUMERO_TOTAL_NOTAS; nota++)
    {
        beep(p_melodia->frecuencia[nota],p_melodia->tiempo[nota]);
    }
     */
    //melodia_play(Melodia *p_melodia, char reset);
    return 0;
}

// ------------------------------------------------------------------------ MAIN

int main(int argc, char** argv)
{
    int p_melodia_init, p_melodia_play, p_melodia_stop, p_melodia_set_frecuencia;
    printf("Comienzo de pruebas del objeto Melodia:\n");

    p_melodia_init = prueba_melodia_init();
    if (!p_melodia_init)
    {
        printf("Pasa prueba_melodia_init\n");
    }
    else
    {
        printf("FAIL prueba_melodia_init\n");
    }

    p_melodia_stop = prueba_melodia_stop();
    if (!p_melodia_stop)
    {
        printf("Pasa prueba_melodia_stop\n");
    }
    else
    {
        printf("FAIL prueba_melodia_stop\n");
    }

    p_melodia_set_frecuencia = prueba_melodia_set_frecuencia();
    if (!p_melodia_set_frecuencia)
    {
        printf("Pasa prueba_melodia_set_frecuencia\n");
    }
    else
    {
        printf("FAIL prueba_melodia_set_frecuencia\n");
    }

    p_melodia_play = prueba_melodia_play();
    if (!p_melodia_play)
    {
        printf("Pasa prueba_melodia_play\n");
    }
    else
    {
        printf("FAIL prueba_melodia_play\n");
    }



    if (!(p_melodia_init || p_melodia_play || p_melodia_stop || p_melodia_set_frecuencia))
    {
        printf("\nTODAS LAS PRUEBAS SE HAN PASADO CON EXITO.\n");
    }
    usleep(1000000);
    return (EXIT_SUCCESS);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void beep(int freq, int length)
{
  fprintf(stdout,"\33[10;%d]\33[11;%d]\a\33[10]\33[11]", freq, length);
  fflush(stdout);
  if (length) usleep(length*1000L);
}


void main(int argc, char *argv[])
{
  //beep(467,1500);
  printf("\007");
  printf("\a");
  usleep(1000*1000L);
  exit(0);
}
 */