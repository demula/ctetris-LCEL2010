/*
   prueba_puerto.c

   Archivo de prueba de algoritmos para el objeto Puerto.

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

// ---------------------------------------------------------------------- HEADER
/* Declaramos las funciones usadas de las libs del Coldfire para que se queje */
void set16_puertoS(unsigned short int valor){}
void output(char string[]){}
#include "../src/control.c"


// ------------------------------------------------------------ SETUPS & RESULTS
//Salidas prueba_init
#define SALIDA_PRUEBA_INIT_SITUACION_PUERTO 0

//Salidas columna_a_puerto
#define SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_0 0x0010
#define SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_1 0x0020
#define SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_2 0x0040
#define SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_3 0x0080

//Setup fila_a_puerto
#define FILA_DE_PRUEBA_1 0xF0 //11110000
#define FILA_DE_PRUEBA_2 0x0F //00001111
#define FILA_DE_PRUEBA_3 0x96 //10010110
#define FILA_DE_PRUEBA_4 0x6D //01101101

//Salidas fila_a_puerto
#define SALIDA_PRUEBA_FILA_A_PUERTO_1 0x00000F00 //(extension signo hasta 32 bits)00001111 | 0000 | 0000
#define SALIDA_PRUEBA_FILA_A_PUERTO_2 0xFFFFF000 //(extension signo hasta 32 bits)11110000 | 0000 | 0000
#define SALIDA_PRUEBA_FILA_A_PUERTO_3 0x00006900 //(extension signo hasta 32 bits)01101001 | 0000 | 0000
#define SALIDA_PRUEBA_FILA_A_PUERTO_4 0xFFFF9200 //(extension signo hasta 32 bits)10010010 | 0000 | 0000

//Salidas puerto_excita_columna
#define SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_1 0x00000F11
#define SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_2 0xFFFFF021
#define SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_3 0x00006941
#define SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_4 0xFFFF9281

//Salidas excita_teclado
#define SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_0 0x00000F11
#define SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_1 0x00000F12
#define SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_2 0x00000F14
#define SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_3 0x00000F18

// --------------------------------------------------------------------- GLOBALS
/*
   Esta parte solo es necesaria si necesitamos que se guarden los valores entre
   tests.
 */
//Puerto puerto;

// --------------------------------------------------------------------- TARGETS
/* Incluidos en control.c */


// ----------------------------------------------------------------------- TESTS
int prueba_puerto_init()
{
    Puerto puerto;
    puerto_init(&puerto);
    printf("    Valor de inicial de situacion puerto = %i\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_INIT_SITUACION_PUERTO) return 1;
    return 0;
}

int prueba_columna_a_puerto()
{
    short int columna_0, columna_1, columna_2, columna_3;

    columna_0 = columna_a_puerto(0);
    printf("    Valor de salida columna 0 = %i\n",columna_0);
    if (columna_0 != SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_0) return 1;

    columna_1 = columna_a_puerto(1);
    printf("    Valor de salida columna 1 = %i\n",columna_1);
    if (columna_1 != SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_1) return 1;

    columna_2 = columna_a_puerto(2);
    printf("    Valor de salida columna 2 = %i\n",columna_2);
    if (columna_2 != SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_2) return 1;

    columna_3 = columna_a_puerto(3);
    printf("    Valor de salida columna 3 = %i\n",columna_3);
    if (columna_3 != SALIDA_PRUEBA_COLUMNA_A_PUERTO_COL_3) return 1;

    return 0;
}

int prueba_fila_a_puerto()
{
    short int fila_0, fila_1, fila_2, fila_3;

    fila_0 = fila_a_puerto(FILA_DE_PRUEBA_1);
    printf("    Valor de salida fila prueba 1 = %u\n",fila_0);
    if (fila_0 != SALIDA_PRUEBA_FILA_A_PUERTO_1) return 1;

    fila_1 = fila_a_puerto(FILA_DE_PRUEBA_2);
    printf("    Valor de salida fila prueba 2 = %u\n",fila_1);
    if (fila_1 != SALIDA_PRUEBA_FILA_A_PUERTO_2) return 1;

    fila_2 = fila_a_puerto(FILA_DE_PRUEBA_3);
    printf("    Valor de salida fila prueba 3 = %u\n",fila_2);
    if (fila_2 != SALIDA_PRUEBA_FILA_A_PUERTO_3) return 1;

    fila_3 = fila_a_puerto(FILA_DE_PRUEBA_4);
    printf("    Valor de salida fila prueba 4 = %u\n",fila_3);
    if (fila_3 != SALIDA_PRUEBA_FILA_A_PUERTO_4) return 1;

    return 0;
}

int prueba_puerto_excita_columna()
{
    Puerto puerto;
    puerto_init(&puerto);

    //Le puteamos un poco para comprobar que no cambia otros bits que no sean los suyos
    puerto.situacion_puerto = 1;

    puerto_excita_columna(&puerto, 0, FILA_DE_PRUEBA_1);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_1) return 1;

    puerto_excita_columna(&puerto, 1, FILA_DE_PRUEBA_2);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_2) return 1;

    puerto_excita_columna(&puerto, 2, FILA_DE_PRUEBA_3);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_3) return 1;

    puerto_excita_columna(&puerto, 3, FILA_DE_PRUEBA_4);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_COLUMNA_4) return 1;

    return 0;
}

