/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : fichiers.h                   *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
*******************************************************/

#ifndef FICHIERS_H_INCLUDED
#define FICHIERS_H_INCLUDED

/* Gestion des dépendances :
La couche « fichiers » requiert la couche « jeu » */
#include "jeu.h"

int enregistrer_deck(FILE* fichier, Tptdeck deck);
int enregistrer_joueur(FILE* fichier, Tptjoueur joueur);
int enregistrer_partie(const char* nomFichier, Tptpartie partie);
int charger_deck(FILE* fichier, Tptdeck deck);
int charger_joueur(FILE* fichier, Tptjoueur joueur);
int charger_partie(const char* nomFichier, Tptpartie partie);

#endif // FICHIERS_H_INCLUDED
