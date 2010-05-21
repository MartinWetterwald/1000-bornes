/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : fichiers.c             *
* DESCRIPTION : Dès que le programme doit        *
* utiliser un fichier (lecture ou écriture),     *
* cela passe par les fonctions définies ici.     *
*                                                *
*************************************************/

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
        /* Parcours du deck principal et écriture dans le fichier */
        success = success && enregistrer_deck(fichier, partie -> deck);

        if(success)
        {
            /* Écriture des infos du joueur1 */
            success = success && enregistrer_joueur(fichier, partie -> joueur_selectionne);

            if(success)
            {
                /* Écriture des infos du joueur2 */
                success = success && enregistrer_joueur(fichier, partie -> autre_joueur);
            }
        }
    }
    else
        success = 0;

    fclose(fichier);
    return success;
}

/* Lecture d'un deck dans un fichier et remplissage de la liste chainée. */
int charger_deck(FILE* fichier, Tptdeck deck)
{
    const char delimiters[] = " \n";
    char ligne[TAILLE_MAX_LIGNE] = "";
    char* carte = NULL;
    int carte_num;
    int success = 1;

    if(fichier != NULL)
    {
        fgets(ligne, TAILLE_MAX_LIGNE, fichier);

        carte = strtok(ligne, delimiters);
        while(carte != NULL && success)
        {
                //Conversion du numéro de la carte en entier
                carte_num = strtol(carte, NULL, 10);

                //Vérification de la validité du numéro
                if(cartes_verifier_validite(carte_num))
                    cartes_deck_add(deck, carte_num, 1);
                else
                    success = 0;

            carte = strtok(NULL, delimiters);
        }
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
        fgets(joueur -> nom, NOM_TAILLE_MAX, fichier); //On récupère le nom brut
        strcpy(joueur -> nom, strtok(joueur -> nom, delimiters)); //On vire le \n de la fin du nom du joueur

        //On charge les autres infos du joueur
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
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
        );

            //On charge son deck de cartes
            charger_deck(fichier, joueur -> deck);
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

    /* On crée deux joueurs vides. J'ai mis « Humain » ici, mais ça n'a pas d'importance,
    le vrai type de joueur écrasera ces préréglages-ci. */
    partie -> joueur_selectionne = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 1);
    partie -> autre_joueur = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 2);

    if(fichier != NULL && partie != NULL)
    {
        /* Lecture et chargement du deck principal */
        success = success && charger_deck(fichier, partie -> deck);

        if(success)
        {
            /* Lecture et chargement du joueur 1 */
            success = success && charger_joueur(fichier, partie -> joueur_selectionne);

            if(success)
            {
                /* Lecture et chargement du joueur 2 */
                success = success && charger_joueur(fichier, partie -> autre_joueur);
            }
        }

    }
    else
        success = 0;

    fclose(fichier);

    if(success)
    {
        //On vérifie que les joueurs ont strictement 6 cartes chacun. Sinon erreur.
        if(partie -> joueur_selectionne -> deck -> taille != CARTES_MAIN || partie -> autre_joueur -> deck -> taille != CARTES_MAIN)
            success = 0;
        else
        {
            //Il n'y a pas d'erreur, on lance la partie !
            printf("Partie chargée avec succès !\n\n");
            jeu(partie);
        }
    }

    //En cas d'échec, on vide tout.
    //if(!success)
        //partie_vider(partie);

    return success;
}