int prueba_puerto_excita_teclado()
{
    Puerto puerto;
    puerto_init(&puerto);

    //Le puteamos un poco para comprobar que no cambia otros bits que no sean los suyos
    puerto.situacion_puerto = 0x00000F10;

    puerto_excita_teclado(&puerto, 1);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_0) return 1;

    puerto_excita_teclado(&puerto, 2);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_1) return 1;

    puerto_excita_teclado(&puerto, 4);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_2) return 1;

    puerto_excita_teclado(&puerto, 8);
    printf("    Valor de salida puerto.situacion_puerto prueba 1 = %u\n",puerto.situacion_puerto);
    if (puerto.situacion_puerto != SALIDA_PRUEBA_PUERTO_EXCITA_TECLADO_3) return 1;

    return 0;
}

// ------------------------------------------------------------------------ MAIN
int main(int argc, char** argv)
{
    int p_puerto_init, p_columna_a_puerto, p_fila_a_puerto, p_prueba_puerto_excita_columna, p_prueba_puerto_excita_teclado;
    printf("Comienzo de pruebas del objeto Puerto:\n");

    p_puerto_init = prueba_puerto_init();
    if (!p_puerto_init) {printf("Pasa prueba_init\n");} else { printf("FAIL prueba_init\n");}

    p_columna_a_puerto = prueba_columna_a_puerto();
    if (!p_columna_a_puerto) {printf("Pasa prueba_columna_a_puerto\n");} else { printf("FAIL prueba_columna_a_puerto\n");}

    p_fila_a_puerto = prueba_fila_a_puerto();
    if (!p_fila_a_puerto) {printf("Pasa prueba_fila_a_puerto\n");} else { printf("FAIL prueba_fila_a_puerto\n");}

    p_prueba_puerto_excita_columna = prueba_puerto_excita_columna();
    if (!p_prueba_puerto_excita_columna) {printf("Pasa prueba_puerto_excita_columna\n");} else { printf("FAIL prueba_puerto_excita_columna\n");}

    p_prueba_puerto_excita_teclado = prueba_puerto_excita_teclado();
    if (!p_prueba_puerto_excita_teclado) {printf("Pasa prueba_puerto_excita_teclado\n");} else { printf("FAIL prueba_puerto_excita_teclado\n");}

    if(!(p_puerto_init || p_columna_a_puerto || p_fila_a_puerto || p_prueba_puerto_excita_columna || p_prueba_puerto_excita_teclado))
    {
        printf("\nTODAS LAS PRUEBAS SE HAN PASADO CON EXITO.\n");
    }

    return (EXIT_SUCCESS);
}

