/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : cartes.c               *
* DESCRIPTION : Ceci correspond à la couche      *
* « carte » du programme. Toutes les fonctions   *
* définies ici permettent d'effectuer un certain *
* nombre d'opérations sur des cartes et des      *
* decks de cartes.                               *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "divers.h"
#include "cartes.h"

//Ajout d'un certain type de carte dans un deck
void cartes_deck_add(Tdeck* deck, int carte_type, int carte_nb)
{
    int i;
    for(i = 1; i <= carte_nb; i++)
        liste_maillon_inserer_tete(deck, carte_type);
}

//Initialisation du deck du jeu + mélangeage (106 cartes).
void cartes_deck_init(Tdeck* deck)
{
    /* Insertion des obstacles */
    cartes_deck_add(deck, PANNE_ESSENCE,        NB_PANNE_ESSENCE);
    cartes_deck_add(deck, CREVE,                NB_CREVE);
    cartes_deck_add(deck, ACCIDENT,             NB_ACCIDENT);
    cartes_deck_add(deck, LIMITE_VITESSE,       NB_LIMITE_VITESSE);
    cartes_deck_add(deck, STOP,                 NB_STOP);


    /* Insertion des parades */
    cartes_deck_add(deck, ESSENCE,              NB_ESSENCE);
    cartes_deck_add(deck, ROUE_DE_SECOURS,      NB_ROUE_DE_SECOURS);
    cartes_deck_add(deck, REPARATIONS,          NB_REPARATIONS);
    cartes_deck_add(deck, FIN_LIMITE_VITESSE,   NB_FIN_LIMITE_VITESSE);
    cartes_deck_add(deck, ROULEZ,               NB_ROULEZ);


    /* Insertion des bottes */
    cartes_deck_add(deck, CITERNE,              NB_CITERNE);
    cartes_deck_add(deck, INCREVABLE,           NB_INCREVABLE);
    cartes_deck_add(deck, AS_DU_VOLANT,         NB_AS_DU_VOLANT);
    cartes_deck_add(deck, PRIORITAIRE,          NB_PRIORITAIRE);


    /* Insertion des bornes */
    cartes_deck_add(deck, BORNES25, NB_BORNES25);
    cartes_deck_add(deck, BORNES50, NB_BORNES50);
    cartes_deck_add(deck, BORNES75, NB_BORNES75);
    cartes_deck_add(deck, BORNES100, NB_BORNES100);
    cartes_deck_add(deck, BORNES200, NB_BORNES200);

    /* On mélange les cartes ! */
    liste_melanger(deck, MELANGER_MIN, MELANGER_MAX);
}

/* Cette fonction compte combien un deck contient chaque type de cartes */
void cartes_deck_compter_sorte
(
    Tdeck* deck,
    int* nb_panne_essence, int* nb_creve, int* nb_accident, int* nb_limite_vitesse, int* nb_stop,
    int* nb_essence, int* nb_roue_de_secours, int* nb_reparations, int* nb_fin_limite_vitesse, int* nb_roulez,
    int* nb_citerne, int* nb_increvable, int* nb_as_du_volant, int* nb_prioritaire,
    int* nb_bornes25, int* nb_bornes50, int* nb_bornes75, int* nb_bornes100, int* nb_bornes200,
    int* nb_obstacles, int* nb_parades, int* nb_bottes, int* nb_bornes
)
{
    if(deck != NULL)
    {
        /* Comptabilisation des obstacles */
        *nb_panne_essence = liste_compter_valeur(deck, PANNE_ESSENCE);
        *nb_creve = liste_compter_valeur(deck, CREVE);
        *nb_accident = liste_compter_valeur(deck, ACCIDENT);
        *nb_limite_vitesse = liste_compter_valeur(deck, LIMITE_VITESSE);
        *nb_stop = liste_compter_valeur(deck, STOP);
        *nb_obstacles = *nb_panne_essence + *nb_creve + *nb_accident + *nb_limite_vitesse + *nb_stop;

        /* Comptabilisation des parades */
        *nb_essence = liste_compter_valeur(deck, ESSENCE);
        *nb_roue_de_secours = liste_compter_valeur(deck, ROUE_DE_SECOURS);
        *nb_reparations = liste_compter_valeur(deck, REPARATIONS);
        *nb_fin_limite_vitesse = liste_compter_valeur(deck, FIN_LIMITE_VITESSE);
        *nb_roulez = liste_compter_valeur(deck, ROULEZ);
        *nb_parades = *nb_essence + *nb_roue_de_secours + *nb_reparations + *nb_fin_limite_vitesse + *nb_roulez;

        /* Comptabilisation des bottes */
        *nb_citerne = liste_compter_valeur(deck, CITERNE);
        *nb_increvable = liste_compter_valeur(deck, INCREVABLE);
        *nb_as_du_volant = liste_compter_valeur(deck, AS_DU_VOLANT);
        *nb_prioritaire = liste_compter_valeur(deck, PRIORITAIRE);
        *nb_bottes = *nb_citerne + *nb_increvable + *nb_as_du_volant + *nb_prioritaire;

        /* Comptabilisation des bornes */
        *nb_bornes25 = liste_compter_valeur(deck, BORNES25);
        *nb_bornes50 = liste_compter_valeur(deck, BORNES50);
        *nb_bornes75 = liste_compter_valeur(deck, BORNES75);
        *nb_bornes100 = liste_compter_valeur(deck, BORNES100);
        *nb_bornes200 = liste_compter_valeur(deck, BORNES200);
        *nb_bornes = *nb_bornes25 + *nb_bornes50 + *nb_bornes75 + *nb_bornes100 + *nb_bornes200;
    }
}

