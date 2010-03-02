/*
   debug.c
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
#include "control.h"
#include "debug.h"
#include "hardware.h"
#include "juego.h"
#include "sonido.h"
#include "vista.h"


int contador0 = 0;
int contador1 = 1000;
int contador2 = 2000;


void debug(void)
{
    retardo(4000);
    _exit(0);
}


void debug_rutina_0(void)
{
    if (contador0 == 3000)
    {
        output("int0\n");
        contador0 = 0;

    }
    contador0++;
}


void debug_rutina_1(void)
{
    if (contador1 == 3000)
    {
        output("int1\n");
        contador1 = 0;

    }
    contador1++;
}


void debug_rutina_2(void)
{
    if (contador2 == 3000)
    {
        output("int2\n");
        contador2 = 0;

    }
    contador2++;
}