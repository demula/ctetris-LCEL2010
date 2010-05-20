/*
   control.h
   Control de ctetris para Motorola Coldfire 5242 sobre la plataforma de desarrollo
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

#ifndef _CONTROL_H
#define	_CONTROL_H

//#include "juego.c"
//#include "m5272lcd.c"
#include "juego.h"


/*
   Constants: Textos de los menus del juego

   Cadenas de texto que se muestran al encender el juego para la seleccion de
   dificultad y que son visibles en la pantalla del ordenador.

 */
#define TEXTO_BIENVENIDA "Bienvenido a ColdtrixTM:\n"
#define TEXTO_NIVELES_POSIBLES "Por favor pulse: (1) Facil, (4) Medio, (7) Dificil\n"
#define TEXTO_NIVEL_SELECCIONADO "Nivel seleccionado: "
#define TEXTO_NIVEL_1 "Facil"
#define TEXTO_NIVEL_2 "Medio"
#define TEXTO_NIVEL_3 "Dificil"
#define TEXTO_NO_NIVEL "No ha seleccionado ningun nivel.\n"
#define TEXTO_COMENZAR_JUEGO ". Pulse A para comenzar la partida...\n"
#define TEXTO_TECLA_ERRONEA "Tecla no valida"

/*
   Constants: Teclado matricial

   Valor de las teclas del teclado matricial de la placa entrenadora para la
   eleccion de nivel en el juego.

 */
#define TECLA_COMIENZO 'A'
#define TECLA_NIVEL_1 '1'
#define TECLA_NIVEL_2 '4'
#define TECLA_NIVEL_3 '7'

/*
   Constants: Constantes de uso para el puerto de salida
  
   Estas constantes configuran el objeto Puerto encargado de manejar la salida.

   EXCITACION - Valor de excitacion de un bit de salida
   POS_TECLADO - Posicion del bit menos significativo del teclado
   POS_COLUMNA - Posicion del bit menos significativo de la salida a las columnas
   POS_FILA - Posicion del bit menos significativo de la salida a las filas
   MASCARA_TECLADO - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados al teclado (mascara AND y luego sumado)
   MASCARA_COLUMNA_LEDS - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados a la columna de leds (mascara AND...)
   MASCARA_FILA_LEDS - Mascara para asegurarse que solo se tocan los bits de 
                        salida asociados a la fila de leds (mascara AND...)

 */
#define EXCITACION 0x0001
#define POS_TECLADO 0
#define POS_COLUMNA 4
#define POS_FILA 8
#define MASCARA_TECLADO 0xFFF0
#define MASCARA_COLUMNA_LEDS 0xFF0F
#define MASCARA_FILA_LEDS 0x00FF

/*
   Struct: Puerto

   Esta estructura tiene guardado el valor del puerto de salida en cada momento 
   ya que este no puede ser leido.

   Para la modificacion de esta estructura (y puerto de salida) se debe hacer
   exclusivamente con los metodos facilitados de el objeto Puerto.

   situacion_puerto - Valor actual del puerto de salida.

 */
typedef struct
{
    short int situacion_puerto;
} Puerto;

/*
   Functions: Prototipos de las funciones contenidas en control.c

   Funciones contenidas en control.c para mas informacion acceder a ellas.

 */
char tecla_pulsada(Puerto *p_puerto);
void menu(Estado *p_estado, Leds *p_leds, Juego *p_juego, Resultados *p_resultados, char *p_lock, char tecla);
void leds_refrescar(Puerto *p_puerto, Leds *p_leds);
void estado_init(Estado *p_estado);
void puerto_init(Puerto *p_puerto);
short int columna_a_puerto(char columna);
short int fila_a_puerto(short int fila_leds);
void puerto_excita_columna(Puerto *p_puerto, char columna, int fila_leds);
void puerto_excita_teclado(Puerto *p_puerto, char columna);
//void lcd_init(void);
//void lcd_imprimir(char* p_mensaje);
//void lcd_limpiar(void);

#endif	/* _CONTROL_H */

