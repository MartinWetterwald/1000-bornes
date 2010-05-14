/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : joueur.h               *
*                                                *
*************************************************/

#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

/* Gestion des dépendances :
La couche « joueur » requiert la couche inférieure : cartes */
#include "cartes.h"

typedef struct Tjoueur {
    int est_ordinateur; //Pour distinguer un joueur ordinateur d'un autre
    char nom[NOM_TAILLE_MAX];
    Tdeck* deck;

    /* Ces variables serviront surtout au comptage des points à la fin */
    int cumul_bornes;
    int nb_bottes_jouees;
    int nb_coups_fourres_joues;
    int nb_200bornes_jouees;
    int couronnement;

    int carte_precedemment_jouee;

    /* État du joueur */
    int est_creve;
    int a_accident;
    int en_panne_dessence;
    int est_limite_par_vitesse;
    int est_arrete; //Feu rouge
    //Bottes
    int increvable;
    int citerne;
    int as_du_volant;
    int prioritaire;

} Tjoueur, *Tptjoueur;

Tjoueur* joueur_init(int est_ordinateur);
Tcarte* joueur_possede_carte(Tjoueur* monJoueur, int carte_type);
void joueur_afficher(Tjoueur* monJoueur);
int joueur_compter_les_points(Tjoueur* joueur, int cumul_bornes_autre_joueur);
void joueur_detruire(Tptjoueur* joueur);

#endif // JOUEUR_H_INCLUDED
