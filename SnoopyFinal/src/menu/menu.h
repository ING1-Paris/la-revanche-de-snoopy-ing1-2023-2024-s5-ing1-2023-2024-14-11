//
// Created by Ewan Kapoor on 06/12/2023.
//

#ifndef SNOOPYFINAL_MENU_H
#define SNOOPYFINAL_MENU_H

// Ce fichier contient les déclarations de fonctions pour le menu du jeu.

// Inclure les bibliothèques nécessaires
#include "../tools/tools.h"
#include "../gameplay/gameplay.h"

// Déclarations des fonctions de menu
void menu();
void afficherMenu();
int selection();

// Fonctions liées aux options du menu
void afficherRegles();
void chargerNiveau();
void leaderboard();
void afficherCredits();
void quitter();


#endif //SNOOPYFINAL_MENU_H
