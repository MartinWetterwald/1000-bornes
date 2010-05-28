/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : ia.h                         *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
*******************************************************/

#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/* Gestion des dépendances :
ia requiert la couche jeu */
#include "jeu.h"

void ia_archi_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_debutant(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_course(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_agressif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_defensif(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);
void ia_expert(Tptjoueur ordinateur, Tptjoueur humain, int* choix_carte, int* choix_jeter);

#endif // IA_H_INCLUDED
