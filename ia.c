/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : ia.c                   *
* DESCRIPTION : Fonctions gérant les différentes *
* intelligences artificielles.                   *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "divers.h"
#include "ia.h"

/* Chacune des fonctions IA doit faire des calculs et à la fin choisir une carte et si l'IA passe son tour ou non.
Si l'IA veut JOUER une carte, il faut mettre le numéro de la carte dans choix_carte, et mettre choix_jeter à -1.
Si l'IA veut JETER une carte, il faut mettre la valeur PASSER_SON_TOUR dans choix_carte, et il faut mettre
le numéro de la carte à jeter dans choix_jeter.
*/

void ia_debutant(Tjoueur* ordinateur, Tjoueur* humain, int* choix_carte, int* choix_jeter)
{
    Tdeck* coupsPossibles = lister_coups_possibles(&ordinateur, &humain);

    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;
        *choix_jeter = carte_aleatoire(ordinateur -> deck);
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;
        *choix_carte = carte_aleatoire(coupsPossibles);
    }
}

void ia_course(Tjoueur* ordinateur, Tjoueur* humain, int* choix_carte, int* choix_jeter)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    Tdeck* coupsPossibles = lister_coups_possibles(&ordinateur, &humain);

    /* Comptabilisation du nombre de chaque type de cartes que possède l'ordinateur */
    cartes_deck_compter_sorte
    (
        ordinateur -> deck,
        &nb_panne_essence, &nb_creve, &nb_accident, &nb_limite_vitesse, &nb_stop,
        &nb_essence, &nb_roue_de_secours, &nb_reparations, &nb_fin_limite_vitesse, &nb_roulez,
        &nb_citerne, &nb_increvable, &nb_as_du_volant, &nb_prioritaire,
        &nb_bornes25, &nb_bornes50, &nb_bornes75, &nb_bornes100, &nb_bornes200,
        &nb_obstacles, &nb_parades, &nb_bottes, &nb_bornes
    );




    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;

        //Si l'IA course doit jeter une carte, elle va faire en sorte de ne pas jeter de carte borne.

        //*choix_jeter = ????;
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;

        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.
        //*choix_jouer = ????;
    }
}

void ia_agressif(Tjoueur* ordinateur, Tjoueur* humain, int* choix_carte, int* choix_jeter)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    Tdeck* coupsPossibles = lister_coups_possibles(&ordinateur, &humain);

    /* Comptabilisation du nombre de chaque type de cartes que possède l'ordinateur */
    cartes_deck_compter_sorte
    (
        ordinateur -> deck,
        &nb_panne_essence, &nb_creve, &nb_accident, &nb_limite_vitesse, &nb_stop,
        &nb_essence, &nb_roue_de_secours, &nb_reparations, &nb_fin_limite_vitesse, &nb_roulez,
        &nb_citerne, &nb_increvable, &nb_as_du_volant, &nb_prioritaire,
        &nb_bornes25, &nb_bornes50, &nb_bornes75, &nb_bornes100, &nb_bornes200,
        &nb_obstacles, &nb_parades, &nb_bottes, &nb_bornes
    );




    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;


        //Faire des calculs pour choisir la carte à jeter parmi les cartes de l'ordinateur.
        //Ses cartes se trouvent dans la liste chainée 'ordinateur -> deck'.
        //*choix_jeter = ????;
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;

        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.
        //*choix_jouer = ????;
    }
}

void ia_defensif(Tjoueur* ordinateur, Tjoueur* humain, int* choix_carte, int* choix_jeter)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    Tdeck* coupsPossibles = lister_coups_possibles(&ordinateur, &humain);

    /* Comptabilisation du nombre de chaque type de cartes que possède l'ordinateur */
    cartes_deck_compter_sorte
    (
        ordinateur -> deck,
        &nb_panne_essence, &nb_creve, &nb_accident, &nb_limite_vitesse, &nb_stop,
        &nb_essence, &nb_roue_de_secours, &nb_reparations, &nb_fin_limite_vitesse, &nb_roulez,
        &nb_citerne, &nb_increvable, &nb_as_du_volant, &nb_prioritaire,
        &nb_bornes25, &nb_bornes50, &nb_bornes75, &nb_bornes100, &nb_bornes200,
        &nb_obstacles, &nb_parades, &nb_bottes, &nb_bornes
    );




    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;


        //Faire des calculs pour choisir la carte à jeter parmi les cartes de l'ordinateur.
        //Ses cartes se trouvent dans la liste chainée 'ordinateur -> deck'.
        //*choix_jeter = ????;
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;

        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.
        //*choix_jouer = ????;
    }
}

void ia_expert(Tjoueur* ordinateur, Tjoueur* humain, int* choix_carte, int* choix_jeter)
{
    int nb_panne_essence, nb_creve, nb_accident, nb_limite_vitesse, nb_stop;
    int nb_essence, nb_roue_de_secours, nb_reparations, nb_fin_limite_vitesse, nb_roulez;
    int nb_citerne, nb_increvable, nb_as_du_volant, nb_prioritaire;
    int nb_bornes25, nb_bornes50, nb_bornes75, nb_bornes100, nb_bornes200;

    int nb_obstacles, nb_parades, nb_bottes, nb_bornes;

    Tdeck* coupsPossibles = lister_coups_possibles(&ordinateur, &humain);

    /* Comptabilisation du nombre de chaque type de cartes que possède l'ordinateur */
    cartes_deck_compter_sorte
    (
        ordinateur -> deck,
        &nb_panne_essence, &nb_creve, &nb_accident, &nb_limite_vitesse, &nb_stop,
        &nb_essence, &nb_roue_de_secours, &nb_reparations, &nb_fin_limite_vitesse, &nb_roulez,
        &nb_citerne, &nb_increvable, &nb_as_du_volant, &nb_prioritaire,
        &nb_bornes25, &nb_bornes50, &nb_bornes75, &nb_bornes100, &nb_bornes200,
        &nb_obstacles, &nb_parades, &nb_bottes, &nb_bornes
    );




    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;


        //Faire des calculs pour choisir la carte à jeter parmi les cartes de l'ordinateur.
        //Ses cartes se trouvent dans la liste chainée 'ordinateur -> deck'.
        //*choix_jeter = ????;
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;

        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.
        //*choix_jouer = ????;
    }
}
