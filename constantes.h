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

/* Jeu */
#define BORNES_MAX 700

/* Erreurs */
#define ERREUR_CARTE_PAS_DANS_MAIN -2
#define ERREUR_COUP_NON_PERMIS -3


/* Points */
#define POINTS_PAR_BOTTE 100
#define POINTS_TOUS_LES_BOTTES 300
#define POINTS_PAR_COUP_FOURRE 300
#define POINTS_SI_BORNES_MAX_EFFECTUEES 400
#define POINTS_COURONNEMENT 300
#define POINTS_SI_AUCUNE_CARTE_200BORNES_JOUEE 300
#define POINTS_SI_CAPOT 500


/* Joueurs */
#define NOM_TAILLE_MAX 50


/* Fichiers */
#define TAILLE_MAX_LIGNE 10000
#define TAILLE_MAX_NOM_FICHIER 50


/* Cartes */
#define CARTES_TOTAL        106
#define CARTES_MAIN         6
#define CARTES_MAIN_MAX     CARTES_MAIN+1
#define CARTES_DIFFERENTES  19

#define MELANGER_MIN        1000
#define MELANGER_MAX        10000

#define CARTE_NOM_MAX       30


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

//Botes
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
#define ARRETER_PARTIE      0
#define PASSER_SON_TOUR     6
#define ENREGISTRER         7
#define ANNULER_PASSER_SON_TOUR     8


/* Nombre de chacune de ces cartes dans le jeu */
//Obstacles
#define NB_PANNE_ESSENCE       3
#define NB_CREVE               3
#define NB_ACCIDENT            3
#define NB_LIMITE_VITESSE      4
#define NB_STOP                5

//Parades
#define NB_ESSENCE             6
#define NB_ROUE_DE_SECOURS     6
#define NB_REPARATIONS         6
#define NB_FIN_LIMITE_VITESSE  6
#define NB_ROULEZ              14

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



#endif // CONSTANTES_H_INCLUDED
