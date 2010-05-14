/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : jeu.c                  *
* DESCRIPTION : Fonctions appelées pendant une   *
* partie. Par exemple on peut vérifier si la     *
* partie est finie, faire jouer un humain, un    *
* ordinateur (intelligence artificielle)...      *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "divers.h"
#include "menu.h"
#include "jeu.h"

Tjoueur* qui_commence(Tjoueur* joueur1, Tjoueur* joueur2)
{
    Tjoueur* joueur_qui_commence;
    int qui_commence;

    qui_commence = (rand() % 2) + 1;

    if(qui_commence == 1)
        joueur_qui_commence = joueur1;
    else if(qui_commence == 2)
        joueur_qui_commence = joueur2;

    return joueur_qui_commence;
}

//Fonction appelée en cas de nouvelle partie
void jeu_init(Tdeck* deck, Tjoueur* joueur1, Tjoueur* joueur2, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur)
{
    if(!joueur1 -> est_ordinateur)
        menu_demander_nom_joueur(joueur1 -> nom);

    if(!joueur2 -> est_ordinateur)
        menu_demander_nom_joueur(joueur2 -> nom);

    cartes_deck_init(deck);
    cartes_distribuer(deck, joueur1 -> deck, joueur2 -> deck, CARTES_MAIN);
    printf("\nLe jeu a été mélangé et les cartes ont été distribuées.\n");

    //On choisit aléatoirement si l'ordinateur va commencer ou le joueur.
    *joueur_selectionne = qui_commence(joueur1, joueur2);

    if(*joueur_selectionne == joueur1)
        *autre_joueur = joueur2;
    else
        *autre_joueur = joueur1;

    printf("Le tirage au sort a décidé que '%s' commence la partie.\n", (*joueur_selectionne) -> nom);
}

//Cette fonction sert à inverser le joueur qui va devoir jouer.
void switch_tour(Tptjoueur** joueur_selectionne, Tptjoueur** autre_joueur)
{
    Tptjoueur* temp = *joueur_selectionne;

    *joueur_selectionne = *autre_joueur;
    *autre_joueur = temp;
}

Tjoueur* detecter_gagnant(Tjoueur* joueur1, Tjoueur* joueur2)
{
    int points_joueur1 = joueur_compter_les_points(joueur1, joueur2 -> cumul_bornes);
    int points_joueur2 = joueur_compter_les_points(joueur2, joueur1 -> cumul_bornes);

    printf("'%s' a effectué un total de %d points.\n", joueur1 -> nom, points_joueur1);
    printf("'%s' a effectué un total de %d points.\n", joueur2 -> nom, points_joueur2);

    if(points_joueur1 > points_joueur2)
        return joueur1;
    else if(points_joueur2 > points_joueur1)
        return joueur2;
    else
        return NULL;
}

int partie_terminee(Tdeck* deck, Tjoueur* joueur1, Tjoueur* joueur2)
{
    return (deck -> taille == 0 || joueur1 -> cumul_bornes >= BORNES_MAX || joueur2 -> cumul_bornes >= BORNES_MAX);
}

//Cette fonction vérifie qu'un joueur a le droit de jouer une carte
int coup_autorise(Tjoueur* joueur_selectionne, Tjoueur* autre_joueur, int carte_type)
{
    if(joueur_selectionne -> est_arrete)
    {
    }
    return 1;
}

//Cette fonction permet à un joueur de jouer une carte (un tour de jeu)
int jouer(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur,  int carte_type, int passe_son_tour)
{
    Tcarte* carte_a_jouer = NULL;

    //Vérification que le joueur a cette carte et récupération de son adresse.
    carte_a_jouer = joueur_possede_carte(*joueur_selectionne, carte_type);
    if(carte_a_jouer != NULL)
    {
        if(passe_son_tour)
        {
            //Supprimer la carte du deck
            liste_maillon_supprimer((*joueur_selectionne) -> deck, carte_a_jouer);
            return 1;
        }
        else
        {
            //Vérifier que le coup est permis
            if(coup_autorise(*joueur_selectionne, *autre_joueur, carte_type))
            {
                //Appliquer les conséquences de la carte jouée
                consequences_coup(joueur_selectionne, autre_joueur, carte_type);

                //Supprimer la carte du deck
                liste_maillon_supprimer((*joueur_selectionne) -> deck, carte_a_jouer);

                /* On sauvegarde le type de carte que le joueur vient de jouer.
                Ceci va nous être utile pour la fonction coup_autorise. */
                (*joueur_selectionne) -> carte_precedemment_jouee = carte_type;

                return 1;
            }
            return ERREUR_COUP_NON_PERMIS;
        }
    }
    return ERREUR_CARTE_PAS_DANS_MAIN;
}

