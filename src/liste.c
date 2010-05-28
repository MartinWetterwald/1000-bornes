/*******************************************************
*              JEU DES 1000 BORNES                     *
*                                                      *
* Réalisé par Nacim Messadi et Martin Wetterwald       *
*                                                      *
*               FICHIER : liste.c                      *
* DESCRIPTION : Fonctions gérant la couche des         *
* listes chainées.                                     *
*                                                      *
* Ce code est mis à disposition selon les termes       *
* de la licence Creative Commons BY-NC-SA.             *
* Le texte complet de la licence est disponible        *
* à l'adresse :                                        *
* http://creativecommons.org/licenses/by-nc-sa/2.0/fr/ *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "divers.h"
#include "liste.h"

//Fonction de création d'une liste chainée.
Tptliste liste_init()
{
    Tptliste maListe = malloc(sizeof(Tliste));
    maListe -> premier = NULL;
    maListe -> dernier = NULL;
    maListe -> taille = 0;
    return maListe;
}

//Fonction de création d'un nouveau maillon
Tptmaillon maillon_nouveau(int val)
{
    Tptmaillon nouveau;
    nouveau = malloc(sizeof(Tmaillon));
    nouveau -> suivant = NULL;
    nouveau -> valeur = val;
    return nouveau;
}

//Fonction qui permet d'insérer un maillon en tête de liste chainée.
Tptmaillon liste_maillon_inserer_tete(Tptliste maListe, int val)
{
    Tptmaillon nouveau = maillon_nouveau(val);
    nouveau -> suivant = maListe -> premier;

    maListe -> premier = nouveau;
    maListe -> taille = (maListe -> taille) + 1;

    if(maListe -> taille == 1)
    {
        maListe -> dernier = nouveau;
    }
    return nouveau;
}

//Fonction qui permet d'insérer un maillon en queue de liste chainée.
Tptmaillon liste_maillon_inserer_queue(Tptliste maListe, int val)
{
    Tptmaillon nouveau = maillon_nouveau(val);

    maListe -> taille++;

    if(maListe -> taille == 1)
        maListe -> premier = nouveau;
    else
        maListe -> dernier -> suivant = nouveau;

    maListe -> dernier = nouveau;

    return nouveau;
}

//Fonction qui permet de supprimer un maillon donné
int liste_maillon_supprimer(Tptliste maListe, Tptmaillon aSupprimer)
{
    Tptmaillon precedent;
    Tptmaillon parcours;
    int success = 0;

    //Y a-t-il quelque chose à faire ?
    if(maListe != NULL && maListe -> premier != NULL && aSupprimer != NULL)
    {
        precedent = maListe -> premier;
        parcours = maListe -> premier;

        //On avance jusqu'au maillon à supprimer, en n'oubliant pas de mémoriser celui juste avant.
        while(parcours != aSupprimer && parcours != NULL)
        {
            precedent = parcours;
            parcours = parcours -> suivant;
        }


        //Cas où on supprime en milieu de liste (ou bien le dernier élément)
        if(parcours != NULL && parcours != precedent)
        {
            precedent -> suivant = parcours -> suivant;

            //Si on supprime le dernier élément de la liste, il faut mettre à jour le champ dernier
            if(parcours == maListe -> dernier)
            {
                maListe -> dernier = precedent;
            }

            free(parcours);
            success = 1;
        }
        //Cas où on supprime le premier élément de la liste
        else if(parcours != NULL && parcours == precedent)
        {
            //S'il s'avère que le premier élément est aussi le dernier, il faut mettre les champs premier et dernier à NULL
            if(parcours == maListe -> dernier)
            {
                maListe -> premier = NULL;
                maListe -> dernier = NULL;
            }
            else
                maListe -> premier = parcours -> suivant;

            free(parcours);
            success = 1;
        }
        else
        {
            return success;
        }
        maListe -> taille = (maListe -> taille) - 1;
    }
    else
    {
        success = 1;
    }
    return success;
}

//Fonction servant à des fins de test : elle remplit une liste chainée avec des nombres de 1 à max.
void liste_remplir_fictif(Tptliste maListe, int max)
{
    int i;
    for(i = max; i >= 1; i--)
    {
        liste_maillon_inserer_tete(maListe, i);
    }
}

//Fonction qui affiche tous les entiers stockés dans la liste chainée
void liste_afficher(Tptliste maListe)
{
    //On initialise un pointeur parcours.
    Tptmaillon parcours = maListe->premier;

    printf("\n\nVoici le contenu de la liste chainée qui contient %d éléments :\n", maListe -> taille);
    while(parcours != NULL)
    {
        printf("%d -> ", parcours -> valeur);
        parcours = parcours -> suivant;
    }
    printf("NULL\n\n");
}

//Cette fonction recherche une valeur dans la liste chainée, et retourne combien de fois elle a été trouvée
int liste_compter_valeur(Tptliste maListe, int val)
{
    Tptmaillon parcours;
    int i = 0;

    //S'il y a quelque chose à faire
    if(maListe != NULL && maListe -> premier != NULL)
    {
        parcours = maListe -> premier;
        while(parcours != NULL)
        {
            if(parcours -> valeur == val)
                i++;

            parcours = parcours -> suivant;
        }
    }

    return i;
}

//Fonction qui prend pour paramètre la position d'un maillon dans une liste chainée, et qui renvoie un pointeur vers ce maillon.
Tptmaillon liste_maillon_pos2point(Tptliste maListe, int num)
{
    int i = 1;
    Tptmaillon parcours;
    if(maListe != NULL && maListe -> premier != NULL)
    {
        if(num >= 1 && num <= maListe -> taille)
        {
            if(num == 1)
                return maListe -> premier;
            else if(num == maListe -> taille)
                return maListe -> dernier;

            parcours = maListe -> premier;
            while(i < num)
            {
                parcours = parcours -> suivant;
                i++;
            }
            return parcours;
        }
    }
    return NULL;
}

Tptmaillon liste_rechercher_maillon(Tptliste maListe, int val)
{
    Tptmaillon parcours;
    if(maListe != NULL && maListe -> premier != NULL)
    {
        parcours = maListe -> premier;
        while(parcours != NULL && parcours -> valeur != val)
        {
            parcours = parcours -> suivant;
        }
        return parcours;
    }
    return NULL;
}

int liste_maillon_substituer(Tptliste maListe, Tptmaillon maillon1, Tptmaillon maillon2)
{
    int success = 0;
    int i = 1, j = 1;
    int maillon1_premier = 0, maillon2_premier = 0;
    Tptmaillon precedent1 = maListe -> premier;
    Tptmaillon precedent2 = maListe -> premier;
    Tptmaillon parcours1 = maListe -> premier;
    Tptmaillon parcours2 = maListe -> premier;
    Tptmaillon fin = NULL;
    Tptmaillon temp = NULL;

    //Si on a quelque chose à faire
    if(maListe != NULL && maListe -> premier != NULL && maillon1 != NULL && maillon2 != NULL && maillon1 != maillon2)
    {
        //Recherche de precedent1
        while(parcours1 != maillon1 && parcours1 != NULL)
        {
            precedent1 = parcours1;
            parcours1 = parcours1 -> suivant;
            i++;
        }

        //Recherche de precedent2
        while(parcours2 != maillon2 && parcours2 != NULL)
        {
            precedent2 = parcours2;
            parcours2 = parcours2 -> suivant;
            j++;
        }

        /*Cette fonction ne gère que le cas où maillon1 se trouve avant maillon2. Si ça n'est pas le cas,
        il nous suffit d'inverser les deux !*/
        if(i > j)
        {
            //Inversion de maillon1 et de maillon2
            temp = maillon1;
            maillon1 = maillon2;
            maillon2 = temp;

            //Inversion de precedent1 et de precedent2
            temp = precedent1;
            precedent1 = precedent2;
            precedent2 = temp;
        }

        //Si parcours1 ou parcours2 est égal à NULL, c'est qu'il y a un problème : on n'a pas trouvé les maillons à substituer.
        if(parcours1 != NULL && parcours2 != NULL)
        {
            //On gère le cas où un des deux maillons à être substitué est le premier de la liste chainée.
            if(maillon1 == maListe -> premier)
                maillon1_premier = 1;
            else if(maillon2 == maListe -> premier)
                maillon2_premier = 1;
            //Les actions qui modifient le pointeur premier seront faites à la fin, sinon on perd la liste chainée...


            if(precedent1 != maillon1)
                precedent1 -> suivant = maillon2;

            fin = maillon2 -> suivant;

            if(maillon2 != maillon1 -> suivant)
                maillon2 -> suivant = maillon1 -> suivant;
            else
                maillon2 -> suivant = maillon1;

            if(maillon1 != precedent2)
                precedent2 -> suivant = maillon1;

            maillon1 -> suivant = fin;

            /*On gère le cas où l'on touche au dernier maillon de la chaine.
            Il faudra donc mettre le champ suivant du nouveau maillon dernier à NULL.*/
            if(maListe -> dernier == maillon1)
            {
                maillon2 -> suivant = NULL;
                maListe -> dernier = maillon2;
            }
            else if(maListe -> dernier == maillon2)
            {
                maillon1 -> suivant = NULL;
                maListe -> dernier = maillon1;
            }


            if(maillon1_premier)
                maListe -> premier = maillon2;
            else if(maillon2_premier)
                maListe -> premier = maillon1;

            success = 1;
        }
    }
    else
        success = 1;

    return success;
}

