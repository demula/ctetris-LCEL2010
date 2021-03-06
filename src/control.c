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
  
   Parameters:

      p_puerto - Puntero a la estructura de manejo de puerto.

 */
char tecla_pulsada(Puerto *puerto)
{
    char fila, columna, fila_mask;
    static char teclas[NUM_FILAS_TECLADO][NUM_COLS_TECLADO] = {
        {"123C"},
        {"456D"},
        {"789E"},
        {"A0BF"}
    };
    while (TRUE)
    {
        for (columna = 0; columna < NUM_COLS_TECLADO; columna++)
        { //Excitamos una columna
            puerto_excita_teclado(puerto, EXCITACION << columna); //Se envía la excitación de columna
            retardo(RET_OPTOACOPLADORES); //Esperamos respuesta de optoacopladores

            for (fila = 0; fila < NUM_FILAS_TECLADO; fila++)
            { // Exploramos las filas en busca de respuesta
                fila_mask = EXCITACION << fila; //Máscara para leer el bit de la fila actual
                if (lee_puertoE() & fila_mask)//Si encuentra tecla pulsada
                {
                    while (lee_puertoE() & fila_mask); //Esperamos a que se suelte
                    retardo(RET_REBOTES); //Retardo antirrebotes
                    return teclas[(int) fila][(int) columna]; //Devolvemos la tecla pulsada
                }
            }//Siguiente columna
        }// Exploración finalizada sin encontrar una tecla pulsada
    }//Reiniciamos exploración
}

/*
   Function: menu

   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.
  
   Los punteros a Leds, Juego, Resultados son necesarios ya que tenemos incluida
   la funcion juego_nuevo_juego dentro de menu.
   TODO: sacarla para reducir dependencia entre objetos/funciones

   Parameters:

      p_estado - Puntero a el estado global.
      tecla - char con el valor de la tecla pulsada.

 */
void menu(Estado *p_estado, Leds *p_leds, Juego *p_juego, Resultados *p_resultados, char *lock, char tecla)
{
    if (*lock == FALSE)
    {
        *lock = TRUE;
    switch (tecla)
    {
        case TECLA_NIVEL_1:
        {
            p_juego->nivel_dificultad = VALOR_NIVEL_1;
            output(TEXTO_NIVEL_SELECCIONADO);
            output(TEXTO_NIVEL_1);
            output(TEXTO_COMENZAR_JUEGO);
        }
            break;
        case TECLA_NIVEL_2:
        {
            p_juego->nivel_dificultad = VALOR_NIVEL_2;
            output(TEXTO_NIVEL_SELECCIONADO);
            output(TEXTO_NIVEL_2);
            output(TEXTO_COMENZAR_JUEGO);
        }
            break;
        case TECLA_NIVEL_3:
        {
            p_juego->nivel_dificultad = VALOR_NIVEL_3;
            output(TEXTO_NIVEL_SELECCIONADO);
            output(TEXTO_NIVEL_3);
            output(TEXTO_COMENZAR_JUEGO);
        }
            break;
        case TECLA_COMIENZO:
        {
            if (p_juego->nivel_dificultad == VALOR_NIVEL_NO_DEFINIDO)
            {
                output(TEXTO_NO_NIVEL);
                output(TEXTO_NIVELES_POSIBLES);
            }
            else
            {
                juego_nuevo_juego(p_leds, p_juego, p_resultados);
                p_estado->jugando = TRUE;
            }
        }
            break;
        default:
        {
            output(TEXTO_TECLA_ERRONEA);
            output(TEXTO_COMENZAR_JUEGO);
        }
            break;
    }
    *lock = FALSE;
    }
}

// ------------------------------------------------------------------------- LCD
/*
   Function: lcd_init
   Inicializa el lcd.
 *//*
void lcd_init(void)
{
    LCD_reset(); // Reseteamos el LCD
    LCD_init(); // e inicializamos el display
}*/

/*
   Function: imprimir_en_lcd
   Imprime una cadena de caracteres por el lcd.

   Parameters:

      mensaje - Cadena de caracteres  imprimir.
 *//*
void lcd_imprimir(char* p_mensaje)
{
    LCD_inst(LIN_1LCD);
    while (*p_mensaje)
    {
        LCD_dato(*p_mensaje++);
    }
}*/

/*
   Function: limpiar_lcd
   Borrar todo lo escrito en el lcd y vuelve a poner el cursor en la 1a linea.
 *//*
void lcd_limpiar(void)
{
    LCD_inst(CLR_DISP);
    LCD_inst(LIN_1LCD);
}*/

// ------------------------------------------------------------------------ LEDS
/*
   Function: refrescar_leds

   Cada vez que llamamos a esta funcion refrescara la la columna de leds que
   toque teniendo en cuenta la pieza activa y actualizara la la informacion de
   columna_a_refrescar en el struct leds.

   Esta funcion esta situada en control.c porque requiere del objeto Puerto y
   colocarla en juego.c (donde le corresponderia) es mas de un dolor de cabeza.

   Parameters:

      p_puerto - Puntero a la estructura de manejo de puerto.
      p_leds - Entero con los datos de una fila de leds.

 */
