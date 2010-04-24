/*
   prueba_ctetris_ncurses.c

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
#include <signal.h>
#include <sys/time.h>
#include <ncurses.h>

#define FPS 24 //Frames Per Second
#define REFRESH_MS 1000/FPS
#define MS_A_S 1000

#define COLORES_RESULTADOS 4
#define COLORES_RESULTADOS_TITULO 5
#define W_ALTO_RESULTADOS 6
#define W_ANCHO_RESULTADOS 20
#define W_X_RESULTADOS 1
#define W_Y_RESULTADOS 1

#define COLORES_LEDS 3
#define W_ALTO_LEDS 8
#define W_ANCHO_LEDS 4
#define W_X_LEDS 22
#define W_Y_LEDS 1

#define COLORES_OUTPUT 2
#define W_ALTO_OUTPUT 10
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
//Ventanas compartidas
WINDOW *w_output;
WINDOW *w_leds;
WINDOW *w_resultados;

//Funcion de pintado emulando output de ColdFire
void output(char string[])
{
    wprintw(w_output, string);
    wrefresh(w_output);
    //refresh();
}

void outNum(int base, int numero, int opciones)
{
    wprintw(w_output, "%i", numero);
    wrefresh(w_output);
}

#include "../ctetris/src/control.c"
#include "../ctetris/src/juego.c"


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
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);

	return local_win;
}

void windows_init()
{
    w_output = create_newwin(W_ALTO_OUTPUT, W_ANCHO_OUTPUT, W_Y_OUTPUT, W_X_OUTPUT);
    w_leds = create_newwin(W_ALTO_LEDS, W_ANCHO_LEDS, W_Y_LEDS, W_X_LEDS);
    w_resultados = create_newwin(W_ALTO_RESULTADOS, W_ANCHO_RESULTADOS, W_Y_RESULTADOS, W_X_RESULTADOS);

    //Colores para las ditintas ventanas
    //init_color(COLOR_RED, 700, 0, 0);
    /* param 1     : color name
     * param 2, 3, 4 : rgb content min = 0, max = 1000 */

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(COLORES_OUTPUT, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLORES_LEDS, COLOR_RED, COLOR_BLACK);
    init_pair(COLORES_RESULTADOS, COLOR_RED, COLOR_BLACK);
    init_pair(COLORES_RESULTADOS_TITULO, COLOR_RED, COLOR_BLACK);
}

void w_leds_refresh(Leds *leds)
{
    int x, y;
    //mvwprintw(win, y, x, "%s", string);

    attron(COLOR_PAIR(COLORES_LEDS));
    wclear(w_leds);
    for (y = 0; y < NUM_FILAS_LED; y++)
    {
        for (x = 0; x < NUM_COLUMNAS_LED; x++)
        {
            if (leds->pantalla[x][y] == 1) mvwprintw(w_leds, y, x,"0");
            else mvwprintw(w_leds, y, x, "'");
        }
    }
    wrefresh(w_leds);
    //refresh();
    attroff(COLOR_PAIR(COLORES_LEDS));
}

char pieza_numero_a_letra(char numero)
{
    switch (numero)
    {
        case 0: return 'O';
        case 1: return 'I';
        case 2: return 'T';
        case 3: return 'L';
        case 4: return 'J';
        case 5: return 'S';
        case 6: return 'Z';
    }
}

void w_resultados_refresh()
{
    attron(COLOR_PAIR(COLORES_RESULTADOS));
    wclear(w_resultados);
    wprintw(w_resultados,"Siguiente: %c\n\n", pieza_numero_a_letra(juego.clase_pieza_siguiente));
    wprintw(w_resultados,"Resultados:\n");
    wprintw(w_resultados,"  Lineas %i\n", resultados.lineas);
    wprintw(w_resultados,"  Tetris %i\n", resultados.tetris_conseguidos);
    wprintw(w_resultados,"  Puntuacion %i\n", resultados.puntuacion);
    wrefresh(w_resultados);
    //refresh();
    attroff(COLOR_PAIR(COLORES_RESULTADOS));
}

void pantalla_refresh(Leds *leds)
{
    w_leds_refresh(leds);
    w_resultados_refresh();
    //refresh();
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
        resultados_ms_transcurrido(&resultados);
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
    struct itimerval req_ts;
    int tecla_pulsada;

    //Setup de timer
    req_ts.it_interval.tv_sec = 0;
    req_ts.it_interval.tv_usec = 0;
    req_ts.it_value.tv_sec = REFRESH_MS / 1000;
    req_ts.it_value.tv_usec = (REFRESH_MS % 1000) * 1000L;
    signal(SIGALRM, contador_timeout);
    setitimer(ITIMER_REAL, &req_ts, 0);

    //Setup de ctetris
    estado_init(&estado);
    //estado.jugando = TRUE;
    leds_init(&leds);
    juego_init(&juego);
    resultados_init(&resultados);

    //Setup de ncurses
    initscr(); /* Start curses mode 		  */
    curs_set(0); /* Cursor: 0 invisible, 1 normal, 2 muy visible */
    if(has_colors() == FALSE)
	{
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
    cbreak();       /* Line buffering disabled, Pass on everty thing to me */
    keypad(stdscr, TRUE); /* Inicializar el teclado */
    noecho(); /* No pintar caracteres pulsados en la pantalla */


    //Inicia las ventas que vamos a usar con sus respectivas propiedades
    windows_init();
    refresh(); /* Print it on to the real screen */

    //Inicio de ctetris
    output(TEXTO_BIENVENIDA);
    output(TEXTO_NIVELES_POSIBLES);
    while (TRUE)
    {
        tecla_pulsada = getch();
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
                    clear();
                    refresh();
                    endwin(); /* End curses mode */
                    return EXIT_SUCCESS;
                    break;
            }
        }
    }
    endwin();
    return EXIT_SUCCESS;
}