//Cette fonction modifie l'état des joueurs en fonction de la carte jouée.
void consequences_coup(Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int carte_type)
{
    switch(carte_type)
    {
        //Obstacles
        case PANNE_ESSENCE:
            (*autre_joueur) -> en_panne_dessence = 1;
            if(!(*autre_joueur) -> prioritaire)
                (*autre_joueur) -> est_arrete = 1;
        break;

        case CREVE:
            (*autre_joueur) -> est_creve = 1;
            if(!(*autre_joueur) -> prioritaire)
                (*autre_joueur) -> est_arrete = 1;
        break;

        case ACCIDENT:
            (*autre_joueur) -> a_accident = 1;
            if(!(*autre_joueur) -> prioritaire)
                (*autre_joueur) -> est_arrete = 1;
        break;

        case LIMITE_VITESSE:
            if(!(*autre_joueur) -> prioritaire)
            {
                (*autre_joueur) -> est_limite_par_vitesse = 1;
                (*autre_joueur) -> est_arrete = 0;
            }
        break;

        case STOP:
            if(!(*autre_joueur) -> prioritaire)
                (*autre_joueur) -> est_arrete = 1;
        break;

        //Parades
        case ESSENCE:
            (*joueur_selectionne) -> en_panne_dessence = 0;
        break;

        case ROUE_DE_SECOURS:
            (*joueur_selectionne) -> est_creve = 0;
        break;

        case REPARATIONS:
            (*joueur_selectionne) -> a_accident = 0;
        break;

        case FIN_LIMITE_VITESSE:
            (*joueur_selectionne) -> est_limite_par_vitesse = 0;
        break;

        case ROULEZ:
            (*joueur_selectionne) -> est_arrete = 0;
        break;

        //Bottes
        case CITERNE:
            (*joueur_selectionne) -> citerne = 1;
            ( (*joueur_selectionne) -> nb_bottes_jouees )++;
        break;

        case INCREVABLE:
            (*joueur_selectionne) -> increvable = 1;
            ( (*joueur_selectionne) -> nb_bottes_jouees )++;
        break;

        case AS_DU_VOLANT:
            (*joueur_selectionne) -> as_du_volant = 1;
            ( (*joueur_selectionne) -> nb_bottes_jouees )++;
        break;

        case PRIORITAIRE:
            (*joueur_selectionne) -> prioritaire = 1;
            ( (*joueur_selectionne) -> nb_bottes_jouees )++;
        break;

        //Bornes
        case BORNES25:
             ( (*joueur_selectionne) -> cumul_bornes ) += 25;
        break;

        case BORNES50:
            ( (*joueur_selectionne) -> cumul_bornes ) += 50;
        break;

        case BORNES75:
            ( (*joueur_selectionne) -> cumul_bornes ) += 75;
        break;

        case BORNES100:
            ( (*joueur_selectionne) -> cumul_bornes ) += 100;
        break;

        case BORNES200:
            ( (*joueur_selectionne) -> cumul_bornes ) += 200;
            ( (*joueur_selectionne) -> nb_200bornes_jouees )++;
        break;

        default:
            printf("ERREUR.");
            exit(0);
    }
}

