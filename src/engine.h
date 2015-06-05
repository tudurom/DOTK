#ifndef ENGINE_H
#define ENGINE_H
#include "textutil/textutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SLEEPCONST 10

int getRandInRange( int min, int max );

/* Returneaza nr. de coloane ale consolei. */
int getConsoleWidth();

/* Returneaza nr. de linii ale consolei */
int getConsoleHeight();

/* Seteaza marimea consolei */
void setWindowSize(int width, int height);
enum ALIGN {
    LEFT = -1,
  CENTER =  0,
   RIGHT =  1
};
/* Afiseaza sirul de caractere 's' la ordonata,
   aliniate la stanga, in centru sau la dreapta
*/
void putStrAlign( int y, char *s, enum ALIGN align );
/* Considerand s continutul unui fisier in care se afla un
   desen ASCII, functia afiseaza s la ordonata y.
   "Align" specifica in ce directie sa fie aliniat textul.
*/
int printASCIIArt( int y, char *s, enum ALIGN align );

/* La fel ca si functia printASCIIArt, doar ca textul este citit dintr-un fisier */
int printASCIIArtFromFile( int y, char *path, enum ALIGN align );

/* Initializeaza consola */
void initConsole();

/* Reseteaza  */
void resetColor();

int buildOptionsMenu(int y, int n, char* options[], enum ALIGN align, int color);
#endif
