/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : liste.h                *
*                                                *
*************************************************/

#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

typedef struct _maillon {
    int valeur;
    struct _maillon* suivant;
} Tmaillon;

typedef struct _liste {
    Tmaillon* premier;
    Tmaillon* dernier;
    int taille;
} Tliste, *Tptliste;

Tliste* liste_init();
Tmaillon* maillon_nouveau(int val);
Tmaillon* liste_maillon_inserer_tete(Tliste* maListe, int val);
int liste_maillon_supprimer(Tliste* maListe, Tmaillon* aSupprimer);
void liste_remplir_fictif(Tliste* maListe, int max);
void liste_afficher(Tliste* maListe);
int liste_compter_valeur(Tliste* maListe, int val);
Tmaillon* liste_maillon_pos2point(Tliste* maListe, int num);
Tmaillon* liste_rechercher_maillon(Tliste* maListe, int val);
int liste_maillon_substituer(Tliste* maListe, Tmaillon* maillon1, Tmaillon* maillon2);
void liste_melanger(Tliste* maListe, int min, int max);
void liste_vider(Tliste* maListe);
void liste_detruire(Tptliste* maListe);

#endif // LISTE_H_INCLUDED
