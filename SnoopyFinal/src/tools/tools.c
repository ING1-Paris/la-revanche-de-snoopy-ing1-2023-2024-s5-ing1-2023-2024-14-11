//
// Created by Ewan Kapoor on 06/12/2023.
//

#include "tools.h"
#include "../menu/menu.h"

// Fonction qui retourne un timestamp pour un nouveau timer (120 secondes plus tard)
int nouveau_timer() {
    return (int)time(NULL) + 120;  // Retourne le timestamp de fin (timestamp: nombre de secondes écoulées depuis le 1er janvier 1970)
}

// Vérifie si l'id de la sauvegarde est valide
int sauvegarde_id_valide(char *id) {
    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", id);
    return access(chemin, F_OK) != -1;  // Retourne 1 si le fichier existe, 0 sinon
}

// Vérifie si la touche Escape a été appuyée
int touche_escape_appuyee() {
    if (_kbhit()) {
        int touche = _getch();
        if (touche == 27) {
            return 1;  // La touche Escape a été appuyée
        }
    }
    return 0;  // La touche Escape n'a pas été appuyée
}

// Charge une sauvegarde
struct ModeleNiveau charger_sauvegarde(char *id, int code) {
    char nouvel_id[50];
    if (code == -1) {
        system("cls");
        afficherFichier("../assets/ASCII/sauvegarde_titre.txt");
        wprintf(L"Veuillez entrer l'id de la sauvegarde (Appuyez sur Escape pour revenir au menu) : \n");

        while (1) {
            if (touche_escape_appuyee()) {
                menu();
                system("cls");
                menu();
            }

            if (_kbhit()) {
                scanf("%s", nouvel_id);
                break;
            }
        }

        return charger_sauvegarde(nouvel_id, 0);
    } else if(code == -2) {
        wprintf(L"Sauvegarde invalide, Veuillez reessayer : \n");
        scanf("%s", nouvel_id);
        return charger_sauvegarde(nouvel_id, 0);
    } else {
        wprintf(L"Chargement de la sauvegarde \"%s\"\n", id);
        if(!sauvegarde_id_valide(id))
            return charger_sauvegarde(nouvel_id, -2);
        else {
            struct ModeleNiveau sauvegarde = modele_niveau(id, 1);
            jeu(sauvegarde);
        }
    }
}

// Sauvegarde les données d'une partie dans un fichier
void sauvegarder_partie(struct ModeleNiveau modele, int temps_restant, char* chemin) {
    FILE *fichier = fopen(chemin, "w");
    fprintf(fichier, "%d\n", temps_restant);
    fprintf(fichier, "%d\n", modele.niveau);
    fprintf(fichier, "%d\n", modele.vies_restantes);
    fprintf(fichier, "%d\n", modele.score);
    fprintf(fichier, "%d\n", modele.sous_case);
    fprintf(fichier, "%d", modele.nb_balles);

    for(int i = 0; i < modele.nb_balles; i++) {
        fprintf(fichier, "\n%d", modele.balles[i].x);
        fprintf(fichier, "\n%d", modele.balles[i].y);
        fprintf(fichier, "\n%d", modele.balles[i].direction);
    };

    for (int i = 0; i < modele.hauteur; i++) {
        fprintf(fichier, "\n");
        for (int j = 0; j < modele.largeur; j++) {
            fprintf(fichier, "%d", modele.modele[i][j]);
        }
    }
    fclose(fichier);
}

// Demande et retourne l'id pour une nouvelle sauvegarde
char *demande_sauvegarde_id() {
    char *nom = malloc(50 * sizeof(char));
    wprintf(L"Veuillez entrer le nom de la sauvegarde :");
    scanf("%s", nom);

    char chemin[100];
    sprintf(chemin, "../assets/sauvegardes/%s.txt", nom);

    if(access(chemin, F_OK) != -1) {
        wprintf(L"Une sauvegarde avec ce nom existe deja, voulez vous l'ecraser ? (o/n)\n");
        char reponse;
        scanf("%c", &reponse);
        if(reponse == 'n') return demande_sauvegarde_id();
    }

    return nom;
}

