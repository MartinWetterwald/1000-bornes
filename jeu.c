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
#include <string.h>
#include <unistd.h>
#include "constantes.h"
#include "divers.h"
#include "menu.h"
#include "jeu.h"
#include "ia.h"

Tptpartie partie_init()
{
    Tptpartie partie = malloc(sizeof(Tpartie));
    partie -> deck = NULL;
    partie -> joueur_selectionne = NULL;
    partie -> autre_joueur = NULL;
    return partie;
}

Tptjoueur qui_commence(Tptjoueur joueur1, Tptjoueur joueur2)
{
    Tptjoueur joueur_qui_commence = NULL;
    int qui_commence;

    qui_commence = (rand() % 2) + 1;

    if(qui_commence == 1)
        joueur_qui_commence = joueur1;
    else if(qui_commence == 2)
        joueur_qui_commence = joueur2;

    return joueur_qui_commence;
}

//Fonction appelée en cas de nouvelle partie
void jeu_init(Tptpartie partie, Tptdeck deck, Tptjoueur joueur1, Tptjoueur joueur2)
{
    Tptjoueur joueur_selectionne;
    Tptjoueur autre_joueur;

    if(!joueur1 -> est_ordinateur)
        menu_demander_nom_joueur(joueur1 -> nom, 1);

    if(!joueur2 -> est_ordinateur)
        menu_demander_nom_joueur(joueur2 -> nom, 2);

    cartes_deck_init(deck);
    cartes_distribuer(deck, joueur1 -> deck, joueur2 -> deck, CARTES_MAIN);
    printf("\nLe jeu a été mélangé et les cartes ont été distribuées. ");

    //On choisit aléatoirement lequel des deux joueurs va commencer.
    joueur_selectionne = qui_commence(joueur1, joueur2);

    if(joueur_selectionne == joueur1)
        autre_joueur = joueur2;
    else
        autre_joueur = joueur1;

    partie -> deck = deck;
    partie -> joueur_selectionne = joueur_selectionne;
    partie -> autre_joueur = autre_joueur;

    printf("Le tirage au sort a décidé que '%s' commence la partie.\n", partie -> joueur_selectionne -> nom);
    demander_appuyez_sur_une_touche_pour_continuer();
}

//Cette fonction sert à inverser le joueur qui va devoir jouer.
void switch_tour(Tptpartie partie)
{
    Tptjoueur temp = partie -> joueur_selectionne;

    partie -> joueur_selectionne = partie -> autre_joueur;
    partie -> autre_joueur = temp;
}

Tptjoueur detecter_gagnant(Tptjoueur joueur1, Tptjoueur joueur2)
{
    int points_joueur1;
    int points_joueur2;

    printf("Détail des points de '%s' : \n", joueur1 -> nom);
    points_joueur1 = joueur_compter_les_points(joueur1, joueur2 -> cumul_bornes);

    printf("\nDétail des points de '%s' : \n", joueur2 -> nom);
    points_joueur2 = joueur_compter_les_points(joueur2, joueur1 -> cumul_bornes);

    printf("\n'%s' a effectué un total de %d points.\n", joueur1 -> nom, points_joueur1);
    printf("'%s' a effectué un total de %d points.\n", joueur2 -> nom, points_joueur2);

    if(points_joueur1 > points_joueur2)
        return joueur1;
    else if(points_joueur2 > points_joueur1)
        return joueur2;
    else
        return NULL;
}

int partie_terminee(Tptpartie partie)
{
    return (
            partie -> deck -> taille == 0 ||
            partie -> joueur_selectionne -> cumul_bornes >= BORNES_MAX ||
            partie -> autre_joueur -> cumul_bornes >= BORNES_MAX
            );
}

