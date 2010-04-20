/*
   melodia.h
   Melodia de ctetris para Motorola Coldfire 5242 sobre la plataforma de
   desarrollo ENT2004CF.

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

#ifndef _MELODIA_H
#define	_MELODIA_H

#include "hardware.h"

#define PARAR_TIMER configurar_timer(PS_0,CE_0,OM_0,ORI_0,FRR_0,CLK_0,0)
#define CONFIG_TIMER0 configurar_timer(PS_0,CE_0,OM_0,ORI_0,FRR_0,CLK_0,1) //0x003C
#define NUMERO_TOTAL_NOTAS 55
#define NOTA_RESET -1
//La frecuencia es el doble porque la salida conmuta y queremos una onda cuadrada
#define ONDA_CUADRADA 2

/*
 * TABLA 1 del enunciado con las frecuencias de las notas
 */
#define FRECUENCIAS \
{\
    1319, 988, 1047, 1175, 1047, 988, 880, 880, 1047, 1319, 1175, 1047, 988, \
    988, 1047, 1175, 1319, 1047, 880, 880, 0, 1175, 1397, 1760, 1568, 1397, \
    1319, 1047, 1319, 1175, 1047, 988, 988, 1047, 1175, 1319, 1047, 880, 880, \
    0, 659, 523, 587, 494, 523, 440, 415, 659, 523, 587, 494, 523, 659, 880, 831\
} /* En Hz */

#define TIEMPOS \
{\
    450, 225, 225, 450, 225, 225, 450, 225, 225, 450, 225, 225, 450, 225, 225, \
    450, 450, 450, 450, 450, 675, 450, 225, 450, 225, 225, 675, 225, 450, 225, \
    225, 450, 225, 225, 450, 450, 450, 450, 450, 450, 900, 900, 900, 900, 900, \
    900, 1800, 900, 900, 900, 900, 450, 450, 900, 1800 \
} /* En ms */

typedef struct
{
    int frecuencia[NUMERO_TOTAL_NOTAS];
    int tiempo[NUMERO_TOTAL_NOTAS];
} Melodia;

//Prototipos de las funciones de melodia.c
void melodia_init(Melodia *p_melodia);
void melodia_play(Melodia *p_melodia, char reset);
void melodia_stop();
void melodia_set_frecuencia(int frecuencia);

#endif	/* _MELODIA_H */

