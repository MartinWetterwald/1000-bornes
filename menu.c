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
#include "constantes.h"
#include "divers.h"
#include "menu.h"



void afficher_logo()
{
    printf("\n\n");
    printf("            88     ,a8888a,        ,a8888a,        ,a8888a,     \n");
    printf("          ,d88   ,8P\"'  `\"Y8,    ,8P\"'  `\"Y8,    ,8P\"'  `\"Y8,   \n");
    printf("        888888  ,8P        Y8,  ,8P        Y8,  ,8P        Y8,  \n");
    printf("            88  88          88  88          88  88          88  \n");
    printf("            88  88          88  88          88  88          88  \n");
    printf("            88  `8b        d8'  `8b        d8'  `8b        d8'  \n");
    printf("            88   `8ba,  ,ad8'    `8ba,  ,ad8'    `8ba,  ,ad8'   \n");
    printf("            88     \"Y8888P\"        \"Y8888P\"        \"Y8888P\"     \n");
    printf("                                                                \n");
    printf("\n");

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

    printf("\n");
    printf("88888888ba     ,ad8888ba,    88888888ba   888b      88  88888888888  ad88888ba   \n");
    printf("88      \"8b   d8\"'    `\"8b   88      \"8b  8888b     88  88          d8\"     \"8b  \n");
    printf("88      ,8P  d8'        `8b  88      ,8P  88 `8b    88  88          Y8,          \n");
    printf("88aaaaaa8P'  88          88  88aaaaaa8P'  88  `8b   88  88aaaaa     `Y8aaaaa,    \n");
    printf("88\"\"\"\"\"\"8b,  88          88  88\"\"\"\"88'    88   `8b  88  88\"\"\"\"\"       `\"\"\"\"\"8b,  \n");
    printf("88      `8b  Y8,        ,8P  88    `8b    88    `8b 88  88                  `8b  \n");
    printf("88      a8P   Y8a.    .a8P   88     `8b   88     `8888  88          Y8a     a8P  \n");
    printf("88888888P\"     `\"Y8888Y\"'    88      `8b  88      `888  88888888888  \"Y88888P\"   \n");

    sleep(4);

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
    printf("Choix : %d", *choix);
    printf("\n\n\n");
}

void menu_demander_nom_joueur(char nom[NOM_TAILLE_MAX])
{
    printf("Veuillez saisir votre nom (joueur humain) : ");
    lire(nom, NOM_TAILLE_MAX);
}

void menu_nouvelle_partie(int* choix)
{
    printf("Vous avez choisi de lancer une nouvelle partie.\n\n");
    printf("Choisissez le niveau de difficulté de l'ordinateur :\n");
    printf("1) Mode débutant\n");
    printf("2) Mode course\n");
    printf("3) Mode agressif\n");
    printf("4) Mode défensif\n");
    printf("5) Mode expert\n");
    printf("0) Annuler et revenir au menu principal\n");
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
}
