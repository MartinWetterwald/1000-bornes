#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : ia.h                   *
*                                                *
*************************************************/

#endif // IA_H_INCLUDED

/* Gestion des dépendances :
ia requiert la couche jeu */
#include "jeu.h"

void ia_archi_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_course(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_agressif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_defensif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_expert(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
