/*
   melodia.c
   Melodia de ctetris para Motorola Coldfire 5242 sobre la plataforma de
   desarrollo ENT2004CF.

   Copyright (C) 2010 Jorge Bravo Jimenez fbravos45@igmail.com
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

//#ifndef _MELODIA_C
//#define	_MELODIA_C

#include "melodia.h"

/*
   Function: melodia_init

   Inicializa la estructura melodia rellenando sus arrays de frencuencias y
   tiempos.

   Parameters:

      p_melodia - Puntero a la estructura Melodia a inicializar
 
 */
void melodia_init(Melodia *p_melodia)
{
    //HORROR no hacer esto... muy feo, tiene que haber otra manera de hacerlo
    int posicion;
    int frecuencias_temp[NUMERO_TOTAL_NOTAS] = FRECUENCIAS;
    int tiempos_temp[NUMERO_TOTAL_NOTAS] = TIEMPOS;

    for (posicion = 0; posicion < NUMERO_TOTAL_NOTAS; posicion++)
    {
        p_melodia->frecuencia[posicion] = frecuencias_temp[posicion];
    }

    for (posicion = 0; posicion < NUMERO_TOTAL_NOTAS; posicion++)
    {
        p_melodia->tiempo[posicion] = tiempos_temp[posicion];
    }
}

/*
   Function: melodia_play

   Reproduce la melodia haciendo uso de la salida del TIMER0. Para ello creamos
   interrupciones periodicas dando el efecto de frecuencia de sonido y
   controlamos el tiempo que suena mediante las interrupciones en el TIMER1.

   Esta funcion esta pensanda para colocarse en la rutina de atencion del TIMER1
   configurado a 1000 interrupciones por segundo donde mediremos que tiempo 
   lleva sonando la nota y obteniendo los tiempo de nota (en ms) desde la
   estructura Melodia.

   Parameters:

      p_melodia - Puntero a la estructura melodia de donde sacamos frecuencias
                  y tiempos.
      reset - 1 Resetea el contador static y hace que la melodia comience de
              nuevo, 0 no hace nada.

 */
void melodia_play(Melodia *p_melodia, char reset)
{
    static int tiempo_nota = 0;
    static int nota_actual = NOTA_RESET;

    if (reset)
    {
        tiempo_nota = 0;
        nota_actual = NOTA_RESET;
    }

    if (tiempo_nota == 0)
    {
        nota_actual++;
        if (nota_actual == NUMERO_TOTAL_NOTAS) { nota_actual = 0;} //Reproduccion continua
        tiempo_nota = p_melodia->tiempo[nota_actual];
        melodia_set_frecuencia(p_melodia->frecuencia[nota_actual]);
    }
    tiempo_nota--;
}

/*
   Function: melodia_stop

   Para la melodia (= silencio). Coloca la configuracion del TIMER0 para que no
   halla interrupciones periodicas.

 */
void melodia_stop()
{
    //TMR0: PS=0x00 CE=00 OM=1 ORI=1 FRR=1 CLK=10 RST=0
    mbar_writeShort(MCFSIM_TMR0, CONFIG_TIMER0_APAGADO);
}

/*
   Function: melodia_set_frecuencia

   Coloca la frecuencia que queramos (dentro del rango que hemos previamente
   configurado) en el TIMER0.

   Parameters:

      frecuencia - Valor en hercios de la frecuencia que queremos hacer sonar.
 
 */
void melodia_set_frecuencia(int frecuencia)
{
    if (frecuencia)
    {
        mbar_writeShort(MCFSIM_TRR0, referencia_timer(ONDA_CUADRADA * frecuencia, PS_0, CLK_0));
        mbar_writeShort(MCFSIM_TMR0, CONFIG_TIMER0_ENCENDIDO);
    }
    else
    {
        melodia_stop();
    }
}

//#endif	/* _MELODIA_C */

