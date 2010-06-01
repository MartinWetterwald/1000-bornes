/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : menu.h                       *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
* Code source : http://github.com/djfox/1000-bornes    *
*******************************************************/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/* Gestion des dépendances :
Le menu requiert la couche joueur. */
#include "jeu.h"

void afficher_logo();
void afficher_licence();

void menu_principal(int* choix);

void menu_difficulte_ordinateur(int* choix, int num_joueur);

void menu_demander_choix_carte(int* choix_carte, int nb_coups_possibles);
void menu_demander_choix_carte_jeter(int* choix_carte);
void menu_demander_coup_fourre(Tptpartie partie, int obstacle, int botte, char* raison_refus, char* raison_refus2);

void menu_demander_ordinateur(int* choix);
void menu_demander_nom_joueur(char nom[NOM_TAILLE_MAX], int joueur_num);
void demander_appuyez_sur_une_touche_pour_continuer();

void menu_charger_partie(char* choix);
void menu_enregistrer_partie(char* choix);

#endif // MENU_H_INCLUDED
