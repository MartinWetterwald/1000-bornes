/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION :                                  *
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

/* Cette fonction prend en entrée un deck de cartes et l'affiche de façon détaillée*/
void cartes_deck_afficher(Tdeck* deck)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    /* Comptabilisation des obstacles */
    nb_panne_essence = liste_compter_valeur(deck, PANNE_ESSENCE);
    nb_creve = liste_compter_valeur(deck, CREVE);
    nb_accident = liste_compter_valeur(deck, ACCIDENT);
    nb_limite_vitesse = liste_compter_valeur(deck, LIMITE_VITESSE);
    nb_stop = liste_compter_valeur(deck, STOP);
    nb_obstacles = nb_panne_essence + nb_creve + nb_accident + nb_limite_vitesse + nb_stop;

    /* Comptabilisation des parades */
    nb_essence = liste_compter_valeur(deck, ESSENCE);
    nb_roue_de_secours = liste_compter_valeur(deck, ROUE_DE_SECOURS);
    nb_reparations = liste_compter_valeur(deck, REPARATIONS);
    nb_fin_limite_vitesse = liste_compter_valeur(deck, FIN_LIMITE_VITESSE);
    nb_roulez = liste_compter_valeur(deck, ROULEZ);
    nb_parades = nb_essence + nb_roue_de_secours + nb_reparations + nb_fin_limite_vitesse + nb_roulez;

    /* Comptabilisation des bottes */
    nb_citerne = liste_compter_valeur(deck, CITERNE);
    nb_increvable = liste_compter_valeur(deck, INCREVABLE);
    nb_as_du_volant = liste_compter_valeur(deck, AS_DU_VOLANT);
    nb_prioritaire = liste_compter_valeur(deck, PRIORITAIRE);
    nb_bottes = nb_citerne + nb_increvable + nb_as_du_volant + nb_prioritaire;

    /* Comptabilisation des bornes */
    nb_bornes25 = liste_compter_valeur(deck, BORNES25);
    nb_bornes50 = liste_compter_valeur(deck, BORNES50);
    nb_bornes75 = liste_compter_valeur(deck, BORNES75);
    nb_bornes100 = liste_compter_valeur(deck, BORNES100);
    nb_bornes200 = liste_compter_valeur(deck, BORNES200);
    nb_bornes = nb_bornes25 + nb_bornes50 + nb_bornes75 + nb_bornes100 + nb_bornes200;


    /* Affichage des résultats */
    printf("Ce deck contient %d cartes :\n", deck -> taille);

    /* Affichage des obstacles */
    printf("- %d obstacles\n", nb_obstacles);
    if(nb_panne_essence >= 1)
        printf("  -> %d x 'panne d'essence'\n", nb_panne_essence);
    if(nb_creve >= 1)
        printf("  -> %d x 'crevé'\n", nb_creve);
    if(nb_accident >= 1)
        printf("  -> %d x 'accident'\n", nb_accident);
    if(nb_limite_vitesse >= 1)
        printf("  -> %d x 'limite de vitesse'\n", nb_limite_vitesse);
    if(nb_stop >= 1)
        printf("  -> %d x 'stop'\n", nb_stop);

    /* Affichage des parades */
    printf("\n- %d parades\n", nb_parades);
    if(nb_essence >= 1)
        printf("  -> %d x 'essence'\n", nb_essence);
    if(nb_roue_de_secours >= 1)
        printf("  -> %d x 'roue de secours'\n", nb_roue_de_secours);
    if(nb_reparations >= 1)
        printf("  -> %d x 'réparations'\n", nb_reparations);
    if(nb_fin_limite_vitesse >= 1)
        printf("  -> %d x 'fin de limite de vitesse'\n", nb_fin_limite_vitesse);
    if(nb_roulez >= 1)
        printf("  -> %d x 'roulez'\n", nb_roulez);

    /* Affichage des bottes */
    printf("\n- %d bottes\n", nb_bottes);
    if(nb_citerne >= 1)
        printf("  -> %d x 'citerne'\n", nb_citerne);
    if(nb_increvable >= 1)
        printf("  -> %d x 'increvable'\n", nb_increvable);
    if(nb_as_du_volant >= 1)
        printf("  -> %d x 'as du volant'\n", nb_as_du_volant);
    if(nb_prioritaire >= 1)
        printf("  -> %d x 'prioritaire'\n", nb_prioritaire);

    /* Affichage des bornes */
    printf("\n- %d bornes\n", nb_bornes);
    if(nb_bornes25 >= 1)
        printf("  -> %d x '25 bornes'\n", nb_bornes25);
    if(nb_bornes50 >= 1)
        printf("  -> %d x '50 bornes'\n", nb_bornes50);
    if(nb_bornes75 >= 1)
        printf("  -> %d x '75 bornes'\n", nb_bornes75);
    if(nb_bornes100 >= 1)
        printf("  -> %d x '100 bornes'\n", nb_bornes100);
    if(nb_bornes200 >= 1)
        printf("  -> %d x '200 bornes'\n", nb_bornes200);
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

void deck_detruire(Tptdeck* deck)
{
    liste_detruire(deck);
}