//Cette fonction est la fonction globale qui gère une partie (reprise en cours ou nouvellement commencée).
//Le paramètre a_qui_le_tour est un pointeur vers un joueur. IL désigne quel joueur va jouer.
void jeu(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur)
{
    int partie_est_terminee = partie_terminee(deck, *joueur_selectionne, *autre_joueur);
    int choix_carte = -1, choix_jeter = -1;
    int resultat_jouer = -1, resultat_jouer_passer_tour = -1;
    char nomFichier[TAILLE_MAX_NOM_FICHIER];
    Tjoueur* gagnant = NULL;
    Tcarte* carte_piochee = NULL;

    while(!partie_est_terminee && choix_carte != ARRETER_PARTIE && choix_carte != ENREGISTRER)
    {
        printf("\nIl reste %d cartes dans le deck principal.\n", deck -> taille);

        printf("\nC'est à '%s' de jouer.\n", (*joueur_selectionne) -> nom);
        joueur_afficher(*joueur_selectionne);

        //On fait piocher une carte au joueur
        carte_piochee = cartes_changer_deck(deck, deck -> premier, (*joueur_selectionne) -> deck);

        printf("'%s' vient de piocher une carte '", (*joueur_selectionne) -> nom);
        cartes_type2francais(carte_piochee -> valeur); //On affiche le nom de la carte en français
        printf("'.\n\n");

        //Affiche la main du joueur
        //cartes_deck_afficher((*joueur_selectionne) -> deck);

        printf("\n");

        //Demande au joueur de choisir une carte à jouer
        resultat_jouer = -1;
        while(resultat_jouer != 1)
        {
            menu_demander_choix_carte(&choix_carte);

            if(choix_carte != ARRETER_PARTIE && choix_carte != ENREGISTRER)
            {
                if(choix_carte != PASSER_SON_TOUR)
                {
                    //Appel de la fonction jouer
                    resultat_jouer = jouer(deck, joueur_selectionne, autre_joueur, choix_carte, 0);
                    switch(resultat_jouer)
                    {
                        case ERREUR_COUP_NON_PERMIS:
                            printf("\nCe coup n'est pas permis !\n");
                            printf("Veuillez choisir une autre carte.\n\n");
                        break;

                        case ERREUR_CARTE_PAS_DANS_MAIN:
                            printf("\nErreur, carte invalide. Soit ce type de carte n'existe pas, soit vous n'avez pas de carte de ce type dans votre main.\n");
                            printf("Merci de choisir une carte valide.\n\n");
                        break;
                    }
                }
                else
                {
                    resultat_jouer_passer_tour = -1;
                    while(resultat_jouer_passer_tour != 1)
                    {
                        menu_demander_choix_carte_jeter(&choix_jeter);
                        if(choix_jeter != ANNULER_PASSER_SON_TOUR)
                        {
                            resultat_jouer_passer_tour = jouer(deck, joueur_selectionne, autre_joueur, choix_jeter, 1);
                            if(resultat_jouer_passer_tour == ERREUR_CARTE_PAS_DANS_MAIN)
                            {
                                printf("\nErreur, carte invalide. Soit ce type de carte n'existe pas, soit vous n'avez pas de carte de ce type dans votre main.\n");
                                printf("Merci de choisir une carte valide.\n\n");
                            }
                        }
                        else
                            resultat_jouer_passer_tour = 1;
                    }
                    if(choix_jeter != ANNULER_PASSER_SON_TOUR)
                    {
                        printf("'%s' passe son tour.\n", (*joueur_selectionne) -> nom);
                        resultat_jouer = 1;
                        cartes_deck_afficher((*joueur_selectionne) -> deck);
                    }
                    else
                    {
                        printf("\nVous avez changé d'avis et ne souhaitez plus passer votre tour.\n");
                        printf("Vous allez être réinvité à sélectionner la carte que vous désirez jouer.\n\n");
                    }
                }
                if(choix_jeter != ANNULER_PASSER_SON_TOUR && resultat_jouer)
                {
                    switch_tour(&joueur_selectionne, &autre_joueur);
                    partie_est_terminee = partie_terminee(deck, *joueur_selectionne, *autre_joueur);
                }
            }
            else
                resultat_jouer = 1;
        }
    }

    //On souhaite enregistrer la partie pour la reprendre plus tard
    if(choix_carte == ENREGISTRER)
    {
        menu_enregistrer_partie(nomFichier);
    }
    else if(choix_carte == ARRETER_PARTIE)
    {
        printf("On arrête la partie !\n");
    }
    //La partie est réellement terminée
    else if(partie_est_terminee)
    {
        printf("\n\nPARTIE TERMINÉE !\n\n");
        gagnant = detecter_gagnant(*joueur_selectionne, *autre_joueur);
        if(gagnant != NULL)
            printf("'%s' gagne la partie !", gagnant -> nom);
        else
            printf("Match nul, vous avez fait le même nombre de points !\n");
    }

    //Nettoyage de fin de partie.
    liste_vider(deck);

    joueur_detruire(joueur_selectionne);
    joueur_detruire(autre_joueur);
    *joueur_selectionne = joueur_init(0);
    *autre_joueur = joueur_init(0);
}
