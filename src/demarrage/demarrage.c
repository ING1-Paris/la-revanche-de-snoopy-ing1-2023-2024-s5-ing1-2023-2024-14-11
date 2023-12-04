//
// Created by Ewan Kapoor on 13/11/2023.
//


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>

#include "demarrage.h"
#include "../tools/tools.h"
#include "../menu/menu.h"

void demarrage() {

    //fonction pour afficher le logo
    afficher_logo();

    //fonction pour afficher le menu suite à la pression de touche
    menu();




};

void afficher_logo() {

    afficher_fichier("../assets/ASCII/logo.txt")

};
