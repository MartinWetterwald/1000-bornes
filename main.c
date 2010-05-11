/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : main.c                 *
* DESCRIPTION : Fonction principale du programme.*
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constantes.h"
#include "divers.h"
#include "joueur.h"
#include "menu.h"


int main()
{
    srand(time(NULL));
    Tdeck* deckPrincipal = liste_init(); //Ceci crée un deck de cartes vides, deck qui sera le tas principal où piocher des cartes.
    Tjoueur* Joueur1 = joueur_init(0);
    Tjoueur* Joueur2 = joueur_init(1); //Le joueur 2 sera un ordinateur.

    int menu1_choix = -1, difficulte_ordinateur = -1;
    char nomFichier[TAILLE_MAX_NOM_FICHIER];

    afficher_logo();

    while(menu1_choix != 0)
    {
        menu_principal(&menu1_choix);
        switch(menu1_choix)
        {
            /* Menu principal - choix1 = Nouvelle partie */
            case 1:
                difficulte_ordinateur = -1;
                while(difficulte_ordinateur == -1)
                {
                    menu_nouvelle_partie(&difficulte_ordinateur);
                    switch(difficulte_ordinateur)
                    {
                        case 1:
                        break;

                        case 2:
                        break;

                        case 3:
                        break;

                        case 4:
                        break;

                        case 5:
                        break;

                        case 0:
                        break;

                        default:
                            printf("\nChoix incorrect. Recommencez.\n");
                            difficulte_ordinateur = -1;
                    }
                }

                if(difficulte_ordinateur != 0)
                {
                    menu_demander_nom_joueur(Joueur1 -> nom);
                    cartes_deck_init(deckPrincipal);
                    cartes_distribuer(deckPrincipal, Joueur1 -> deck, Joueur2 -> deck, CARTES_MAIN);




                    printf("Le jeu a été mélangé et les cartes ont été distribuées.\n");

                    printf("\nContenu du deck principal :\n");
                    cartes_deck_afficher(deckPrincipal);

                    printf("\nJoueur 1 :\n");
                    joueur_afficher(Joueur1);

                    printf("\nJoueur 2 :\n");
                    joueur_afficher(Joueur2);

                    printf("\n\nPARTIE TERMINÉE !\n");
                }
            break;

            /* Menu principal - choix2 = Charger partie */
            case 2:
                menu_charger_partie(nomFichier);
                /*if(!charger_partie(nomFichier, deckPrincipal, deckJoueur1, deckJoueur2))
                {
                    printf("\nLe chargement de la partie a échoué. Les causes possibles sont :\n");
                    printf("- fichier inaccessible (vérifier que '%s' existe bien et que le programme a les droits d'accès à ce fichier) ;\n", nomFichier);
                    printf("- fichier corrompu car modifié par l'utilisateur manuellement.\n\n");
                }
                else
                {
                    printf("\nPartie chargée avec succès !\n");

                    printf("\nContenu du deck principal :\n");
                    cartes_deck_afficher(deckPrincipal);

                    printf("\nContenu du deck du joueur 1 :\n");
                    cartes_deck_afficher(deckJoueur1);

                    printf("\nContenu du deck joueur 2 :\n");
                    cartes_deck_afficher(deckJoueur2);

                    //Ne pas oublier de vider les decks en fin de partie sinon les cartes s'accumulent !

                    printf("\n\nPARTIE TERMINÉE !\n");
                }*/
            break;

            /* Menu principal - choix0 = Quitter le programme */
            case 0:
                printf("Au revoir !\n");
            break;

            default:
                printf("\nChoix incorrect. Recommencez.\n");
        }
    }

    /*if(enregistrer_partie(nomFichier, deckJoueur1, deckJoueur2))
        printf("La partie a été enregistrée avec succès !\n");
    else
        printf("Une erreur est survenue lors de l'enregistrement de la partie.\n");*/

    liste_detruire(&deckPrincipal);
    /*liste_detruire(&deckJoueur1);
    liste_detruire(&deckJoueur2);*/
    return 0;
}
