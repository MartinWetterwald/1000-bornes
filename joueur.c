/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : joueurs.c              *
* DESCRIPTION : Fonctions gérant la couche       *
* des joueurs.                                   *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "divers.h"
#include "joueur.h"

//Cette fonction initialise un joueur vide.
Tjoueur* joueur_init(int est_ordinateur)
{
    char nom_ordinateur[NOM_TAILLE_MAX] = "Ordinateur";

    Tjoueur* monJoueur = malloc(sizeof(Tjoueur));
    monJoueur -> est_ordinateur = est_ordinateur;

    if(est_ordinateur)
        strcpy(monJoueur -> nom, nom_ordinateur);

    monJoueur -> deck = liste_init(); //On crée un deck vide et on l'attribut au joueur.
    monJoueur -> est_creve = 0;
    monJoueur -> a_accident = 0;
    monJoueur -> en_panne_dessence = 0;
    monJoueur -> est_limite_par_vitesse = 0;
    monJoueur -> est_arrete = 1; //Par défaut, un joueur est arrêté (feu rouge).

    return monJoueur;
}

//Cette fonction affiche toutes les infos sur un joueur.
void joueur_afficher(Tjoueur* monJoueur)
{
    //S'il y a quelque chose à faire
    if(monJoueur != NULL)
    {
        printf("Type de joueur : ");
        if(monJoueur -> est_ordinateur)
            printf("ordinateur");
        else
            printf("humain");

        printf("\nNom du joueur : %s\n", monJoueur -> nom);

        printf("Voici un récapitulatif des cartes de '%s'\n", monJoueur -> nom);
        cartes_deck_afficher(monJoueur -> deck);

        printf("\nSes handicaps : \n");
        if(monJoueur -> est_creve)
            printf("- Il a les pneus crevés.\n");

        if(monJoueur -> a_accident)
            printf("Il a un accident.\n");

        if(monJoueur -> en_panne_dessence)
            printf("Il n'a plus d'essence.\n");

        if(monJoueur -> est_limite_par_vitesse)
            printf("Sa vitesse est limitée.\n");

        if(monJoueur -> est_arrete)
            printf("Il est à l'arrêt.\n");
    }
}

void joueur_detruire(Tptjoueur* joueur)
{
    //Si on a quelque chose à faire
    if(*joueur != NULL)
    {
        deck_detruire(&((*joueur) -> deck)); //On fournit l'adresse du deck qui se trouve dans ((pointeur de joueur) pointé deck)
        free(*joueur);
        *joueur = NULL;
    }
}
