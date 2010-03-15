/*
   juego.c
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


#include "juego.h"


/*
   Function: nueva_pieza

   Dependiendo de la tecla que se le pase cambia el nivel de dificultad. Por
   defecto no hace nada.

   Parameters:

      clase - Caracter con la clase de la que queremos la pieza.

   Returns:

      Pieza colocada en coordenadas de inicio superiores al marco de la pantalla.
*/
void set_coordenadas(Pieza *pieza, int x, int y)
{
    pieza->x = x;
    pieza->y = y;
}


/*
   Function: copia_texto_forma

   Copia caracteres de una cadena a otra.

   Necesitamos esta funcion ya que no se pueden asignar cadenas completas ni
   strncpy esta disponible. Ademas necesitamos quitar las comas y puntos y comas
   que pusimos por legibilidad en las constantes.

   Parameters:

      *destino - Puntero a la cadena que queremos copiar los carecteres de origen.
      origen - Cadena de caracteres que queremos copiar.
*/
void copia_texto_forma(char *destino, char origen[])
{
    int posicion_origen;
    int posicion_destino = 0;
    for (posicion_origen=0; posicion_origen<ANCHO_PIEZA*ALTO_PIEZA*ROTACIONES-ALTO_PIEZA*ROTACIONES; posicion_origen++)
    {
        switch (origen[posicion_origen])
        {
            case '0':
                destino[posicion_destino] = origen[posicion_origen];
                posicion_destino++;
                break;
            case '1':
                destino[posicion_destino] = origen[posicion_origen];
                posicion_destino++;
                break;
        }
    }

}


/*
   Function: forma_init

   Parameters:

      *pieza - Puntero a la estructura Pieza que queremos inicializar.
*/
void forma_init(Pieza *pieza)
{
    copia_texto_forma(*pieza->forma, FORMA_O);
    copia_texto_forma(*pieza->forma, FORMA_I);
    copia_texto_forma(*pieza->forma, FORMA_T);
    copia_texto_forma(*pieza->forma, FORMA_L);
    copia_texto_forma(*pieza->forma, FORMA_J);
    copia_texto_forma(*pieza->forma, FORMA_S);
    copia_texto_forma(*pieza->forma, FORMA_Z);
}


/*
   Function: posiciones_comienzo_init

   Parameters:

      *pieza - Puntero a la estructura Pieza que queremos inicializar.
*/
void posiciones_comienzo_init(Pieza *pieza)
{
    pieza->x_comienzo[PIEZA_O] = O_X;
    pieza->y_comienzo[PIEZA_O] = O_Y;
    pieza->x_comienzo[PIEZA_I] = I_X;
    pieza->y_comienzo[PIEZA_I] = I_Y;
    pieza->x_comienzo[PIEZA_T] = T_X;
    pieza->y_comienzo[PIEZA_T] = T_Y;
    pieza->x_comienzo[PIEZA_L] = L_X;
    pieza->y_comienzo[PIEZA_L] = L_Y;
    pieza->x_comienzo[PIEZA_J] = J_X;
    pieza->y_comienzo[PIEZA_J] = J_Y;
    pieza->x_comienzo[PIEZA_S] = S_X;
    pieza->y_comienzo[PIEZA_S] = S_Y;
    pieza->x_comienzo[PIEZA_Z] = Z_X;
    pieza->y_comienzo[PIEZA_Z] = Z_Y;
}


/*
   Function: pieza_init
 
   Inicializa una estructura pieza con la pieza de clase O.

   Parameters:

      *pieza - Puntero a la estructura Pieza que queremos inicializar.
*/
void pieza_init(Pieza *pieza)
{
    pieza->clase = PIEZA_O; //Notice the equal to and the comma
    pieza->rotacion  = 0;
    pieza->x  = O_X;
    pieza->y = O_Y;
    forma_init(pieza);
    posiciones_comienzo_init(pieza);
}