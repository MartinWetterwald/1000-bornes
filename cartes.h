/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION :                                  *
*                                                *
*************************************************/

#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

/* Gestion des dépendances :
La couche « cartes » requiert la couche inférieure : liste */
#include "liste.h"

/* Pour simplifier la compréhension
et respecter l'étanchéité des différentes couches du programme,
on oublie la notion de liste chainée. On parlera dans cette couche de decks de cartes. */
typedef Tliste Tdeck;
typedef Tptliste Tptdeck;

typedef Tmaillon Tcarte;
typedef Tptmaillon Tptcarte;

void cartes_deck_add(Tptdeck deck, int carte_type, int carte_nb);
void cartes_deck_init(Tptdeck deck);
void cartes_deck_compter_sorte
(
    Tptdeck deck,
    int* nb_panne_essence, int* nb_creve, int* nb_accident, int* nb_limite_vitesse, int* nb_stop,
    int* nb_essence, int* nb_roue_de_secours, int* nb_reparations, int* nb_fin_limite_vitesse, int* nb_roulez,
    int* nb_citerne, int* nb_increvable, int* nb_as_du_volant, int* nb_prioritaire,
    int* nb_bornes25, int* nb_bornes50, int* nb_bornes75, int* nb_bornes100, int* nb_bornes200,
    int* nb_obstacles, int* nb_parades, int* nb_bottes, int* nb_bornes
);
void cartes_deck_afficher(Tptdeck deck);
Tptcarte cartes_changer_deck(Tptdeck deck_source, Tptcarte carte_source, Tptdeck deck_cible);
void cartes_type2francais(int val);
void cartes_distribuer(Tptdeck deck, Tptdeck deck_joueur1, Tptdeck deck_joueur2, int nb);
int cartes_char2int(char* chaine);
int cartes_verifier_validite(int carte);
int carte_aleatoire(Tptdeck deck);
void deck_vider(Tptdeck deck);
void deck_detruire(Tptdeck deck);

#endif // CARTES_H_INCLUDED
