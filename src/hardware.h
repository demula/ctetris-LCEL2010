/*
   hardware.h
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

#ifndef _HARDWARE_CONF_H
#define	_HARDWARE_CONF_H

#include "m5272.h"
#include "m5272lib.h"

//Definicion de verdadero y falso para evitar numeros magicos
#define TRUE 1 //cualquier cosa distinta de 0 es verdadera
#define FALSE 0

/*
   Constants: Configuración del hardware del teclado matricial

   NUM_FILAS - Número de filas en el teclado matricial.
   NUM_COLS - Número de columnas en el teclado matricial
   RET_OPTOACOPLADORES - Tiempo de espera por el retardo de los optoacopladores ~50us
   RET_REBOTES - Retardo antirrebotes cuando se lee una tecla

 */
#define NUM_FILAS_TECLADO 4
#define NUM_COLS_TECLADO 4
#define RET_OPTOACOPLADORES 1150
#define RET_REBOTES 1150

/*
   Constants: Configuración del hardware interno del ColdFire

   Esta tabla contiene las direcciones de memoria de las rutinas de atencion de
   las interrupciones vectorizadas.

   V_BASE - Dirección de inicio de los vectores de interrupción
   DIR_VTMR0 - Dirección del vector de TMR0
   DIR_VTMR1 - Dirección del vector de TMR1
   DIR_VTMR2 - Dirección del vector de TMR2

 */
#define V_BASE 0x40 //Posicion tipica de la interrupciones de usuario
#define DIR_VTMR0 4*(V_BASE+5)
#define DIR_VTMR1 4*(V_BASE+6)
#define DIR_VTMR2 4*(V_BASE+7)

/*
   Documentacion: Timers

   Para configurar los timers del Coldfire se necesita acceder y configurar los
   registros:

    - TMRn(obligatorio): Registro de control (modo) para configuracion (16bits)
        - PS: Preescalado (8bits) -> Fcont = Fin / (PS+1)
        - CE: Captura de entrada y habilitacion de interrupciones (2bits)
            - 00: captura e interrupciones inhabilitadas
            - 01: captura con flanco de subida + interrupcion
            - 10: captura con flanco de bajada + interrupcion
            - 11: captura con ambos flancos + interrupcion
        - OM: Modo de salida (solo en TIMER0 y TIMER1) (1 bit)
            - 0: genera un pulso activo a nivel bajo durante un ciclo en TOUTn
            - 1: conmuta el nivel de la salida TOUTn
        - ORI: Habilita interrupciones en comparacion de salida (si habilita, ORI=1)
        - FRR: Modo continuo/reinicio del contador (si reinicia, FRR=1)
        - CLK: Fuente de reloj, Fin (2 bits)
            - 00: detiene el contador
            - 01: el reloj es el del sistema
            - 10: el reloj es el del sistema dividido por 16
            - 11: el reloj es una señal externa en TINn (solo en TIMER0 y TIMER1)
        - RST: Habilita (RST=1) o no el temporizador (lo pone a 0 con el paso a RST=0)

    - TCNn: Contador ascendente de 16 bits

    - TRRn: Registro de referencia (16 bits)
        - Valor de referencia para las comparaciones de salida
        - Terminales de salida: TOUT0 y TOUT1 (solo en TIMER0 y TIMER1)

    - TERn: Registro de estado (16 bits)
        - REF (posicion bit 1): bit que indica (REF=1) que se ha alcanzado el valor de referencia
        - CAP (posicion bit 0): bit que indica (CAP=1) la captura de una flanco de entrada
        - Se ponen a 0 escribiendo un 1 (escribir un 0 no afecta)
        - El resto de los bits deben estar a cero (reservados)

    - TCAPn:

   configurar_timer - Funcion que devuelve el valor de configuracion del TMRn
   referencia_timer - Funcion que devuelve el valor de configuracion del TRRn
   BORRA_CAP - Valor necesario para borrar CAP en el TERn
   BORRA_REF - Valor necesario para borrar REF en el TERn
   BORRA_CONTADOR - Valor inicial para el borrado del contador TCNn

 */
#define configurar_timer(ps,ce,om,ori,frr,clk,rst) ps*256+ce*64+om*32+ori*16+frr*8+clk*2+rst
#define referencia_timer(frecuencia,preescalado,tipo_reloj) MCF_CLK/(frecuencia*(preescalado+1)*(tipo_reloj&2?16:1))
//Valor de borrado de interr. pendientes de toutn para TERn
#define BORRA_CAP 0x0001
#define BORRA_REF 0x0002
#define BORRA_CONTADOR 0x0000

