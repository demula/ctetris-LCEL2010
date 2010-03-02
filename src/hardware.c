/*
   hardware.c
   Configuracion del hardware par ctetris para Motorola Coldfire 5242 sobre la plataforma de desarrollo
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


#include "m5272.h"
#include "m5272lib.h"
#include "hardware.h"


/*
   Function: tecla_pulsada

   Explora el teclado matricial y devuelve la tecla pulsada.

   Posible mejora (pag 25 del enunciado):
   Si únicamente se emplea las teclas ‘1’, ‘4’ , ‘7’ y ‘A’, que están conectadas
   a la misma columna y un mismo terminal de salida (el bit 0 del puerto de
   salida), es posible no realizar el barrido, sino excitar esa columna (en la
   inicialización del objeto Tecla) y leer el puerto de entrada (conectado a las
   filas del teclado matricial como se muestra en la Figura 2) para ver si
   alguna de esas teclas ha sido pulsada. Se debe registrar la tecla pulsada y
   el instante de tiempo de la pulsación.

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
        for(columna = 0; columna < NUM_COLS; columna++)
        {   //Excitamos una columna
            set_puertoS(EXCIT << columna);//Se envía la excitación de columna    TODO: comprobar que funciona bien
            retardo(RET_OPTOACOPLADORES);//Esperamos respuesta de optoacopladores

            for(fila = 0; fila < NUM_FILAS; fila++)
            {   // Exploramos las filas en busca de respuesta
                fila_mask = EXCIT << fila;//Máscara para leer el bit de la fila actual   TODO: comprobar que funciona bien
                if(lee_puertoE() & fila_mask)//Si encuentra tecla pulsada
                {
                    while(lee_puertoE() & fila_mask);//Esperamos a que se suelte
                    retardo(RET_REBOTES);//Retardo antirrebotes
                    return teclas[fila][columna];//Devolvemos la tecla pulsada
                }
            }//Siguiente columna
        }// Exploración finalizada sin encontrar una tecla pulsada
    }//Reiniciamos exploración
}


// -------------------------------------------------------------- INTERRUPCIONES
/*
   Function: habilitar_interrupciones

   Habilita las interrupciones definidas en la configuracion de VALOR_ICR1.

   See also:<Configuración de las interrupciones>
*/
void habilitar_interrupciones(void)
{
    mbar_writeLong(MCFSIM_ICR1, VALOR_ICR1);
}


/*
   Function: deshabilitar_interrupciones

   Deshabilita todas las interrupciones de registro de configuracion ICR1.
*/
void deshabilitar_interrupciones(void)
{
    mbar_writeLong(MCFSIM_ICR1, 0x88888888);
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
    mbar_writeShort(MCFSIM_TMR0, CONFIG_TIMER0);
    mbar_writeShort(MCFSIM_TCN0, 0x0000);// Ponemos a 0 el contador del TIMER0
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
    mbar_writeShort(MCFSIM_TCN1, 0x0000);// Ponemos a 0 el contador del TIMER0
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
    mbar_writeShort(MCFSIM_TCN2, 0x0000);// Ponemos a 0 el contador del TIMER0
    mbar_writeShort(MCFSIM_TRR2, REFERENCIA_TIMER2);
}


/*
   Function: interrupciones_init

   Inicializa la tabla de vectores de atencion a rutinas
 */
void interrupciones_init(void)
{
    mbar_writeByte(MCFSIM_PIVR,V_BASE);// Fija comienzo de vectores de interrupción en V_BASE.
    ACCESO_A_MEMORIA_LONG(DIR_VTMR0)= (ULONG)_prep_TOUT0;// Escribimos la dirección de la función para TMR0
    ACCESO_A_MEMORIA_LONG(DIR_VTMR1)= (ULONG)_prep_TOUT1;// Escribimos la dirección de la función para TMR1
    ACCESO_A_MEMORIA_LONG(DIR_VTMR2)= (ULONG)_prep_TOUT2;// Escribimos la dirección de la función para TMR1
    habilitar_interrupciones();
}