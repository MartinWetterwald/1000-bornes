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
typedef Tliste Tdeck; typedef Tptliste Tptdeck;
typedef Tmaillon Tcarte;

void cartes_deck_add(Tdeck* deck, int carte_type, int carte_nb);
void cartes_deck_init(Tdeck* deck);
void cartes_deck_afficher(Tdeck* deck);
Tcarte* cartes_changer_deck(Tdeck* deck_source, Tcarte* carte_source, Tdeck* deck_cible);
void cartes_type2francais(int val);
void cartes_distribuer(Tdeck* deck, Tdeck* deck_joueur1, Tdeck* deck_joueur2, int nb);
int cartes_char2int(char* chaine);
int cartes_verifier_validite(int carte);
void deck_detruire(Tptdeck* deck);

#endif // CARTES_H_INCLUDED