/*
   Constants: Configuración del timer0

   Este temporizador los usaremos para generar las ondas cuadradas de la musica
   del juego. La configuracion inicial no es importante ya que andaremos
   cambiandola segun cada nota de la cancion y su duracion.

    - Preescalado (PS) -> 0 Para tener maxima granularidad a la hora de escoger frecuencias
    - Captura de entrada (CE) -> 0 No lo usaremos para capturar nada
    - Modo de salida (OM) -> 1 Conmutamos salida en TOUT0
    - Habilita interrupciones (ORI) -> 1 Interrupciones al llegar a TRR0 habilitadas
    - Modo continuo/reinicio (FRR) -> 1 Modo Reinicio de contador
    - Fuente de reloj (CLK) -> 0b10 Reloj del sitema 66 MHz dividido entre 16
    - Habilita temporizador (RST) -> 1 Activa el contador

   FREC_INT0 - Frecuencia a la que queremos que se produzcan las interrupciones
   PRIORIDAD_INT0 - Nivel de prioridad de interrupcion de la CPU
   PS_0 - Preescalado
   CE_0 - Captura de entrada
   OM_0 - Modo de salida
   ORI_0 - Habilita interrupciones
   FRR_0 - Modo continuo/reinicio
   CLK_0 - Fuente de reloj
   CONFIG_TIMER0_ENCENDIDO - Valor con la configuracion a escribir en el registro TMR0 para encenderlo
   CONFIG_TIMER0_APAGADO - Valor con la configuracion a escribir en el registro TMR0 para apagado
   REFERENCIA_TIMER0 - Referencia para lanzar interrupciones a escribir en TRR0

   See also:<Timers>

 */
#define FREC_INT0 1000 //Indiferente
#define PRIORIDAD_INT0 0 //No interrumpe en el sistema -- sonido
#define PS_0 0x00
#define CE_0 0
#define OM_0 1
#define ORI_0 1
#define FRR_0 1
#define CLK_0 2 //10 en binario
#define CONFIG_TIMER0_ENCENDIDO configurar_timer(PS_0,CE_0,OM_0,ORI_0,FRR_0,CLK_0,1)
#define CONFIG_TIMER0_APAGADO configurar_timer(PS_0,CE_0,OM_0,ORI_0,FRR_0,CLK_0,0)//PS_0*256+CE_0*64+OM_0*32+ORI_0*16+FRR_0*8+CLK_0*2+RST_0
#define REFERENCIA_TIMER0 referencia_timer(FREC_INT0,PS_0,CLK_0) //MCF_CLK/(FREC_INT0*(PS_0+1)*(CLK_0&2?16:1))
//entonces es el reloj interno/16 sino lo dejamos a 1

/*
   Constants: Configuración del timer1

   Este temporizador los usaremos para generar interrupciones periodicas para
   reproducir la melodia del juego.

   En esta caso lo usaremos para contar el tiempo que suena cada nota y en de
   que se halla cumplido la rutina de atencion se encargara de cambiar a la
   frencuencia de la siguiente nota en el timer0.

   Para la configuracion de interrupciones periodicas cada 1ms (1KHz) del timer1
   necesitaremos colocar en el registro TMR1 los valores de:
    - Preescalado (PS) -> Al maximo 0x4F
    - Captura de entrada (CE) -> 0 No lo usaremos para capturar nada
    - Modo de salida (OM) -> 1 Irrelevante para nuestro uso
    - Habilita interrupciones (ORI) -> 1 Interrupciones al llegar a TRR1 habilitadas
    - Modo continuo/reinicio (FRR) -> 1 Modo Reinicio de contador
    - Fuente de reloj (CLK) -> 0b10 Reloj del sitema 66 MHz dividido entre 16
    - Habilita temporizador (RST) -> 1 Activa el contador

   Ademas necesitamos que tenga una prioridad de interrpucion medio/alta para
   que otros procesos del sistema no deforme el sonido saliente. Luego
   configuramos el nivel de interrupcion a 5 (de los 7 posibles).

   FREC_INT1 - Frecuencia a la que queremos que se produzcan las interrupciones
   PRIORIDAD_INT1 - Nivel de prioridad de interrupcion de la CPU
   PS_1 - Preescalado
   CE_1 - Captura de entrada
   OM_1 - Modo de salida
   ORI_1 - Habilita interrupciones
   FRR_1 - Modo continuo/reinicio
   CLK_1 - Fuente de reloj
   RST_1 - Habilita temporizador
   CONFIG_TIMER1 - Valor con la configuracion a escribir en el registro TMR1
   REFERENCIA_TIMER1 - Referencia para lanzar interrupciones a escribir en TRR1

   See also:<Timers>

 */
