/*
   prueba_ctetris.c

   Archivo de prueba de algoritmos para el juego de ctetris.

   IMPORTANTE: Al compilar este archivo se debe linkar la libreria ncurses!
               Para ello añadir el flag -lncurses en la linea de comandos al gcc
               Ej. $gcc <archivo> -lncurses

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
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
//#include <ncurses.h>

#define FPS 24 //Frames Per Second
#define REFRESH_MS 1000/FPS
#define MS_A_S 1000

#define COLORES_RESULTADOS 4
#define COLORES_RESULTADOS_TITULO 5
#define W_ALTO_RESULTADOS 4
#define W_ANCHO_RESULTADOS 20
#define W_X_RESULTADOS 10
#define W_Y_RESULTADOS 3

#define COLORES_LEDS 3
#define W_ALTO_LEDS 8
#define W_ANCHO_LEDS 4
#define W_X_LEDS 22
#define W_Y_LEDS 1

#define COLORES_OUTPUT 2
#define W_ALTO_OUTPUT 8
#define W_ANCHO_OUTPUT 78
#define W_X_OUTPUT 1
#define W_Y_OUTPUT 11

#define COLORES_PRINCIPAL 1
#define W_ALTO_PRINCIPAL
#define W_ANCHO_PRINCIPAL

/* Omitimos las librerias del Coldfire */
#define __M5272LIB_H__
#define	m5272_h
#define __M5272LCD_C__
#define	_HARDWARE_CONF_H
#define	_HARDWARE_CONF_C

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

// --------------------------------------------------------------------- NCURSES
//Funcion de pintado emulando output de ColdFire

void output(char string[])
{
    static int linea_actual = 0;
    int i = 0;
    printf("\033[%i;%iH%s", W_Y_OUTPUT + linea_actual, W_X_OUTPUT, string);
    while (string[i] != '\0') //&& i < strlen(string))
    {
        if (string[i] == '\n')linea_actual++;
        i++;
    }
    if (linea_actual == W_ALTO_OUTPUT)
    {
        linea_actual = 0;
    }
}

void outNum(int base, int numero, int opciones)
{
    char numero_string [5];
    sprintf(numero_string, "%i", numero);
    output(numero_string);
}

#include "../src/control.c"


// --------------------------------------------------------------------- GLOBALS
Estado estado;
//Reloj reloj;
Leds leds;
//Puerto puerto;
Juego juego;
//Melodia melodia;
Resultados resultados;


// ------------------------------------------------------------------- FUNCTIONS

void msleep(unsigned long delay_ms)
{
    /*
    struct timespec req_ts;
    req_ts.tv_sec = delay_ms / 1000;
    req_ts.tv_nsec = (delay_ms % 1000) * 1000000L;
    while (nanosleep(&req_ts, NULL) == -1)
        continue;
     */
    usleep(delay_ms * 1000);

}

void windows_init()
{
    printf("\nResultados:\n  lineas 0");
}

void w_clear()
{
    printf("\033[2J");
    printf("\033[0;0H");
}

void w_leds_refresh(Leds *leds)
{
    int x, y;

    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            if (leds->pantalla[x][y] == 1) printf("\033[%i;%iH0", W_Y_LEDS + y, W_X_LEDS + x);
            else printf("\033[%i;%iH·", W_Y_LEDS + y, W_X_LEDS + x);
        }
    }
    //printf("\033[Line;ColumnH");
}

void w_resultados_refresh()
{
    printf("\033[%i;%iH%i", W_Y_RESULTADOS, W_X_RESULTADOS, resultados.lineas);
}

void pantalla_refresh(Leds *leds)
{
    w_leds_refresh(leds);
    w_resultados_refresh();
}

void contador_timeout(int i)
{
    struct itimerval req_ts;

    req_ts.it_interval.tv_sec = 0;
    req_ts.it_interval.tv_usec = 0;
    req_ts.it_value.tv_sec = REFRESH_MS / 1000;
    req_ts.it_value.tv_usec = (REFRESH_MS % 1000) * 1000L;

    signal(SIGALRM, contador_timeout);
    setitimer(ITIMER_REAL, &req_ts, 0);

    if (estado.jugando == TRUE)
    {
        juego_caida_timeout(&leds, &juego, &resultados, &estado, juego_tiempo_caida_pieza(&juego) * FPS / MS_A_S); //Tiempo en segundos
        pantalla_refresh(&leds);
    }
}

void no_interrrupcion(int i)
{
    signal(SIGALRM, no_interrrupcion);
}

int main(int argc, char** argv)
{
    char tecla_pulsada;
    int c;
    int i = 0;
    struct itimerval req_ts;
    struct termios t;

    //Setup del terminal
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON; //No espera a enter para meter la informacion
    t.c_lflag &= ~ECHO; //No imprime el caracter en pantalla
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    /* No funcionan...
    printf("\033f");//Esconder el cursor
    printf("\033w");//Desactivar wrapping mode
     */
    w_clear();

    //Setup de timer
    req_ts.it_interval.tv_sec = 0;
    req_ts.it_interval.tv_usec = 0;
    req_ts.it_value.tv_sec = REFRESH_MS / 1000;
    req_ts.it_value.tv_usec = (REFRESH_MS % 1000) * 1000L;
    signal(SIGALRM, contador_timeout);
    setitimer(ITIMER_REAL, &req_ts, 0);

    //Setup de ctetris
    estado_init(&estado);
    leds_init(&leds);
    juego_init(&juego);
    resultados_init(&resultados);

    //Setup de las posiciones dentro del terminal
    windows_init();

    //Inicio de ctetris
    output(TEXTO_BIENVENIDA);
    output(TEXTO_NIVELES_POSIBLES);
    while (c = getchar())
    {
        tecla_pulsada = (char) c;

        if (estado.jugando == FALSE)
        {
            menu(&estado, &leds, &juego, &resultados, tecla_pulsada);
        }
        else
        {
            //Remapeamos las teclas para que sea comodo de usar en el PC
            switch (tecla_pulsada)
            {
                case KEY_LEFT:
                    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_IZQUIERDA);
                    break;
                case KEY_DOWN:
                    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_ABAJO);
                    break;
                case KEY_RIGHT:
                    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_DERECHA);
                    break;
                case KEY_UP:
                    juego_tecla_pulsada(&leds, &juego, &resultados, &estado, TECLA_ROTAR);
                    break;
                case 'e':
                    //Para tener una salida "limpia" en el Netbeans...
                    signal(SIGALRM, no_interrrupcion);
                    w_clear();
                    return EXIT_SUCCESS;
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
