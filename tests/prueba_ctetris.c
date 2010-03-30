/*
   prueba_ctetris.c

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

#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <ncurses.h>

#define FPS 24 //Frames Per Second
#define REFRESH_MS 1000/FPS

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
#define TRUE 1

void set16_puertoS(unsigned short int valor)
{
}

void output(char string[])
{
}

void habilitar_interrupciones(void){}
void deshabilitar_interrupciones(void){}
int lee_puertoE(void){}
void retardo(int ms){}

#include "../ctetris/src/control.c"


// --------------------------------------------------------------------- GLOBALS
Estado estado;
//Reloj reloj;
Leds leds;
//Puerto puerto;
Juego juego;
//Melodia melodia;
Resultados resultados;

// ------------------------------------------------------------------- FUNCTIONS

/*void msleep(unsigned long delay_ms)
{
    struct timespec req_ts;
    req_ts.tv_sec = delay_ms / 1000;
    req_ts.tv_nsec = (delay_ms % 1000) * 1000000L;
    while (nanosleep(&req_ts, NULL) == -1)
        continue;

}*/

void pantalla_refresh(Leds *leds)
{
    int x, y;

    //clear_terminal();
    clear();
    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        printw("         1");
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            if (leds->pantalla[x][y] == 1) printw("1");
            else printw("0");
        }
        printw("1\n");
    }
    printw("         111111\n");
    refresh();
}

void contador_timeout(int i)
{
    struct itimerval req_ts;

    req_ts.it_interval.tv_sec = 0;
    req_ts.it_interval.tv_usec = 0;
    req_ts.it_value.tv_sec = REFRESH_MS / 1000;
    req_ts.it_value.tv_usec = (REFRESH_MS % 1000) * 1000L;
    
    signal(SIGALRM,contador_timeout);
    setitimer(ITIMER_REAL, &req_ts,0);

    if (estado.jugando == TRUE)
    {
        juego_caida_timeout(&leds, &juego, 1*FPS); //Tiempo en segundos
        pantalla_refresh(&leds);
    }
}

void no_interrrupcion(int i)
{
    signal(SIGALRM,no_interrrupcion);
}

int main(int argc, char** argv)
{
    struct itimerval req_ts;
    int tecla_pulsada;

    req_ts.it_interval.tv_sec = 0;
    req_ts.it_interval.tv_usec = 0;
    req_ts.it_value.tv_sec = REFRESH_MS / 1000;
    req_ts.it_value.tv_usec = (REFRESH_MS % 1000) * 1000L;
    signal(SIGALRM,contador_timeout);
    setitimer(ITIMER_REAL, &req_ts,0);

    estado_init(&estado);
    estado.jugando = TRUE;
    leds_init(&leds);
    juego_init(&juego);
    juego.nivel_dificultad = 1;
    resultados_init(&resultados);

	initscr();			/* Start curses mode 		  */
    keypad(stdscr, TRUE); /* Inicializar el teclado */
    noecho(); /* No pintar caracteres pulsados en la pantalla */    
	refresh();			/* Print it on to the real screen */
    
    while(1)
    {
        tecla_pulsada = getch();
        switch (tecla_pulsada)
        {
            case KEY_LEFT:
                juego_tecla_pulsada(&leds, &juego, TECLA_IZQUIERDA);
                break;
            case KEY_DOWN:
                juego_tecla_pulsada(&leds, &juego, TECLA_ABAJO);
                break;
            case KEY_RIGHT:
                juego_tecla_pulsada(&leds, &juego, TECLA_DERECHA);
                break;
            case KEY_UP:
                juego_tecla_pulsada(&leds, &juego, TECLA_ROTAR);
                break;
            case 'e':
                signal(SIGALRM,no_interrrupcion);
                clear();
                refresh();
                endwin(); /* End curses mode */
                return EXIT_SUCCESS;
                break;
        }
    }
	endwin();
	return EXIT_SUCCESS;
}
