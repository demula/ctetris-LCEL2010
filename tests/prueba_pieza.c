/*
   prueba_pieza.c

   Archivo de prueba de algoritmos para el objeto Pieza.

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
#define __M5272LCD_C__
#define __M5272LIB_H__
#define	m5272_h
#define	_HARDWARE_CONF_C

// ---------------------------------------------------------------------- HEADER
/* Declaramos las funciones usadas de las libs del Coldfire para que se queje */
#define TRUE 1 //cualquier cosa distinta de 0 es verdadera
#define FALSE 0
#define SIN_SIGNO 1
#define NUM_FILAS_TECLADO 4
#define NUM_COLS_TECLADO 4
#define RET_OPTOACOPLADORES 1150
#define RET_REBOTES 1150

void habilitar_interrupciones(void)
{
}

void deshabilitar_interrupciones(void)
{
}

void outNum(int base, long num, char opciones)
{
}

void retardo(int microsegundos)
{
}

char lee_puertoE(void)
{
}

void set16_puertoS(unsigned short int valor)
{
}

void output(char string[])
{
}

#include "../src/juego.c"


// ------------------------------------------------------------ SETUPS & RESULTS
#define PRUEBA_EXITO 0
#define PRUEBA_FALLO 1

//Setup excita_teclado
#define ROTACION_PRUEBA_RELLENA_ARRAY_FORMA 2
#define FORMA_PRUEBA_RELLENA_ARRAY_FORMA "0100,0110,0100,0000;0100,1110,0000,0000;0100,1100,0100,0000;0000,1110,0100,0000;"

//Salidas excita_teclado
#define SALIDA_PRUEBA_RELLENA_ARRAY_FORMA "0100110001000000" //Ojo, tiene que coincidir con la rotacion


// --------------------------------------------------------------------- GLOBALS
/*
   Esta parte solo es necesaria si necesitamos que se guarden los valores entre
   tests.
 */
//Pieza pieza;


// --------------------------------------------------------------------- TARGETS
/* Incluido en juego.c */


// ----------------------------------------------------------------------- TESTS
int prueba_rellena_array_forma()
{
    char forma[NUM_CLASES][ROTACIONES][ANCHO_PIEZA][ALTO_PIEZA];
    //Iniciamos a 0 todo el array
    int c,r,x,y;
    char salida_esperada[ANCHO_PIEZA*ALTO_PIEZA] = SALIDA_PRUEBA_RELLENA_ARRAY_FORMA;
    for (c = 0;c<NUM_CLASES;c++)
    {
        for (r=0;r<ROTACIONES;r++)
        {
            for(x=0;x<ANCHO_PIEZA;x++)
            {
                for(y=0;y<ALTO_PIEZA;y++)
                {
                    forma[c][r][x][y] = 0;
                }
            }
        }
    }

    rellena_array_forma(forma, FORMA_PRUEBA_RELLENA_ARRAY_FORMA, 2);
    printf("    Valores de la forma de prueba:\n");

    for (y=0;y<ALTO_PIEZA;y++)
    {
        printf("        ");
        for (x=0;x<ANCHO_PIEZA;x++)
        {
            printf("%i",forma[2][ROTACION_PRUEBA_RELLENA_ARRAY_FORMA][x][y]);
            //Restamos 48 para que coincida con el caracter
            if (forma[2][ROTACION_PRUEBA_RELLENA_ARRAY_FORMA][x][y] != (salida_esperada[y*ANCHO_PIEZA + x] - 48))
            {
                return PRUEBA_FALLO;
            }
        }
        printf("\n");
    }
    return PRUEBA_EXITO;
}

void prueba_pieza_init()
{
    Pieza pieza;
    pieza_init(&pieza);

    printf("    Valores de todas las piezas con su respectivos puntos de inicio:\n");
    int c,r,x,y;
    for (c = 0;c<NUM_CLASES;c++)
    {
        printf("        Puntos de comienzo para pieza %i:  ",c);
        printf("x:%i, ",pieza.x_comienzo[c]);
        printf("y:%i\n",pieza.y_comienzo[c]);
        for(y=0;y<ALTO_PIEZA;y++)
        {
            printf("        ");
            for (r=0;r<ROTACIONES;r++)
            {
                printf("    ");
                for(x=0;x<ANCHO_PIEZA;x++)
                {
                    printf("%i",pieza.forma[c][r][x][y]);
                }
            }
            printf("\n");
        }
    }

}


// ------------------------------------------------------------------------ MAIN
int main(int argc, char** argv)
{
    int p_rellena_array_forma;
    printf("Comienzo de pruebas del objeto Pieza:\n");

    p_rellena_array_forma = prueba_rellena_array_forma();
    if (!p_rellena_array_forma) {printf("Pasa prueba_rellena_array_forma\n");} else { printf("FAIL prueba_rellena_array_forma\n");}

    prueba_pieza_init();

    if (!(p_rellena_array_forma))
    {
        printf("\nTODAS LAS PRUEBAS SE HAN PASADO CON EXITO.\n");
    }
    return (EXIT_SUCCESS);
}

