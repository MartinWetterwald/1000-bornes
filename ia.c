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

    int nb_possible_panne_essence, nb_possible_creve, nb_possible_accident, nb_possible_limite_vitesse, nb_possible_stop;
    int nb_possible_essence, nb_possible_roue_de_secours, nb_possible_reparations, nb_possible_fin_limite_vitesse, nb_possible_roulez;
    int nb_possible_citerne, nb_possible_increvable, nb_possible_as_du_volant, nb_possible_prioritaire;
    int nb_possible_bornes25, nb_possible_bornes50, nb_possible_bornes75, nb_possible_bornes100, nb_possible_bornes200;

    int nb_possible_obstacles, nb_possible_parades, nb_possible_bottes, nb_possible_bornes;

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

    /* Comptabilisation du nombre de chaque type de cartes que peut jouer l'ordinateur*/
    cartes_deck_compter_sorte
    (
        coupsPossibles,
        &nb_possible_panne_essence, &nb_possible_creve, &nb_possible_accident, &nb_possible_limite_vitesse, &nb_possible_stop,
        &nb_possible_essence, &nb_possible_roue_de_secours, &nb_possible_reparations, &nb_possible_fin_limite_vitesse, &nb_possible_roulez,
        &nb_possible_citerne, &nb_possible_increvable, &nb_possible_as_du_volant, &nb_possible_prioritaire,
        &nb_possible_bornes25, &nb_possible_bornes50, &nb_possible_bornes75, &nb_possible_bornes100, &nb_possible_bornes200,
        &nb_possible_obstacles, &nb_possible_parades, &nb_possible_bottes, &nb_possible_bornes
    );




    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if( (coupsPossibles -> taille) == 0)
    {
        *choix_carte = PASSER_SON_TOUR;

        //Si l'IA course doit jeter une carte, elle va faire en sorte de ne pas jeter de carte borne.
        if ((ordinateur -> deck) -> taille == nb_bornes)
        {
            if(nb_bornes25 > 0)
                *choix_jeter = BORNES25;
            else if (nb_bornes50 > 0)
                *choix_jeter = BORNES50;
            else if (nb_bornes75 > 0)
                *choix_jeter = BORNES75;
            else if (nb_bornes100 > 0)
                *choix_jeter = BORNES100;
            else if (nb_bornes200 > 0)
                *choix_jeter = BORNES200;
        }
        else
        {
            *choix_jeter = carte_aleatoire(ordinateur -> deck);
            while(  *choix_jeter == BORNES25 || *choix_jeter == BORNES50 || *choix_jeter == BORNES75 ||
                    *choix_jeter == BORNES100 || *choix_jeter == BORNES200
            )
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
        }
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        *choix_jeter = -1;
        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.

        if (nb_possible_bornes > 0)
        {
            if(nb_possible_bornes200 > 0)
                *choix_carte = BORNES200;
            else if (nb_possible_bornes100 > 0)
                *choix_carte = BORNES100;
            else if (nb_possible_bornes75 > 0)
                *choix_carte = BORNES75;
            else if (nb_possible_bornes50 > 0)
                *choix_carte = BORNES50;
            else if (nb_possible_bornes25 > 0)
                *choix_carte = BORNES25;
        }

        else
            *choix_carte = carte_aleatoire(coupsPossibles);
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
