//
// Created by Ewan Kapoor on 13/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "../tools/tools.h"


void menu() {
    afficher_menu();

}

void afficher_menu() {
    afficher_fichier("../assets/menu.txt");
}

void afficher_regles() {
    system(cls);
    afficher_fichier("../assets/ASCII/regles.txt");
    menu();
}
