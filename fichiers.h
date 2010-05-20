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

/* Gestion des dépendances :
La couche « fichiers » requiert la couche « jeu » */
#include "jeu.h"

int enregistrer_deck(FILE* fichier, Tptdeck deck);
int enregistrer_joueur(FILE* fichier, Tptjoueur joueur);
int enregistrer_partie(const char* nomFichier, Tptpartie partie);
int charger_partie(const char* nomFichier, Tptdeck deckPrincipal, Tptdeck deckJoueur1, Tptdeck deckJoueur2);

#endif // FICHIERS_H_INCLUDED
