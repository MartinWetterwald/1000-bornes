/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : menu.h                 *
*                                                *
*************************************************/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/* Gestion des dépendances :
Le menu requiert la couche joueur. */
#include "joueur.h"

void afficher_logo();

void menu_principal(int* choix);

void menu_difficulte_ordinateur(int* choix);

void menu_demander_choix_carte(int* choix_carte);
void menu_demander_choix_carte_jeter(int* choix_carte, int nb_coups_possibles);
void menu_demander_coup_fourre(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int obstacle, int botte, char* raison_refus, char* raison_refus2);

void menu_quitter_etes_vous_sur(int* choix);
void menu_demander_ordinateur(int* choix);
void menu_demander_nom_joueur(char nom[NOM_TAILLE_MAX], int joueur_num);
void demander_appuyez_sur_une_touche_pour_continuer();

void menu_charger_partie(char* choix);
void menu_enregistrer_partie(char* choix);

#endif // MENU_H_INCLUDED
