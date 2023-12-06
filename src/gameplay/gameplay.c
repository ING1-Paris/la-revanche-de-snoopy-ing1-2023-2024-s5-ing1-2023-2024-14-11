//
// Created by Ewan Kapoor on 06/12/2023.
//

//Bibliothèque

#include "gameplay.h"

// Fonction qui démarre une nouvelle partie avec l'ID de sauvegarde donné
void nouvellePartie(char *id) {
    struct ModeleNiveau modele = modele_niveau(id, 0);
    jeu(modele);
}

// Fonction principale du jeu
void jeu(struct ModeleNiveau modele) {
    int temps_arrivee = (modele.temps_restant > 0) ? (int)time(NULL) + modele.temps_restant : nouveau_timer();
    int pause = 0;
    int menu_principal = 0;
    char nom_joueur[50];

    // Demande au joueur d'entrer son nom
    wprintf(L"Entrez votre nom : ");
    scanf("%s", nom_joueur);

    // Supprime le caractère de nouvelle ligne de la saisie du nom
    size_t len = wcslen(nom_joueur);
    if (nom_joueur[len - 1] == L'\n') {
        nom_joueur[len - 1] = L'\0';
    }

    char derniere_direction = ' ';

    // Boucle principale du jeu
    while ((temps_arrivee - (int)time(NULL) > 0 || pause != 0) && nombreOiseaux(modele) && modele.vies_restantes && !menu_principal) {
        // Gère les entrées du clavier
        handleKeypress(&modele, &temps_arrivee, &pause, &menu_principal, &derniere_direction);

        // Si le jeu est en pause, continue à la prochaine itération de la boucle
        if (pause != 0) continue;

        // Efface l'écran et affiche le niveau
        system("cls");
        afficherNiveau(modele, temps_arrivee - (int)time(NULL), derniere_direction);

        // Déplace les balles
        for (int i = 0; i < modele.nb_balles; i++) {
            deplacer_balle(&modele, i);
        }

        // Affiche un éventuel message
        if (strlen(modele.message)) {
            wprintf(L"Message: \n");
            COULEUR(ROUGE_FLUO, NOIR);
            wprintf(L"%s\n", modele.message);
            COULEUR(BLEU_FONCE, NOIR);
        }

        // Affiche le nombre de vies
        afficherVies(modele.vies_restantes);

        // Vérifie si une balle touche Snoopy
        for (int i = 0; i < modele.nb_balles; i++) {
            if (modele.balles[i].x == modele.snoopy.x && modele.balles[i].y == modele.snoopy.y && modele.vies_restantes) {
                modele.vies_restantes--;
                modele.message = "La balle vous a touche, vous avez perdu une vie !";
            }
        }

        // Affiche le temps restant
        afficherTempsRestant(temps_arrivee - (int)time(NULL));

        // Affiche le nombre d'oiseaux restants
        afficherOiseauxRestant(nombreOiseaux(modele));

        // Pause pour une courte période
        usleep(250000);
    }

    // Si le joueur retourne au menu principal
    if (menu_principal == 1) {
        system("cls");
        menu();
    } else if (!nombreOiseaux(modele)) {  // Si le joueur gagne
        int temps_restant = temps_arrivee - (int)time(NULL);
        float temps_restant_prct = (float)(temps_restant * 100) / (float)120;
        modele.score += temps_restant * 100;

        // Affiche l'écran de victoire
        system("cls");
        afficherFichier("../assets/ASCII/win.txt");
        wprintf(L"\n\nScore du niveau %d : %d\n", modele.niveau, temps_restant * 100);
        wprintf(L"Temps restant : %d (%.2f%%)\n", temps_restant, temps_restant_prct);
        wprintf(L"Nombre de vies restantes : %d\n", modele.vies_restantes);
        wprintf(L"Score total : %d\n", modele.score);
        wprintf(L"Appuyez sur une touche pour continuer...\n");
        sleep(1);

        // Attend que le joueur appuie sur une touche
        while (!kbhit()) usleep(250000);

        // Enregistre le résultat dans le leaderboard
        enregistrer_resultat(nom_joueur, modele.niveau, modele.score);

        // Sauvegarde la partie temporaire pour le prochain niveau
        int score = modele.score;
        int vies = modele.vies_restantes;
        char nouveau_niveau[10];
        sprintf(nouveau_niveau, "%d", modele.niveau + 1);

        modele = modele_niveau(nouveau_niveau, 0);
        modele.score = score;
        modele.vies_restantes = vies;

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt");
        charger_sauvegarde("sauvegarde_temporaire", 0);

    } else if ((temps_arrivee - (int)time(NULL) <= 0) || !modele.vies_restantes) {  // Si le joueur perd
        system("cls");
        afficherFichier("../assets/ASCII/lose.txt");

        // Réduit le nombre de vies s'il en reste
        if (modele.vies_restantes) modele.vies_restantes--;

        // Affiche le message de fin
        if (modele.vies_restantes) wprintf(L"Vous avez ete pris par le temps !");
        else wprintf(L"Vous n'avez plus de vies restantes !");

        wprintf(L"\n\nNombre de vies restantes : %d\n", modele.vies_restantes);
        wprintf(L"Score total : %d\n", modele.score);

        // Si le joueur n'a plus de vies, retourne au menu principal
        if (!modele.vies_restantes) {
            wprintf(L"Appuyez sur une touche pour retourner au menu principal...\n");
            sleep(1);

            while (!kbhit());

            system("cls");
            afficherFichier("../assets/ASCII/logo.txt");
            menu();
            return;
        }

        // Sinon, propose de ressayer le niveau
        wprintf(L"Appuyez sur une touche pour ressayer le niveau...\n");
        sleep(1);

        while (!kbhit());

        // Charge le niveau temporaire pour recommencer
        int score = modele.score;
        int vies = modele.vies_restantes;
        char nouveau_niveau[10];
        sprintf(nouveau_niveau, "%d", modele.niveau);
        modele = modele_niveau(nouveau_niveau, 0);
        modele.score = score;
        modele.vies_restantes = vies;

        sauvegarder_partie(modele, 120, "../assets/sauvegardes/sauvegarde_temporaire.txt");
        charger_sauvegarde("sauvegarde_temporaire", 0);
    }
}

