//
// Created by Ewan Kapoor on 13/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "sauvegarde.h"
#include "../game/game.h"
#include "../timer/timer.h"
#include "../menu/menu.h"

int sauvegarde_id_valide(char *id) {
    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", id);
    return access(chemin, F_OK) != -1;
}

struct ModeleNiveau charger_sauvegarde(char *id, int code) {
    char nouvel_id[50];
    if (code == -1 || code == -2) {
        system("cls");
        afficher_fichier("../assets/ASCII/charger_partie.txt");
        wprintf(L"Veuillez entrer l'id de la sauvegarde : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else {
        wprintf(L"Chargement de la sauvegarde \"%s\"\n", id);
        if (!sauvegarde_id_valide(id))
            return charger_sauvegarde(nouvel_id, -2);
        else {
            struct ModeleNiveau sauvegarde = modele_niveau(id, 1);
            jeu(sauvegarde);
        }
    }
}

void sauvegarder_partie(struct ModeleNiveau modele, int temps_restant, char* chemin) {
    FILE *fichier = fopen(chemin, "w");
    fprintf(fichier, "%d\n%d\n%d\n%d\n%d\n%d", temps_restant, modele.niveau, modele.vies_restantes, modele.score, modele.sous_case, modele.nb_balles);

    for (int i = 0; i < modele.nb_balles; i++)
        fprintf(fichier, "\n%d\n%d\n%d", modele.balles[i].x, modele.balles[i].y, modele.balles[i].direction);

    for (int i = 0; i < modele.hauteur; i++) {
        fprintf(fichier, "\n");
        for (int j = 0; j < modele.largeur; j++)
            fprintf(fichier, "%d", modele.modele[i][j]);
    }

    fclose(fichier);
}

char *demande_sauvegarde_id() {
    char *nom = malloc(50 * sizeof(char));
    wprintf(L"Veuillez entrer le nom de la sauvegarde :");
    scanf("%s", nom);

    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);

    if (access(chemin, F_OK) != -1) {
        wprintf(L"Une sauvegarde de ce nom existe deja, voulez vous la remplacer ? (o/n)\n");
        char reponse;
        scanf(" %c", &reponse);
        if (reponse == 'n')
            return demande_sauvegarde_id();
    }

    return nom;
}
