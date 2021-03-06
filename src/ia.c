/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : ia.c                         *
* DESCRIPTION : Fonctions gérant les différentes       *
* intelligences artificielles.                         *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
* Code source : http://github.com/djfox/1000-bornes    *
*******************************************************/

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

void ia_archi_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
{
    char raison_refus[TAILLE_MAX_REFUS], raison_refus2[TAILLE_MAX_REFUS];

    if(DEBUG_IA) printf("[IA ACHI-DÉBUTANT] Je sélectionne dans mon jeu une carte au hasard.\n");
    *choix_carte = carte_aleatoire(ordinateur -> deck);

    //Si l'ordinateur a le droit de jouer la carte tirée, on la joue.
    if(coup_autorise(raison_refus, raison_refus2, ordinateur, humain, *choix_carte))
    {
        if(DEBUG_IA) printf("[IA ARCHI-DÉBUTANT] Il se trouve que j'ai le droit de jouer cette carte. Je la joue !\n");
        *choix_jeter = -1;
    }

    //Si l'ordinateur n'a pas le droit de jouer la carte tirée, on la jette.
    else
    {
        if(DEBUG_IA) printf("[IA ARCHI-DÉBUTANT] Je n'ai pas le droit de jouer la carte que j'ai choisie. Ça n'est pas grave, je vais la jeter !\n");
        *choix_jeter = *choix_carte;
        *choix_carte = PASSER_SON_TOUR;
    }
}

void ia_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
{
    Tptdeck coupsPossibles = lister_coups_possibles(ordinateur, humain);

    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if(coupsPossibles -> taille == 0)
    {
        if(DEBUG_IA) printf("[IA DÉBUTANT] Je suis obligé de passer mon tour car je ne peux rien jouer.\n");
        if(DEBUG_IA) printf("[IA DÉBUTANT] Je vais choisir aléatoirement une carte à jeter.\n");
        *choix_carte = PASSER_SON_TOUR;
        *choix_jeter = carte_aleatoire(ordinateur -> deck);
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        if(DEBUG_IA) printf("[IA DÉBUTANT] J'ai la possibilité de jouer, je vais donc saisir cette opportunité !\n");
        if(DEBUG_IA) printf("[IA DÉBUTANT] Je vais choisir aléatoirement une carte à jouer parmi les coups autorisés.\n");
        *choix_jeter = -1;
        *choix_carte = carte_aleatoire(coupsPossibles);
    }
}

