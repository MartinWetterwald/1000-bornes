/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION :                                  *
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
    int est_creve;
    int a_accident;
    int en_panne_dessence;
    int est_limite_par_vitesse;
    int est_arrete; //Feu rouge
} Tjoueur, *Tptjoueur;

Tjoueur* joueur_init(int est_ordinateur);
void joueur_afficher(Tjoueur* monJoueur);
void joueur_detruire(Tptjoueur* joueur);

#endif // JOUEUR_H_INCLUDED
