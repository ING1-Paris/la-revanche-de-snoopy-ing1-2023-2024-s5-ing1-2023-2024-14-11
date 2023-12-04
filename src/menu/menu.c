//
// Created by Ewan Kapoor on 13/11/2023.
//

#include "menu.h"
#include "../tools/tools.h"
#include "../classement/classement.h"


void menu() {
    afficher_menu();
    int option;
    switch(option) {
        case 1:
            afficher_regles();
            break;
        case 2:
            // lancer une partie
            break;
        case 3:
            // charger une partie
            break;
        case 4:
            // charger un niveau (MDP)
            break;
        case 5:
            // classement
            classement();
            break;
        case 6:
            quitter();
            break;
        default:
            system("cls");
            menu();
    }
}

void afficher_menu() {

    afficher_fichier("../assets/menu.txt");

};

void afficher_regles() {

    system("cls");
    afficher_fichier("../assets/ASCII/regles.txt");
    menu();
};

void quitter() {

    sleep(3);
    exit(0);

};