void leds_refrescar(Puerto *p_puerto, Leds *p_leds)
{
    static char columna_a_refrescar = 0;
    static int contador_resfresco = 0;
    int fila_leds;
    contador_resfresco++;
    if (contador_resfresco == TASA_REFRESCO)
    {
        contador_resfresco = 0;
        leds_fila_a_int(p_leds, columna_a_refrescar, &fila_leds);
        puerto_excita_columna(p_puerto, columna_a_refrescar, fila_leds);
        columna_a_refrescar++;
        if (columna_a_refrescar == NUM_COLUMNAS_LED)
        {
            columna_a_refrescar = 0;
        }
    }
}

// ---------------------------------------------------------------------- ESTADO
/*
   Function: estado_init
 
   Inicializa una estructura Estado con lo valores que se le dan declarados en
   control.h.
   
   Parameters:

      p_estado - Puntero a la estructura Estado que queremos inicializar.

 */
void estado_init(Estado *p_estado)
{
    p_estado->jugando = 0;
    p_estado->texto_menu[0] = TEXTO_NIVEL_1;
    p_estado->texto_menu[1] = TEXTO_NIVEL_2;
    p_estado->texto_menu[2] = TEXTO_NIVEL_3;
}

// ---------------------------------------------------------------------- PUERTO
/*
   Function: puerto_init

   Inicializa una estructura Puerto con valores a 0.

   Parameters:

      p_puerto - Puntero a la estructura Puerto que queremos inicializar.
 
 */
void puerto_init(Puerto *p_puerto)
{
    p_puerto->situacion_puerto = 0;
    set16_puertoS(0);
}

/*
   Function: columna_a_puerto
   
   Convierte el valor numerico que representa a la columna al valor de salida 
   en el puerto. 
   
   Recordamos que la columna tiene que estar a nivel alto (1) para encenderse.

   Parameters:

      columna - valor numerico de la columna de leds que queremos excitar.

 */
short int columna_a_puerto(char columna)
{
    short int salida = 0;
    salida = EXCITACION << columna;
    salida = salida << POS_COLUMNA;
    return salida;
}

/*
   Function: fila_a_puerto
   
   Coniverte el string que representa a la fila a el valor que necesitamos en el
   puerto de salida.

   Recordamos que la columna tiene que estar a nivel bajo (0) para encenderse.

   Parameters:

      fila_leds - String con la informacion de los leds que se vana encender.

 */
short int fila_a_puerto(short int fila_leds)
{
    short int salida = 0;
    //Para encender los leds tienen que estar a nivel bajo en fila
    fila_leds = ~fila_leds; //El operador ~ es negacion BIT A BIT (! no vale)
    salida = fila_leds << POS_FILA;
    return salida;
}

/*
   Function: puerto_excita_columna
   
   Excita la columna de leds que queremos con la informacion de fila dados.

   Parameters:

      p_puerto - Puntero a la estructura Puerto que queremos inicializar.
      columna - Columna que queremos excitar.
      fila_leds - Informacion de los leds encendidos de dicha columna.

 */
void puerto_excita_columna(Puerto *p_puerto, char columna, int fila_leds)
{
    /*
       Deshabilitamos y posteriormente habilitamos interrupciones para evitar
       que se corrompan las variables globales. TODO: Implementar locks (mas elegante)
     */
    //deshabilitar_interrupciones();
    short int columna_en_puerto = 0;
    short int fila_en_puerto = 0;

    //Colocamos la columna en su posicion correspondiente en el puerto de salida
    columna_en_puerto = columna_a_puerto(columna);
    //Limpiamos todos lo bits que no debe usar la columna (por seguridad ya que luego SUMAMOS)
    columna_en_puerto = ~MASCARA_COLUMNA_LEDS & columna_en_puerto;
    //Ponemos los bits pertencientes a la columna a 0
    p_puerto->situacion_puerto = p_puerto->situacion_puerto & MASCARA_COLUMNA_LEDS;
    p_puerto->situacion_puerto += columna_en_puerto;

    //Colocamos la fila en su posicion correspondiente en el puerto de salida
    fila_en_puerto = fila_a_puerto(fila_leds);
    //Limpiamos todos lo bits que no debe usar la fila (por seguridad ya que luego SUMAMOS)
    fila_en_puerto = ~MASCARA_FILA_LEDS & fila_en_puerto;
    //Ponemos los bits pertencientes a la fila a 0
    p_puerto->situacion_puerto = p_puerto->situacion_puerto & MASCARA_FILA_LEDS;
    p_puerto->situacion_puerto += fila_en_puerto;
    set16_puertoS(p_puerto->situacion_puerto);
    //habilitar_interrupciones();
}

/*
   Function: puerto_excita_teclado
   
   Excita la columna del teclado indicada sin modificar los demas valores del
   puerto de salida.

   Parameters:

      p_puerto - Puntero a la estructura Puerto que queremos inicializar.
      columna_teclado - Columna que queremos excitar.
 
 */
void puerto_excita_teclado(Puerto *p_puerto, char columna_teclado)
{
    p_puerto->situacion_puerto = p_puerto->situacion_puerto & MASCARA_TECLADO;
    p_puerto->situacion_puerto += columna_teclado;

    set16_puertoS(p_puerto->situacion_puerto);
}


