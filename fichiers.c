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
#include "joueur.h"

/* Cette fonction permet d'enregistrer une partie pour pouvoir la reprendre plus tard. */
int enregistrer_partie(const char* nomFichier, Tptdeck deckPrincipal, Tptdeck deckJoueur1, Tptdeck deckJoueur2)
{
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "w+");

    Tptcarte parcours;

    if(fichier != NULL && deckPrincipal != NULL && deckPrincipal -> premier != NULL && deckJoueur1 != NULL && deckJoueur1 -> premier != NULL && deckJoueur2 != NULL && deckJoueur2 -> premier != NULL)
    {
        /* Parcours du deck principal et écriture dans le fichier */
        parcours = deckPrincipal -> premier;
        while(parcours != NULL)
        {
            fprintf(fichier, "%d ", parcours -> valeur);
            parcours = parcours -> suivant;
        }
        fprintf(fichier, "\n");

        /* Parcours du deck du joueur 1 et écriture dans le fichier */
        parcours = deckJoueur1 -> premier;
        while(parcours != NULL)
        {
            fprintf(fichier, "%d ", parcours -> valeur);
            parcours = parcours -> suivant;
        }
        fprintf(fichier, "\n");

        /* Parcours du joueur 2 et écriture dans le fichier */
        parcours = deckJoueur2 -> premier;
        while(parcours != NULL)
        {
            fprintf(fichier, "%d ", parcours -> valeur);
            parcours = parcours -> suivant;
        }
        fprintf(fichier, "\n");
        fclose(fichier);
        return 1;
    }
    else
        return 0;
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
int charger_joueur(FILE* fichier, Tptjoueur monJoueur)
{
    const char delimiters[] = "\n";
    char ligne[TAILLE_MAX_LIGNE] = "";
    char* item = NULL;
    int success = 1, i = 0;

    if(fichier != NULL)
    {
        fgets(ligne, TAILLE_MAX_LIGNE, fichier);

        item = strtok(ligne, delimiters);
        while(item != NULL && success)
        {
            printf("%s\n", item);
            /*
            i++;
            //est_ordinateur
            if(i == 1)


            //nom

            //on s'occupe du deck plus tard

            //est_creve

            //a_accident

            //en_panne_dessence

            //est_limite_par_vitesse

            //est_arrete*/
            item = strtok(NULL, delimiters);
        }
    }
    else
        success = 0;

    return success;
}








//Cette fonction charge une partie à partir d'un fichier.
int charger_partie(const char* nomFichier, Tptdeck deckPrincipal, Tptdeck deckJoueur1, Tptdeck deckJoueur2)
{
    int success = 1;
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");

    if(fichier != NULL && deckPrincipal != NULL && deckJoueur1 != NULL && deckJoueur2 != NULL)
    {
        /* Lecture et chargement du deck principal */
        success = (success && charger_deck(fichier, deckPrincipal));

        if(success)
        {
            /* Lecture et chargement du deck du joueur 1 */
            success = (success && charger_deck(fichier, deckJoueur1));

            if(success)
            {
                /* Lecture et chargement du deck du joueur 2 */
                success = (success && charger_deck(fichier, deckJoueur2));
            }
        }
        fclose(fichier);
    }
    else
        success = 0;

    if(success)
    {
        //On vérifie que les joueurs ont strictement 6 ou 7 cartes chacun. Sinon erreur.
        if(!(
            deckJoueur1 -> taille >= CARTES_MAIN && deckJoueur1 -> taille <= CARTES_MAIN_MAX &&
            deckJoueur2 -> taille >= CARTES_MAIN && deckJoueur2 -> taille <= CARTES_MAIN_MAX
        ))
            success = 0;
        //De plus il est impossible que les deux joueurs aient autant de cartes.
        else if(deckJoueur1 -> taille == deckJoueur2 -> taille)
            success = 0;
        //Il n'y a pas d'erreur, on va maintenant déterminer quel est le joueur qui doit jouer.
        else
        {
            /*if(deckJoueur1 > deckJoueur2)
            else*/
        }
    }


    //En cas d'échec, on vide les deux decks.
    if(!success)
    {
        liste_vider(deckPrincipal);
        liste_vider(deckJoueur1);
        liste_vider(deckJoueur2);
    }

    return success;
}