// Fonction qui affiche le nombre de vies
void afficherVies(int vies) {
    setmode(_fileno(stdout), _O_U16TEXT);
    COULEUR(BLEU_FONCE, NOIR);
    wprintf(L"♥ : %d\n", vies);
}

// Fonction qui affiche le temps restant
void afficherTempsRestant(int tempsRestant) {
    setmode(_fileno(stdout), _O_U16TEXT);
    COULEUR(BLEU_FONCE, NOIR);
    wprintf(L"Timer : %d secondes\n", tempsRestant);
}

// Fonction qui affiche le nombre d'oiseaux restants
void afficherOiseauxRestant(int nombre_oiseaux(modele)) {
    setmode(_fileno(stdout), _O_U16TEXT);
    COULEUR(BLEU_FONCE, NOIR);
    wprintf(L"♫ : %d\n", nombre_oiseaux);
}

// Fonction qui vérifie si un niveau existe
int niveau_existe(char *niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%s.txt", niveau);
    return access(path, F_OK) != -1;
}

// Fonction qui affiche la bordure
int bordure(int indice) {
    COULEUR(BLEU_FONCE, NOIR);

    if (indice == 0 || indice == 1) {
        wprintf(L"█");
    } else {
        wprintf(L"█");
    }

    COULEUR(BLEU_FONCE, NOIR);
    return 0;
}

// Fonction qui récupère les dimensions d'un niveau
struct Dimensions dimensions_niveau(int niveau) {
    char path[100];
    sprintf(path, "../assets/niveaux/%d.txt", niveau);

    FILE *fichier = fopen(path, "r");
    if(fichier == NULL) {
        perror("Impossible d'ouvrir le fichier");
    }

    char ligne[100];

    fgets(ligne, sizeof ligne, fichier);

    struct Dimensions dimensions;
    dimensions.largeur = strlen(ligne)-1;
    dimensions.hauteur = 1;

    while(fgets(ligne, sizeof ligne, fichier) != NULL) {
        dimensions.hauteur++;
    }

    return dimensions;
}

