/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : fichiers.c                   *
* DESCRIPTION : Dès que le programme doit              *
* utiliser un fichier (lecture ou écriture),           *
* cela passe par les fonctions définies ici.           *
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
#include <string.h>
#include "constantes.h"
#include "divers.h"
#include "fichiers.h"

int enregistrer_deck(FILE* fichier, Tptdeck deck)
{
    if(fichier != NULL && deck != NULL)
    {
        Tptcarte carte = deck -> premier;
        while(carte != NULL)
        {
            fprintf(fichier, "%d ", carte -> valeur);
            carte = carte -> suivant;
        }
        fprintf(fichier, "\n");
        return 1;
    }
    else
        return 0;
}

int enregistrer_joueur(FILE* fichier, Tptjoueur joueur)
{
    int success = 1;

    if(fichier != NULL && joueur != NULL)
    {
        //Écriture de toutes les infos du joueur. On met le nom du joueur sur une ligne à part, sinon ça serait trop compliqué
        //à gérer lors du chargement, si son nom contient des espaces.

        fprintf(fichier, "%s\n%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
            joueur -> nom,
            joueur -> est_ordinateur,
            joueur -> difficulte_ordinateur,

            joueur -> cumul_bornes,
            joueur -> nb_bottes_jouees,
            joueur -> nb_coups_fourres_joues,
            joueur -> nb_200bornes_jouees,
            joueur -> couronnement,

            joueur -> est_creve,
            joueur -> a_accident,
            joueur -> en_panne_dessence,
            joueur -> est_limite_par_vitesse,
            joueur -> est_arrete,

            joueur -> increvable,
            joueur -> citerne,
            joueur -> as_du_volant,
            joueur -> prioritaire
        );

        /* Parcours du deck du joueur et écriture dans le fichier */
        success = success && enregistrer_deck(fichier, joueur -> deck);
    }
    else
        success = 0;

    return success;
}

/* Cette fonction permet d'enregistrer une partie pour pouvoir la reprendre plus tard. */
int enregistrer_partie(const char* nomFichier, Tptpartie partie)
{
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w+");
    int success = 1;

    if(
            fichier != NULL &&
            partie != NULL &&
            partie -> deck != NULL &&
            partie -> joueur_selectionne != NULL &&
            partie -> joueur_selectionne -> deck != NULL &&
            partie -> autre_joueur != NULL &&
            partie -> autre_joueur -> deck != NULL
    )
    {
        /* Sauvegarde du deck principal */
        success = success && enregistrer_deck(fichier, partie -> deck);

        /* Sauvegarde de la poubelle */
        success = success && enregistrer_deck(fichier, partie -> poubelle);

        if(success)
        {
            /* Sauvegarde du joueur1 */
            success = success && enregistrer_joueur(fichier, partie -> joueur_selectionne);

            if(success)
            {
                /* Sauvegarde du joueur2 */
                success = success && enregistrer_joueur(fichier, partie -> autre_joueur);
            }
        }
    }
    else
        success = 0;

    fclose(fichier);
    return success;
}

/* Lecture d'un deck dans un fichier et remplissage de la liste chainée.
*  Pour réinsérer les cartes dans le bon ordre, on va cette fois utiliser cartes_deck_add_queue. */
int charger_deck(FILE* fichier, Tptdeck deck)
{
    const char delimiters[] = " \n";
    char ligne[TAILLE_MAX_LIGNE] = "";
    char* carte = NULL;
    int carte_num;
    int success = 1;

    if(fichier != NULL)
    {
        if(fgets(ligne, TAILLE_MAX_LIGNE, fichier) != NULL)
        {
            carte = strtok(ligne, delimiters);
            while(carte != NULL && success)
            {
                    //Conversion du numéro de la carte en entier
                    carte_num = strtol(carte, NULL, 10);

                    //Vérification de la validité du numéro et insertion
                    if(cartes_verifier_validite(carte_num))
                        cartes_deck_add_queue(deck, carte_num, 1);
                    else
                        success = 0;

                carte = strtok(NULL, delimiters);
            }
        }
        else
            success = 0;
    }
    else
        success = 0;

    return success;
}

