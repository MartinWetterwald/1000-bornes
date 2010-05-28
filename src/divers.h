/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : divers.h                     *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
*******************************************************/

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

#define COULEUR_OBSTACLES       ROUGE
#define COULEUR_PARADES         VERT
#define COULEUR_BOTTES          JAUNE
#define COULEUR_BORNES          CYAN
#define COULEUR_VOITURE        BLEU
#define COULEUR_VOITURE_ROUES   JAUNE


void printfEx(COULEUR couleur, const char *str, ...);
void console_titre(const char *titre);


//int char2int(char* chaine);
void viderBuffer();
int lire(char *chaine, int longueur);
long lireLong();

#endif // DIVERS_H_INCLUDED
