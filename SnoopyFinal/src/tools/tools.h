//
// Created by Ewan Kapoor on 06/12/2023.
//

#ifndef SNOOPYFINAL_TOOLS_H
#define SNOOPYFINAL_TOOLS_H

// Ce fichier contient les déclarations de bibliothèques, définitions, structures et fonctions utilitaires.

// Inclure les bibliothèques nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <io.h>

// Définitions de couleurs
#define NOIR 0
#define BLEU_FONCE 1
#define VERT_FONCE 2
#define TURQUOISE 3
#define ROUGE_FONCE 4
#define VIOLET 5
#define VERT_CACA_DOIE 6
#define GRIS_CLAIR 7
#define GRIS_FONCE 8
#define BLEU_FLUO 9
#define VERT_FLUO 10
#define TURQUOISE_2 11
#define ROUGE_FLUO 12
#define VIOLET_2 13
#define JAUNE 14
#define BLANC 15
#define MAX_JOUEURS 100

// Structures
struct Coordonnees {
    int x;
    int y;
};

struct ModeleNiveau charger_sauvegarde(char *id, int code);

struct Joueur {
    char nom[50];
    int niveau;
    int score_total;
};

// Fonctions utilitaires
void afficherFichier(char *path);
void COULEUR(int couleurDuTexte, int couleurDeFond);

void sauvegarder_partie(struct ModeleNiveau modele, int temps_restant, char *chemin);
char *demande_sauvegarde_id();
int sauvegarde_id_valide(char *id);

int nouveau_timer();

void enregistrer_resultat(char *nom_joueur, int niveau, int score_total);

int touche_escape_appuyee();


#endif //SNOOPYFINAL_TOOLS_H
