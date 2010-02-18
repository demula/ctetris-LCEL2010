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


#include "m5272lib.c"
#include "control.c"
#include "vista.c"


// -------------------------------------- (configuración del sistema) CONSTANTES
/*
   Constants: Configuración inicial del ctetris

   NIVEL_DIFICULTAD_INICIAL - Nivel de dificultad con el que empieza el jugador.
*/
#define NIVEL_DIFICULTAD_INICIAL 0


/*
   Constants: Configuración del hardware del teclado

   NUM_FILAS - Número de filas en el teclado matricial.
   NUM_COLS - Número de columnas en el teclado matricial
   EXCIT - Excitación de salida bit 0
*/
#define NUM_FILAS 4
#define NUM_COLS 4
#define EXCIT 1


// ---------------------------------------------------------- VARIABLES GLOBALES
/*
   Variables: Variables globales

   estado - Contiene todo lo referente al estado del juego.
   relojes - 
   puerto - 
   resultados - 
*/
Estado estado;
//Relojes relojes;
//Puerto puerto;
//Resultados resultados;


// --------------------------------------------------------- ATENCION DE RUTINAS
/*
   Function: tecla_pulsada

   Explora el teclado matricial y devuelve la tecla pulsada.

   Credits:
   Teclado_GNU.c
   Autores Juan Manuel Montero, Rubén San Segundo y Javier Guillén Álvarez.
*/
char tecla_pulsada(void)
{
    BYTE fila, columna, fila_mask;
    static char teclas[NUM_FILAS][NUM_COLS] = {{"123C"},
                                               {"456D"},
                                               {"789E"},
                                               {"A0BF"}};
    while(TRUE)
    {
        for(columna = NUM_COLS - 1; columna >= 0; columna--)
        {   //Excitamos una columna
            set_puertoS(EXCIT << columna);//Se envía la excitación de columna
            retardo(1150);//Esperamos respuesta de optoacopladores

            for(fila = NUM_COLS - 1; fila >= 0; fila--)
            {   // Exploramos las filas en busca de respuesta
                fila_mask = EXCIT << fila;//Máscara para leer el bit de la fila actual
                if(lee_puertoE() & fila_mask)//Si encuentra tecla pulsada
                {
                    while(lee_puertoE() & fila_mask);//Esperamos a que se suelte
                    retardo(1150);//Retardo antirrebotes
                    return teclas[fila][columna];//Devolvemos la tecla pulsada
                }
            }//Siguiente columna
        }// Exploración finalizada sin encontrar una tecla pulsada
    }//Reiniciamos exploración
}


/*
   Functions: Rutinas de atención
   
   Definición de rutinas de atención a las interrupciones del sistema.
   Es necesario definirlas aunque estén vacías.
*/
void rutina_int1(void){}
void rutina_int2(void){}
void rutina_int3(void){}
void rutina_int4(void){}
void rutina_tout0(void){}
void rutina_tout1(void){}
void rutina_tout2(void){}
void rutina_tout3(void){}


// -------------------------------------------------------------- INICIALIZACION
// -------------------------------------------------------------------- software
/*
   Function: software_init
   
   Función que inicializa todos los objetos/variables del software.
   Definida en start.asg
*/
void software_init(void)
{
    estado_init(&estado, NIVEL_DIFICULTAD_INICIAL, 0);
}


// -------------------------------------------------------------------- hardware
/*
   Function: hardware_init
   
   Función que inicializa las interrupciones y los puertos.
   Definida en start.asg
*/
void hardware_init(void)
{
    lcd_init();
}


// ----------------------------------------------------------------- global init
/*
   Function: __init
   
   Función por defecto de inicialización del sistema.
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
    while (TRUE)
    {
        if (estado.jugando==FALSE)
        {
            char tecla = tecla_pulsada();
            menu(&estado, tecla);
            imprimir_en_lcd(estado.texto_niveles[estado.nivel_dificultad]);
        }
        else
        {
            limpiar_lcd();
            imprimir_en_lcd("Jugando...");
        }
    }
}
