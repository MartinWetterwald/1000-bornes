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
#include "menu.h"

//Cette fonction initialise un joueur vide.
Tptjoueur joueur_init(int est_ordinateur, int difficulte, int num_joueur)
{
    char nom_ordinateur[NOM_TAILLE_MAX];
    Tptjoueur monJoueur = malloc(sizeof(Tjoueur));

    sprintf(nom_ordinateur, "Ordinateur %d", num_joueur);


    monJoueur -> est_ordinateur = est_ordinateur;

    if(est_ordinateur)
    {
        strcpy(monJoueur -> nom, nom_ordinateur);
        monJoueur -> difficulte_ordinateur = difficulte;
    }

    monJoueur -> deck = liste_init(); //On crée un deck vide et on l'attribut au joueur.

    monJoueur -> cumul_bornes = 0;
    monJoueur -> nb_bottes_jouees = 0;
    monJoueur -> nb_coups_fourres_joues = 0;
    monJoueur -> nb_200bornes_jouees = 0;
    monJoueur -> couronnement = 0;

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

Tptcarte joueur_possede_carte(Tptjoueur monJoueur, int carte_type)
{
    Tptcarte carte = NULL;

    //Vérifier que ce type de carte existe
    if(cartes_verifier_validite(carte_type))
    {
        //Vérifier qu'au moins un exemplaire se trouve dans son jeu et le récupérer (adresse)
        carte = liste_rechercher_maillon(monJoueur -> deck, carte_type);
        return carte;
    }
    return NULL;
}

void choisir_difficulte_ordinateur(int* jouer_contre_ordinateur, int* difficulte_ordinateur, int num_joueur)
{
    *difficulte_ordinateur = -1;
    while(*difficulte_ordinateur == -1)
    {
        menu_difficulte_ordinateur(difficulte_ordinateur, num_joueur);
        switch(*difficulte_ordinateur)
        {
            case ARCHI_DEBUTANT:
            break;

            case DEBUTANT:
            break;

            case COURSE:
            break;

            case AGRESSIF:
            break;

            case DEFENSIF:
            break;

            case EXPERT:
            break;

            case ARRETER_PARTIE:
                *jouer_contre_ordinateur = -1;
            break;

            default:
                printf("\nChoix incorrect. Recommencez.\n");
                *difficulte_ordinateur = -1;
        }
    }
}

//Cette fonction affiche toutes les infos sur un joueur (pour débugage uniquement).
void joueur_afficher(Tptjoueur monJoueur)
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
        printf("%d cartes en main :\n", (monJoueur -> deck) -> taille);
        cartes_deck_afficher(monJoueur -> deck);


        printf("\nIl a parcouru %d bornes.\n", monJoueur -> cumul_bornes);
        printf("Il a joué %d cartes 'botte'.\n", monJoueur -> nb_bottes_jouees);
        printf("Il a joué %d coups fourres.\n", monJoueur -> nb_coups_fourres_joues);
        printf("Il a joué %d cartes '200 bornes'.\n", monJoueur -> nb_200bornes_jouees);
        if(monJoueur -> couronnement)
            printf("Il a effectué un couronnement.\n");
        else
            printf("Il n'a pas effectué de couronnement.\n");

        printf("\nSes immunités (cartes 'botte' activées) : \n");
        if(monJoueur -> increvable)
            printf("- Il est increvable.\n");

        if(monJoueur -> citerne)
            printf("- C'est un camion citerne (il ne peut plus avoir de panne d'essence).\n");

        if(monJoueur -> as_du_volant)
            printf("- C'est un as du volant (il ne peut plus avoir d'accident).\n");

        if(monJoueur -> prioritaire)
            printf("- C'est un véhicule prioritaire (il ne peut pas être arrêté et sa vitesse ne peut pas être limitée).\n");





        printf("\n\nSes handicaps : \n");
        if(monJoueur -> est_creve)
            printf("- Il a les pneus crevés.\n");

        if(monJoueur -> a_accident)
            printf("- Il a un accident.\n");

        if(monJoueur -> en_panne_dessence)
            printf("- Il n'a plus d'essence.\n");

        if(monJoueur -> est_limite_par_vitesse)
            printf("- Sa vitesse est limitée.\n");

        if(monJoueur -> est_arrete)
            printf("- Il est à l'arrêt.\n");
    }
}

