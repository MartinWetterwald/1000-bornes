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
#include "fichiers.h"

int main()
{
    srand(time(NULL));
    Tptpartie partie = partie_init();
    Tptjoueur joueur1 = NULL;
    Tptjoueur joueur2 = NULL;

    int menu1_choix = -1, jouer_contre_ordinateur = -1, difficulte_ordinateur1 = -1, difficulte_ordinateur2 = -1;
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
                            //On demande la difficulté de l'ordinateur
                            choisir_difficulte_ordinateur(&jouer_contre_ordinateur, &difficulte_ordinateur2, 2);

                            //On initialise les joueurs
                            joueur1 = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 1);
                            joueur2 = joueur_init(ORDINATEUR, difficulte_ordinateur2, 2);
                        break;

                        case 2:
                            joueur1 = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 1);
                            joueur2 = joueur_init(HUMAIN, PAS_DE_DIFFICULTE, 2);
                        break;

                        case 3:
                            /* On demande la difficulté de chaque ordinateur */
                            choisir_difficulte_ordinateur(&jouer_contre_ordinateur, &difficulte_ordinateur1, 1);
                            if(difficulte_ordinateur1 != ARRETER_PARTIE)
                                choisir_difficulte_ordinateur(&jouer_contre_ordinateur, &difficulte_ordinateur2, 2);

                            /* On initialise les deux joueurs */
                            joueur1 = joueur_init(ORDINATEUR, difficulte_ordinateur1, 1);
                            joueur2 = joueur_init(ORDINATEUR, difficulte_ordinateur2, 2);
                        break;

                        case 0:
                        break;

                        default:
                            printf("\nChoix incorrect. Recommencez.\n");
                            jouer_contre_ordinateur = -1;
                    }
                }

                if(jouer_contre_ordinateur != ARRETER_PARTIE && difficulte_ordinateur1 != ARRETER_PARTIE && difficulte_ordinateur2 != ARRETER_PARTIE)
                {
                    jeu_init(partie, joueur1, joueur2);
                    jeu(partie);
                }
            break;

            /* Menu principal - choix2 = Charger partie */
            case 2:
                menu_charger_partie(nomFichier);
                if(!charger_partie(nomFichier, partie))
                {
                    printf("\nLe chargement de la partie a échoué. Les causes possibles sont :\n");
                    printf("- fichier inaccessible (vérifier que '%s' existe bien et que le programme a les droits d'accès à ce fichier) ;\n", nomFichier);
                    printf("- fichier corrompu car modifié par l'utilisateur manuellement.\n\n");
                }
            break;

            /* Menu principal - choix0 = Quitter le programme */
            case 0:
                printf("Au revoir !\n");
            break;

            default:
                printf("\nChoix incorrect. Recommencez.\n");
        }
    }

    return 0;
}
