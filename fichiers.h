/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION :                                  *
*                                                *
*************************************************/

#ifndef FICHIERS_H_INCLUDED
#define FICHIERS_H_INCLUDED

int enregistrer_partie(const char* nomFichier, Tdeck* deckPrincipal, Tdeck* deckJoueur1, Tdeck* deckJoueur2);
int charger_partie(const char* nomFichier, Tdeck* deckPrincipal, Tdeck* deckJoueur1, Tdeck* deckJoueur2);

#endif // FICHIERS_H_INCLUDED
