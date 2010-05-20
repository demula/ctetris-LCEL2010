/*
   hardware.c
   Configuracion del hardware par ctetris para Motorola Coldfire 5242 sobre la 
   plataforma de desarrollo ENT2004CF.

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

#ifndef _HARDWARE_CONF_C
#define	_HARDWARE_CONF_C

#include "hardware.h"

// -------------------------------------------------------------- INTERRUPCIONES
/*
   Function: habilitar_interrupciones

   Habilita las interrupciones definidas en la configuracion de VALOR_ICR1.

   See also:<Configuración de las interrupciones>

 */
void habilitar_interrupciones(void)
{
    mbar_writeLong(MCFSIM_ICR1, HABILITAR_INTERRUPCIONES);
}

/*
   Function: deshabilitar_interrupciones

   Deshabilita todas las interrupciones de registro de configuracion ICR1.

 */
void deshabilitar_interrupciones(void)
{
    mbar_writeLong(MCFSIM_ICR1, DESHABILITAR_INTERRUPCIONES);
}

/*
   Function: timer0_inter_atendida

   Permite que se vuelva a activar la interrupcion. Hay que llamarla cada vez que
   se atiende una interrupcion de timer 0.

 */
void timer0_inter_atendida(void)
{
    mbar_writeShort(MCFSIM_TER0, BORRA_REF);
}

/*
   Function: timer1_inter_atendida

   Permite que se vuelva a activar la interrupcion. Hay que llamarla cada vez que
   se atiende una interrupcion de timer 1.

 */
void timer1_inter_atendida(void)
{
    mbar_writeShort(MCFSIM_TER1, BORRA_REF);
}

/*
   Function: timer2_inter_atendida

   Permite que se vuelva a activar la interrupcion. Hay que llamarla cada vez que
   se atiende una interrupcion de timer 2.
 
 */
void timer2_inter_atendida(void)
{
    mbar_writeShort(MCFSIM_TER2, BORRA_REF);
}

// ------------------------------------------------------------ INICIALIZACIONES
/*
   Function: timer0_init

   Inicializa el temporizador 0 con los valores definidos en su configuracion de
   constantes.

   See also:<Configuración del timer0><CONFIG_TIMER0><REFERENCIA_TIMER0>

 */
void timer0_init(void)
{
    mbar_writeShort(MCFSIM_TMR0, CONFIG_TIMER0_APAGADO);
    mbar_writeShort(MCFSIM_TCN0, BORRA_CONTADOR); // Ponemos a 0 el contador del TIMER0
    mbar_writeShort(MCFSIM_TRR0, REFERENCIA_TIMER0);
}

/*
   Function: timer1_init

   Inicializa el temporizador 0 con los valores definidos en su configuracion de
   constantes.

   See also:<Configuración del timer1><CONFIG_TIMER1><REFERENCIA_TIMER1>
 
 */
void timer1_init(void)
{
    mbar_writeShort(MCFSIM_TMR1, CONFIG_TIMER1);
    mbar_writeShort(MCFSIM_TCN1, BORRA_CONTADOR);
    mbar_writeShort(MCFSIM_TRR1, REFERENCIA_TIMER1);
}

/*
   Function: timer1_init

   Inicializa el temporizador 0 con los valores definidos en su configuracion de
   constantes.

   See also:<Configuración del timer1><CONFIG_TIMER1><REFERENCIA_TIMER1>

 */
void timer2_init(void)
{
    mbar_writeShort(MCFSIM_TMR2, CONFIG_TIMER2);
    mbar_writeShort(MCFSIM_TCN2, BORRA_CONTADOR);
    mbar_writeShort(MCFSIM_TRR2, REFERENCIA_TIMER2);
}

/*
   Function: interrupciones_init

   Inicializa la tabla de vectores de atencion a rutinas
 
 */
void interrupciones_init(void)
{
    mbar_writeByte(MCFSIM_PIVR, V_BASE); // Fija comienzo de vectores de interrupción en V_BASE.
    ACCESO_A_MEMORIA_LONG(DIR_VTMR0) = (ULONG) _prep_TOUT0; // Escribimos la dirección de la función para TMR0
    ACCESO_A_MEMORIA_LONG(DIR_VTMR1) = (ULONG) _prep_TOUT1; // Escribimos la dirección de la función para TMR1
    ACCESO_A_MEMORIA_LONG(DIR_VTMR2) = (ULONG) _prep_TOUT2; // Escribimos la dirección de la función para TMR1
    habilitar_interrupciones();
}

#endif	/* _HARDWARE_CONF_C */