//Cette fonction vérifie qu'un joueur a le droit de jouer une carte
int coup_autorise(char* raison_refus, char* raison_refus2, Tptjoueur joueur_selectionne, Tptjoueur autre_joueur, int carte_type)
{
    /* Aucune condition n'est commentée, cela est volontaire.
    En effet, les sprintf sont très explicites et expliquent chaque condition. */

    /* Carte ROULEZ (feu vert) */
    if(carte_type == ROULEZ)
    {
        if(joueur_selectionne -> est_creve)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Roulez' alors que vous avez les pneus crevés...\n");
            sprintf(raison_refus2, "Jouez une carte 'Roue de secours' et vous pourrez à nouveau rouler !\n");
            return 0;
        }
        if(joueur_selectionne -> a_accident)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Roulez' mais vous avez un accident...\n");
            sprintf(raison_refus2, "Jouez une carte 'Réparations' et vous pourrez à nouveau rouler !\n");
            return 0;
        }
        if(joueur_selectionne -> en_panne_dessence)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Roulez' mais vous n'avez plus d'essence...\n");
            sprintf(raison_refus2, "Jouez une carte 'Essence', et vous pourrez à nouveau rouler !\n");
            return 0;
        }
    }


    /* Obstacles */
    if(carte_type >= PANNE_ESSENCE && carte_type <= STOP)
    {
        if(carte_type != LIMITE_VITESSE && autre_joueur -> est_arrete)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte obstacle, alors que votre adversaire est à l'arrêt...\n");
            return 0;
        }

        //Panne d'essence
        if(carte_type == PANNE_ESSENCE)
        {
            if(autre_joueur -> est_creve || autre_joueur -> a_accident)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Panne d'essence', alors que votre adversaire a les pneus crevés ou a un accident...\n");
                return 0;
            }
            if(autre_joueur -> en_panne_dessence)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Panne d'essence', alors que votre adversaire est déjà en panne d'essence...\n");
                return 0;
            }
            if(autre_joueur -> citerne)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Panne d'essence', alors que votre adversaire est protégé par une carte botte 'Citerne'...\n");
                return 0;
            }
        }

        //Crevé
        if(carte_type == CREVE)
        {
            if(autre_joueur -> en_panne_dessence || autre_joueur -> a_accident)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Crevé', alors que votre adversaire est en panne d'essence ou a un accident...\n");
                return 0;
            }
            if(autre_joueur -> est_creve)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Crevé', alors que votre adversaire a déjà les pneus crevées...\n");
                return 0;
            }
            if(autre_joueur -> increvable)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Crevé', alors que votre adversaire est protégé par une carte botte 'Increvable'...\n");
                return 0;
            }
        }

        //Accident
        if(carte_type == ACCIDENT)
        {
            if(autre_joueur -> en_panne_dessence || autre_joueur -> est_creve)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Accident', alors que votre adversaire est en panne d'essence ou a les pneus crevés...\n");
                return 0;
            }
            if(autre_joueur -> a_accident)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Accident', alors que votre adversaire a déjà un accident...\n");
                return 0;
            }
            if(autre_joueur -> as_du_volant)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Accident', alors que votre adversaire est protégé par une carte botte 'As du volant'...\n");
                return 0;
            }
        }

        //Limite de vitesse
        if(carte_type == LIMITE_VITESSE)
        {
            if(autre_joueur -> est_limite_par_vitesse)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Limite de vitesse', alors que la vitesse de votre adversaire est déjà limitée...\n");
                return 0;
            }
            if(autre_joueur -> prioritaire)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Limite de vitesse', alors que votre adversaire est protégé par une carte botte 'Prioritaire'...\n");
                return 0;
            }
        }

        //Stop
        if(carte_type == STOP)
        {
            if(autre_joueur -> est_arrete)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Stop', alors que votre adversaire est déjà à l'arrêt...\n");
                return 0;
            }
            if(autre_joueur -> prioritaire)
            {
                sprintf(raison_refus, "Vous voulez jouer une carte 'Stop', alors que votre adversaire est protégé par une carte botte 'Prioritaire'...\n");
                return 0;
            }
        }
    }

    /* Parades */
    if(carte_type >= ESSENCE && carte_type <= ROULEZ)
    {
        //Essence
        if(carte_type == ESSENCE && !(joueur_selectionne -> en_panne_dessence))
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Essence' alors que vous n'êtes pas en panne d'essence...\n");
            return 0;
        }

        //Roue de secours
        if(carte_type == ROUE_DE_SECOURS && !(joueur_selectionne -> est_creve))
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Roue de secours' alors que vos pneus ne sont pas crevés...\n");
            return 0;
        }

        //Réparations
        if(carte_type == REPARATIONS && !(joueur_selectionne -> a_accident))
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Réparations' alors que vous n'avez pas d'accident...\n");
            return 0;
        }

        //Fin de limite de vitesse
        if(carte_type == FIN_LIMITE_VITESSE && !(joueur_selectionne -> est_limite_par_vitesse))
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Fin de limitation de vitesse' alors que votre vitesse n'est pas limitée...\n");
            return 0;
        }

        //Roulez (feu vert)
        if(carte_type == ROULEZ && !(joueur_selectionne -> est_arrete))
        {
            sprintf(raison_refus, "Vous voulez jouer une carte 'Roulez' alors que vous êtes déjà en train de rouler...\n");
            return 0;
        }
    }

    /* Bornes */
    if(carte_type >= BORNES25 && carte_type <= BORNES200)
    {
        if(joueur_selectionne -> est_creve)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte de distance pour avancer alors que vos pneus sont crevés...\n");
            sprintf(raison_refus2, "Vous devez d'abord jouer une carte 'Roue de secours' !\n");
            return 0;
        }

        if(joueur_selectionne -> a_accident)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte de distance pour avancer alors que vous avez un accident...\n");
            sprintf(raison_refus2, "Vous devez d'abord jouer une carte 'Réparations' !\n");
            return 0;
        }

        if(joueur_selectionne -> en_panne_dessence)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte de distance pour avancer alors que vous êtes en panne d'essence...\n");
            sprintf(raison_refus2, "Vous devez d'abord jouer une carte 'Essence' !\n");
            return 0;
        }

        if(joueur_selectionne -> est_arrete)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte de distance alors que vous êtes à l'arrêt (feu rouge)...\n");
            sprintf(raison_refus2, "Vous devez d'abord jouer une carte 'Roulez' (feu vert) !\n");
            return 0;
        }

        if(joueur_selectionne -> est_limite_par_vitesse && carte_type >= BORNES75)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte de distance supérieure à 50 bornes pour avancer alors que votre vitesse est limitée à 50 bornes/h...\n");
            sprintf(raison_refus2, "Vous devez d'abord jouer une carte 'Fin de limitation de vitesse' si vous voulez jouer des cartes de distance supérieures à 50 bornes. !\n");
            return 0;
        }

        if(carte_type == BORNES200 && joueur_selectionne -> nb_200bornes_jouees == 2)
        {
            sprintf(raison_refus, "Vous voulez jouer une carte '200 bornes' alors que vous en avez déjà joué deux depuis le début de la partie, et c'est le maximum autorisé...\n");
            return 0;
        }

        if( ((joueur_selectionne -> cumul_bornes) + carte_type) > BORNES_MAX )
        {
            sprintf(raison_refus, "Vous n'avez pas le droit de parcourir plus que %d bornes, vous n'avez que le droit d'atteindre cette distance exactement...\n", BORNES_MAX);
            return 0;
        }
    }

    return 1;
}


