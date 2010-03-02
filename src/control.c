/*
   control.c
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


#include "control.h"
#include "vista.h"


/*
   Function: menu
   
   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.

   Parameters:

      *estado - Puntero a el estado global.
      tecla - char con el valor de la tecla pulsada.
*/
void menu (Estado *estado, char tecla)
{
    switch (tecla)
    {
        case TECLA_NIVEL_1:
        {
            estado->nivel_dificultad = 0;
        }
        break;
        case TECLA_NIVEL_2:
        {
            estado->nivel_dificultad = 1;
        }
        break;
        case TECLA_NIVEL_3:
        {
            estado->nivel_dificultad = 2;
        }
        break;
        case TECLA_COMIENZO:
        {
            estado->jugando = 1;//TRUE
        }
        break;
        default:
        {
            
        }
        break;
    }
}


/*
   Function: estado_init
   Inicializa una estructura Estado con lo valores que se le dan.
   
   Parameters:

      *estado - Puntero a la estructura Estado que queremos inicializar.
      nivel_dificultad - int con el nivel dificultad para la partida.
*/
void estado_init (Estado *estado, int nivel_dificultad)
{
    estado->nivel_dificultad = nivel_dificultad;
    estado->jugando = 0;
    estado->texto_niveles[0] = TEXTO_NIVEL_1;
    estado->texto_niveles[1] = TEXTO_NIVEL_2;
    estado->texto_niveles[2] = TEXTO_NIVEL_3;
}


/*
   Function: reloj_init
   Inicializa una estructura Reloj con valores a 0.

   Parameters:

      *reloj - Puntero a la estructura Reloj que queremos inicializar.
*/
void reloj_init (Reloj *reloj)
{
    reloj->columna_led = 0;
    reloj->refresco = TASA_REFRESCO;
    reloj->nota = 0;
}