/* Lecture d'un joueur et remplissage de la structure */
int charger_joueur(FILE* fichier, Tptjoueur joueur)
{
    int success = 1;
    const char delimiters[] = "\n";

    if(fichier != NULL && joueur != NULL)
    {
        //On charge le nom du joueur
        if(fgets(joueur -> nom, NOM_TAILLE_MAX, fichier) != NULL) //On récupère le nom brut
        {
            strcpy(joueur -> nom, strtok(joueur -> nom, delimiters)); //On vire le \n de la fin du nom du joueur

            //On charge les autres infos du joueur
            if(fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                &joueur -> est_ordinateur,
                &joueur -> difficulte_ordinateur,

                &joueur -> cumul_bornes,
                &joueur -> nb_bottes_jouees,
                &joueur -> nb_coups_fourres_joues,
                &joueur -> nb_200bornes_jouees,
                &joueur -> couronnement,

                &joueur -> est_creve,
                &joueur -> a_accident,
                &joueur -> en_panne_dessence,
                &joueur -> est_limite_par_vitesse,
                &joueur -> est_arrete,

                &joueur -> increvable,
                &joueur -> citerne,
                &joueur -> as_du_volant,
                &joueur -> prioritaire
            ))
            {
                //On charge son deck de cartes
                charger_deck(fichier, joueur -> deck);
            }
            else
                success = 0;
        }
        else
            success = 0;
    }
    else
        success = 0;

    return success;
}

