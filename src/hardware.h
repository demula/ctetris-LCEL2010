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


/*
   Constants: Constantes varias del Motorola ColdFire 5272
  
   MCF_CLK - Frecuencia del reloj interno del Motorola ColdFire 5272
   BORRA_CAP - Valor de borrado de interr. pendientes de toutn para TERn
   BORRA_REF - Valor de borrado de interr. pendientes de toutn para TERn
 */
#define	MCF_CLK 66000000
#define BORRA_CAP 0x0001
#define BORRA_REF 0x0002


/*
   Constants: Configuración del hardware del teclado

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
 */


/*
   Constants: Configuración del timer0

   Este temporizador los usaremos para generar las ondas cuadradas de la musica
   del juego. La configuracion inicial no es importante ya que andaremos
   cambiandola segun cada nota de la cancion y su duracion.

   Para la configuracion de interrupciones periodicas cada 1ms (1KHz) del timer0
   necesitaremos colocar en el registro TMR0 los valores de:
    - Preescalado (PS) -> Al maximo 0x4F
    - Captura de entrada (CE) -> 0 No lo usaremos para capturar nada
    - Modo de salida (OM) -> 1 Conmutamos salida en TOUT0
    - Habilita interrupciones (ORI) -> 1 Interrupciones al llegar a TRR0 habilitadas
    - Modo continuo/reinicio (FRR) -> 1 Modo Reinicio de contador
    - Fuente de reloj (CLK) -> 0b10 Reloj del sitema 66 MHz dividido entre 16
    - Habilita temporizador (RST) -> 1 Activa el contador

   FREC_INT0 - Frecuencia a la que queremos que se produzcan las interrupciones
   PS_0 - Preescalado
   CE_0 - Captura de entrada
   OM_0 - Modo de salida
   ORI_0 - Habilita interrupciones
   FRR_0 - Modo continuo/reinicio
   CLK_0 - Fuente de reloj
   RST_0 - Habilita temporizador
   CONFIG_TIMER0 - Valor con la configuracion a escribir en el registro TMR0
   REFERENCIA_TIMER0 - Referencia para lanzar interrupciones a escribir en TRR0

   See also:<Timers>
 */
#define FREC_INT0 1000
#define PRIORIDAD_INT0 6
#define PS_0 0x4F
#define CE_0 0
#define OM_0 1
#define ORI_0 1
#define FRR_0 1
#define CLK_0 2 //10 en binario
#define RST_0 1
#define CONFIG_TIMER0 PS_0*256+CE_0*64+OM_0*32+ORI_0*16+FRR_0*8+CLK_0*2+RST_0
#define REFERENCIA_TIMER0 (MCF_CLK)/(FREC_INT0*(PS_0+1)*(CLK_0&2?16:1))//CLK_0&2?16:1 Si CLK_0 == 10
//entonces es el reloj interno/16 sino lo dejamos a 1

/*
   Constants: Configuración del timer1

   Este temporizador los usaremos para generar interrupciones periodicas para
   reproducir la melodia deñ juego.

   Para la configuracion de interrupciones periodicas cada 1ms (1KHz) del timer1
   necesitaremos colocar en el registro TMR1 los valores de:
    - Preescalado (PS) -> Al maximo 0x4F
    - Captura de entrada (CE) -> 0 No lo usaremos para capturar nada
    - Modo de salida (OM) -> 1 Irrelevante para nuestro uso
    - Habilita interrupciones (ORI) -> 1 Interrupciones al llegar a TRR1 habilitadas
    - Modo continuo/reinicio (FRR) -> 1 Modo Reinicio de contador
    - Fuente de reloj (CLK) -> 0b10 Reloj del sitema 66 MHz dividido entre 16
    - Habilita temporizador (RST) -> 1 Activa el contador

   FREC_INT1 - Frecuencia a la que queremos que se produzcan las interrupciones
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
#define CONFIG_TIMER1 PS_1*256+CE_1*64+OM_1*32+ORI_1*16+FRR_1*8+CLK_1*2+RST_1
#define REFERENCIA_TIMER1 (MCF_CLK)/(FREC_INT1*(PS_1+1)*(CLK_1&2?16:1))


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

   FREC_INT2 - Frecuencia a la que queremos que se produzcan las interrupciones
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
#define CONFIG_TIMER2 PS_2*256+CE_2*64+OM_2*32+ORI_2*16+FRR_2*8+CLK_2*2+RST_2
#define REFERENCIA_TIMER2 (MCF_CLK)/(FREC_INT2*(PS_2+1)*(CLK_2&2?16:1))


/*
   Constants: Configuración de las interrupciones

   VALOR_ICR1 - Valor inicial de registro de interrupciones ICR1
 */
#define VALOR_ICR1 0x88888888+PRIORIDAD_INT0*4096+PRIORIDAD_INT1*256+PRIORIDAD_INT2*16


/*
   Functions: Declaracion de las funciones contenidas en hardware_conf.c

   Funciones contenidas en hardware_conf.c para mas informacion acceder a ellas.
 */
// -------------------------------------------------------------- INTERRUPCIONES
void habilitar_interrupciones(void);
void deshabilitar_interrupciones(void);
void timer0_inter_atendida(void);
void timer1_inter_atendida(void);
void timer2_inter_atendida(void);
// ------------------------------------------------------------ INICIALIZACIONES
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void interrupciones_init(void);


#endif	/* _HARDWARE_CONF_H */