void ia_course(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
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

    Tptdeck coupsPossibles = lister_coups_possibles(ordinateur, humain);

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
    if(coupsPossibles -> taille == 0)
    {
        if(DEBUG_IA) printf("[IA COURSE] Je suis obligé de passer mon tour car je ne peux rien jouer.\n");
        *choix_carte = PASSER_SON_TOUR;

        //Si l'IA course est obligée de jeter une carte borne car elle n'a que ça dans son jeu, on va établir une priorité.
        //On préfèrera jeter une carte 25 bornes qu'une 50 bornes, une 50 bornes qu'une 75 bornes, etc.
        if(ordinateur -> deck -> taille == nb_bornes)
        {
            if(DEBUG_IA) printf("[IA COURSE] Je suis obligé de jeter une carte 'borne' car je n'ai que ce type de cartes dans ma main.\n");
            if(nb_bornes25 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je jette une carte '25 bornes', c'est la carte borne la moins avantageuse.\n");
                *choix_jeter = BORNES25;
            }
            else if (nb_bornes50 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '25 bornes', je jette une carte 50 bornes, la deuxième la moins avantageuse.\n");
                *choix_jeter = BORNES50;
            }
            else if (nb_bornes75 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '25 bornes' ni '50 bornes', je jette une carte 75 bornes, la troisième la moins avantageuse.\n");
                *choix_jeter = BORNES75;
            }
            else if (nb_bornes100 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '25 bornes' ni '50 bornes' ni '75 bornes', je jette une carte 100 bornes, la quatrième la moins avantageuse.\n");
                *choix_jeter = BORNES100;
            }
            else if (nb_bornes200 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '25 bornes' ni '50 bornes' ni '75 bornes' ni '100 bornes', c'est avec regret que je jette une carte 200 bornes, la plus avantageuse de toutes.\n");
                *choix_jeter = BORNES200;
            }
        }
        //Si l'IA course n'est pas obligée de jeter une carte 'borne', elle va jeter un autre type de carte.
        else
        {
            if(DEBUG_IA) printf("[IA COURSE] Je ne suis pas obligé de jeter une carte 'borne', je vais donc en jeter une autre, peu importe laquelle !\n");
            *choix_jeter = carte_aleatoire(ordinateur -> deck);
            while(*choix_jeter >= BORNES25 && *choix_jeter <= BORNES200)
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
        }
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        if(DEBUG_IA) printf("[IA COURSE] Je peux jouer une carte. Je vais bien évidemment saisir cette opportunité !\n");
        *choix_jeter = -1;
        //Faire des calculs pour choisir la carte à jouer parmi les cartes de la liste chainée 'coupsPossibles'.

        //Si on peut jouer au moins une carte 'borne', on va la jouer, mais on va préférer jouer une carte 200 bornes
        //qu'une 100 bornes, une 100 bornes qu'une 75, etc.
        if(nb_possible_bornes > 0)
        {
            if(DEBUG_IA) printf("[IA COURSE] Je peux jouer une carte 'borne' ! :D\n");
            if(nb_possible_bornes200 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je joue une carte '200 bornes' car c'est la plus avantageuse !\n");
                *choix_carte = BORNES200;
            }
            else if (nb_possible_bornes100 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '200 bornes', je vais donc jouer une carte '100 bornes' car c'est la deuxième la plus avantageuse.\n");
                *choix_carte = BORNES100;
            }
            else if (nb_possible_bornes75 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '200 bornes' ni '100 bornes', je vais donc jouer une carte '75 bornes' car c'est la troisième la plus avantageuse.\n");
                *choix_carte = BORNES75;
            }
            else if (nb_possible_bornes50 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '200 bornes' ni '100 bornes' ni '75 bornes', je vais donc jouer une carte '50 bornes' car c'est la quatrième la plus avantageuse.\n");
                *choix_carte = BORNES50;
            }
            else if (nb_possible_bornes25 > 0)
            {
                if(DEBUG_IA) printf("[IA COURSE] Je n'ai pas de carte '200 bornes' ni '100 bornes' ni '75 bornes' ni '50 bornes', c'est donc avec regret que je vais jouer une carte '25 bornes', la moins avantageuse.\n");
                *choix_carte = BORNES25;
            }
        }
        //On ne peut pas jouer de carte borne, on en choisit donc une au hasard.
        else
        {
            if(DEBUG_IA) printf("[IA COURSE] Je ne peux pas jouer de carte 'borne'. Je vais donc jouer n'importe quoi...\n");
            *choix_carte = carte_aleatoire(coupsPossibles);
        }
    }
}

