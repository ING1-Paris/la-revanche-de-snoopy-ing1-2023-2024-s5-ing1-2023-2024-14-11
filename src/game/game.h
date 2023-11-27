//
// Created by Ewan Kapoor on 11/27/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define COLONNES 22
#define LIGNES 22

#include "../tools/tools.h"

#ifndef SNOOPY_GAME
#define SNOOPY_GAME

struct Balle {

    int x;
    int y;
    int direction;

};

struct Niveau {


};

struct Dimension {

    int largeur;
    int hauteur;

};

#endif //SNOOPY_GAME