//Cette fonction retourne un nouveau deck de cartes, qui contient les cartes jouables.
//Elle est utilisée, afin de simplifier la tâche des joueurs et des ordinateurs.
//Du coup pour un ordinateur on n'aura plus qu'à lui faire choisir parmi les coups qu'il a le droit de jouer.
Tptdeck lister_coups_possibles(Tptjoueur joueur_selectionne, Tptjoueur autre_joueur)
{
    char raison_refus[TAILLE_MAX_REFUS] = "";
    char raison_refus2[TAILLE_MAX_REFUS] = "";
    int coup_est_autorise = 0;
    Tptdeck coupsPossibles = liste_init();
    Tptcarte carte_courante = NULL;


    //Pour chaque carte contenue dans le deck de l'ordinateur, on va la faire passer dans la fonction
    //coup_autorise. Si cette fonction renvoie 1, on copie la carte dans le nouveau deck des coups autorisés.
    if(joueur_selectionne -> deck != NULL)
    {
        carte_courante = joueur_selectionne -> deck -> premier;
        while(carte_courante != NULL)
        {
            coup_est_autorise = coup_autorise(raison_refus, raison_refus2, joueur_selectionne, autre_joueur, carte_courante -> valeur);
            if(coup_est_autorise)
                liste_maillon_inserer_tete(coupsPossibles, carte_courante -> valeur);

            carte_courante = carte_courante -> suivant;
        }
    }
    return coupsPossibles;
}

