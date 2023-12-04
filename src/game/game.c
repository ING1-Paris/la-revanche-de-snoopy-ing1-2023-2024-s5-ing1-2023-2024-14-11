//
// Created by Ewan Kapoor on 11/27/2023.
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "../tools/tools.h"
#include "../menu/menu.h"
#include "../timer/timer.h"
#include "../sauvegarde/sauvegarde.h"

int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction);
void teleportation(struct ModeleNiveau *modele, int x, int y);
void oiseaux(struct ModeleNiveau *modele);
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction);

int getCaseValue(struct ModeleNiveau modele, int x, int y) {
    return modele.modele[y][x];
}

void updateSnoopy(struct ModeleNiveau *modele, int new_x, int new_y) {
    modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case;
    modele->sous_case = 0;
    modele->snoopy.y = new_y;
    modele->snoopy.x = new_x;
    modele->sous_case = modele->modele[modele->snoopy.y][modele->snoopy.x];
    modele->modele[modele->snoopy.y][modele->snoopy.x] = 8;
}

void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction) {
    *derniere_direction = direction;

    int add_x = 0, add_y = 0;
    switch (direction) {
        case 'z': add_y = -1; break;
        case 'q': add_x = -1; break;
        case 's': add_y = 1;  break;
        case 'd': add_x = 1;  break;
    }

    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);

    if (nouvelle_case == 0 || nouvelle_case == 2 && pousse_bloc(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y, direction)) {
        updateSnoopy(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
    } else if (nouvelle_case == 5) {
        updateSnoopy(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
        teleportation(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
    } else if (nouvelle_case == 6) {
        updateSnoopy(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
        tapis_roulant(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y, direction);
    } else if (nouvelle_case == 9) {
        updateSnoopy(modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
        oiseaux(modele);
    }

    for (int i = 0; i < modele->nb_balles; i++) {
        struct Balle balle = modele->balles[i];
        if ((modele->snoopy.x != balle.x || modele->snoopy.y != balle.y) &&
            balle.x == modele->snoopy.x && balle.y == modele->snoopy.y) {
            modele->vies_restantes--;
            modele->message = "Oups ! Vous perdez une vie car la balle vous touche !";
        }
    }
}

void deplacer_balle(struct ModeleNiveau *modele, int i) {

    int add_x = 0;
    int add_y = 0;
    if(modele->balles[i].y == modele->hauteur-2 && modele->balles[i].direction <= 1) { // Si la balle est en bas et qu'elle va vers le bas (traitement Nord/Sud)
        modele->balles[i].direction = modele->balles[i].direction == 0 ? 3 : 2; // Sud Est -> Nord Est, Sud Ouest -> Nord Ouest
        return deplacer_balle(modele, i); // On rappelle la fonction pour deplacer la balle pour retraiter son état et changer sa direciton (est/ouest)
    }
    if(modele->balles[i].y == 1 && modele->balles[i].direction > 1) { // Si la balle est en haut et qu'elle va vers le haut (traitement Nord/Sud)
        modele->balles[i].direction = modele->balles[i].direction == 2 ? 1 : 0; // Nord Ouest -> Sud Ouest, Nord Est -> Sud Est
        return deplacer_balle(modele, i); // On rappelle la fonction pour deplacer la balle pour retraiter son état et changer sa direciton (est/ouest)
    }
    if(modele->balles[i].x == modele->largeur-2 && modele->balles[i].direction%3 == 0) { // Si la balle est a droite et qu'elle va vers la droite (traitement Est/Ouest)
        modele->balles[i].direction = modele->balles[i].direction == 3 ? 2 : 1; // Sud Est -> Sud Ouest, Nord Est -> Nord Ouest
        // Pas besoin de rappeler la fonction car la direction Nord/Sud a deja ete traitee précédemment
    }
    if(modele->balles[i].x == 1  && modele->balles[i].direction%3 != 0) { // Si la balle est a gauche et qu'elle va vers la gauche (traitement Est/Ouest)
        modele->balles[i].direction = modele->balles[i].direction == 1 ? 0 : 3; // Sud Ouest -> Sud Est, Nord Ouest -> Nord Est
        // Pas besoin de rappeler la fonction car la direction Nord/Sud a deja ete traitee précédemment
    }
    switch (modele->balles[i].direction) { // On ajoute les coordonnees en fonction de la direction
        case 0: // Sud Est
            add_y = 1; // On ajoute 1 a y pour descendre
            add_x = 1; // On ajoute 1 a x pour aller a droite
            break;
        case 1: // Sud Ouest
            add_y = 1; // On ajoute 1 a y pour descendre
            add_x = -1; // On ajoute -1 a x pour aller a gauche
            break;
        case 2: // Nord Ouest
            add_y = -1; // On ajoute -1 a y pour monter
            add_x = -1; // On ajoute -1 a x pour aller a gauche
            break;
        case 3: // Nord Est
            add_y = -1; // On ajoute -1 a y pour monter
            add_x = 1; // On ajoute 1 a x pour aller a droite
            break;
    }
    modele->balles[i].y += add_y; // On ajoute les coordonnees
    modele->balles[i].x += add_x;
}

void casse_bloc(struct ModeleNiveau *modele, const char *direction) {
    int add_x = 0, add_y = 0;
    switch (*direction) {
        case 'z': add_y = -1; break;
        case 'q': add_x = -1; break;
        case 's': add_y = 1;  break;
        case 'd': add_x = 1;  break;
    }

    int nouvelle_case = getCaseValue(*modele, modele->snoopy.x + add_x, modele->snoopy.y + add_y);
    if (nouvelle_case == 1 || nouvelle_case == 3) {
        modele->modele[modele->snoopy.y + add_y][modele->snoopy.x + add_x] = 0;
    }
    if (nouvelle_case == 3) {
        modele->vies_restantes--;
        modele->message = "Vous avez casse un bloc piege... Vous venez de perdre une vie !";
    }
}

int pousse_bloc(struct ModeleNiveau *modele, int x, int y, int direction) { // Fonction de pousse de bloc
    int add_x = 0; // On initialise les variables d'ajout de coordonnees du bloc a pousser
    int add_y = 0;
    switch (direction) { // On ajoute les coordonnees en fonction de la direction
        case 'z': // Nord
            add_y = -1; // On ajoute -1 a y pour monter
            break;
        case 'q': // Ouest
            add_x = -1; // On ajoute -1 a x pour aller a gauche
            break;
        case 's': // Sud
            add_y = 1; // On ajoute 1 a y pour descendre
            break;
        case 'd': // Est
            add_x = 1; // On ajoute 1 a x pour aller a droite
            break;
    }

    int nouvelle_case = getCaseValue(*modele, x+add_x, y+add_y); // On recupere la valeur de la case ou on veut aller
    // Si la case est vide ou un bloc poussable (dans ce cas, on rappelle la fonction pour pousser le bloc après le bloc actuel, etc)
    if(nouvelle_case == 0 || (nouvelle_case == 2 && pousse_bloc(modele, x+add_x, y+add_y, direction))) {
        modele->modele[y+add_y][x+add_x] = 4; // On met le bloc sur la case
        modele->modele[y][x] = 0; // On met la case actuelle vide
        return 1; // On retourne 1 pour dire que le bloc a bien ete pousse
    }

    return 0; // On retourne 0 pour dire que le bloc n'a pas ete pousse
}
void teleportation(struct ModeleNiveau *modele, int x, int y) { // Fonction de teleportation de snoopy
    modele->sous_case = 5;
    if(modele->nb_teleporteurs <= 1) return; // Si il n'y a pas d'autre teleporteur, on ne fait rien
    srand(time(NULL)); // On initialise le random
    struct Coordonnees tp_coord; // On initialise les coordonnees du nouveau teleporteur
    do { // On boucle les coordonnees du nouveau teleporteur tant qu'elles sont les memes que celles du tp actuel (pour ne pas se teleporter sur le meme)
        tp_coord = modele->teleporteurs[rand() % modele->nb_teleporteurs]; // On recupere les coordonnees d'un teleporteur aleatoire
    } while (tp_coord.x == x && tp_coord.y == y); // tant qu'elles sont les memes que celles du tp actuel
    modele->snoopy.x = tp_coord.x; // On teleporte snoopy
    modele->snoopy.y = tp_coord.y;
    modele->modele[modele->snoopy.y][modele->snoopy.x] = 8; // On met snoopy sur la case
}
void oiseau(struct ModeleNiveau *modele) { // Fonction de disparition de l'oiseau
    for(int i = 0; i < modele->nb_oiseaux; i++) { // On boucle les oiseaux
        struct Coordonnees oiseau = modele->oiseaux[i]; // On recupere les coordonnees de l'oiseau
        if(oiseau.x == modele->snoopy.x && oiseau.y == modele->snoopy.y) { // Si l'oiseau est sur la case de snoopy
            modele->oiseaux[i].x = modele->largeur; // On le fait disparaitre (on le met en dehors de la map)
            modele->oiseaux[i].y = modele->hauteur;
        }
    }
}
void tapis_roulant(struct ModeleNiveau *modele, int x, int y, int direction) { // Fonction de deplacement de snoopy sur un tapis roulant
    modele->modele[y][x] = 8; // On remet l'état de la case sur laquelle était snoopy
    modele->snoopy.x = x; // On ajoute les coordonnees
    modele->snoopy.y = y;
    modele->sous_case = 6; // On remet l'état de la case sous snoopy a 0 (case vide)

    int add_x = 0; // On initialise les variables d'ajout de coordonnees
    int add_y = 0;
    switch (direction) { // On ajoute les coordonnees en fonction de la direction
        case 'z': // Nord
            add_y = -1; // On ajoute -1 a y pour monter
            break;
        case 'q': // Ouest
            add_x = -1; // On ajoute -1 a x pour aller a gauche
            break;
        case 's': // Sud
            add_y = 1; // On ajoute 1 a y pour descendre
            break;
        case 'd': // Est
            add_x = 1; // On ajoute 1 a x pour aller a droite
            break;
    }

    // On recupere la valeur de la case ou on veut aller
    int nouvelle_case = getCaseValue(*modele, x+add_x, y+add_y);

    // Case vide ou bloc poussable (dans ce cas, on rappelle la fonction pour pousser le bloc après le bloc actuel, etc)
    if(nouvelle_case == 0 || (nouvelle_case == 2 && pousse_bloc(modele, x+add_x, y+add_y, direction))) {
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case; // On remet l'état de la case sur laquelle était snoopy
        modele->sous_case = 0; // On remet l'état de la case sous snoopy a 0 (case vide)
        modele->snoopy.y = y+add_y; // On ajoute les coordonnees
        modele->snoopy.x = x+add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8; // On met snoopy sur la case
    } else if(nouvelle_case == 5) { // Bloc apparition/disparition
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case; // On remet l'état de la case sur laquelle était snoopy
        teleportation(modele, x+add_x, y+add_y); // On teleporte snoopy
    } else if(nouvelle_case == 6) { // Tapis roulant
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case; // On remet l'état de la case sur laquelle était snoopy
        tapis_roulant(modele, x+add_x, y+add_y, direction); // On deplace snoopy
    } else if(nouvelle_case == 9) { // Oiseau
        modele->modele[modele->snoopy.y][modele->snoopy.x] = modele->sous_case; // On remet l'état de la case sur laquelle était snoopy
        modele->snoopy.y = y+add_y; // On ajoute les coordonnees
        modele->snoopy.x = x+add_x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8; // On met snoopy sur la case
        modele->sous_case = 0; // On remet l'état de la case sous snoopy a 0 (case vide)
        oiseau(modele); // On fait disparaitre l'oiseau
    } else { // Si la case est un bloc sur lequel snoopy ne peut pas aller (bloc piege, bloc indestructible, etc)
        modele->snoopy.y = y; // On ajoute les coordonnees
        modele->snoopy.x = x;
        modele->modele[modele->snoopy.y][modele->snoopy.x] = 8; // On met snoopy sur la case
    }
}

void handleKeypress(struct ModeleNiveau *modele, int *temps_arrivee, int *pause, int *menu_principal, char *derniere_direction) {
    if (kbhit()) {
        switch (getch()) {
            case 'p':
                if (*pause == 0) {
                    *pause = (int) time(NULL);
                    wprintf(L"Pause\n");
                } else {
                    *temps_arrivee += (int) time(NULL) - *pause;
                    *pause = 0;
                }
                break;
            case 's':
                if (*pause != 0) break;
                int pause_timestamp = (int) time(NULL);
                *menu_principal = 1;
                system("cls");
                char *nom = demande_sauvegarde_id();
                char chemin[200];
                sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);
                sauvegarder_partie(*modele, *temps_arrivee - pause_timestamp, chemin);
                break;
            case 'q':
                if (*pause != 0) break;
                *menu_principal = 1;
                break;
            case 'r':
                if (*pause != 0) break;
                if (modele->vies_restantes <= 1) {
                    system("cls");
                    wprintf(L"Vous n'avez plus qu'une vie restante ! Vous ne pouvez donc pas réessayer\n");
                    sleep(1);
                    break;
                }
                *derniere_direction = ' ';
                int score = modele->score;
                int vies = --modele->vies_restantes;
                char niveau[10];
                sprintf(niveau, "%d", modele->niveau);
                *modele = modele_niveau(niveau, 0);
                *temps_arrivee = nouveau_timer();
                modele->score = score;
                modele->vies_restantes = vies;
                system("cls");
                sleep(1);
                // Le jeu va ensuite recommencer automatiquement
            case 32: // Espace
                if (*pause != 0) break;
                casse_bloc(modele, derniere_direction);
                break;
            case 224:
                if (*pause != 0) break;
                switch (getch()) {
                    case 72: deplacer(modele, 'z', derniere_direction); break;
                    case 80: deplacer(modele, 's', derniere_direction); break;
                    case 75: deplacer(modele, 'q', derniere_direction); break;
                    case 77: deplacer(modele, 'd', derniere_direction); break;
                }
                break;
        }
    }
}

int niveau_existe(char *niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%s.txt", niveau);
    return access(path, F_OK) != -1;
}

int affiche_unite(int indice, int unites_rouges) { // Affiche une unité du chrono
    if(indice < unites_rouges) { // Si l'unité est rouge
        COULEUR(ROUGE_FONCE, NOIR); // On met la couleur en rouge
        wprintf(L"█"); // On affiche un carré plein
        COULEUR(TURQUOISE, NOIR); // On remet la couleur par défaut
        return 1; // On renvoie que l'unité est rouge
    } else { // Si l'unité est verte
        COULEUR(VERT_FONCE, NOIR); // On met la couleur en vert
        wprintf(L"█"); // On affiche un carré plein
        COULEUR(TURQUOISE, NOIR); // On remet la couleur par défaut
        return 0; // On renvoie que l'unité est verte
    }
}

struct Dimensions dimensions_niveau(int niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%d.txt", niveau);

    FILE *fichier = fopen(path, "r");
    if (!fichier) {
        perror("Impossible d'ouvrir le fichier");
    }

    char ligne[100];
    fgets(ligne, sizeof ligne, fichier);

    struct Dimensions dimensions;
    dimensions.largeur = strlen(ligne) - 1;
    dimensions.hauteur = 1;

    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        dimensions.hauteur++;
    }

    return dimensions;
}

struct ModeleNiveau modele_niveau(char *id, int sauvegarde) {
    char path[100];
    if (sauvegarde) {
        sprintf(path, "../assets/sauvegardes/%s.txt", id);
    } else {
        sprintf(path, "../assets/niveaux/%s.txt", id);
        if (!niveau_existe(id)) {
            system("cls");
            wprintf(L"Votre partie est terminee !");
            sleep(3);
            system("cls");
            afficher_fichier("../assets/ASCII/logo.txt");
            menu();
        }
    }

    struct Coordonnees snoopy = {0, 0};
    struct Coordonnees *oiseaux = malloc(4 * sizeof(struct Coordonnees));

    int temps_restant = 0;
    int niveau = atoi(id);
    int nb_vies = 3;
    int score = 0;
    int sous_case = 0;

    int nb_oiseaux = 0;
    int nb_teleporteurs = 0;
    int nb_balles = 0;

    struct Balle *balles = malloc(1 * sizeof(struct Balle));

    FILE *fichier = fopen(path, "r");
    if (!fichier)
        perror("Impossible d'ouvrir le fichier");

    if(sauvegarde) {

        char ligne[100];
        fgets(ligne, sizeof ligne, fichier);
        temps_restant = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier); // On récupère la deuxième ligne du fichier
        niveau = atoi(ligne); // On stocke le niveau

        fgets(ligne, sizeof ligne, fichier); // On récupère la troisième ligne du fichier
        nb_vies = atoi(ligne); // On stocke le nombre de vies

        fgets(ligne, sizeof ligne, fichier); // On récupère la quatrième ligne du fichier
        score = atoi(ligne); // On stocke le score

        fgets(ligne, sizeof ligne, fichier); // On récupère la cinquième ligne du fichier
        sous_case = atoi(ligne); // On stocke la sous case

        fgets(ligne, sizeof ligne, fichier); // On récupère la sixième ligne du fichier
        nb_balles = atoi(ligne); // On stocke le nombre de balles

        balles = malloc(nb_balles * sizeof(struct Balle)); // On prépare la mémoire pour stocker les balles
        for(int i = 0; i < nb_balles; i++) { // On parcourt les balles
            struct Balle balle = {0, 0, 0}; // On prépare la mémoire pour stocker les coordonnées et la direction de la balle
            fgets(ligne, sizeof ligne, fichier); // On récupère la ligne du fichier
            balle.x = atoi(ligne); // On stocke la position x de la balle
            fgets(ligne, sizeof ligne, fichier); // On récupère la ligne du fichier
            balle.y = atoi(ligne); // On stocke la position y de la balle
            fgets(ligne, sizeof ligne, fichier); // On récupère la ligne du fichier
            balle.direction = atoi(ligne); // On stocke la direction de la balle

            balles[i] = balle; // On stocke la balle dans le tableau de balles

            // On affiche les valeurs
            wprintf(L"(%d) x: %d, y: %d, direction: %d\n", i, balle.x, balle.y, balle.direction);
        }
    } else {
        id = (char *)time(NULL);
    }

    struct Dimensions dimensions = dimensions_niveau(niveau);

    int **modele = malloc(dimensions.hauteur * sizeof(int *));
    int nb_balles2 = 0;

    for(int i = 0; i < dimensions.hauteur; i++) { // On parcourt les lignes du fichier
        modele[i] = malloc(dimensions.largeur * sizeof(int)); // On prépare la mémoire pour stocker les colonnes du modèle
        for(int j = 0; j < dimensions.largeur; j++) { // On parcourt les colonnes du fichier
            char c = fgetc(fichier); // On récupère le caractère
            switch (c) { // On stocke le caractère dans le modèle
                case '\n': // Si le caractère est un retour à la ligne
                    c = fgetc(fichier); // On récupère le caractère suivant
                    break;
                case '5': // Si le caractère est un téléporteur
                    nb_teleporteurs++; // On incrémente le nombre de téléporteurs
                    break;
                case '7': // Si le caractère est la balle
                    nb_balles2++;
                    break;
                case '8': // Si le caractère est Snoopy
                    snoopy.x = j; // On stocke la position x de Snoopy
                    snoopy.y = i; // On stocke la position y de Snoopy
                    break;
                case '9': // Si le caractère est un oiseau
                    oiseaux[nb_oiseaux].x = j; // On stocke la position x de l'oiseau
                    oiseaux[nb_oiseaux].y = i; // On stocke la position y de l'oiseau
                    nb_oiseaux++; // On incrémente le nombre d'oiseaux
                    break;
            }
            modele[i][j] = (c-'0'); // On stocke le caractère dans le modèle
        }
    }

    if(!sauvegarde) balles = malloc(nb_balles2 * sizeof(struct Balle)); // On prépare la mémoire pour stocker les balles

    struct Coordonnees *teleporteurs = malloc(nb_teleporteurs * sizeof(struct Coordonnees));
    int nb_teleporteurs2 = 0;
    nb_balles2 = 0;
    for(int i = 1; i < dimensions.hauteur-1; i++) // On parcourt les lignes du modèle
        for(int j = 1; j < dimensions.largeur-1; j++) { // On parcourt les colonnes du modèle
            if (modele[i][j] == 5)
                teleporteurs[nb_teleporteurs2++] = (struct Coordonnees) {j, i}; // On stocke les coordonnées des téléporteurs
            if (modele[i][j] == 7) {
                struct Balle balle = {0, 0, rand() % 4}; // On prépare la mémoire pour stocker les coordonnées et la direction de la balle
                balle.x = j; // On stocke la position x de la balle
                balle.y = i; // On stocke la position y de la balle
                balles[nb_balles2++] = balle; // On stocke la balle dans le tableau de balles
                modele[i][j] = 0;
            }
        }
    char message[500]; // On prépare la mémoire pour stocker le message

    struct ModeleNiveau result = { // On retourne le modèle du niveau
            id,
            modele,
            dimensions.hauteur,
            dimensions.largeur,
            niveau,
            temps_restant,
            nb_vies,
            nb_oiseaux,
            nb_teleporteurs,
            nb_balles | nb_balles2,
            message,
            score,
            sous_case,
            snoopy,
            oiseaux,
            teleporteurs,
            balles
    };
    return result;
}

void afficher_niveau(struct ModeleNiveau modele, int temps_restant, char derniere_direction) { // Affiche le niveau

    // Calcul du temps restant en pourcentage (pourcentage de la barre verte)
    float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
    // Calcul du nombre d'unités rouges
    int unites_rouges = (modele.hauteur-1)*2+(modele.largeur-1)*2 - unite_chrono_restant(temps_restant_prct, modele.hauteur, modele.largeur);
    int indice_unite = 0; // On initialise l'indice de l'unité à 0

    for(int k = 0; k < modele.largeur; k++) { // On affiche la première ligne du chrono
        int z = affiche_unite(indice_unite, unites_rouges); // On affiche une unité du chrono (rouge ou verte)
        if(z) indice_unite++; // Si l'unité est rouge, on incrémente l'indice de l'unité
    }
    wprintf(L"\n"); // On affiche un retour à la ligne



    for(int i = 1; i < modele.hauteur-1; i++) { // On parcourt les lignes du modèle
        for(int j = 0; j < modele.largeur; j++) { // On parcourt les colonnes du modèle
            if(j == 0) { // Si on est sur la première colonne (donc le chrono)
                affiche_unite(2*(modele.hauteur + modele.largeur - 2) - i, unites_rouges); // On affiche une unité du chrono (rouge ou verte)
            } else if(j == modele.largeur-1) { // Si on est sur la dernière colonne (donc le chrono)
                int z = affiche_unite(indice_unite, unites_rouges); // On affiche une unité du chrono (rouge ou verte)
                if(z) indice_unite++; // Si l'unité est rouge, on incrémente l'indice de l'unité
            } else { // Si on est sur une autre colonne (donc le contenu du niveau)
                int est_sur_balle = 0;
                for(int k=0; k < modele.nb_balles; k++) {
                    if(modele.balles[k].x == j && modele.balles[k].y == i) {
                        est_sur_balle = 1;
                        wprintf(L"●"); // On affiche la balle
                        break;
                    }
                }
                if(!est_sur_balle) switch(modele.modele[i][j]) { // On affiche le contenu de la case
                        case 0: // Si la case est vide
                            wprintf(L" ");
                            break;
                        case 1: // Si la case est un bloc cassable
                            wprintf(L"▨");
                            break;
                        case 2: // Si la case est un bloc poussable
                            wprintf(L"▢");
                            break;
                        case 3: // Si la case est un bloc piégé
                            wprintf(L"▨");
                            break;
                        case 4: // Si la case est un bloc indestructible
                            wprintf(L"█");
                            break;
                        case 5: // Si la case est un téléporteur
                            wprintf(L"⏏");
                            break;
                        case 6: // Si la case est un tapis roulant
                            wprintf(L"☰");
                            break;
                        case 8: // Si la case est Snoopy
                            switch (derniere_direction) { // On affiche Snoopy en fonction de sa dernière direction
                                case 'z': // Si la dernière direction est le haut
                                    wprintf(L"▲");
                                    break;
                                case 'q': // Si la dernière direction est la gauche
                                    wprintf(L"◀");
                                    break;
                                case 's': // Si la dernière direction est le bas
                                    wprintf(L"▼");
                                    break;
                                case 'd': // Si la dernière direction est la droite
                                    wprintf(L"▶");
                                    break;
                                default: // Si la dernière direction est inconnue
                                    wprintf(L"X");
                                    break;
                            }
                            break;
                        case 9: // Si la case est un oiseau
                            wprintf(L"★");
                            break;
                    }
            }
        }
        wprintf(L"\n");
    }
    for(int k = 0; k<modele.largeur; k++) {
        int z = affiche_unite(indice_unite+modele.largeur-k, unites_rouges);
        if(z) indice_unite++;
    }
    wprintf(L"\n");
}

int unite_timer_restant(int prct_restant, int hauteur, int largeur) {
    int unites = (largeur - 1) * 2 + (hauteur - 1) * 2;
    return (unites * prct_restant) / 100;
}

int nombre_oiseaux(struct ModeleNiveau modele) { // Récupère le nombre d'oiseaux restants
    int nb_oiseaux = 0; // On initialise le nombre d'oiseaux à 0
    for(int i = 0; i < modele.nb_oiseaux; i++) { // On parcourt les oiseaux
        if(modele.oiseaux[i].x != modele.largeur && modele.oiseaux[i].y != modele.hauteur) nb_oiseaux++; // Si l'oiseau n'est pas mort, on incrémente le nombre d'oiseaux
    }

    return nb_oiseaux;
}

void nouvelle_partie(char *id) { // id = nom du fichier de sauvegarde
    game(modele_niveau(id, 0)); // 0 = niveau traditionnel, 1 = sauvegarde
}

void game(struct ModeleNiveau modele) { // Boucle principale du jeu
    // Affiche le temps restant
    system("cls"); // Clear la console
    int temps_arrivee = modele.temps_restant > 0 ? (int)time(NULL) + modele.temps_restant : nouveau_timer(); // Temps d'arrivée = temps actuel + 120 secondes
    int pause = 0; // On initialise la pause à 0 (non-pause)
    int menu_principal = 0; // On initialise le menu principal à 0 (non-ouvert)

    char derniere_direction = ' '; // On initialise la dernière direction à ' ' (inconnue)
    // Boucle principale du jeu
    // Tant que:
    // - Le temps d'arrivée est supérieur au temps actuel   OU      la pause est activée
    // - ET Il reste des oiseaux
    // - ET Il reste des vies
    // - ET Le menu principal n'est pas ouvert
    while((temps_arrivee - (int) time(NULL) > 0 || pause != 0) && nombre_oiseaux(modele) && modele.vies_restantes && !menu_principal) {
        handleKeypress(&modele, &temps_arrivee, &pause, &menu_principal, &derniere_direction); // Gestion des touches
        if(pause != 0) continue; // Si la pause est activée, on passe à l'itération suivante
        system("cls"); // Clear la console

        afficher_niveau(modele, temps_arrivee - (int) time(NULL), derniere_direction); // Afficher le niveau

        for(int i=0; i<modele.nb_balles; i++) {
            deplacer_balle(&modele, i); // Déplacer la balle
        }
        if(strlen(modele.message)) { // Si un message doit être affiché
            wprintf(L"Message: \n"); // Afficher le message
            COULEUR(ROUGE_FLUO, NOIR); // Couleur rouge
            wprintf(L"%s\n", modele.message);
            COULEUR(TURQUOISE, NOIR);
        }
        afficher_vies(modele.vies_restantes); // Afficher les vies
        for(int i=0; i<modele.nb_balles; i++) {
            if(modele.balles[i].x == modele.snoopy.x && modele.balles[i].y == modele.snoopy.y && modele.vies_restantes) { // Si la balle touche Snoopy
                modele.vies_restantes--; // On enlève une vie
                modele.message = "La balle vous a touche, vous avez perdu une vie !"; // On affiche un message
            }
        }
        usleep(250000); // On attend 250ms (0.25s)
    }

    if(menu_principal == 1) { // Si le menu principal est ouvert
        system("cls"); // Clear la console
        afficher_fichier("../assets/ASCII/logo.txt"); // Afficher le logo
        menu(); // Afficher le menu
    } else if(!nombre_oiseaux(modele)) { // Si il n'y a plus d'oiseaux
        int temps_restant = temps_arrivee - (int) time(NULL); // Temps restant = temps d'arrivée - temps actuel
        float temps_restant_prct = (float)(temps_restant * 100) / (float)120; // Temps restant en pourcentage
        modele.score += temps_restant*100; // On ajoute le score du niveau au score total
        system("cls"); // Clear la console
        afficher_fichier("../assets/ASCII/victoire.txt"); // Afficher le logo de victoire
        wprintf(L"\n\nScore du niveau %d : %d\n", modele.niveau, temps_restant*100); // Afficher le score du niveau
        wprintf(L"Temps restant : %d (%.2f%%)\n", temps_restant, temps_restant_prct); // Afficher le temps restant + pourcentage (.2f = 2 chiffres après la virgule)
        wprintf(L"Nombre de vies restantes : %d\n", modele.vies_restantes); // Afficher le nombre de vies restantes
        wprintf(L"Score total : %d\n", modele.score); // Afficher le score total
        wprintf(L"Appuyez sur une touche pour continuer...\n");
        sleep(1);
        while(!kbhit()) usleep(250000); // Attendre qu'une touche soit pressée (kbhit = keyboard hit : clavier touché)

        int score = modele.score; // On sauvegarde le score
        int vies = modele.vies_restantes; // On sauvegarde le nombre de vies restantes
        char nouveau_niveau[10]; // On initialise une variable pour le nouveau niveau
        sprintf(nouveau_niveau, "%d", modele.niveau+1); // On convertit le niveau en chaine de caractères

        modele = modele_niveau(nouveau_niveau, 0); // On charge le nouveau niveau
        modele.score = score; // On charge le score
        modele.vies_restantes = vies; // On charge le nombre de vies restantes

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt"); // On sauvegarde la partie
        charger_sauvegarde("sauvegarde_temporaire", 0); // On charge la sauvegarde
    } else if((temps_arrivee - (int) time(NULL) <= 0) || !modele.vies_restantes) { // Si le temps d'arrivée est inférieur au temps actuel OU qu'il n'y a plus de vies restantes
        system("cls"); // Clear la console
        afficher_fichier("../assets/ASCII/defaite.txt"); // Afficher le logo de défaite
        if(modele.vies_restantes) modele.vies_restantes--; // Si il reste des vies, on enlève une vie
        if(modele.vies_restantes) wprintf(L"Vous avez été pris par le temps !"); // Si il reste des vies, on affiche un message
        else wprintf(L"Vous n'avez plus de vies restantes !"); // Sinon, on affiche un autre message
        wprintf(L"\n\nNombre de vies restantes : %d\n", modele.vies_restantes);
        wprintf(L"Score total : %d\n", modele.score);

        if(!modele.vies_restantes) { // Si il n'y a plus de vies restantes
            wprintf(L"Appuyez sur une touche pour retourner au menu principal...\n");
            sleep(1);
            while(!kbhit()); // Attendre qu'une touche soit pressée (kbhit = keyboard hit : clavier touché)
            system("cls");
            afficher_fichier("../assets/ASCII/logo.txt"); // Afficher le logo
            menu(); // Afficher le menu
            return;
        }

        wprintf(L"Appuyez sur une touche pour ressayer le niveau...\n");
        sleep(1);
        while(!kbhit()); // Attendre qu'une touche soit pressée (kbhit = keyboard hit : clavier touché)

        int score = modele.score; // On sauvegarde le score
        int vies = modele.vies_restantes; // On sauvegarde le nombre de vies restantes
        char nouveau_niveau[10]; // On initialise une variable pour le nouveau niveau
        sprintf(nouveau_niveau, "%d", modele.niveau); // On convertit le niveau en chaine de caractères
        modele = modele_niveau(nouveau_niveau, 0); // On charge le nouveau niveau
        modele.score = score; // On charge le score
        modele.vies_restantes = vies; // On charge le nombre de vies restantes

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt"); // On sauvegarde la partie
        charger_sauvegarde("sauvegarde_temporaire", 0); // On charge la sauvegarde
    }
}

void afficher_vie(int vies) { // Afficher les vies
    if(vies == 0) return; // Si il n'y a plus de vies, on ne fait rien
//    tableau de 3 fichiers
    FILE *fichiers[3]; // On initialise un tableau de 3 fichiers
    for(int i=0; i<vies; i++) fichiers[i] = fopen("../assets/ASCII/coeur.txt", "r"); // On ouvre les fichiers coeur.txt

    char ligne[100]; // On initialise une variable pour la ligne
    int fin = 0; // On initialise la fin à 0 (non-fin)
    while(!fin) { // Tant que la fin n'est pas atteinte
        for(int i=0; i<vies; i++) { // Pour chaque fichier
            if(fgets(ligne, sizeof ligne, fichiers[i]) == NULL) { // Si la ligne est vide
                fin = 1; // On passe la fin à 1 (fin)
                break;
            }
            if(ligne[strlen(ligne)-1] == '\n') ligne[strlen(ligne)-1] = '\0'; // Si la ligne se termine par un retour à la ligne, on le supprime
            for(int j=0; j< strlen(ligne); j++) ligne[j] = ligne[j] == 'x' ? ' ' : ligne[j]; // On remplace les 'x' par des espaces (car les espaces sont supprimés par l'IDE)
            wprintf(L"%s", ligne); // On affiche la ligne
            if(i == vies-1) wprintf(L"\n"); // Si c'est le dernier fichier, on affiche un retour à la ligne
        }
    }

    wprintf(L"\n\n");

    for(int i=0; i<vies; i++) fclose(fichiers[i]); // On ferme les fichiers
}