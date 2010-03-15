/*
   ctetris.c
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

#include "m5272lib.h"
#include "hardware.h" //-->>control.h-->>juego.h
//#include "sonido.h"
#include "debug.h"



// --------------------------------------------------- CONFIGURACION DEL CTETRIS
/*
   Constants: Configuración inicial del ctetris

   DEBUG - Modo debug para pruebas de funcionamiento
   NIVEL_DIFICULTAD_INICIAL - Nivel de dificultad con el que empieza el jugador.
 */
#define DEBUG 1
#define NIVEL_DIFICULTAD_INICIAL 0


// ---------------------------------------------------------- VARIABLES GLOBALES
/*
   Variables: Variables globales

   estado - Contiene todo lo referente al estado del juego.
   relojes - Contadores varios para todos los usos que requieran temporización.
   leds - Informacion de la pantalla de leds
   pieza - Informacion de la pieza que esta en juego
   melodia - Informacion de la melodia y de la nota que actualmente esta sonando
   resultados - lineas completadas y puntos obtenidos
 */
Estado estado;
Reloj reloj;
Leds leds;
Puerto puerto;
Juego juego;
//Melodia melodia;
//Resultados resultados;


// --------------------------------------------------------- RUTINAS DE ATENCION

/*
   Functions: Rutinas de atención
   
   Definición de rutinas de atención a las interrupciones del sistema.
   Es necesario definirlas aunque estén vacías.
 */
void rutina_int1(void)
{
}

void rutina_int2(void)
{
}

void rutina_int3(void)
{
}

void rutina_int4(void)
{
}

void rutina_tout3(void)
{
}

/*
   Function: rutina_tout0

   Rutina de atencion para la generacion de una onda cuadrada a la frecuencia de
   la nota que queremos. (Tiene maxima prioridad en el sistema -- 6)
 */
void rutina_tout0(void)
{
    timer0_inter_atendida();
    if (DEBUG)
    {
        debug_rutina_0();
    } else
    {

    }
}

/*
   Function: rutina_tout1

   Rutina de atencion que se encarga de la actualizacion de la fisica del juego.
   Consiste en la caida de la pieza y actualizaciones del juego como juego
   perdido o linea completada. (Segunda en prioridad en el sistema -- 5)
 */
void rutina_tout1(void)
{
    timer1_inter_atendida();
    if (DEBUG)
    {
        debug_rutina_1();
    } else
    {

    }
}

/*
   Function: rutina_tout2

   Rutina de atencion para el pintando y refresco de la pantalla de leds. (Tiene
   la minima prioridad en el sistema -- 4)
 */
void rutina_tout2(void)
{
    timer2_inter_atendida();
    if (DEBUG)
    {
        debug_rutina_2();
    } else
    {

    }
}


// -------------------------------------------------------------- INICIALIZACION

/*
   Function: software_init
   
   Función que inicializa todos los objetos/variables del software.
   Definida en start.asg
 */
void software_init(void)
{
    output("Bienvenido a ColdtrixTM:\nElija nivel de juego\n");
    estado_init(&estado);
    puerto_init(&puerto);
    reloj_init(&reloj);
    leds_init(&leds);
    juego_init(&juego, NIVEL_DIFICULTAD_INICIAL);
}

/*
   Function: hardware_init
   
   Función que inicializa las interrupciones y los puertos.
   Definida en start.asg
 */
void hardware_init(void)
{
    interrupciones_init();
    lcd_init();
    timer0_init();
    timer1_init();
    timer2_init();
}

/*
   Function: __init
  
   Función por defecto de inicialización global del sistema.
 */
void __init(void)
{
    software_init();
    hardware_init();
}


// ------------------------------------------------------ BUCLE PRINCIPAL (MAIN)

/*
   Function: bucleMain
   
   Bucle principal del programa.
 */
void bucleMain(void)
{
    if (DEBUG)
    {
        output("MODO DEBUG");
        debug();
    } else
    {
        while (TRUE)
        {
            if (estado.jugando == FALSE)
            {
                char tecla;
                imprimir_en_lcd(TEXTO_BIENVENIDA);
                retardo(1000);
                imprimir_en_lcd(estado.texto_menu[juego.nivel_dificultad]);
                tecla = tecla_pulsada(&puerto);
                menu(&estado, &juego, tecla);
                imprimir_en_lcd(estado.texto_menu[juego.nivel_dificultad]);
            } else
            {
                limpiar_lcd();
                imprimir_en_lcd("Jugando...");
                retardo(1000);
                _exit(0);
            }
        }
    }
}