//Cette fonction est appelée s'il y a coup fourré.
void coup_fourre(Tptpartie partie, int obstacle, int botte, char* raison_refus, char* raison_refus2)
{
    Tptcarte carte_piochee = NULL;

    partie -> autre_joueur -> nb_coups_fourres_joues++;

    printf("\n\nCOUP FOURRÉ !\n");
    printf("'%s', vous venez de jouer une carte '", partie -> joueur_selectionne -> nom);
    cartes_type2francais(obstacle);
    printf("', mais '%s' détient la carte botte '", partie -> autre_joueur -> nom);
    cartes_type2francais(botte);
    printf("' dans son jeu et il se trouve qu'il a déclaré « coup fourré ».\n");

    printf(" Votre coup n'a donc aucun effet. ");
    printf("'%s' joue sa carte '", partie -> autre_joueur -> nom);
    cartes_type2francais(botte);
    printf("', il a donc cinq cartes et va en piocher deux.\n");

    //On fait jouer à l'adversaire sa carte botte.
    if(jouer(partie, botte, 0, raison_refus, raison_refus2) != 1)
        printf("Erreur à la fonction jouer pour le coup fourré. :/\n");

    //On fait piocher une carte à l'adversaire, pour qu'il ait à nouveau six cartes
    if(partie -> autre_joueur -> deck  -> taille > 0)
    {
        carte_piochee = cartes_changer_deck(partie -> deck, partie -> deck -> premier, partie -> autre_joueur -> deck);

        printf("Votre adversaire '%s' vient de piocher une carte '", partie -> autre_joueur -> nom);
        cartes_type2francais(carte_piochee -> valeur); //On affiche le nom de la carte en français
        printf("'.\n\n");
    }
}

//Cette fonction permet à un joueur de jouer une carte (un tour de jeu)
int jouer(Tptpartie partie,  int carte_type, int passe_son_tour, char* raison_refus, char* raison_refus2)
{
    Tptcarte carte_a_jouer = NULL;

    //Vérification que le joueur a cette carte et récupération de son adresse.
    carte_a_jouer = joueur_possede_carte(partie -> joueur_selectionne, carte_type);
    if(carte_a_jouer != NULL)
    {
        if(passe_son_tour)
        {
            //Supprimer la carte du deck
            liste_maillon_supprimer(partie -> joueur_selectionne -> deck, carte_a_jouer);
            return 1;
        }
        else
        {
            //Vérifier que le coup est permis
            if(coup_autorise(raison_refus, raison_refus2, partie -> joueur_selectionne, partie -> autre_joueur, carte_type))
            {
                //Appliquer les conséquences de la carte jouée
                consequences_coup(partie, carte_type);

                //Supprimer la carte du deck
                liste_maillon_supprimer(partie -> joueur_selectionne -> deck, carte_a_jouer);

                return 1;
            }
            return ERREUR_COUP_NON_PERMIS;
        }
    }
    return ERREUR_CARTE_PAS_DANS_MAIN;
}