void ia_agressif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
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

    Tptdeck coupsPossibles = lister_coups_possibles(ordinateur, humain);

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

    if(DEBUG_IA) cartes_deck_afficher(coupsPossibles);

    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if(coupsPossibles -> taille == 0)
    {
        *choix_carte = PASSER_SON_TOUR;
        if(DEBUG_IA) printf("[IA AGRESSIF] Je suis obligé de passer mon tour car je ne peux rien jouer.\n");

        //Si l'IA est obligée de jeter une carte obstacle car elle n'a que des cartes obstacles dans sa main, on établit une priorité.
        //L'obstacle le moins intéressant est la limite de vitesse, suivi du feu rouge (stop). Les autres obstocles sont équivalents et sont à jeter en dernier recours.
        if (ordinateur -> deck -> taille == nb_obstacles)
        {
            if(DEBUG_IA) printf("[IA AGRESSIF] Je n'ai que des cartes obstacle dans ma main, je suis obligé d'en jeter une. :'(\n");
            if(nb_limite_vitesse > 0)
            {
                if(DEBUG_IA) printf("[IA AGRESSIF] Je me débarasse de la carte 'limite de vitesse' car c'est l'obstacle le moins intéressant.\n");
                *choix_jeter = LIMITE_VITESSE;
            }
            else if(nb_stop > 0)
            {
                if(DEBUG_IA) printf("[IA AGRESSIF] Je me débarrasse de la carte 'stop', car je n'ai pas de carte 'limite de vitesse à jeter' et c'est donc le deuxième obstacle le moins intéressant.\n");
                *choix_jeter = STOP;
            }
            else
            {
                if(DEBUG_IA) printf("[IA AGRESSIF] Je n'ai ni de 'limite de vitesse', ni de 'stop' à jeter. Je suis contraint de jeter une super carte obstacle de la mort. :'(\n");
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
            }
        }
        //Si l'IA agressif doit jeter une carte et qu'elle peut en jeter une autre qu'un obstacle,
        //elle va le faire et ne pas choisir l'obstacle.
        else
        {
            if(DEBUG_IA) printf("[IA AGRESSIF] Je ne suis pas obligé de jeter une carte obstacle. Je vais donc en jeter une autre, peu importe laquelle !\n");
            *choix_jeter = carte_aleatoire(ordinateur -> deck);
            while(*choix_jeter >= PANNE_ESSENCE && *choix_jeter <= STOP)
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
        }
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        if(DEBUG_IA) printf("[IA AGRESSIF] Je peux jouer une carte ! Je vais donc bien évidemment saisir cette opportunité.\n");
        *choix_jeter = -1;
        //S'il peut jouer au moins un obstacle, on le force à en jouer un. Il faut choisir lequel il va jouer.
        if (nb_possible_obstacles > 0)
        {
            if(DEBUG_IA) printf("[IA AGRESSIF] Ah, au moins une carte obstacle se trouve dans les cartes que j'ai le droit de jouer. Tant mieux, je vais pouvoir jouer un obstacle !\n");
            //Si les seules cartes 'obstacle' qu'il peut jouer sont des stops et/ou des limites de vitesses
            if(nb_possible_limite_vitesse + nb_possible_stop == nb_possible_obstacles)
            {
                if(DEBUG_IA) printf("[IA AGRESSIF] Merde, je vais être obligé de choisir entre les deux obstacles les plus pourris. Si je peux, je jouerai le stop, sinon la limite de vitesse :'(\n");

                //S'il est obligé de jouer une carte 'limite de vitesse', il la joue.
                if(nb_possible_limite_vitesse > 0 && nb_possible_limite_vitesse == nb_possible_obstacles)
                {
                    if(DEBUG_IA) printf("[IA AGRESSIF] Je suis obligé de jouer l'obstacle le plus pourri : 'limite de vitesse'. :'(\n");
                    *choix_carte = LIMITE_VITESSE;
                }
                //S'il n'est pas obligé de jouer une carte 'limite de vitesse' mais qu'il n'a que le choix entre 'limite de vitesse' et 'stop', il va préférer 'stop'.
                else
                {
                    if(DEBUG_IA) printf("[IA AGRESSIF] Je ne suis pas obligé de jouer 'limite de vitesse', je vais jouer 'stop' le deuxième obstacle le plus pourri. :'(\n");
                    *choix_carte = STOP;
                }

            }
            //S'il n'est pas contraint de jouer une carte stop ou une carte limite de vitesse, on lui fait jouer un autre obstacle que ces deux-là !
            else
            {
                if(DEBUG_IA) printf("[IA AGRESSIF] Cool ! Je vais pouvoir jouer un obstacle de la mort ! :D\n");
                *choix_carte = carte_aleatoire(coupsPossibles);
                while(*choix_carte != PANNE_ESSENCE && *choix_carte != CREVE && *choix_carte != ACCIDENT)
                    *choix_carte = carte_aleatoire(coupsPossibles);
            }
        }
        //S'il ne peut jouer aucun obstacle, on le fait choisir une carte de façon aléatoire, parmi celles qu'il peut jouer
        else
        {
            if(DEBUG_IA) printf("[IA AGRESSIF] Je ne peux jouer aucun obstacle. Je vais donc jouer n'importe quoi. :'(\n");
            *choix_carte = carte_aleatoire(coupsPossibles);
        }
    }
}

