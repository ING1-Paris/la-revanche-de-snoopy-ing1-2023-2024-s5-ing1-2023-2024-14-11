//
// Created by Ewan Kapoor on 06/12/2023.
//

#include "menu.h"

void menu() {
    // Affiche le menu principal, récupère l'option sélectionnée et effectue l'action correspondante
    afficherMenu();
    int option = selection();

    switch (option) {
        case 1: afficherRegles(); break;
        case 2: nouvellePartie("1"); break;
        case 3: charger_sauvegarde("", -1); break;
        case 4: chargerNiveau(); break;
        case 5: leaderboard(); break;
        case 6: afficherCredits(); break;
        case 7: quitter(); break;
        default:
            system("cls");
            menu();
    }
}

void afficherMenu() {
    // Affiche le contenu du fichier de menu
    afficherFichier("../assets/menu.txt");
}

int selection() {
    // Récupère la touche pressée pour sélectionner une option du menu
    int option;
    char touche = _getch();

    switch (touche) {
        case '1': option = 1; break;
        case '2': option = 2; break;
        case '3': option = 3; break;
        case '4': option = 4; break;
        case '5': option = 5; break;
        case '6': option = 6; break;
        case '7': option = 7; break;
        default: option = -1; break;
    }

    return option;
}

void attendre_escape_pour_menu() {
    // Attend que la touche Escape soit pressée pour revenir au menu
    char touche = _getch();
    while (touche != 27) {
        touche = _getch();
    }
}

void afficher_et_attendre_retour_menu(const wchar_t *fichier) {
    // Affiche le contenu du fichier spécifié et attend la touche Escape pour revenir au menu
    system("cls");
    afficherFichier(fichier);
    attendre_escape_pour_menu();
    system("cls");
    menu();
}

void afficherRegles() {
    // Affiche les règles du jeu et attend la touche Escape pour revenir au menu
    afficher_et_attendre_retour_menu("../assets/regles.txt");
}

void leaderboard() {
    // Affiche le classement et attend la touche Escape pour revenir au menu
    afficher_et_attendre_retour_menu("../assets/leaderboard.txt");
}

void afficherCredits() {
    // Affiche les crédits du jeu et attend la touche Escape pour revenir au menu
    afficher_et_attendre_retour_menu("../assets/credits.txt");
}

void quitter() {
    // Affiche un message de fermeture avec compte à rebours et quitte le programme après 5 secondes
    wprintf(L"Fermeture dans 5 secondes\n");
    fflush(stdout);

    for (int i = 4; i >= 0; --i) {
        sleep(1);
        wprintf(L"%d\n", i);
        fflush(stdout);
    }

    wprintf(L"\n");

    exit(0);
}

void chargerNiveau() {
    // Affiche l'écran de chargement de niveau, demande à l'utilisateur de saisir un niveau, puis lance la nouvelle partie
    system("cls");
    afficherFichier("../assets/ASCII/charger_niveau.txt");
    wprintf(L"Quel niveau voulez-vous charger ? (Appuyez sur Escape pour revenir au menu)\n");

    while (1) {
        if (touche_escape_appuyee()) {
            system("cls");
            menu();
        }

        if (_kbhit()) {
            char id[10];
            scanf("%s", id);
            nouvellePartie(id);
            break;
        }
    }
}

