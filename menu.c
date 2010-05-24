/*************************************************
*              JEU DES 1000 BORNES               *
*                                                *
* Réalisé par Nacim Messadi et Martin Wetterwald *
*                                                *
*               FICHIER : menu.c                 *
* DESCRIPTION : Fonctions gérant l'affichage des *
* différents menus (interface).                  *
*                                                *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constantes.h"
#include "divers.h"
#include "menu.h"
#include "jeu.h"


void afficher_logo()
{
    printf("                               #       .'+';`\n");
    printf("                                 ,',:::,,,,,...#\n");
    printf("                         ` #   #,::,,+:`` ,#:.....\n");
    printf("                         ` #   ,::,,`#:       .;;...+\n");
    printf("                         # :  .:::+   :'       `.` ,..`\n");
    printf("                             ,:,     ,#     ```:;``#..`\n");
    printf("                         : :  :::`     :'` ```````.```,`..\n");
    printf("                             #::;     `,``````````.+```,``:\n");
    printf("                     . `  :::     `',``````````#.````;..'\n");
    printf("                         +::`   ```:;```````````.`````,..\n");
    printf("                         ::,``````:,.```````````.#`````..#\n");
    printf("                         #::'```++,::,,,,,,,,,.........:+..\n");
    printf("                         :::;:::::+':.,,:,,,,,......:+',.....:,\n");
    printf("                         '::::;::::::::,,,,,,,,,..........,,.',,,+\n");
    printf("                      ,,:::::::,,+:,:::::,,,,,,,,......:,..,,,,',,;\n");
    printf("                     .:::::::::,,,:::::::::,,,,,,,,,..,....,.,,,,,,. ;\n");
    printf("                   '::::::::");printfEx(JAUNE, "#+++++");   printf("':,,::::,,,,,,,,,,+..");printfEx(JAUNE, "+++++++");         printf(",,:,;``;\n");
    printf("                +::::::::,");printfEx(JAUNE, "##::::'+#");  printf(":::::::,,,,,,,,,,,");   printfEx(JAUNE, "+#:::,;+#");       printf(",,::.``\n");
    printf(" `,            #::::::::");printfEx(JAUNE, "+#:;:;::,##");  printf(":,:::::,,,,,,,,,");     printfEx(JAUNE, "##:;::::,+#");     printf(":::,``#\n");
    printf("    .     `     :,::::::");printfEx(JAUNE, "#+;;.'``;:,#"); printf(",::::::::,,,,,,");      printfEx(JAUNE, "#+;;;;+;::,#");    printf(",:::,#+\n");
    printf("     .  +  `     ..```..");printfEx(JAUNE, "#+';'````::+#");printf(",:::::,,,,,,,,");       printfEx(JAUNE, "##;'+;``.::#+");   printf(",::::,\n");
    printf("               ',,,.....");printfEx(JAUNE, "+''..+```;:##");printf(",::::::,:,,,,,");       printfEx(JAUNE, "+;'+'.';`':'#");   printf(",'#,```\n");
    printf("         ;`    ';;::::::");printfEx(JAUNE, "+''..',``;;'#");printf("..........,,..");       printfEx(JAUNE, "+''#.;.``'::#");   printf("``````:\n");
    printf("     ,      . ,  ++++++''");printfEx(JAUNE, "#'+#...`+;;"); printf("++,,,,,,,.......");     printfEx(JAUNE, "#+'+.::;`;:##");   printf("`````:\n");
    printf("         .:`              ");printfEx(JAUNE, "@##++#,.+");  printf("';;####     ##+++");    printfEx(JAUNE, "###+'+,.;..;:");   printf(" #',,,`\n");
    printf("                              +++++'';                   #+++#';;\n");
    printf("                             #+++''                     '''';;\n");
    printf("\n");
    printf("                          .:;##+:,.`                 `,:::###+;,,\n");
    printf("          `;,`                                                        `:#:\n");
    printf("  ,.                                                                        \n");

    printf("\n");
    printfEx(JAUNE, "    _   __     __     __       ___    _____  ___    _   _  ___    ___   \n");
    printfEx(JAUNE, " /' )/' _`\\ /' _`\\ /' _`\\    (  _`\\ (  _  )|  _`\\ ( ) ( )(  _`\\ (  _`\\ \n");
    printfEx(JAUNE, "(_, || ( ) || ( ) || ( ) |   | (_) )| ( ) || (_) )| `\\| || (_(_)| (_(_)\n");
    printfEx(JAUNE, "  | || | | || | | || | | |   |  _ <'| | | || ,  / | , ` ||  _)_ `\\__ \\ \n");
    printfEx(JAUNE, "  | || (_) || (_) || (_) |   | (_) )| (_) || |\\ \\ | |`\\ || (_( )( )_) |\n");
    printfEx(JAUNE, "  (_)`\\___/'`\\___/'`\\___/'   (____/'(_____)(_) (_)(_) (_)(____/'`\\____)\n");

    sleep(3);

    printf("\n\nBienvenue sur le jeux des 1000 bornes !\n");
    printf("Developped & Designed by NA2S & Martin's Prince\n\n");
}

void menu_principal(int* choix)
{
    printf("\n\n\nMENU PRINCIPAL\n");
    printf("1) Nouvelle partie\n");
    printf("2) Charger une partie\n");
    printf("0) Quitter le jeu\n");
    printf("Votre choix : ");

    *choix = lireLong();
    printf("\n\n\n");
}

void menu_demander_ordinateur(int* choix)
{
    printf("Vous avez choisi de lancer une nouvelle partie.\n\n");
    printf("Choisissez le mode de jeu : \n");
    printf("1) Humain VS Ordinateur\n");
    printf("2) Humain VS Humain\n");
    printf("3) Ordinateur VS Ordinateur\n");
    printf("0) Annuler et revenir au menu principal\n");
    printf("Votre choix : ");

    *choix = lireLong();
    printf("\n");
}

void menu_demander_nom_joueur(char nom[NOM_TAILLE_MAX], int joueur_num)
{
    printf("Veuillez saisir votre nom (joueur humain n° %d) : ", joueur_num);
    lire(nom, NOM_TAILLE_MAX);
}

void demander_appuyez_sur_une_touche_pour_continuer()
{
    char kikoo[NOM_TAILLE_MAX];
    printf("Appuyez sur 'entrée' pour continuer...\n");
    lire(kikoo, NOM_TAILLE_MAX);
    printf("----------------------------------------------\n");
}

void menu_demander_choix_carte(int* choix_carte, int nb_coups_possibles)
{
    if(nb_coups_possibles > 0)
        printf("Entrez le code de la carte à jouer.\n");
    else
        printf("Vous ne pouvez jouer aucun coup et êtes obligé de passer votre tour (code %d).\n", PASSER_SON_TOUR);
    printf("Si vous ne souhaitez (ou ne pouvez) pas jouer de carte, vous pouvez :\n");
    printf("- jeter une carte et passer votre tour (code %d) ;\n", PASSER_SON_TOUR);
    printf("- arrêter la partie sans enregistrer (code %d) ;\n", ARRETER_PARTIE);
    printf("- arrêter la partie et l'enregister (code %d).\n", ENREGISTRER);

    printf("Votre choix ? ");

    *choix_carte = lireLong();
}

void menu_demander_choix_carte_jeter(int* choix_carte)
{
    printf("\nVous passez votre tour, mais vous devez avant vous débarasser d'une carte.\n");
    printf("Entrez le code de la carte à jeter. ");
    printf("Vous pouvez aussi entrer le code %d si vous avez changé d'avis et que vous ne souhaitez plus passer votre tour.\n", ANNULER_PASSER_SON_TOUR);
    printf("Votre choix ? ");
    *choix_carte = lireLong();
}

void menu_demander_coup_fourre(Tptpartie partie, int obstacle, int botte, char* raison_refus, char* raison_refus2)
{
    int choix_coup_fourre = 0;
    int tirage_au_sort = 0;

    if(partie -> autre_joueur -> est_ordinateur)
    {
        //Le mode archi-débutant ne voit jamais les coups fourrés.
        //Le mode débutant a 20% de chances de les voir.
        //Le mode course a 40% de chances de les voir.
        //Le mode agressif a 60% de chances de les voir.
        //Le mode défensif a 80% de chances de les voir.
        //Le mode expert a 100% de chances de les voir.

        tirage_au_sort = (rand() % 101) + 100; //On tire au sort un nombre entre 0 et 100

        switch(partie -> autre_joueur -> difficulte_ordinateur)
        {
            case ARCHI_DEBUTANT:
                //Le mode archi-débutant ne voit jamais les coups fourrés.
            break;

            case DEBUTANT:
                //Le mode débutant a 20% de chances de les voir.
                if(tirage_au_sort <= 20)
                    coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
            break;

            case COURSE:
                //Le mode course a 40% de chances de les voir.
                if(tirage_au_sort <= 40)
                    coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
            break;

            case AGRESSIF:
                //Le mode agressif a 60% de chances de les voir.
                if(tirage_au_sort <= 60)
                    coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
            break;

            case DEFENSIF:
                //Le mode défensif a 80% de chances de les voir.
                if(tirage_au_sort <= 80)
                    coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
            break;

            case EXPERT:
                //Le mode expert a 100% de chances de les voir.
                coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
            break;

            default:
                printf("Erreur, la difficulté de l'IA est invalide (menu.c).");
                exit(0);
        }
    }
    else
    {
        //Si c'est un humain, on n'a pas trop le choix, on lui demande s'il veut dire « coup fourré » ou pas.
        //Tout le monde répondra toujours « oui » à cette question, mais bon...

        printf("\n'%s', votre adversaire '%s' vient de jouer une carte '", partie -> autre_joueur -> nom, partie -> joueur_selectionne -> nom);
        cartes_type2francais(obstacle);
        printf("' mais vous avez dans votre jeu la carte 'botte' '");
        cartes_type2francais(botte);
        printf("'.\n");

        printf("Vous avez la possibilité de déclarer « coup fourré », ");
        printf("ainsi l'attaque de votre adversaire '%s' sera annulée et votre carte botte sera activée.\n", partie -> joueur_selectionne -> nom);
        printf("Vous aurez donc cinq cartes dans votre main, piocherez deux fois et ce sera toujours à vous de jouer.\n");
        printf("Ceci est intéressant car vous gagnez %d points supplémentaires par coup fourré en fin de partie.", POINTS_PAR_COUP_FOURRE);

        while(choix_coup_fourre != 1 && choix_coup_fourre != 2)
        {
            printf("\n\n");
            printf("1) Déclarer « coup fourré » ;\n");
            printf("2) Faire semblant que vous n'avez rien vu.\n");
            printf("Votre choix ? ");

            choix_coup_fourre = lireLong();
        }

        if(choix_coup_fourre == 1)
            coup_fourre(partie, obstacle, botte, raison_refus, raison_refus2);
    }
}

void menu_difficulte_ordinateur(int* choix, int num_joueur)
{
    printf("Choisissez le niveau de difficulté de l'ordinateur n° %d :\n", num_joueur);
    printf("1) Mode archi-débutant\n");
    printf("2) Mode débutant\n");
    printf("3) Mode course\n");
    printf("4) Mode agressif\n");
    printf("5) Mode défensif\n");
    printf("6) Mode expert\n");
    printf("0) Annuler et revenir au menu prédécent\n");
    printf("Votre choix : ");
    *choix = lireLong();
    printf("\n");
}

void menu_charger_partie(char* choix)
{
    printf("Vous avez choisi de charger une partie.\n\n");
    printf("Entrez le nom du fichier à charger : ");
    lire(choix, TAILLE_MAX_NOM_FICHIER);
}

void menu_enregistrer_partie(char* choix)
{
    printf("Entrez le nom du fichier dans lequel vous souhaitez sauvegarder la partie : ");
    lire(choix, TAILLE_MAX_NOM_FICHIER);
}