//Cette fonction modifie l'état des joueurs en fonction de la carte jouée.
void consequences_coup(Tptpartie partie, int carte_type)
{
    switch(carte_type)
    {
        //Obstacles
        case PANNE_ESSENCE:
            partie -> autre_joueur -> en_panne_dessence = 1;
            if(!partie -> autre_joueur -> prioritaire)
                partie -> autre_joueur -> est_arrete = 1;
        break;

        case CREVE:
            partie -> autre_joueur -> est_creve = 1;
            if(!partie -> autre_joueur -> prioritaire)
                partie -> autre_joueur -> est_arrete = 1;
        break;

        case ACCIDENT:
            partie -> autre_joueur -> a_accident = 1;
            if(!partie -> autre_joueur -> prioritaire)
                partie -> autre_joueur -> est_arrete = 1;
        break;

        case LIMITE_VITESSE:
            if(!partie -> autre_joueur -> prioritaire)
                partie -> autre_joueur -> est_limite_par_vitesse = 1;
        break;

        case STOP:
            if(!partie -> autre_joueur -> prioritaire)
                partie -> autre_joueur -> est_arrete = 1;
        break;

        //Parades
        case ESSENCE:
            partie -> joueur_selectionne -> en_panne_dessence = 0;
        break;

        case ROUE_DE_SECOURS:
            partie -> joueur_selectionne -> est_creve = 0;
        break;

        case REPARATIONS:
            partie -> joueur_selectionne -> a_accident = 0;
        break;

        case FIN_LIMITE_VITESSE:
            partie -> joueur_selectionne -> est_limite_par_vitesse = 0;
        break;

        case ROULEZ:
            partie -> joueur_selectionne -> est_arrete = 0;
        break;

        //Bottes
        case CITERNE:
            partie -> joueur_selectionne -> citerne = 1;
            partie -> joueur_selectionne -> en_panne_dessence = 0;
            partie -> joueur_selectionne -> nb_bottes_jouees++;
        break;

        case INCREVABLE:
            partie -> joueur_selectionne -> increvable = 1;
            partie -> joueur_selectionne -> est_creve = 0;
            partie -> joueur_selectionne -> nb_bottes_jouees++;
        break;

        case AS_DU_VOLANT:
            partie -> joueur_selectionne -> as_du_volant = 1;
            partie -> joueur_selectionne -> a_accident = 0;
            partie -> joueur_selectionne -> nb_bottes_jouees++;
        break;

        case PRIORITAIRE:
            partie -> joueur_selectionne -> prioritaire = 1;
            partie -> joueur_selectionne -> est_limite_par_vitesse = 0;
            partie -> joueur_selectionne -> est_arrete = 0;
            partie -> joueur_selectionne -> nb_bottes_jouees++;
        break;

        //Bornes
        case BORNES25:
            partie -> joueur_selectionne -> cumul_bornes += 25;
        break;

        case BORNES50:
            partie -> joueur_selectionne -> cumul_bornes += 50;
        break;

        case BORNES75:
            partie -> joueur_selectionne -> cumul_bornes += 75;
        break;

        case BORNES100:
            partie -> joueur_selectionne -> cumul_bornes += 100;
        break;

        case BORNES200:
            partie -> joueur_selectionne -> cumul_bornes += 200;
            partie -> joueur_selectionne -> nb_200bornes_jouees++;
        break;

        default:
            printf("ERREUR.");
            exit(0);
    }

    //Si on effectue un couronnement
    if(partie -> deck -> taille == 0 && partie -> joueur_selectionne -> cumul_bornes == BORNES_MAX)
        partie -> joueur_selectionne -> couronnement = 1;
}

