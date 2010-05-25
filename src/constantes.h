/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : constantes.h           *
* DESCRIPTION : Définit en un seul endroit       *
* toutes les constantes du jeu.                  *
*                                                *
*************************************************/

#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define LINUX //À commenter si on compile pour Windows

#define DEBUG_IA   0

/* Jeu */
#define BORNES_MAX 1000

/* Erreurs */
#define ERREUR_CARTE_PAS_DANS_MAIN  -2
#define ERREUR_COUP_NON_PERMIS      -3

/* Joueurs */
#define HUMAIN      0
#define ORDINATEUR  1

/* Difficulté de l'ordinateur */
#define PAS_DE_DIFFICULTE   -1
#define ARCHI_DEBUTANT      1
#define DEBUTANT            2
#define COURSE              3
#define AGRESSIF            4
#define DEFENSIF            5
#define EXPERT              6


/* Points */
#define POINTS_PAR_BOTTE                        100
#define POINTS_TOUS_LES_BOTTES                  300
#define POINTS_PAR_COUP_FOURRE                  300
#define POINTS_SI_BORNES_MAX_EFFECTUEES         400
#define POINTS_COURONNEMENT                     300
#define POINTS_SI_AUCUNE_CARTE_200BORNES_JOUEE  300
#define POINTS_SI_CAPOT                         500


/* Chaines de caractères */
#define NOM_TAILLE_MAX      50 //Ceci correspond à la taille maximum pour le nom d'un joueur
#define TAILLE_MAX_REFUS    200 //Taille maximum du refus signifié par la fonction 'coup_autorise' de jeu.c
#define TAILLE_MAX_LIGNE        10000
#define TAILLE_MAX_NOM_FICHIER  50
#define CARTE_NOM_MAX       30


/* Cartes */
#define CARTES_TOTAL        106
#define CARTES_MAIN         6
#define CARTES_MAIN_MAX     CARTES_MAIN+1
#define CARTES_DIFFERENTES  19

#define MELANGER_MIN        1000
#define MELANGER_MAX        10000



/* Définition des cartes */
//Obstacles
#define PANNE_ESSENCE       1
#define CREVE               2
#define ACCIDENT            3
#define LIMITE_VITESSE      4
#define STOP                5

//Parades
#define ESSENCE             10
#define ROUE_DE_SECOURS     11
#define REPARATIONS         12
#define FIN_LIMITE_VITESSE  13
#define ROULEZ              14

//Bottes
#define CITERNE             20
#define INCREVABLE          21
#define AS_DU_VOLANT        22
#define PRIORITAIRE         23

//Bornes
#define BORNES25            25
#define BORNES50            50
#define BORNES75            75
#define BORNES100           100
#define BORNES200           200

//Autres choix possibles (qui ne sont pas des cartes)
#define PASSER_SON_TOUR             6
#define ENREGISTRER                 7
#define ANNULER_PASSER_SON_TOUR     8
#define ARRETER_PARTIE              9

#define CONFIRMER_QUITTER_PARTIE 1
#define INFIRMER_QUITTER_PARTIE 2

/* Nombre de chacune de ces cartes dans le jeu */
//Obstacles
#define NB_PANNE_ESSENCE       3
#define NB_CREVE               3
#define NB_ACCIDENT            3
#define NB_LIMITE_VITESSE      4
#define NB_STOP                5
#define NB_OBSTACLES (NB_PANNE_ESSENCE + NB_CREVE + NB_ACCIDENT + NB_LIMITE_VITESSE + NB_STOP)

//Parades
#define NB_ESSENCE             6
#define NB_ROUE_DE_SECOURS     6
#define NB_REPARATIONS         6
#define NB_FIN_LIMITE_VITESSE  6
#define NB_ROULEZ              14
#define NB_PARADES (NB_ESSENCE + NB_ROUE_DE_SECOURS + NB_REPARATIONS + NB_FIN_LIMITE_VITESSE + NB_ROULEZ)

//Bottes
#define NB_CITERNE             1
#define NB_INCREVABLE          1
#define NB_AS_DU_VOLANT        1
#define NB_PRIORITAIRE         1
#define NB_BOTTES (NB_CITERNE + NB_INCREVABLE + NB_AS_DU_VOLANT + NB_PRIORITAIRE)

//Bornes
#define NB_BORNES25            10
#define NB_BORNES50            10
#define NB_BORNES75            10
#define NB_BORNES100           12
#define NB_BORNES200           4
#define NB_BORNES (NB_BORNES25 + NB_BORNES50 + NB_BORNES75 + NB_BORNES100 + NB_BORNES200)


#endif // CONSTANTES_H_INCLUDED
