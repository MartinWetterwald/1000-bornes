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
Tjoueur* qui_commence(Tjoueur* joueur1, Tjoueur* joueur2);
void jeu_init(Tptpartie partie, Tdeck* deck, Tjoueur* joueur1, Tjoueur* joueur2);
void switch_tour(Tptjoueur** joueur_selectionne, Tptjoueur** autre_joueur);
Tjoueur* detecter_gagnant(Tjoueur* joueur1, Tjoueur* joueur2);
int partie_terminee(Tptpartie);
int coup_autorise(char* raison_refus, char* raison_refus2, Tjoueur* joueur_selectionne, Tjoueur* autre_joueur, int carte_type);
Tdeck* lister_coups_possibles(Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur);
void coup_fourre(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int obstacle, int botte, char* raison_refus, char* raison_refus2);
int jouer(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur,  int carte_type, int passe_son_tour, char* raison_refus, char* raison_refus2);
void consequences_coup(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int carte_type);
void jeu(Tptpartie partie);

#endif // JEU_H_INCLUDED
