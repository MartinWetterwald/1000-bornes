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
    /*printf("\n\n");
    printf("            88     ,a8888a,        ,a8888a,        ,a8888a,     \n");
    printf("          ,d88   ,8P\"'  `\"Y8,    ,8P\"'  `\"Y8,    ,8P\"'  `\"Y8,   \n");
    printf("        888888  ,8P        Y8,  ,8P        Y8,  ,8P        Y8,  \n");
    printf("            88  88          88  88          88  88          88  \n");
    printf("            88  88          88  88          88  88          88  \n");
    printf("            88  `8b        d8'  `8b        d8'  `8b        d8'  \n");
    printf("            88   `8ba,  ,ad8'    `8ba,  ,ad8'    `8ba,  ,ad8'   \n");
    printf("            88     \"Y8888P\"        \"Y8888P\"        \"Y8888P\"     \n");
    printf("                                                                \n");
    printf("\n");*/

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
    printf("                   '::::::::#+++++':,,::::,,,,,,,,,,+..+++++++,,:,;``;\n");
    printf("                +::::::::,##::::'+#:::::::,,,,,,,,,,,+#:::,;+#,,::.``\n");
    printf(" `,            #::::::::+#:;:;::,##:,:::::,,,,,,,,,##:;::::,+#:::,``#\n");
    printf("    .     `     :,::::::#+;;.'``;:,#,::::::::,,,,,,#+;;;;+;::,#,:::,#+\n");
    printf("     .  +  `     ..```..#+';'````::+#,:::::,,,,,,,,##;'+;``.::#+,::::,\n");
    printf("               ',,,.....+''..+```;:##,::::::,:,,,,,+;'+'.';`':'#,'#,```\n");
    printf("         ;`    ';;::::::+''..',``;;'#..........,,..+''#.;.``'::#``````:\n");
    printf("     ,      . ,  ++++++''#'+#...`+;;++,,,,,,,.......#+'+.::;`;:##`````:\n");
    printf("         .:`              @##++#,.+';;####     ##+++###+'+,.;..;: #',,,`\n");
    printf("                              +++++'';                   #+++#';;\n");
    printf("                             #+++''                     '''';;\n");
    printf("\n");
    printf("                          .:;##+:,.`                 `,:::###+;,,\n");
    printf("          `;,`                                                        `:#:\n");
    printf("  ,.                                                                        \n");

    /*printf("\n");
    printf("88888888ba     ,ad8888ba,    88888888ba   888b      88  88888888888  ad88888ba   \n");
    printf("88      \"8b   d8\"'    `\"8b   88      \"8b  8888b     88  88          d8\"     \"8b  \n");
    printf("88      ,8P  d8'        `8b  88      ,8P  88 `8b    88  88          Y8,          \n");
    printf("88aaaaaa8P'  88          88  88aaaaaa8P'  88  `8b   88  88aaaaa     `Y8aaaaa,    \n");
    printf("88\"\"\"\"\"\"8b,  88          88  88\"\"\"\"88'    88   `8b  88  88\"\"\"\"\"       `\"\"\"\"\"8b,  \n");
    printf("88      `8b  Y8,        ,8P  88    `8b    88    `8b 88  88                  `8b  \n");
    printf("88      a8P   Y8a.    .a8P   88     `8b   88     `8888  88          Y8a     a8P  \n");
    printf("88888888P\"     `\"Y8888Y\"'    88      `8b  88      `888  88888888888  \"Y88888P\"   \n");*/

    printf("\n");
    printf("   _   __     __     __       ___    _____  ___    _   _  ___    ___   \n");
    printf(" /' )/' _`\\ /' _`\\ /' _`\\    (  _`\\ (  _  )|  _`\\ ( ) ( )(  _`\\ (  _`\\ \n");
    printf("(_, || ( ) || ( ) || ( ) |   | (_) )| ( ) || (_) )| `\\| || (_(_)| (_(_)\n");
    printf("  | || | | || | | || | | |   |  _ <'| | | || ,  / | , ` ||  _)_ `\\__ \\ \n");
    printf("  | || (_) || (_) || (_) |   | (_) )| (_) || |\\ \\ | |`\\ || (_( )( )_) |\n");
    printf("  (_)`\\___/'`\\___/'`\\___/'   (____/'(_____)(_) (_)(_) (_)(____/'`\\____)\n");

    //sleep(4);

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

void menu_demander_nom_joueur(char nom[NOM_TAILLE_MAX])
{
    printf("Veuillez saisir votre nom (joueur humain) : ");
    lire(nom, NOM_TAILLE_MAX);
}

void demander_appuyez_sur_une_touche_pour_continuer()
{
    char kikoo[NOM_TAILLE_MAX];
    printf("Appuyez sur 'entrée' pour continuer...\n");
    lire(kikoo, NOM_TAILLE_MAX);
}