/* Cette fonction prend en entrée un deck de cartes et l'affiche de façon détaillée*/
void cartes_deck_afficher(Tdeck* deck)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    if(deck != NULL)
    {

        /* Comptabilisation du nombre de chaque type de cartes */
        cartes_deck_compter_sorte
        (
            deck,
            &nb_panne_essence, &nb_creve, &nb_accident, &nb_limite_vitesse, &nb_stop,
            &nb_essence, &nb_roue_de_secours, &nb_reparations, &nb_fin_limite_vitesse, &nb_roulez,
            &nb_citerne, &nb_increvable, &nb_as_du_volant, &nb_prioritaire,
            &nb_bornes25, &nb_bornes50, &nb_bornes75, &nb_bornes100, &nb_bornes200,
            &nb_obstacles, &nb_parades, &nb_bottes, &nb_bornes
        );


        /* Affichage des résultats */


        /* Affichage des obstacles */
        printf("- %d obstacles\n", nb_obstacles);
        if(nb_panne_essence >= 1)
            printf("  -> %d x 'panne d'essence' (code %d)\n", nb_panne_essence, PANNE_ESSENCE);
        if(nb_creve >= 1)
            printf("  -> %d x 'crevé' (code %d)\n", nb_creve, CREVE);
        if(nb_accident >= 1)
            printf("  -> %d x 'accident' (code %d)\n", nb_accident, ACCIDENT);
        if(nb_limite_vitesse >= 1)
            printf("  -> %d x 'limite de vitesse' (code %d)\n", nb_limite_vitesse, LIMITE_VITESSE);
        if(nb_stop >= 1)
            printf("  -> %d x 'stop' (code %d)\n", nb_stop, STOP);

        /* Affichage des parades */
        printf("\n- %d parades\n", nb_parades);
        if(nb_essence >= 1)
            printf("  -> %d x 'essence' (code %d)\n", nb_essence, ESSENCE);
        if(nb_roue_de_secours >= 1)
            printf("  -> %d x 'roue de secours' (code %d)\n", nb_roue_de_secours, ROUE_DE_SECOURS);
        if(nb_reparations >= 1)
            printf("  -> %d x 'réparations' (code %d)\n", nb_reparations, REPARATIONS);
        if(nb_fin_limite_vitesse >= 1)
            printf("  -> %d x 'fin de limite de vitesse' (code %d)\n", nb_fin_limite_vitesse, FIN_LIMITE_VITESSE);
        if(nb_roulez >= 1)
            printf("  -> %d x 'roulez' (code %d)\n", nb_roulez, ROULEZ);

        /* Affichage des bottes */
        printf("\n- %d bottes\n", nb_bottes);
        if(nb_citerne >= 1)
            printf("  -> %d x 'citerne' (code %d)\n", nb_citerne, CITERNE);
        if(nb_increvable >= 1)
            printf("  -> %d x 'increvable' (code %d)\n", nb_increvable, INCREVABLE);
        if(nb_as_du_volant >= 1)
            printf("  -> %d x 'as du volant' (code %d)\n", nb_as_du_volant, AS_DU_VOLANT);
        if(nb_prioritaire >= 1)
            printf("  -> %d x 'prioritaire' (code %d)\n", nb_prioritaire, PRIORITAIRE);

        /* Affichage des bornes */
        printf("\n- %d bornes\n", nb_bornes);
        if(nb_bornes25 >= 1)
            printf("  -> %d x '25 bornes' (code %d)\n", nb_bornes25, BORNES25);
        if(nb_bornes50 >= 1)
            printf("  -> %d x '50 bornes' (code %d)\n", nb_bornes50, BORNES50);
        if(nb_bornes75 >= 1)
            printf("  -> %d x '75 bornes' (code %d)\n", nb_bornes75, BORNES75);
        if(nb_bornes100 >= 1)
            printf("  -> %d x '100 bornes' (code %d)\n", nb_bornes100, BORNES100);
        if(nb_bornes200 >= 1)
            printf("  -> %d x '200 bornes' (code %d)\n", nb_bornes200, BORNES200);
    }
}

