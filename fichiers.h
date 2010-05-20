/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : fichiers.h             *
*                                                *
*************************************************/

#ifndef FICHIERS_H_INCLUDED
#define FICHIERS_H_INCLUDED

int enregistrer_partie(const char* nomFichier, Tptdeck deckPrincipal, Tptdeck deckJoueur1, Tptdeck deckJoueur2);
int charger_partie(const char* nomFichier, Tptdeck deckPrincipal, Tptdeck deckJoueur1, Tptdeck deckJoueur2);

#endif // FICHIERS_H_INCLUDED