void ia_defensif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
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

    Tptdeck coupsPossibles = lister_coups_possibles(ordinateur, humain);

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
    if(DEBUG_IA) cartes_deck_afficher(coupsPossibles);

    //Si l'ordinateur ne peut pas jouer de carte, il faut lui en faire jeter une.
    if(coupsPossibles -> taille == 0)
    {
        *choix_carte = PASSER_SON_TOUR;
        if(DEBUG_IA) printf("[IA DÉFENSIF] Je suis obligé de passer mon tour car je ne peux rien jouer.\n");

        //Si l'IA est obligée de jeter une carte 'botte' ou 'parade', elle le fait.
        //Le moins intéressant des deux est la parade. C'est donc la première chose à balancer.
        if (ordinateur -> deck -> taille == nb_bottes + nb_parades)
        {
            if(DEBUG_IA) printf("[IA DÉFENSIF] Je n'ai que des cartes bottes/parades confondues dans ma main, je suis obligé d'en jeter une. :'(\n");
            if(nb_parades > 0)
            {
                if(DEBUG_IA) printf("[IA DÉFENSIF] Je me débarasse d'une parade, car c'est bien moins intéressant qu'une carte 'botte'.\n");
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
                while(*choix_jeter < ESSENCE || *choix_jeter > ROULEZ)
                    *choix_jeter = carte_aleatoire(ordinateur -> deck);
            }
            else
            {
                //Ce cas n'arrivera jamais, car une carte botte est toujours jouable. On n'aura donc jamais à en jeter. =)
                if(DEBUG_IA) printf("[IA DÉFENSIF] Je n'ai pas de carte 'parade' à balancer. Je suis contraint de jeter une super carte 'BOTTE' de la mort. :'(\n");
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
            }
        }
        //Si l'IA défensif doit jeter une carte et qu'elle peut en jeter une autre qu'un (botte/parade confondus),
        //elle va le faire et ne pas choisir ces types de cartes.
        else
        {
            if(DEBUG_IA) printf("[IA DÉFENSIF] Je ne suis pas obligé de jeter une carte botte/parade. Je vais donc en jeter une autre, peu importe laquelle !\n");
            *choix_jeter = carte_aleatoire(ordinateur -> deck);
            while( (*choix_jeter >= ESSENCE && *choix_jeter <= ROULEZ) || (*choix_jeter >= CITERNE && *choix_jeter <= PRIORITAIRE) )
                *choix_jeter = carte_aleatoire(ordinateur -> deck);
        }
    }

    //Si l'ordinateur peut jouer une carte, on lui en fait jouer une.
    else
    {
        if(DEBUG_IA) printf("[IA DÉFENSIF] Je peux jouer une carte ! Je vais donc bien évidemment saisir cette opportunité.\n");
        *choix_jeter = -1;
        //S'il peut jouer au moins un botte/parade, on le force à en jouer un. Il faut choisir ce qu'il va jouer.
        if (nb_possible_parades + nb_possible_bottes > 0)
        {
            if(DEBUG_IA) printf("[IA DÉFENSIF] Ah, au moins une carte botte/parade confondues se trouve dans les cartes que j'ai le droit de jouer. Tant mieux, je vais pouvoir en jouer une !\n");

            //S'il a une carte 'botte' dans sa main, on lui fait jouer tout de suite (tant pis, on ne favorise pas le déclenchement de coups fourrés, mais bon).
            if(nb_possible_bottes > 0)
            {
                if(DEBUG_IA) printf("[IA DÉFENSIF] Cool ! Je peux jouer une carte 'BOTTE' ! :D\n");
                *choix_carte = carte_aleatoire(coupsPossibles);
                while(*choix_carte < CITERNE || *choix_carte > PRIORITAIRE)
                    *choix_carte = carte_aleatoire(coupsPossibles);
            }
            //Sinon, c'est qu'on va lui faire jouer une parade.
            else
            {
                if(DEBUG_IA) printf("[IA DÉFENSIF] Dommage, je n'ai pas de carte 'botte', mais je vais jouer une PARADE. :)\n");
                *choix_carte = carte_aleatoire(coupsPossibles);
                while(*choix_carte < ESSENCE || *choix_carte > ROULEZ)
                    *choix_carte = carte_aleatoire(coupsPossibles);
            }
        }
        //S'il ne peut jouer aucun botte/parade, on le fait choisir une carte de façon aléatoire, parmi celles qu'il peut jouer
        else
        {
            if(DEBUG_IA) printf("[IA DÉFENSIF] Je ne peux jouer ni 'botte' ni 'parade'. Je vais donc jouer n'importe quoi. :'(\n");
            *choix_carte = carte_aleatoire(coupsPossibles);
        }
    }
}