//Fonction qui mélange une liste chainée.
void liste_melanger(Tptliste maListe, int min, int max)
{
    int nombre_substitutions;
    int i = 1;
    int maillon1_num, maillon2_num;
    Tptmaillon maillon1;
    Tptmaillon maillon2;

    //A-t-on besoin de faire quelque chose ?
    if(maListe != NULL && maListe -> premier != NULL)
    {
        //On choisit aléatoirement le nombre de fois que l'on va substituer des maillons.
        nombre_substitutions = (rand() % (max - min + 1)) + max;

        //C'est parti !
        while(i <= nombre_substitutions)
        {
            //Pour chaque substitution, on choisit aléatoirement les deux maillons que l'on va substituer.
            maillon1_num = (rand() % ((maListe -> taille - 1) + 1)) + 1;
            maillon2_num = (rand() % ((maListe -> taille - 1) + 1)) + 1;

            //On récupère l'adresse de ces maillons fraichement choisis
            maillon1 = liste_maillon_pos2point(maListe, maillon1_num);
            maillon2 = liste_maillon_pos2point(maListe, maillon2_num);

            //On les substitue !
            if(!liste_maillon_substituer(maListe, maillon1, maillon2))
            {
                exit(0);
            }

            i++;
        }
    }
}

/* Cette fonction tire au sort un maillon dans une liste chainée et sort sa valeur. */
int liste_maillon_valeur_aleatoire(Tptliste maListe)
{
    int maillon_num = 0;
    Tptmaillon maillon = NULL;
    if(maListe != NULL && (maListe -> taille) > 0)
    {
        maillon_num = (rand() % ((maListe -> taille - 1) + 1)) + 1;

        //On récupère l'adresse du maillon fraichement choisi.
        maillon = liste_maillon_pos2point(maListe, maillon_num);

        return maillon -> valeur;
    }
    return -1;
}

void liste_vider(Tptliste maListe)
{
    Tptmaillon parcours = NULL;

    //Si on a quelque chose à faire
    if(maListe != NULL)
    {
        if(maListe -> premier != NULL)
        {
            parcours = maListe -> premier;
            while(parcours != NULL)
            {
                liste_maillon_supprimer(maListe, parcours);
                parcours = parcours -> suivant;
            }
        }
    }
}

void liste_detruire(Tptliste maListe)
{
    //Si on a quelque chose à faire
    if(maListe != NULL)
    {
        liste_vider(maListe);
        free(maListe);
    }
}
