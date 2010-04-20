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

#define mbar_writeShort(dir,x) if (dir == MCFSIM_TRR0) r_trr0 = x;\
                                if (dir == MCFSIM_TMR0) r_tmr0 = x

// ---------------------------------------------------------------------- HEADER
#include "../src/melodia.c"

// ------------------------------------------------------------ SETUPS & RESULTS
#define PRUEBA_EXITO 0
#define PRUEBA_FALLO 1

//Salida prueba_melodia_stop
#define SALIDA_STOP_TMR0 0x003C
#define SALIDA_STOP_TRR0 0

//init 0x4F3D); TMR0: PS=0x50-1 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
//stop 0x003C); TMR0: PS=0x00 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=0
/*repr freq
 trr0 = ((MCF_CLK) / 16) / (2 * frecuenciaNotaActual);
        mbar_writeShort(MCFSIM_TRR0, trr0);   //Fijamos la cuenta final del contador
        mbar_writeShort(MCFSIM_TMR0, 0x003D); //TMR0: PS=0x00 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=1
 */
//Setup prueba_melodia_set_frecuencia
#define FREC_880 880
#define FREC_1319 1319
#define FREC_415 415
#define FREC_1760 1760
#define FREC_0 0

//Salida prueba_melodia_set_frecuencia
#define SALIDA_SET_TMR0 0x003D
#define SALIDA_SET_880_TRR0 0x0927
#define SALIDA_SET_1319_TRR0 0x061B
#define SALIDA_SET_415_TRR0 0x1369
#define SALIDA_SET_1760_TRR0 0x0493

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
            return PRUEBA_FALLO;
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
            return PRUEBA_FALLO;
        }
        if (posicion % 10 == 9)
        {
            printf("\n        ");
        }
    }
    printf("\n");
    return PRUEBA_EXITO;
}

int prueba_melodia_stop()
{
    melodia_stop();
    printf("    Prueba de melodia_stop():\n");
    printf("        Valor del TRR0 %i, debe ser %i.\n", r_trr0, SALIDA_STOP_TRR0);
    if (r_trr0 != SALIDA_STOP_TRR0) return PRUEBA_FALLO;
    printf("        Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_STOP_TMR0);
    if (r_tmr0 != SALIDA_STOP_TMR0) return PRUEBA_FALLO;
    return PRUEBA_EXITO;
}

int prueba_melodia_set_frecuencia()
{
    printf("    Prueba de prueba_melodia_set_frecuencia():\n");
    melodia_set_frecuencia(FREC_880);
    printf("        Freciencia %i\n", FREC_880);
    printf("            Valor del TRR0 %i, debe ser %i.\n", r_trr0, SALIDA_SET_880_TRR0);
    if (r_trr0 != SALIDA_SET_880_TRR0) return PRUEBA_FALLO;
    printf("            Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_SET_TMR0);
    if (r_tmr0 != SALIDA_SET_TMR0) return PRUEBA_FALLO;
    melodia_set_frecuencia(FREC_1319);
    printf("        Freciencia %i\n", FREC_1319);
    printf("            Valor del TRR0 %i, debe ser %i.\n", r_trr0, SALIDA_SET_1319_TRR0);
    if (r_trr0 != SALIDA_SET_1319_TRR0) return PRUEBA_FALLO;
    printf("            Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_SET_TMR0);
    if (r_tmr0 != SALIDA_SET_TMR0) return PRUEBA_FALLO;
    melodia_set_frecuencia(FREC_415);
    printf("        Freciencia %i\n", FREC_415);
    printf("            Valor del TRR0 %i, debe ser %i.\n", r_trr0, SALIDA_SET_415_TRR0);
    if (r_trr0 != SALIDA_SET_415_TRR0) return PRUEBA_FALLO;
    printf("            Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_SET_TMR0);
    if (r_tmr0 != SALIDA_SET_TMR0) return PRUEBA_FALLO;
    melodia_set_frecuencia(FREC_1760);
    printf("        Freciencia %i\n", FREC_1760);
    printf("            Valor del TRR0 %i, debe ser %i.\n", r_trr0, SALIDA_SET_1760_TRR0);
    if (r_trr0 != SALIDA_SET_1760_TRR0) return PRUEBA_FALLO;
    printf("            Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_SET_TMR0);
    if (r_tmr0 != SALIDA_SET_TMR0) return PRUEBA_FALLO;
    melodia_set_frecuencia(FREC_0);
    printf("        Freciencia %i\n", FREC_0);
    printf("            Valor del TRR0 %i, indiferente.\n", r_trr0);
    printf("            Valor del TMR0 %i, debe ser %i.\n", r_tmr0, SALIDA_STOP_TMR0);
    if (r_tmr0 != SALIDA_STOP_TMR0) return PRUEBA_FALLO;
    return PRUEBA_EXITO;
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
    Melodia melodia;
    int nota;
    int tiempo_nota;
    int tiempo_total_nota;

    printf("    Prueba de prueba_melodia_play():  (TMR0, TRR0)\n        ");
    melodia_init(&melodia);
    for (nota = 0; nota < NUMERO_TOTAL_NOTAS + 2; nota++)//2 notas de mas para ver bucle
    {
        tiempo_total_nota = melodia.tiempo[nota % NUMERO_TOTAL_NOTAS];
        for (tiempo_nota = 0; tiempo_nota < tiempo_total_nota; tiempo_nota++)
        {
            melodia_play(&melodia, FALSE); //Se tiene que llamar cada ms de la nota
        }
        printf("(%i, %i), ", r_tmr0, r_trr0);
        if (nota % 6 == 5)
        {
            printf("\n        ");
        }
    }
    printf("\n");
    return PRUEBA_EXITO;
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