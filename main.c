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
#include "menu.h"
#include "jeu.h"


int main()
{
    srand(time(NULL));
    Tdeck* deckPrincipal = liste_init(); //Ceci crée un deck de cartes vides, deck qui sera le tas principal où piocher des cartes.
    Tjoueur* joueur1 = NULL;
    Tjoueur* joueur2 = NULL;
    Tjoueur* joueur_selectionne = NULL;
    Tjoueur* autre_joueur = NULL;

    int menu1_choix = -1, jouer_contre_ordinateur = -1, difficulte_ordinateur = -1;
    char nomFichier[TAILLE_MAX_NOM_FICHIER];

    afficher_logo();

    //Menu principal
    while(menu1_choix != 0)
    {
        menu_principal(&menu1_choix);
        switch(menu1_choix)
        {
            /* Menu principal - choix n°1 = Nouvelle partie */
            case 1:
                jouer_contre_ordinateur = -1;
                while(jouer_contre_ordinateur == -1)
                {
                    menu_demander_ordinateur(&jouer_contre_ordinateur);
                    switch(jouer_contre_ordinateur)
                    {
                        case 1:
                            difficulte_ordinateur = -1;
                            while(difficulte_ordinateur == -1)
                            {
                                menu_difficulte_ordinateur(&difficulte_ordinateur);
                                switch(difficulte_ordinateur)
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

                                    case 0:
                                        jouer_contre_ordinateur = -1;
                                    break;

                                    default:
                                        printf("\nChoix incorrect. Recommencez.\n");
                                        difficulte_ordinateur = -1;
                                }
                            }
                            joueur1 = joueur_init(HUMAIN, difficulte_ordinateur, 1);
                            joueur2 = joueur_init(ORDINATEUR, difficulte_ordinateur, 2);
                        break;

                        case 2:
                            joueur1 = joueur_init(HUMAIN, difficulte_ordinateur, 1);
                            joueur2 = joueur_init(HUMAIN, difficulte_ordinateur, 2);
                        break;

                        case 3:
                            difficulte_ordinateur = -1;
                            while(difficulte_ordinateur == -1)
                            {
                                menu_difficulte_ordinateur(&difficulte_ordinateur);
                                switch(difficulte_ordinateur)
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

                                    case 0:
                                        jouer_contre_ordinateur = -1;
                                    break;

                                    default:
                                        printf("\nChoix incorrect. Recommencez.\n");
                                        difficulte_ordinateur = -1;
                                }
                            }
                            joueur1 = joueur_init(ORDINATEUR, difficulte_ordinateur, 1);
                            joueur2 = joueur_init(ORDINATEUR, difficulte_ordinateur, 2);
                        break;

                        case 0:
                        break;

                        default:
                            printf("\nChoix incorrect. Recommencez.\n");
                            jouer_contre_ordinateur = -1;
                    }
                }

                if(jouer_contre_ordinateur != 0 && difficulte_ordinateur != 0)
                {
                    jeu_init(deckPrincipal, joueur1, joueur2, &joueur_selectionne, &autre_joueur);
                    jeu(deckPrincipal, &joueur_selectionne, &autre_joueur);
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

    return 0;
}