#define FREC_INT1 1000
#define PRIORIDAD_INT1 5
#define PS_1 0x4F
#define CE_1 0
#define OM_1 1
#define ORI_1 1
#define FRR_1 1
#define CLK_1 2 //10 en binario
#define RST_1 1
#define CONFIG_TIMER1 configurar_timer(PS_1,CE_1,OM_1,ORI_1,FRR_1,CLK_1,RST_1)//PS_1*256+CE_1*64+OM_1*32+ORI_1*16+FRR_1*8+CLK_1*2+RST_1
#define REFERENCIA_TIMER1 referencia_timer(FREC_INT1,PS_1,CLK_1)//MCF_CLK/(FREC_INT1*(PS_1+1)*(CLK_1&2?16:1))

/*
   Constants: Configuración del timer2

   Este temporizador los usaremos para refrescar los leds de la pantalla de
   juego.

   Para la configuracion de interrupciones periodicas cada 1ms (1KHz) del timer2
   necesitaremos colocar en el registro TMR2 los valores de:
    - Preescalado (PS) -> Al maximo 0x4F
    - Captura de entrada (CE) -> 0 No lo usaremos para capturar nada
    - Modo de salida (OM) -> 1 Conmutamos salida en TOUT0
    - Habilita interrupciones (ORI) -> 1 Interrupciones al llegar a TRR0 habilitadas
    - Modo continuo/reinicio (FRR) -> 1 Modo Reinicio de contador
    - Fuente de reloj (CLK) -> 0b10 Reloj del sitema 66 MHz dividido entre 16
    - Habilita temporizador (RST) -> 1 Activa el contador

   Ya que este proceso tiene menos urgencia que la reproduccion del sonido le
   asignamos un nivel de prioridad inferior 4 (sobre 7).

   FREC_INT2 - Frecuencia a la que queremos que se produzcan las interrupciones
   PRIORIDAD_INT2 - Nivel de prioridad de interrupcion de la CPU
   PS_2 - Preescalado
   CE_2 - Captura de entrada
   OM_2 - Modo de salida
   ORI_2 - Habilita interrupciones
   FRR_2 - Modo continuo/reinicio
   CLK_2 - Fuente de reloj
   RST_2 - Habilita temporizador
   CONFIG_TIMER2 - Valor con la configuracion a escribir en el registro TMR2
   REFERENCIA_TIMER2 - Referencia para lanzar interrupciones a escribir en TRR2

   See also:<Timers>

 */
#define FREC_INT2 1000
#define PRIORIDAD_INT2 4
#define PS_2 0x4F
#define CE_2 0
#define OM_2 1
#define ORI_2 1
#define FRR_2 1
#define CLK_2 2 //10 en binario
#define RST_2 1
#define CONFIG_TIMER2 configurar_timer(PS_2,CE_2,OM_2,ORI_2,FRR_2,CLK_2,RST_2)//PS_2*256+CE_2*64+OM_2*32+ORI_2*16+FRR_2*8+CLK_2*2+RST_2
#define REFERENCIA_TIMER2 referencia_timer(FREC_INT2,PS_2,CLK_2)//MCF_CLK/(FREC_INT2*(PS_2+1)*(CLK_2&2?16:1))

/*
   Constants: Configuración de las interrupciones

   HABILITAR_INTERRUPCIONES - Valor inicial de registro de interrupciones ICR1
   DESHABILITAR_INTERRUPCIONES - Valor para deshabilitar todas las interrupciones en el ICR1

 */
#define HABILITAR_INTERRUPCIONES 0x88888888+PRIORIDAD_INT0*4096+PRIORIDAD_INT1*256+PRIORIDAD_INT2*16
#define DESHABILITAR_INTERRUPCIONES 0x88888888

/*
   Functions: Declaracion de las funciones contenidas en hardware_conf.c

   Funciones contenidas en hardware_conf.c para mas informacion acceder a ellas.

 */
void habilitar_interrupciones(void);
void deshabilitar_interrupciones(void);
void timer0_inter_atendida(void);
void timer1_inter_atendida(void);
void timer2_inter_atendida(void);
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void interrupciones_init(void);

#endif	/* _HARDWARE_CONF_H */