//Cette fonction est la fonction globale qui gère une partie (reprise en cours ou nouvellement commencée).
//Grâce aux paramètres joueur_selectionne et autre_joueur, on sait à qui c'est de jouer.
void jeu(Tptpartie partie)
{
    int partie_est_terminee = partie_terminee(partie);
    int choix_carte = -1, choix_jeter = -1;
    int resultat_jouer = -1, resultat_jouer_passer_tour = -1;

    char nomFichier[TAILLE_MAX_NOM_FICHIER];
    char raison_refus[TAILLE_MAX_REFUS] = "";
    char raison_refus2[TAILLE_MAX_REFUS] = "";

    Tptjoueur gagnant = NULL;
    Tptcarte carte_piochee = NULL;

    Tptdeck les_coups_possibles = NULL;

    while(!partie_est_terminee && choix_carte != ARRETER_PARTIE && choix_carte != ENREGISTRER)
    {
        choix_carte = -1;
        choix_jeter = -1;
        printf("\nIl reste %d cartes dans le deck principal.\n", partie -> deck -> taille);

        printf("\nC'est à '%s' de jouer.\n", partie -> joueur_selectionne -> nom);

        if(partie -> deck -> taille > 0)
        {
            //On fait piocher une carte au joueur
            carte_piochee = cartes_changer_deck(partie -> deck, partie -> deck -> premier, partie -> joueur_selectionne -> deck);

            //On affiche la carte que le joueur vient de piocher que si ça n'est pas un ordinateur
            if(!(partie -> joueur_selectionne -> est_ordinateur))
            {
                printf("'%s' vient de piocher une carte '", partie -> joueur_selectionne -> nom);
                cartes_type2francais(carte_piochee -> valeur); //On affiche le nom de la carte en français
                printf("'.\n");
                demander_appuyez_sur_une_touche_pour_continuer();
            }
            else
            {
                printf("'%s' vient de piocher une carte.\n", partie -> joueur_selectionne -> nom);
            }
        }

        //On n'affiche les infos que si le joueur n'est pas un ordinateur.
        if(!(partie -> joueur_selectionne -> est_ordinateur))
        {
            printf("\n\nÉTAT DE VOTRE ADVERSAIRE :");
            joueur_afficher_infos_utiles(partie -> autre_joueur);

            printf("\n\nVOTRE ÉTAT :");
            joueur_afficher_infos_utiles(partie -> joueur_selectionne);
            demander_appuyez_sur_une_touche_pour_continuer();

            //Affiche la main du joueur
            printf("\n\nVOTRE MAIN :\n");
            printf("Vous avez %d cartes en main : \n", partie -> joueur_selectionne -> deck -> taille);
            cartes_deck_afficher(partie -> joueur_selectionne -> deck);

            printf("\n");
            demander_appuyez_sur_une_touche_pour_continuer();

            les_coups_possibles = lister_coups_possibles(partie -> joueur_selectionne, partie -> autre_joueur);
            printf("Voici les coups possibles pour ce tour : \n");
            printf("Il y a %d coups possibles :\n", les_coups_possibles -> taille);
            cartes_deck_afficher(les_coups_possibles);

            printf("\n");
        }

        //Demande au joueur de choisir une carte à jouer (si c'est un humain seulement)
        if(!(partie -> joueur_selectionne -> est_ordinateur))
        {
            resultat_jouer = -1;

            //S'il n'est pas possible de jouer une carte, on force l'utilisateur à en jeter une.
            if(les_coups_possibles -> taille == 0)
                choix_carte = PASSER_SON_TOUR;

            while(resultat_jouer != 1)
            {
                if(les_coups_possibles -> taille > 0)
                    menu_demander_choix_carte(&choix_carte);

                if(choix_carte != ARRETER_PARTIE && choix_carte != ENREGISTRER)
                {
                    if(choix_carte != PASSER_SON_TOUR)
                    {
                        //Appel de la fonction jouer
                        resultat_jouer = jouer(partie, choix_carte, 0, raison_refus, raison_refus2);
                        switch(resultat_jouer)
                        {
                            case ERREUR_COUP_NON_PERMIS:
                                printf("\nCe coup n'est pas permis ! Voici une explication : \n\n");
                                if(strlen(raison_refus) > 0)
                                {
                                    printf("%s", raison_refus);

                                    if(strlen(raison_refus2) > 0)
                                        printf("%s", raison_refus2);
                                }

                                sprintf(raison_refus, "");
                                sprintf(raison_refus2, "");

                                printf("\n\nVeuillez choisir une autre carte.\n\n");
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
                            menu_demander_choix_carte_jeter(&choix_jeter, les_coups_possibles -> taille);
                            if(choix_jeter != ANNULER_PASSER_SON_TOUR)
                            {
                                resultat_jouer_passer_tour = jouer(partie, choix_jeter, 1, raison_refus, raison_refus2);
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
                            printf("'%s' passe son tour et jette une carte.\n", partie -> joueur_selectionne -> nom);
                            resultat_jouer = 1;
                            //cartes_deck_afficher(partie -> joueur_selectionne -> deck);
                        }
                        else if(les_coups_possibles -> taille > 0)
                        {
                            choix_jeter = -1;
                            printf("\nVous avez changé d'avis et ne souhaitez plus passer votre tour.\n");
                            printf("Vous allez être réinvité à sélectionner la carte que vous désirez jouer.\n\n");
                        }
                    }
                }
                else
                    resultat_jouer = 1;
            }
        }
        //C'est un ordinateur, on demande à l'IA de jouer
        else
        {
            switch(partie -> joueur_selectionne -> difficulte_ordinateur)
            {
                case ARCHI_DEBUTANT:
                    ia_archi_debutant(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                case DEBUTANT:
                    ia_debutant(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                case COURSE:
                    ia_course(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                case AGRESSIF:
                    ia_agressif(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                case DEFENSIF:
                    ia_defensif(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                case EXPERT:
                    ia_expert(partie -> joueur_selectionne, partie -> autre_joueur, &choix_carte, &choix_jeter);
                break;

                default:
                    printf("Erreur, la difficulté de l'IA est invalide (jeu.c).");
                    exit(0);
            }

            /* Le choix de la carte a été fait par l'ordinateur. On joue sa carte. */
            if(choix_carte == PASSER_SON_TOUR)
            {
                resultat_jouer = jouer(partie, choix_jeter, 1, raison_refus, raison_refus2);
                printf("\n'%s' passe son tour et jette une carte.\n", partie -> joueur_selectionne -> nom);
                if(DEBUG_IA)
                {
                    printf("La carte qu'il vient de JETER est : '");
                    cartes_type2francais(choix_jeter);
                    printf("'.\n");
                }
                demander_appuyez_sur_une_touche_pour_continuer();
            }
            else
                resultat_jouer = jouer(partie, choix_carte, 0, raison_refus, raison_refus2);

            if(resultat_jouer != 1)
            {
                printf("Erreur : l'ordinateur a choisi une carte qui n'est pas valide.\n");
                printf("Code de l'erreur : %d. ", resultat_jouer);
                printf("L'ordinateur avait essayé de jouer : '");
                cartes_type2francais(choix_carte);
                printf(" %d", choix_carte);
                printf("'.\n");
                exit(0);
            }
        }


        if(     choix_carte != ENREGISTRER && choix_carte != ARRETER_PARTIE
                && choix_jeter != ANNULER_PASSER_SON_TOUR && resultat_jouer == 1)
        {
            if(choix_carte != PASSER_SON_TOUR)
            {
                printf("\n'%s' vient de jouer une carte '", partie -> joueur_selectionne -> nom);
                cartes_type2francais(choix_carte);
                printf("'.\n");
                demander_appuyez_sur_une_touche_pour_continuer();
            }

            //« Y a-t-il coup fourré ? »
            if(     choix_carte == PANNE_ESSENCE &&
                    partie -> autre_joueur -> en_panne_dessence &&
                    joueur_possede_carte(partie -> autre_joueur, CITERNE) != NULL)
            {
                menu_demander_coup_fourre(partie, PANNE_ESSENCE, CITERNE, raison_refus, raison_refus2);
            }
            else if(choix_carte == CREVE &&
                    partie -> autre_joueur -> est_creve &&
                    joueur_possede_carte(partie -> autre_joueur, INCREVABLE) != NULL)
            {
                menu_demander_coup_fourre(partie, CREVE, INCREVABLE, raison_refus, raison_refus2);
            }
            else if(choix_carte == ACCIDENT &&
                partie -> autre_joueur -> a_accident &&
                    joueur_possede_carte(partie -> autre_joueur, AS_DU_VOLANT) != NULL)
            {
                menu_demander_coup_fourre(partie, ACCIDENT, AS_DU_VOLANT, raison_refus, raison_refus2);
            }
            else if(choix_carte == LIMITE_VITESSE &&
                    partie -> autre_joueur -> est_limite_par_vitesse &&
                joueur_possede_carte(partie -> autre_joueur, PRIORITAIRE) != NULL)
            {
                menu_demander_coup_fourre(partie, LIMITE_VITESSE, PRIORITAIRE, raison_refus, raison_refus2);
            }
            else if(choix_carte == STOP &&
                    partie -> autre_joueur -> est_arrete &&
                    joueur_possede_carte(partie -> autre_joueur, PRIORITAIRE) != NULL)
            {
                menu_demander_coup_fourre(partie, STOP, PRIORITAIRE, raison_refus, raison_refus2);
            }

            /* Si le joueur vient de jouter une carte 'botte', il a le droit de rejouer
            Il ne faut donc pas switcher les joueurs dans ce cas */
            if(choix_carte >= CITERNE && choix_carte <= PRIORITAIRE)
                printf("\n'%s' vient de jouer une carte 'botte', c'est donc encore une fois à lui de jouer !\n", partie -> joueur_selectionne -> nom);
            else
                switch_tour(partie);

            partie_est_terminee = partie_terminee(partie);
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
        gagnant = detecter_gagnant(partie -> joueur_selectionne, partie -> autre_joueur);
        if(gagnant != NULL)
            printf("'%s' gagne la partie !", gagnant -> nom);
        else
            printf("Match nul, vous avez fait le même nombre de points !\n");
    }

    //Nettoyage de fin de partie.
    partie_vider(partie);
}

void partie_vider(Tptpartie partie)
{
    deck_vider(partie -> deck);
    joueur_detruire(partie -> joueur_selectionne);
    joueur_detruire(partie -> autre_joueur);

    partie -> joueur_selectionne = NULL;
    partie -> autre_joueur = NULL;
}
