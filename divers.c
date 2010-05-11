/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION :                                  *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "divers.h"

/* Fonction qui convertit un char en entier */
/*int char2int(char* chaine)
{
    int nombre = 0;

    for (; *chaine; chaine++)
    {
       nombre *= 10;
       nombre += *chaine - '0';
    }
    return nombre;
}*/

/* Fonctions de saisie sécurisée, pour remplacer le scanf */
/* Source : http://www.siteduzero.com/tutoriel-3-14185-la-saisie-de-texte-securisee.html */

/* Cette fonction sert uniquement à la fonction suivante. */
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/* Cette fonction sécurise la saisie. C'est un alternatif au scanf. */
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

/* Cette fonction permet de faire saisir un nombre à l'utilisateur. Il sera récupéré directement en long, et pas en char*. */
long lireLong()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if(lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer -1
        return -1;
    }
}
