/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : divers.h               *
*                                                *
*************************************************/

#ifndef DIVERS_H_INCLUDED
#define DIVERS_H_INCLUDED

#include "constantes.h"

#ifndef LINUX
    #include <windows.h>

    typedef enum e_color
    {
        NOIR,
        BLEU,
        VERT,
        CYAN,
        ROUGE,
        ROSE,
        JAUNE,
        BLANC
    } COULEUR;
#else
    typedef enum e_color
    {
        NOIR,
        ROUGE,
        VERT,
        JAUNE,
        BLEU,
        ROSE,
        CYAN,
        BLANC
    } COULEUR;
#endif

void printfEx(COULEUR couleur, const char *str, ...);
void console_titre(const char *titre);


//int char2int(char* chaine);
void viderBuffer();
int lire(char *chaine, int longueur);
long lireLong();

#endif // DIVERS_H_INCLUDED
