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

    monJoueur -> cumul_bornes = 0;
    monJoueur -> nb_bottes_jouees = 0;
    monJoueur -> nb_coups_fourres_joues = 0;
    monJoueur -> nb_200bornes_jouees = 0;
    monJoueur -> couronnement = 0;

    monJoueur -> carte_precedemment_jouee = 0;

    /* Handicaps */
    monJoueur -> est_creve = 0;
    monJoueur -> a_accident = 0;
    monJoueur -> en_panne_dessence = 0;
    monJoueur -> est_limite_par_vitesse = 0;
    monJoueur -> est_arrete = 1; //Par défaut, un joueur est arrêté (feu rouge).

    //Bottes
    monJoueur -> increvable = 0;
    monJoueur -> citerne = 0;
    monJoueur -> as_du_volant = 0;
    monJoueur -> prioritaire = 0;

    return monJoueur;
}

Tcarte* joueur_possede_carte(Tjoueur* monJoueur, int carte_type)
{
    Tcarte* carte = NULL;

    //Vérifier que ce type de carte existe
    if(cartes_verifier_validite(carte_type))
    {
        printf("Type existe\n");
        //Vérifier qu'au moins un exemplaire se trouve dans son jeu et le récupérer (adresse)
        carte = liste_rechercher_maillon(monJoueur -> deck, carte_type);
        return carte;
    }
    return NULL;
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


        printf("\nIl a parcouru %d bornes.\n", monJoueur -> cumul_bornes);
        printf("\nIl a joué %d cartes 'botte'.\n", monJoueur -> nb_bottes_jouees);
        printf("\nIl a joué %d coups fourres.\n", monJoueur -> nb_coups_fourres_joues);
        printf("\nIl a joué %d cartes '200 bornes'.\n", monJoueur -> nb_200bornes_jouees);
        if(monJoueur -> couronnement)
            printf("\nIl a effectué un couronnement.\n");
        else
            printf("\nIl n'a pas effectué de couronnement.\n");


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

int joueur_compter_les_points(Tjoueur* joueur, int cumul_bornes_autre_joueur)
{
    int points = 0;

    if(joueur != NULL)
    {
        /* Chaque joueur reçoit autant de points que le nombre de bornes qu'il a parcourues */
        points += (joueur -> cumul_bornes);

        /* Points par carte botte jouée */
        points += (joueur -> nb_bottes_jouees) * POINTS_PAR_BOTTE;

        /* Bonus additionnel si toutes les cartes botte ont été jouées par le même joueur */
        if((joueur -> nb_bottes_jouees) == NB_BOTTES)
            points += POINTS_TOUS_LES_BOTTES;

        /* Points par coup fourré */
        points += (joueur -> nb_coups_fourres_joues) * POINTS_PAR_COUP_FOURRE;

        /* Points si le joueur a effectué BORNES_MAX bornes */
        if((joueur -> cumul_bornes) == BORNES_MAX)
            points += POINTS_SI_BORNES_MAX_EFFECTUEES;

        /* Points si le joueur effectue un couronnement
        (la dernière carte qu'il joue fait monter son total à BORNES_MAX bornes). */
        if(joueur -> couronnement)
            points += POINTS_COURONNEMENT;

        /* Points si la manche est complétée sans que le joueur ait utilisé de carte 200 bornes */
        if((joueur -> cumul_bornes) == BORNES_MAX && (joueur -> nb_200bornes_jouees) == 0)
            points += POINTS_SI_AUCUNE_CARTE_200BORNES_JOUEE;

        /* Points si un capot est effectué
        (atteinte de BORNES_MAX par un joueur, alors que l'autre joueur est toujours à 0 borne) */
        if((joueur -> cumul_bornes) == BORNES_MAX && cumul_bornes_autre_joueur == 0)
            points += POINTS_SI_CAPOT;
    }
    return points;
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
