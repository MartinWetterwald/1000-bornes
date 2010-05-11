/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER :                        *
* DESCRIPTION : Fonctions gérant la couche des   *
* listes chainées.                               *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "divers.h"
#include "liste.h"

//Fonction de création d'une liste chainée.
Tliste* liste_init()
{
    Tliste* maListe = malloc(sizeof(Tliste));
    maListe -> premier = NULL;
    maListe -> dernier = NULL;
    maListe -> taille = 0;
    return maListe;
}

//Fonction de création d'un nouveau maillon
Tmaillon* maillon_nouveau(int val)
{
    Tmaillon* nouveau;
    nouveau = malloc(sizeof(Tmaillon));
    nouveau -> suivant = NULL;
    nouveau -> valeur = val;
    return nouveau;
}

//Fonction qui permet d'insérer un maillon en tête de liste chainée.
Tmaillon* liste_maillon_inserer_tete(Tliste* maListe, int val)
{
    Tmaillon* nouveau = maillon_nouveau(val);
    nouveau -> suivant = maListe -> premier;

    maListe -> premier = nouveau;
    maListe -> taille = (maListe -> taille) + 1;

    if(maListe -> taille == 1)
    {
        maListe -> dernier = nouveau;
    }
    return nouveau;
}

//Fonction qui permet de supprimer un maillon donné
int liste_maillon_supprimer(Tliste* maListe, Tmaillon* aSupprimer)
{
    Tmaillon* precedent;
    Tmaillon* parcours;
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
void liste_remplir_fictif(Tliste* maListe, int max)
{
    int i;
    for(i = max; i >= 1; i--)
    {
        liste_maillon_inserer_tete(maListe, i);
    }
}

//Fonction qui affiche tous les entiers stockés dans la liste chainée
void liste_afficher(Tliste* maListe)
{
    //On initialise un pointeur parcours.
    Tmaillon* parcours = maListe->premier;

    printf("\n\nVoici le contenu de la liste chainée qui contient %d éléments :\n", maListe -> taille);
    while(parcours != NULL)
    {
        printf("%d -> ", parcours -> valeur);
        parcours = parcours -> suivant;
    }
    printf("NULL\n\n");
}

//Cette fonction recherche une valeur dans la liste chainée, et retourne combien de fois elle a été trouvée
int liste_compter_valeur(Tliste* maListe, int val)
{
    Tmaillon* parcours;
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
Tmaillon* liste_maillon_pos2point(Tliste* maListe, int num)
{
    int i = 1;
    Tmaillon* parcours;
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

int liste_maillon_substituer(Tliste* maListe, Tmaillon* maillon1, Tmaillon* maillon2)
{
    int success = 0;
    int i = 1, j = 1;
    int maillon1_premier = 0, maillon2_premier = 0;
    Tmaillon* precedent1 = maListe -> premier;
    Tmaillon* precedent2 = maListe -> premier;
    Tmaillon* parcours1 = maListe -> premier;
    Tmaillon* parcours2 = maListe -> premier;
    Tmaillon* fin = NULL;
    Tmaillon* temp = NULL;

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
                precedent2 -> suivant = maillon1; //Ça ça marche

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
void liste_melanger(Tliste* maListe, int min, int max)
{
    int nombre_substitutions;
    int i = 1;
    int maillon1_num, maillon2_num;
    Tmaillon* maillon1;
    Tmaillon* maillon2;

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

void liste_vider(Tliste* maListe)
{
    Tmaillon* parcours = NULL;

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

void liste_detruire(Tptliste* maListe)
{
    //Si on a quelque chose à faire
    if(*maListe != NULL)
    {
        liste_vider(*maListe);
        free(*maListe);
        *maListe = NULL;
    }
}