//Cette fonction charge une partie à partir d'un fichier.
int charger_partie(const char* nomFichier, Tptpartie partie)
{
    int success = 1;
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");

    int nb_panne_essence_deck, nb_creve_deck, nb_accident_deck, nb_limite_vitesse_deck, nb_stop_deck;
    int nb_essence_deck, nb_roue_de_secours_deck, nb_reparations_deck, nb_fin_limite_vitesse_deck, nb_roulez_deck;
    int nb_citerne_deck, nb_increvable_deck, nb_as_du_volant_deck, nb_prioritaire_deck;
    int nb_bornes25_deck, nb_bornes50_deck, nb_bornes75_deck, nb_bornes100_deck, nb_bornes200_deck;
    int nb_obstacles_deck, nb_parades_deck, nb_bottes_deck, nb_bornes_deck;

    int nb_panne_essence_poubelle, nb_creve_poubelle, nb_accident_poubelle, nb_limite_vitesse_poubelle, nb_stop_poubelle;
    int nb_essence_poubelle, nb_roue_de_secours_poubelle, nb_reparations_poubelle, nb_fin_limite_vitesse_poubelle, nb_roulez_poubelle;
    int nb_citerne_poubelle, nb_increvable_poubelle, nb_as_du_volant_poubelle, nb_prioritaire_poubelle;
    int nb_bornes25_poubelle, nb_bornes50_poubelle, nb_bornes75_poubelle, nb_bornes100_poubelle, nb_bornes200_poubelle;
    int nb_obstacles_poubelle, nb_parades_poubelle, nb_bottes_poubelle, nb_bornes_poubelle;

    int nb_panne_essence_joueur1, nb_creve_joueur1, nb_accident_joueur1, nb_limite_vitesse_joueur1, nb_stop_joueur1;
    int nb_essence_joueur1, nb_roue_de_secours_joueur1, nb_reparations_joueur1, nb_fin_limite_vitesse_joueur1, nb_roulez_joueur1;
    int nb_citerne_joueur1, nb_increvable_joueur1, nb_as_du_volant_joueur1, nb_prioritaire_joueur1;
    int nb_bornes25_joueur1, nb_bornes50_joueur1, nb_bornes75_joueur1, nb_bornes100_joueur1, nb_bornes200_joueur1;
    int nb_obstacles_joueur1, nb_parades_joueur1, nb_bottes_joueur1, nb_bornes_joueur1;

    int nb_panne_essence_joueur2, nb_creve_joueur2, nb_accident_joueur2, nb_limite_vitesse_joueur2, nb_stop_joueur2;
    int nb_essence_joueur2, nb_roue_de_secours_joueur2, nb_reparations_joueur2, nb_fin_limite_vitesse_joueur2, nb_roulez_joueur2;
    int nb_citerne_joueur2, nb_increvable_joueur2, nb_as_du_volant_joueur2, nb_prioritaire_joueur2;
    int nb_bornes25_joueur2, nb_bornes50_joueur2, nb_bornes75_joueur2, nb_bornes100_joueur2, nb_bornes200_joueur2;
    int nb_obstacles_joueur2, nb_parades_joueur2, nb_bottes_joueur2, nb_bornes_joueur2;

    /* On crée deux joueurs vides. J'ai mis « Humain » ici, mais ça n'a pas d'importance,
    le vrai type de joueur écrasera ces préréglages-ci. */
    partie -> joueur_selectionne = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 1);
    partie -> autre_joueur = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 2);

    if(fichier != NULL && partie != NULL)
    {
        /* Chargement du deck principal */
        success = success && charger_deck(fichier, partie -> deck);

        if(success)
        {
            /* Chargement de la poubelle */
            success = success && charger_deck(fichier, partie -> poubelle);

            if(success)
            {
                /* Chargement du joueur 1 */
                success = success && charger_joueur(fichier, partie -> joueur_selectionne);

                if(success)
                {
                    /* Chargement du joueur 2 */
                    success = success && charger_joueur(fichier, partie -> autre_joueur);
                }
            }
        }
        fclose(fichier);
    }
    else
        success = 0;

    if(success)
    {
        //On vérifie qu'il n'y a eu aucun trafic et qu'il y a le bon nombre de cartes au total.
        //C'est d'ailleurs uniquement à cela que sert la sauvegarde de la poubelle.

        /* On commence par comptabiliser chaque type de cartes dans chacun des quatre decks. */

        /* Deck principal */
        cartes_deck_compter_sorte
        (
            partie -> deck,
            &nb_panne_essence_deck, &nb_creve_deck, &nb_accident_deck, &nb_limite_vitesse_deck, &nb_stop_deck,
            &nb_essence_deck, &nb_roue_de_secours_deck, &nb_reparations_deck, &nb_fin_limite_vitesse_deck, &nb_roulez_deck,
            &nb_citerne_deck, &nb_increvable_deck, &nb_as_du_volant_deck, &nb_prioritaire_deck,
            &nb_bornes25_deck, &nb_bornes50_deck, &nb_bornes75_deck, &nb_bornes100_deck, &nb_bornes200_deck,
            &nb_obstacles_deck, &nb_parades_deck, &nb_bottes_deck, &nb_bornes_deck
        );

        /* Poubelle */
        cartes_deck_compter_sorte
        (
            partie -> poubelle,
            &nb_panne_essence_poubelle, &nb_creve_poubelle, &nb_accident_poubelle, &nb_limite_vitesse_poubelle, &nb_stop_poubelle,
            &nb_essence_poubelle, &nb_roue_de_secours_poubelle, &nb_reparations_poubelle, &nb_fin_limite_vitesse_poubelle, &nb_roulez_poubelle,
            &nb_citerne_poubelle, &nb_increvable_poubelle, &nb_as_du_volant_poubelle, &nb_prioritaire_poubelle,
            &nb_bornes25_poubelle, &nb_bornes50_poubelle, &nb_bornes75_poubelle, &nb_bornes100_poubelle, &nb_bornes200_poubelle,
            &nb_obstacles_poubelle, &nb_parades_poubelle, &nb_bottes_poubelle, &nb_bornes_poubelle
        );

        /* Joueur 1 */
        cartes_deck_compter_sorte
        (
            partie -> joueur_selectionne -> deck,
            &nb_panne_essence_joueur1, &nb_creve_joueur1, &nb_accident_joueur1, &nb_limite_vitesse_joueur1, &nb_stop_joueur1,
            &nb_essence_joueur1, &nb_roue_de_secours_joueur1, &nb_reparations_joueur1, &nb_fin_limite_vitesse_joueur1, &nb_roulez_joueur1,
            &nb_citerne_joueur1, &nb_increvable_joueur1, &nb_as_du_volant_joueur1, &nb_prioritaire_joueur1,
            &nb_bornes25_joueur1, &nb_bornes50_joueur1, &nb_bornes75_joueur1, &nb_bornes100_joueur1, &nb_bornes200_joueur1,
            &nb_obstacles_joueur1, &nb_parades_joueur1, &nb_bottes_joueur1, &nb_bornes_joueur1
        );

        /* Joueur 2 */
        cartes_deck_compter_sorte
        (
            partie -> autre_joueur -> deck,
            &nb_panne_essence_joueur2, &nb_creve_joueur2, &nb_accident_joueur2, &nb_limite_vitesse_joueur2, &nb_stop_joueur2,
            &nb_essence_joueur2, &nb_roue_de_secours_joueur2, &nb_reparations_joueur2, &nb_fin_limite_vitesse_joueur2, &nb_roulez_joueur2,
            &nb_citerne_joueur2, &nb_increvable_joueur2, &nb_as_du_volant_joueur2, &nb_prioritaire_joueur2,
            &nb_bornes25_joueur2, &nb_bornes50_joueur2, &nb_bornes75_joueur2, &nb_bornes100_joueur2, &nb_bornes200_joueur2,
            &nb_obstacles_joueur2, &nb_parades_joueur2, &nb_bottes_joueur2, &nb_bornes_joueur2
        );

        //On fait les vérifications !
        if(
                partie -> joueur_selectionne -> deck -> taille != CARTES_MAIN ||
                partie -> autre_joueur -> deck -> taille != CARTES_MAIN ||
                partie -> deck -> taille + partie -> poubelle -> taille + partie -> joueur_selectionne -> deck -> taille + partie -> autre_joueur -> deck -> taille != CARTES_TOTAL ||

                //Obstacles
                nb_panne_essence_deck       + nb_panne_essence_poubelle         + nb_panne_essence_joueur1          + nb_panne_essence_joueur2          != NB_PANNE_ESSENCE     ||
                nb_creve_deck               + nb_creve_poubelle                 + nb_creve_joueur1                  + nb_creve_joueur2                  != NB_CREVE             ||
                nb_accident_deck            + nb_accident_poubelle              + nb_accident_joueur1               + nb_accident_joueur2               != NB_ACCIDENT          ||
                nb_limite_vitesse_deck      + nb_limite_vitesse_poubelle        + nb_limite_vitesse_joueur1         + nb_limite_vitesse_joueur2         != NB_LIMITE_VITESSE    ||
                nb_stop_deck                + nb_stop_poubelle                  + nb_stop_joueur1                   + nb_stop_joueur2                   != NB_STOP              ||

                //Parades
                nb_essence_deck             + nb_essence_poubelle               + nb_essence_joueur1                + nb_essence_joueur2                != NB_ESSENCE           ||
                nb_roue_de_secours_deck     + nb_roue_de_secours_poubelle       + nb_roue_de_secours_joueur1        + nb_roue_de_secours_joueur2        != NB_ROUE_DE_SECOURS   ||
                nb_reparations_deck         + nb_reparations_poubelle           + nb_reparations_joueur1            + nb_reparations_joueur2            != NB_REPARATIONS       ||
                nb_fin_limite_vitesse_deck  + nb_fin_limite_vitesse_poubelle    + nb_fin_limite_vitesse_joueur1     + nb_fin_limite_vitesse_joueur2     != NB_FIN_LIMITE_VITESSE||
                nb_roulez_deck              + nb_roulez_poubelle                + nb_roulez_joueur1                 + nb_roulez_joueur2                 != NB_ROULEZ            ||

                //Bottes
                nb_citerne_deck             + nb_citerne_poubelle               + nb_citerne_joueur1                + nb_citerne_joueur2                != NB_CITERNE           ||
                nb_increvable_deck          + nb_increvable_poubelle            + nb_increvable_joueur1             + nb_increvable_joueur2             != NB_INCREVABLE        ||
                nb_as_du_volant_deck        + nb_as_du_volant_poubelle          + nb_as_du_volant_joueur1           + nb_as_du_volant_joueur2           != NB_AS_DU_VOLANT      ||
                nb_prioritaire_deck         + nb_prioritaire_poubelle           + nb_prioritaire_joueur1            + nb_prioritaire_joueur2            != NB_PRIORITAIRE       ||

                //Bornes
                nb_bornes25_deck            + nb_bornes25_poubelle              + nb_bornes25_joueur1               + nb_bornes25_joueur2               != NB_BORNES25          ||
                nb_bornes50_deck            + nb_bornes50_poubelle              + nb_bornes50_joueur1               + nb_bornes50_joueur2               != NB_BORNES50          ||
                nb_bornes75_deck            + nb_bornes75_poubelle              + nb_bornes75_joueur1               + nb_bornes75_joueur2               != NB_BORNES75          ||
                nb_bornes100_deck           + nb_bornes100_poubelle             + nb_bornes100_joueur1              + nb_bornes100_joueur2              != NB_BORNES100         ||
                nb_bornes200_deck           + nb_bornes200_poubelle             + nb_bornes200_joueur1              + nb_bornes200_joueur2              != NB_BORNES200         ||

                //Totaux
                nb_obstacles_deck           + nb_obstacles_poubelle             + nb_obstacles_joueur1              + nb_obstacles_joueur2              != NB_OBSTACLES         ||
                nb_parades_deck             + nb_parades_poubelle               + nb_parades_joueur1                + nb_parades_joueur2                != NB_PARADES           ||
                nb_bottes_deck              + nb_bottes_poubelle                + nb_bottes_joueur1                 + nb_bottes_joueur2                 != NB_BOTTES            ||
                nb_bornes_deck              + nb_bornes_poubelle                + nb_bornes_joueur1                 + nb_bornes_joueur2                 != NB_BORNES
        )
            success = 0;
        else
        {
            //Il n'y a pas d'erreur, on lance la partie !
            printf("Partie chargée avec succès !\n\n");
            jeu(partie);
        }
    }

    //En cas d'échec, on vide tout.
    if(!success)
        partie_vider(partie);

    return success;
}
