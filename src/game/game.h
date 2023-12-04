//
// Created by Ewan Kapoor on 11/27/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "../tools/tools.h"

#ifndef SNOOPY_GAME
#define SNOOPY_GAME

struct Dimensions {
    int largeur, hauteur;
};

struct Balle {
    int x, y, direction;
};

struct ModeleNiveau {
    char *id;
    int **modele, hauteur, largeur, niveau, temps_restant, vies_restantes;
    int nb_oiseaux, nb_teleporteurs, nb_balles, score, sous_case;
    char *message;
    struct Coordonnees snoopy;
    struct Coordonnees *oiseaux, *teleporteurs;
    struct Balle *balles;
};

void afficher_niveau(struct ModeleNiveau modele, int temps_restant, char derniere_direction);
struct ModeleNiveau modele_niveau(char *id, int sauvegarde);
struct Dimensions dimensions_niveau(int niveau);
int unite_chrono_restant(int prct_restant, int hauteur, int largeur);
int nombre_oiseaux(struct ModeleNiveau modele);

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction);
void casse_bloc(struct ModeleNiveau *modele, const char *direction);
void deplacer_balle(struct ModeleNiveau *modele, int i);

void handleKeypress(struct ModeleNiveau *modele, int *chrono, int *pause, int *menu_principal, char *derniere_direction);

void nouvelle_partie(char *id);
void afficher_vies(int vies);
void game(struct ModeleNiveau modele);
void retour_menu_principal();
void victoire_niveau();
void defaite_niveau();

#endif // SNOOPY_NIVEAU_H

#endif //SNOOPY_GAME