void ia_expert(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter)
{
    int ordi_arrete, humain_arrete;

    ordi_arrete = ordinateur -> est_creve || ordinateur -> a_accident || ordinateur -> en_panne_dessence || ordinateur -> est_arrete;
    humain_arrete = humain -> est_creve || humain -> a_accident || humain -> en_panne_dessence || humain -> est_arrete;

    //L'IA expert fait appel aux autres IA selon les cas.

    //Si les deux joueurs sont arrêtés, l'ordinateur va se défendre.
    if(ordi_arrete && humain_arrete)
    {
        if(DEBUG_IA) printf("[IA EXPERT] Nous sommes tous les deux arrêtés, je vais me défendre.\n");
        ia_defensif(ordinateur, humain, choix_carte, choix_jeter);
    }

    //Si l'ordinateur est arrêté, mais que le joueur roule, il faut l'empêcher de rouler ! L'ordinateur va attaquer.
    else if(ordi_arrete && !humain_arrete)
    {
        if(DEBUG_IA) printf("[IA EXPERT] Je suis arrêté, mais pas mon adversaire. À l'abordaaaaaaaage ! :pirate:\n");
        ia_agressif(ordinateur, humain, choix_carte, choix_jeter);
    }

    //Si l'ordinateur roule, mais que l'adversaire est à l'arrêt, il faut en profiter pour parcourir des kilomètres.
    else if(!ordi_arrete && humain_arrete)
    {
        if(DEBUG_IA) printf("[IA EXPERT] Je roule, mais mon adversaire est à l'arrêt. Vite, vite, je me mets en mode course !\n");
        ia_course(ordinateur, humain, choix_carte, choix_jeter);
    }

    //Si l'ordinateur et le joueur roulent, cela dépend des cas :
    else if(!ordi_arrete && !humain_arrete)
    {
        if(DEBUG_IA) printf("[IA EXPERT] Mon adversaire et moi-même roulons tous les deux. Analysons la situation...\n");
        //Dans le cas où l'ordinateur serait en retard par rapport au joueur, il va l'attaquer.
        if(ordinateur -> cumul_bornes <= humain -> cumul_bornes)
        {
            if(DEBUG_IA) printf("[IA EXPERT] Je suis en retard, je vais attaquer !\n");
            ia_agressif(ordinateur, humain, choix_carte, choix_jeter);
        }
        //Sinon, s'il est plutôt en avance par rapport au joueur, il va mettre le turbo pour terminer la partie.
        else
        {
            if(DEBUG_IA) printf("[IA EXPERT] Je suis en avance, j'appuie sur le champignon !\n");
            ia_course(ordinateur, humain, choix_carte, choix_jeter);
        }
    }
}
