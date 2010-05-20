/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : jeu.h                  *
*                                                *
*************************************************/

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

/* Gestion des dépendances :
La couche « jeu » requiert la couche inférieure : joueur */
#include "joueur.h"

typedef struct Tpartie
{
    Tptdeck deck;
    Tptjoueur joueur_selectionne;
    Tptjoueur autre_joueur;
} Tpartie, *Tptpartie;

Tptpartie partie_init();
Tptjoueur qui_commence(Tptjoueur joueur1, Tptjoueur joueur2);
void jeu_init(Tptpartie partie, Tptjoueur joueur1, Tptjoueur joueur2);
void switch_tour(Tptpartie partie);
Tptjoueur detecter_gagnant(Tptjoueur joueur1, Tptjoueur joueur2);
int partie_terminee(Tptpartie);
int coup_autorise(char* raison_refus, char* raison_refus2, Tptjoueur joueur_selectionne, Tptjoueur autre_joueur, int carte_type);
Tptdeck lister_coups_possibles(Tptjoueur joueur_selectionne, Tptjoueur autre_joueur);
void coup_fourre(Tptpartie partie, int obstacle, int botte, char* raison_refus, char* raison_refus2);
int jouer(Tptpartie partie,  int carte_type, int passe_son_tour, char* raison_refus, char* raison_refus2);
void consequences_coup(Tptpartie partie, int carte_type);
void jeu(Tptpartie partie);
void partie_vider(Tptpartie partie);

#endif // JEU_H_INCLUDED