// Structure pour stocker les informations d'un joueur
typedef struct {
    char nom_joueur[50];
    int niveau;
    int score_total;
} Joueur;

// Fonction de comparaison pour le tri des joueurs
int comparaison(const void *a, const void *b) {
    return ((Joueur *)b)->score_total - ((Joueur *)a)->score_total;
}

// Enregistre le résultat d'une partie dans le leaderboard
void enregistrer_resultat(char *nom_joueur, int niveau, int score_total) {
    FILE *fichier = fopen("../assets/leaderboard.txt", "a+");  // Ouvrir le fichier en mode append et lecture

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier leaderboard.txt");
        exit(EXIT_FAILURE);
    }

    // Vérifie si la séquence ASCII a déjà été écrite (au début du fichier)
    long position = ftell(fichier);
    if (position == 0) {
        // Affichage du texte ASCII dans le fichier
        fprintf(fichier, ".----..-.     .--.   .----. .----..----..-.  .-..----..-. .-..-----.\n");
        fprintf(fichier, "| }`-'} |    / {} \\ { {__-`{ {__-`} |__}}  \\/  {} |__}|  \\{ |`-' '-'\n");
        fprintf(fichier, "| },-.} '--./  /\\  \\.-._} }.-._} }} '__}| {  } |} '__}| }\\  {  } {\n");
        fprintf(fichier, "`----'`----'`-'  `-'`----' `----' `----'`-'  `-'`----'`-' `-'  `-'\n");
    }

    // Vérifie si le joueur existe déjà
    int joueur_existe = 0;
    Joueur joueurs[MAX_JOUEURS];
    int nombre_joueurs = 0;

    rewind(fichier);  // Retour au début du fichier pour la lecture
    while (fscanf(fichier, "%s %d %d", joueurs[nombre_joueurs].nom_joueur,
                  &joueurs[nombre_joueurs].niveau,
                  &joueurs[nombre_joueurs].score_total) == 3) {
        nombre_joueurs++;
        if (strcmp(joueurs[nombre_joueurs - 1].nom_joueur, nom_joueur) == 0) {
            joueur_existe = 1;
            if (score_total > joueurs[nombre_joueurs - 1].score_total) {
                joueurs[nombre_joueurs - 1].niveau = niveau;
                joueurs[nombre_joueurs - 1].score_total = score_total;
            }
            break;
        }
    }

    if (!joueur_existe) {
        if (nombre_joueurs < MAX_JOUEURS) {
            strcpy(joueurs[nombre_joueurs].nom_joueur, nom_joueur);
            joueurs[nombre_joueurs].niveau = niveau;
            joueurs[nombre_joueurs].score_total = score_total;
            nombre_joueurs++;
        } else {
            fprintf(stderr, "Le nombre maximal de joueurs est atteint.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Trie les joueurs par score total en ordre décroissant
    qsort(joueurs, nombre_joueurs, sizeof(Joueur), comparaison);

    // Écriture des joueurs dans le fichier
    rewind(fichier);  // Retour au début du fichier pour l'écriture
    for (int i = 0; i < nombre_joueurs; i++) {
        fprintf(fichier, "\n\nNom = %s\n", joueurs[i].nom_joueur);
        fprintf(fichier, "Score = %d\n", joueurs[i].score_total);
        fprintf(fichier, "Niveau = %d\n", joueurs[i].niveau);
    }

    fclose(fichier);
}

// Affiche le contenu d'un fichier
void afficherFichier(char *path) {
    FILE *fichier = fopen(path, "r");

    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char ligne[100];
    while(fgets(ligne, sizeof ligne, fichier) != NULL)
        wprintf(L"%s", ligne);
    wprintf(L"\n");
    fclose(fichier);
}

// Change la couleur du texte dans la console
void COULEUR(int couleurDuTexte,int couleurDeFond) {
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}