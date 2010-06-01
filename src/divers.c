/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : divers.c                     *
* DESCRIPTION : Fonctions diverses, c'est-à-dire       *
* pouvant être appelées n'importe où dans le           *
* code, et ne rentrant dans aucune catégorie.          *
* Grosso modo ce sont des fonctions externes qui       *
* peuvent être utiles dans de nombreux                 *
* programmes et qui ne sont pas spécifiques au         *
* jeu des mille bornes.                                *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
* Code source : http://github.com/djfox/1000-bornes    *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "divers.h"

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

//Les deux fonctions suivantes proviennent du site http://www.cppfrance.com/codes/COULEUR-CONSOLE_40135.aspx
/* Fonction permettant d'écrire du texte en couleur dans la console à la fois sous Linux et Windows */
void printfEx(COULEUR couleur, const char *str, ...)
{
    #ifndef LINUX
        HANDLE hCmd = NULL;
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        COORD pt;
    #endif
        char buf[1024] = "";
        va_list ap;

        if (!str || *str == '\0')
            return;

    #ifndef LINUX
        hCmd = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hCmd, &consoleInfo);
        SetConsoleTextAttribute(hCmd, (short) (couleur | FOREGROUND_INTENSITY));
    #endif

    va_start(ap, str);
    vsprintf(buf, str, ap);
    va_end(ap);

    #ifndef LINUX
        printf(buf);
        SetConsoleTextAttribute(hCmd, consoleInfo.wAttributes);
    #else
        printf("\033[3%dm %s \033[m", couleur, buf);
    #endif
}

/* Fonction permettant de changer le titre de la console à la fois sous Linux et Windows */
void console_titre(const char *titre)
{
    #ifndef LINUX
        SetConsoleTitle(titre);
    #else
        printf("\033]0;%s\007", titre);
    #endif
}