//Cette fonction affiche les infos utiles sur un joueur.
void joueur_afficher_infos_utiles(Tptjoueur monJoueur)
{
    //S'il y a quelque chose à faire
    if(monJoueur != NULL)
    {
        printf("\n'%s' a parcouru %d bornes.\n", monJoueur -> nom, monJoueur -> cumul_bornes);

        printf("\nLes immunités de '%s' (cartes 'botte' activées) sont : \n", monJoueur -> nom);
        if(monJoueur -> increvable)
            printf("- Il est increvable.\n");

        if(monJoueur -> citerne)
            printf("- C'est un camion citerne (il ne peut plus avoir de panne d'essence).\n");

        if(monJoueur -> as_du_volant)
            printf("- C'est un as du volant (il ne peut plus avoir d'accident).\n");

        if(monJoueur -> prioritaire)
            printf("- C'est un véhicule prioritaire (il ne peut pas être arrêté et sa vitesse ne peut pas être limitée).\n");


        printf("\n\nLes handicaps de '%s' sont : \n", monJoueur -> nom);
        if(monJoueur -> est_creve)
            printf("- Il a les pneus crevés.\n");

        if(monJoueur -> a_accident)
            printf("- Il a un accident.\n");

        if(monJoueur -> en_panne_dessence)
            printf("- Il n'a plus d'essence.\n");

        if(monJoueur -> est_limite_par_vitesse)
            printf("- Sa vitesse est limitée.\n");

        if(monJoueur -> est_arrete)
            printf("- Il est à l'arrêt.\n");
    }
}

/* Cette fonction comptabilise les points qu'a effectués un joueur */
int joueur_compter_les_points(Tptjoueur joueur, int cumul_bornes_autre_joueur)
{
    int points = 0;

    if(joueur != NULL)
    {
        /* Chaque joueur reçoit autant de points que le nombre de bornes qu'il a parcourues */
        points += (joueur -> cumul_bornes);
        printf("- %d points car %d bornes parcourues\n", joueur -> cumul_bornes, joueur -> cumul_bornes);

        /* Points par carte botte jouée */
        points += (joueur -> nb_bottes_jouees) * POINTS_PAR_BOTTE;
        if(joueur -> nb_bottes_jouees > 0)
            printf("- %d points supplémentaires par cartes 'botte' jouées (%d jouées) => soit un total de %d points !\n", POINTS_PAR_BOTTE, joueur -> nb_bottes_jouees, (joueur -> nb_bottes_jouees) * POINTS_PAR_BOTTE);

        /* Bonus additionnel si toutes les cartes botte ont été jouées par le même joueur */
        if((joueur -> nb_bottes_jouees) == NB_BOTTES)
        {
            points += POINTS_TOUS_LES_BOTTES;
            printf("- %d points supplémentaires car vous avez joué les %d cartes 'botte' du jeu !\n", POINTS_PAR_BOTTE, NB_BOTTES);
        }

        /* Points par coup fourré */
        points += (joueur -> nb_coups_fourres_joues) * POINTS_PAR_COUP_FOURRE;
        if(joueur -> nb_coups_fourres_joues > 0)
            printf("- %d points supplémentaires par coup fouré (%d effectués) => soit un total de %d points !\n", POINTS_PAR_COUP_FOURRE, joueur -> nb_coups_fourres_joues, (joueur -> nb_coups_fourres_joues) * POINTS_PAR_COUP_FOURRE);

        /* Points si le joueur a effectué BORNES_MAX bornes */
        if((joueur -> cumul_bornes) == BORNES_MAX)
        {
            points += POINTS_SI_BORNES_MAX_EFFECTUEES;
            printf("- %d points supplémentaires pour avoir parcouru le maximum de %d bornes !\n", POINTS_SI_BORNES_MAX_EFFECTUEES, BORNES_MAX);
        }

        /* Points si le joueur effectue un couronnement
        (la dernière carte qu'il joue fait monter son total à BORNES_MAX bornes). */
        if(joueur -> couronnement)
        {
            points += POINTS_COURONNEMENT;
            printf("- %d points supplémentaires pour avoir effectué un couronnement (atteindre %d bornes alors qu'on ne peut plus piocher de cartes) !\n", POINTS_COURONNEMENT, BORNES_MAX);
        }

        /* Points si la manche est complétée sans que le joueur ait utilisé de carte 200 bornes */
        if((joueur -> cumul_bornes) == BORNES_MAX && (joueur -> nb_200bornes_jouees) == 0)
        {
            points += POINTS_SI_AUCUNE_CARTE_200BORNES_JOUEE;
            printf("- %d points supplémentaires pour avoir parcouru %d bornes sans avoir joué une seule carte '200 bornes' !\n", POINTS_SI_AUCUNE_CARTE_200BORNES_JOUEE, BORNES_MAX);
        }

        /* Points si un capot est effectué
        (atteinte de BORNES_MAX par un joueur, alors que l'autre joueur est toujours à 0 borne) */
        if((joueur -> cumul_bornes) == BORNES_MAX && cumul_bornes_autre_joueur == 0)
        {
            points += POINTS_SI_CAPOT;
            printf("- %d points supplémentaires pour avoir effectué un capot (parcourir un total de %d bornes alors que l'autre joueur n'a pas du tout avancé) !\n", POINTS_SI_CAPOT, BORNES_MAX);
        }
        printf("TOTAL : %d points.\n", points);
    }
    return points;
}

//Cette fonction libère la mémoire attribuée pour le stockage du joueur.
void joueur_detruire(Tptjoueur joueur)
{
    //Si on a quelque chose à faire
    if(joueur != NULL)
    {
        deck_detruire(joueur -> deck); //On fournit l'adresse du deck qui se trouve dans ((pointeur de joueur) pointé deck)
        free(joueur);
    }
}
