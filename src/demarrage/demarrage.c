//
// Created by Ewan Kapoor on 13/11/2023.
//


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>

#include "demarrage.h"
#include "../tools/tools.h"

void demarrage() {

    afficher_logo();

    clrscr();
    textcolor(WHITE+BLINK);
    cprintf("Appuyez sur une touche pour commencer");

};

void afficher_logo() {

    afficher_fichier("../assets/ASCII/logo.txt")
    
};
