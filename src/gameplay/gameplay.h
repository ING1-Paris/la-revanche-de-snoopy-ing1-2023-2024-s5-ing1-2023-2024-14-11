//
// Created by Ewan Kapoor on 06/12/2023.
//

#ifndef SNOOPYFINAL_GAMEPLAY_H
#define SNOOPYFINAL_GAMEPLAY_H

//Bibliothèque

#include "../tools/tools.h"
#include "../menu/menu.h"
#include "../keyboard/keyboard.h"

//Structures

struct Dimensions {
    int largeur;
    int hauteur;
};
struct Balle {
    int x;
    int y;
    int direction;
};
struct ModeleNiveau {
    char *id;
    int **modele;
    int hauteur;
    int largeur;
    int niveau;
    int temps_restant;
    int vies_restantes;
    int nb_oiseaux;
    int nb_teleporteurs;
    int nb_balles;
    char *message;
    int score;
    int sous_case;
    struct Coordonnees snoopy;
    struct Coordonnees *oiseaux;
    struct Coordonnees *teleporteurs;
    struct Balle *balles;
};

struct ModeleNiveau modele_niveau(char *id, int sauvegarde);
struct Dimensions dimensions_niveau(int niveau);

//Fonctions

void afficherNiveau(struct ModeleNiveau modele, int temps_restant, char derniere_direction);

int nombreOiseaux(struct ModeleNiveau modele);

void nouvellePartie(char *id);
void afficherVies(int vies);
void afficherTempsRestant(int tempsRestant);
void afficherOiseauxRestant(int nombre_oiseaux(modele));
void jeu(struct ModeleNiveau modele);

#endif //SNOOPYFINAL_GAMEPLAY_H