// Fonction qui récupère le modèle d'un niveau
struct ModeleNiveau modele_niveau(char *id, int sauvegarde) {
    char path[100];
    if(sauvegarde) {
        sprintf(path, "../assets/sauvegardes/%s.txt", id);
    } else {
        sprintf(path, "../assets/niveaux/%s.txt", id);
        if(!niveau_existe(id)) {
            system("cls");
            wprintf(L"Votre partie est terminee !");
            sleep(3);
            system("cls");
            afficherFichier("../assets/ASCII/logo.txt");
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
    if(fichier == NULL)
        perror("Impossible d'ouvrir le fichier");

    if(sauvegarde) {
        char ligne[100];
        fgets(ligne, sizeof ligne, fichier);
        temps_restant = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        niveau = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        nb_vies = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        score = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        sous_case = atoi(ligne);

        fgets(ligne, sizeof ligne, fichier);
        nb_balles = atoi(ligne);

        balles = malloc(nb_balles * sizeof(struct Balle));
        for(int i = 0; i < nb_balles; i++) {
            struct Balle balle = {0, 0, 0};
            fgets(ligne, sizeof ligne, fichier);
            balle.x = atoi(ligne);
            fgets(ligne, sizeof ligne, fichier);
            balle.y = atoi(ligne);
            fgets(ligne, sizeof ligne, fichier);
            balle.direction = atoi(ligne);

            balles[i] = balle;

            wprintf(L"(%d) x: %d, y: %d, direction: %d\n", i, balle.x, balle.y, balle.direction);
        }
    } else id = (char *)time(NULL);

    struct Dimensions dimensions = dimensions_niveau(niveau);

    int **modele = malloc(dimensions.hauteur * sizeof(int *));
    int nb_balles2 = 0;
    for(int i = 0; i < dimensions.hauteur; i++) {
        modele[i] = malloc(dimensions.largeur * sizeof(int));
        for(int j = 0; j < dimensions.largeur; j++) {
            char c = fgetc(fichier);
            switch (c) {
                case '\n':
                    c = fgetc(fichier);
                    break;
                case '5':
                    nb_teleporteurs++;
                    break;
                case '7':
                    nb_balles2++;
                    break;
                case '8':
                    snoopy.x = j;
                    snoopy.y = i;
                    break;
                case '9':
                    oiseaux[nb_oiseaux].x = j;
                    oiseaux[nb_oiseaux].y = i;
                    nb_oiseaux++;
                    break;
            }
            modele[i][j] = (c-'0');
        }
    }

    if(!sauvegarde) balles = malloc(nb_balles2 * sizeof(struct Balle));

    struct Coordonnees *teleporteurs = malloc(nb_teleporteurs * sizeof(struct Coordonnees));
    int nb_teleporteurs2 = 0;
    nb_balles2 = 0;
    for(int i = 1; i < dimensions.hauteur-1; i++)
        for(int j = 1; j < dimensions.largeur-1; j++) {
            if (modele[i][j] == 5)
                teleporteurs[nb_teleporteurs2++] = (struct Coordonnees) {j, i};
            if (modele[i][j] == 7) {
                struct Balle balle = {0, 0, rand() % 4};
                balle.x = j;
                balle.y = i;
                balles[nb_balles2++] = balle;
                modele[i][j] = 0;
            }
        }
    char message[500];

    struct ModeleNiveau result = {
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

// Fonction qui affiche le niveau
void afficherNiveau(struct ModeleNiveau modele, int temps_restant, char derniere_direction) {
    for(int k = 0; k < modele.largeur; k++) {
        int z = bordure(k);
    }
    wprintf(L"\n");

    for(int i = 1; i < modele.hauteur-1; i++) {
        for(int j = 0; j < modele.largeur; j++) {
            if(j == 0 || j == modele.largeur-1) {
                int z = bordure(j);
            } else {
                int est_sur_balle = 0;
                for(int k = 0; k < modele.nb_balles; k++) {
                    if(modele.balles[k].x == j && modele.balles[k].y == i) {
                        est_sur_balle = 1;
                        COULEUR(BLANC, NOIR);
                        wprintf(L"☺");
                        COULEUR(BLEU_FONCE, NOIR);
                        break;
                    }
                }
                if(!est_sur_balle) switch(modele.modele[i][j]) {
                        case 0:
                            wprintf(L" ");
                            break;
                        case 1:
                            wprintf(L"♠");
                            break;
                        case 2:
                            wprintf(L"→");
                            break;
                        case 3:
                            wprintf(L"♣");
                            break;
                        case 4:
                            wprintf(L"☼");
                            break;
                        case 5:
                            wprintf(L"◘");
                            break;
                        case 6:
                            wprintf(L"▬");
                            break;
                        case 8:
                            COULEUR(BLANC, NOIR);
                            switch (derniere_direction) {
                                case 'z':
                                    wprintf(L"♂");
                                    break;
                                case 'q':
                                    wprintf(L"♂");
                                    break;
                                case 's':
                                    wprintf(L"♂");
                                    break;
                                case 'd':
                                    wprintf(L"♂");
                                    break;
                                default:
                                    wprintf(L"♂");
                                    break;
                            }
                            COULEUR(BLEU_FONCE, NOIR);
                            break;
                        case 9:
                            COULEUR(JAUNE, NOIR);
                            wprintf(L"♫");
                            COULEUR(BLEU_FONCE, NOIR);
                            break;
                    }
            }
        }
        wprintf(L"\n");
    }
    for(int k = 0; k < modele.largeur; k++) {
        int z = bordure(k);
    }
    wprintf(L"\n");
}

// Fonction qui retourne le nombre d'oiseaux restants
int nombreOiseaux(struct ModeleNiveau modele) {
    int nb_oiseaux = 0;
    for(int i = 0; i < modele.nb_oiseaux; i++) {
        if(modele.oiseaux[i].x != modele.largeur && modele.oiseaux[i].y != modele.hauteur) nb_oiseaux++;
    }

    return nb_oiseaux;
}