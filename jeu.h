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

Tjoueur* qui_commence(Tjoueur* joueur1, Tjoueur* joueur2);
void jeu_init(Tdeck* deck, Tjoueur* joueur1, Tjoueur* joueur2, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur);
void switch_tour(Tptjoueur** joueur_selectionne, Tptjoueur** autre_joueur);
Tjoueur* detecter_gagnant(Tjoueur* joueur1, Tjoueur* joueur2);
int partie_terminee(Tdeck* deck, Tjoueur* joueur1, Tjoueur* joueur2);
int coup_autorise(char* raison_refus, char* raison_refus2, Tjoueur* joueur_selectionne, Tjoueur* autre_joueur, int carte_type);
void coup_fourre(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int obstacle, int botte, char* raison_refus, char* raison_refus2);
int jouer(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur,  int carte_type, int passe_son_tour, char* raison_refus, char* raison_refus2);
void consequences_coup(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int carte_type);
void jeu(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur);

#endif // JEU_H_INCLUDED