/* Cette fonction change une carte de deck :
elle ajoute la carte au deck cible et l'enlève du deck source */
Tcarte* cartes_changer_deck(Tdeck* deck_source, Tcarte* carte_source, Tdeck* deck_cible)
{
    Tcarte* nouvelle_carte = NULL;
    //S'il y a quelque chose à faire
    if(deck_source != NULL && deck_source -> premier != NULL && deck_cible != NULL && carte_source != NULL)
    {
        nouvelle_carte = liste_maillon_inserer_tete(deck_cible, carte_source -> valeur);
        liste_maillon_supprimer(deck_source, carte_source);
    }

    return nouvelle_carte;
}

/* Cette fonction affiche le nom d'une carte à partir de son type numérique */
void cartes_type2francais(int val)
{
    switch(val)
    {
        //Obstacles
        case PANNE_ESSENCE:
            printf("Panne d'essence");
        break;

        case CREVE:
            printf("Crevé");
        break;

        case ACCIDENT:
            printf("Accident");
        break;

        case LIMITE_VITESSE:
            printf("Limite de vitesse");
        break;

        case STOP:
            printf("Stop (feu rouge)");
        break;

        //Parades
        case ESSENCE:
            printf("Essence");
        break;

        case ROUE_DE_SECOURS:
            printf("Roue de secours");
        break;

        case REPARATIONS:
            printf("Réparations");
        break;

        case FIN_LIMITE_VITESSE:
            printf("Fin de limitation de vitesse");
        break;

        case ROULEZ:
            printf("Roulez (feu vert)");
        break;

        //Bottes
        case CITERNE:
            printf("Citerne");
        break;

        case INCREVABLE:
            printf("Increvable");
        break;

        case AS_DU_VOLANT:
            printf("As du volant");
        break;

        case PRIORITAIRE:
            printf("Véhicule prioritaire");
        break;

        //Bornes
        case BORNES25:
            printf("25 bornes");
        break;

        case BORNES50:
            printf("50 bornes");
        break;

        case BORNES75:
            printf("75 bornes");
        break;

        case BORNES100:
            printf("100 bornes");
        break;

        case BORNES200:
            printf("200 bornes");
        break;

        default:
            printf("Il n'y a plus de carte dans le deck !");
    }
}

/* Cette fonction distribue les cartes en début de partie */
void cartes_distribuer(Tdeck* deck, Tdeck* deck_joueur1, Tdeck* deck_joueur2, int nb)
{
    int i;
    //Si on a quelque chose à faire
    if(deck != NULL && deck -> premier != NULL && deck_joueur1 != NULL && deck_joueur2 != NULL)
    {
        /* Distribution des cartes pour le joueur1 */
        for(i = 1; i <= nb; i++)
            cartes_changer_deck(deck, deck -> premier, deck_joueur1);

        /* Distribution des cartes pour le joueur2 */
        for(i = 1; i <= nb; i++)
            cartes_changer_deck(deck, deck -> premier, deck_joueur2);
    }
}

/* Vérifie si une carte existe */
int cartes_verifier_validite(int carte)
{
    if(
        (carte >= PANNE_ESSENCE && carte <= STOP) ||
        (carte >= ESSENCE && carte <= ROULEZ) ||
        (carte >= CITERNE && carte <= PRIORITAIRE) ||
        (carte == BORNES25 || carte == BORNES50 || carte == BORNES75 || carte == BORNES100 || carte == BORNES200)
    )
        return 1;
    else
        return 0;
}

int carte_aleatoire(Tdeck* deck)
{
    return liste_maillon_valeur_aleatoire(deck);
}

void deck_detruire(Tptdeck* deck)
{
    liste_detruire(deck);
}