void menu_demander_choix_carte(int* choix_carte)
{
    printf("Entrez le code de la carte à jouer.\n");
    printf("Si vous ne souhaitez (ou ne pouvez) pas jouer de carte, vous pouvez :\n");
    printf("- ne rien jouer et simplement passer votre tour (code %d) ;\n", PASSER_SON_TOUR);
    printf("- arrêter la partie sans enregistrer (code %d) ;\n", ARRETER_PARTIE);
    printf("- arrêter la partie et l'enregister (code %d).\n", ENREGISTRER);

    printf("Votre choix ? ");

    *choix_carte = lireLong();
}

void menu_demander_choix_carte_jeter(int* choix_carte, int nb_coups_possibles)
{
    if(nb_coups_possibles > 0)
        printf("\nMême si vous passez votre tour, vous êtes obligé d'enlever une carte de votre main.\n");
    else
        printf("\nVous êtes obligé de passer votre tour car vous ne pouvez jouer aucune carte de votre main.\n");

    printf("Entrez le code de la carte à jeter. ");

    if(nb_coups_possibles > 0)
        printf("Vous pouvez aussi entrer le code %d si vous avez changé d'avis et que vous ne souhaitez plus passer votre tour.\n", ANNULER_PASSER_SON_TOUR);

    printf("Votre choix ? ");
    *choix_carte = lireLong();
}

void menu_demander_coup_fourre(Tdeck* deck, Tptjoueur* joueur_selectionne, Tptjoueur* autre_joueur, int obstacle, int botte, char* raison_refus, char* raison_refus2)
{
    int choix_coup_fourre = 0;
    int tirage_au_sort = 0;

    if((*autre_joueur) -> est_ordinateur)
    {
        //Le mode débutant ne voit jamais les coups fourrés.
        //Le mode course a 25% de chances de les voir.
        //Le mode agressif a 50% de chances de les voir.
        //Le mode défensif a 75% de chances de les voir.
        //Le mode expert a 100% de chances de les voir.

        tirage_au_sort = (rand() % 101) + 100; //On tire au sort un nombre entre 0 et 100

        switch((*autre_joueur) -> difficulte_ordinateur)
        {
            case DEBUTANT:
                //Le mode débutant ne voit jamais les coups fourrés.
            break;

            case COURSE:
                //Le mode course a 25% de chances de les voir.
                if(tirage_au_sort <= 25)
                    coup_fourre(deck, joueur_selectionne, autre_joueur, obstacle, botte, raison_refus, raison_refus2);
            break;

            case AGRESSIF:
                //Le mode agressif a 50% de chances de les voir.
                if(tirage_au_sort <= 50)
                    coup_fourre(deck, joueur_selectionne, autre_joueur, obstacle, botte, raison_refus, raison_refus2);
            break;

            case DEFENSIF:
                //Le mode défensif a 75% de chances de les voir.
                if(tirage_au_sort <= 75)
                    coup_fourre(deck, joueur_selectionne, autre_joueur, obstacle, botte, raison_refus, raison_refus2);
            break;

            case EXPERT:
                //Le mode expert a 100% de chances de les voir.
                coup_fourre(deck, joueur_selectionne, autre_joueur, obstacle, botte, raison_refus, raison_refus2);
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

        printf("\n'%s', votre adversaire '%s' vient de jouer une carte '", (*autre_joueur) -> nom, (*joueur_selectionne) -> nom);
        cartes_type2francais(obstacle);
        printf("' mais vous avez dans votre jeu la carte 'botte' '");
        cartes_type2francais(botte);
        printf("'.\n");

        printf("Vous avez la possibilité de déclarer « coup fourré », ");
        printf("ainsi l'attaque de votre adversaire '%s' sera annulée et votre carte botte sera activée.\n", (*joueur_selectionne) -> nom);
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
            coup_fourre(deck, joueur_selectionne, autre_joueur, obstacle, botte, raison_refus, raison_refus2);
    }
}

void menu_difficulte_ordinateur(int* choix)
{
    printf("Vous avez choisi de jouer contre l'ordinateur.\n\n");
    printf("Choisissez le niveau de difficulté de l'ordinateur :\n");
    printf("1) Mode débutant\n");
    printf("2) Mode course\n");
    printf("3) Mode agressif\n");
    printf("4) Mode défensif\n");
    printf("5) Mode expert\n");
    printf("0) Annuler et revenir au menu prédécent\n");
    printf("Votre choix : ");
    *choix = lireLong();
}

void menu_charger_partie(char* choix)
{
    printf("Vous avez choisi de charger une partie.\n\n");
    printf("Entrez le nom du fichier à charger : ");
    lire(choix, TAILLE_MAX_NOM_FICHIER);
}

void menu_enregistrer_partie(char* choix)
{
    printf("Le menu d'enregistrement de partie est encore en construction. :p");
}
