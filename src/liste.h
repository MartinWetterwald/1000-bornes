/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : liste.h                      *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
*******************************************************/

#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

typedef struct _maillon {
    int valeur;
    struct _maillon* suivant;
} Tmaillon, *Tptmaillon;

typedef struct _liste {
    Tptmaillon premier;
    Tptmaillon dernier;
    int taille;
} Tliste, *Tptliste;

Tptliste liste_init();
Tptmaillon maillon_nouveau(int val);
Tptmaillon liste_maillon_inserer_tete(Tptliste maListe, int val);
Tptmaillon liste_maillon_inserer_queue(Tptliste maListe, int val);
int liste_maillon_supprimer(Tptliste maListe, Tptmaillon aSupprimer);
void liste_remplir_fictif(Tptliste maListe, int max);
void liste_afficher(Tptliste maListe);
int liste_compter_valeur(Tptliste maListe, int val);
Tptmaillon liste_maillon_pos2point(Tptliste maListe, int num);
Tptmaillon liste_rechercher_maillon(Tptliste maListe, int val);
int liste_maillon_substituer(Tptliste maListe, Tptmaillon maillon1, Tptmaillon maillon2);
void liste_melanger(Tptliste maListe, int min, int max);
int liste_maillon_valeur_aleatoire(Tptliste maListe);
void liste_vider(Tptliste maListe);
void liste_detruire(Tptliste maListe);

#endif // LISTE_H_INCLUDED
