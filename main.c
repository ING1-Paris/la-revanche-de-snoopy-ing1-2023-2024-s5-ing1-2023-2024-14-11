#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define LIGNES 22
#define COLONNES 22

int main(void) {
    int touche;

    printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
           "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
           "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
           "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
           "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
           "                                                                                                                     \n");
    printf(" Les regles du jeu sont les suivantes : \n");
    printf(" \t - Initialement, vous possedez 3 vies \n");
    printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et recommencez le niveau. \n");
    printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis (si presents).\n");
    printf(" Cliquer sur A et entrer pour acceder aux niveaux\n");

    char ligne[LIGNES] = "____________________";
    char colonne[COLONNES] = "|                    |";
    int i, x = 6, y = 11;
    char jeu[12][22] = {""};
    int fin[4] = {0};
    int total={0};

    do {
        touche = getchar();
        if (touche == 'a') {
            printf("Niveau 1 :\n");
            printf(" \t -> Cliquer sur b pour entrer dans le niveau 1 :  \n");
        }
    }
    while (touche != 'a');

    do {
        touche = getchar();
        if (touche == 'b') {
            printf("Appuyer sur : \n");
            printf("\t - Z pour monter \n");
            printf("\t - S pour descendre \n");
            printf("\t - D pour aller a droite\n");
            printf("\t - Q pour aller a gauche \n");

            strcpy(jeu[0], ligne);
            printf("%s\n", jeu[0]);

            for (i = 1; i < 11; i++) {
                strcpy(jeu[i], colonne);
                jeu[6][11] = 0xB;
                jeu[1][1] = 0xE;
                jeu[10][1] = 0xE;
                jeu[1][20] = 0xE;
                jeu[10][20] = 0xE;
                jeu[5][10] = 0x6;
                printf("%s\n", jeu[i]);
            }
            strcpy(jeu[11], ligne);
            printf("%s\n", jeu[11]);
            printf("%d %d\n", x, y);
            printf("%c%c%c", 0x03, 0x03, 0x03);
        }
    }
    while (touche != 'b');

    do {

        touche = getchar();

        if (touche == 'z') {
            if (x > 1) x = x - 1;
        }

        if (touche == 's') {
            if (x < 10) x = x + 1;
        }
        if (touche == 'd') {
            if (y < 20) y = y + 1;
        }

        if (touche == 'q') {
            if (y > 1) y = y - 1;
        }

        if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {

            strcpy(jeu[0], ligne);
            printf("%s\n", jeu[0]);
            for (i = 1; i < 11; i++) {
                strcpy(jeu[i], colonne);
                if (fin[0] != 1) jeu[1][1] = 0xE;
                if (fin[1] != 1) jeu[10][1] = 0xE;
                if (fin[2] != 1) jeu[1][20] = 0xE;
                if (fin[3] != 1) jeu[10][20] = 0xE;
                jeu[5][10] = 0x6;
                jeu[x][y] = 0xB;
                if (x==1 && y==1) fin[0]=1;
                if (x==10 && y==1) fin[1]=1;
                if (x==1 && y==20) fin[2]=1;
                if (x==10 && y==20) fin[3]=1;
                printf("%s\n", jeu[i]);
            }
            strcpy(jeu[11], ligne);
            printf("%s\n", jeu[11]);
            printf("%d %d\n", x, y);
            printf("%c%c%c", 0x03, 0x03, 0x03);
            if (fin[0]==1 || fin[1]==1 || fin[2]==1 || fin[3]==1) {
                total = fin[0]+fin[1]+fin[2]+fin[3];
                printf("vous avez %d oiseau(x)",total);
            }
            if (total ==4) {
                printf("Vous avez tous vos oiseaux, le niveau est fini");
                touche='m';
            }
        }
    }
    while (touche != 'm');
}

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    // Add your code to print the timer data
    printf("%02d:%02d\n", minute, second);
}

int counter(int touche) {
    Color(5, 0);
    while (touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        second++;
        if (second > 59) {
            second = 0;
            minute++;

            if (minute == 2*(m+1)) {
                printf("Timer 120s, vous avez perdu une vie.\n");
                mort[m]=1;
                m=m+1;
            }
        }
        printData();
        sleep(1);

        if (kbhit()) {
            touche = getchar();
        }
    }
    return touche;
}

int main(void) {
    printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
           "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
           "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
           "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
           "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
           "                                                                                                                     \n");
    Color(4, 0);
    printf(" Les regles du jeu sont les suivantes : \n");
    printf(" \t - Initialement, vous possedez 3 vies \n");
    printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
    printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
    Color(0, 8);
    printf(" Cliquer sur A et entrer pour acceder aux niveaux\n");

    char ligne1[22] = "|                    |";
    char jeu[12][22] = {""};

    do {
        touche = getchar();
        if (touche == 'a') {
            printf("Niveau 1 :\n");
            printf(" \t -> Cliquer sur b pour entrer dans le niveau 1 :  \n");
        }
    } while (touche != 'a');

    do {
        touche = getchar();
        if (touche == 'b') {
            Color(11, 0);
            printf("Appuyer sur : \n");
            printf("\t - Z pour monter \n");
            printf("\t - S pour descendre \n");
            printf("\t - D pour aller a droite\n");
            printf("\t - Q pour aller a gauche \n");
            Color(15, 0);
            for (j = 0; j < 16; j++) {
                jeu[0][j] = 0xF;
            }
            printf("%s\n", jeu[0]);

            for (int i = 1; i < 11; i++) {
                strcpy(jeu[i], ligne1);
                jeu[i][0] = 0xF;
                jeu[i][21] = 0xF;
                jeu[6][11] = 0xB;
                jeu[1][1] = 0xE;
                jeu[10][1] = 0xE;
                jeu[1][20] = 0xE;
                jeu[10][20] = 0xE;
                jeu[5][10] = 0x6;
                printf("%s\n", jeu[i]);
            }

            for (j = 0; j < 16; j++) {
                jeu[11][j] = 0xF;
            }
            printf("%s\n", jeu[11]);
            printf("%d %d\n", x, y);
            printf("%c%c%c\n", 0x03, 0x03, 0x03);
        }
    } while (touche != 'b');

    do {
        touche = getchar();
        touche = counter(touche);
        Color(15, 0);
        if (touche == 'z') {
            if (x > 1) x = x - 1;
        }

        if (touche == 's') {
            if (x < 10) x = x + 1;
        }
        if (touche == 'd') {
            if (y < 20) y = y + 1;
        }

        if (touche == 'q') {
            if (y > 1) y = y - 1;
        }

        if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
            for (j = 0; j < 16; j++) {
                jeu[0][j] = 0xF;
            }
            printf("%s\n", jeu[0]);

            for (int i = 1; i < 11; i++) {
                strcpy(jeu[i], ligne1);
                jeu[i][0] = 0xF;
                jeu[i][21] = 0xF;
                if (fin[0] != 1) jeu[1][1] = 0xE;
                if (fin[1] != 1) jeu[10][1] = 0xE;
                if (fin[2] != 1) jeu[1][20] = 0xE;
                if (fin[3] != 1) jeu[10][20] = 0xE;
                jeu[5][10] = 0x6;
                jeu[x][y] = 0xB;

                if (x == 1 && y == 1) fin[0] = 1;
                if (x == 10 && y == 1) fin[1] = 1;
                if (x == 1 && y == 20) fin[2] = 1;
                if (x == 10 && y == 20) fin[3] = 1;

                printf("%s\n", jeu[i]);
            }

            for (j = 0; j < 16; j++) {
                jeu[11][j] = 0xF;
            }
            printf("%s\n", jeu[11]);
            printf("%d %d\n", x, y);
            if (mort[0]!=1) printf("%c", 0x03);
            if (mort[1]!=1) printf("%c", 0x03);
            if (mort[2]!=1) printf("%c\n", 0x03);
            if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                total = fin[0] + fin[1] + fin[2] + fin[3];
                printf("vous avez %d oiseau(x)\n", total);
            }
            if (total == 4) {
                printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                touche = 'm';
            }
            if (mort[2]==1){
                printf("vous n avez plus de vie, GAME OVER");
            }
        }
    } while (touche != 'm'|| mort[2]!=1);

}



//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//
//int main() {
//    int chrono = 120;
//    int a;
//    for(a=chrono;a>0;a--){
//        printf("%ds\n",a);
//        sleep(1);
//    }


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;
char ligne1[22] = "|                    |";
char jeu[12][22] = {""};
int choixmenu;
char niveauchoisi[2];



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    printf("%02d:%02d\n", minute, second);
}

int counter(int touche) {
    Color(5, 0);
    while (touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        second++;
        if (second > 59) {
            second = 0;
            minute++;

            if (minute == 2*(m+1)) {
                printf("Timer 120s, vous avez perdu une vie.\n");
                mort[m]=1;
                m=m+1;
            }
        }
        printData();
        sleep(1);

        touche =0;
        if (kbhit()){
            touche = getch();
        }
    }
    return touche;
}

int main(void) {
    char motdepasse1 [20] = "SNOOPY";
    char motdepasse2 [20] ="JEUVIDEO";

    do {
        printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
               "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
               "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
               "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
               "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
               "                                                                                                                     \n");
        Color(4, 0);
        printf("MENU\n");
        printf("1. Les regles du jeu \n");
        printf("2. Les niveaux \n");
        printf("0. Quitter\n");
        scanf("%d", &choixmenu);
        getchar();

        switch (choixmenu) {
            case 1 :
                printf(" Les regles du jeu sont les suivantes : \n");
                printf(" \t - Initialement, vous possedez 3 vies \n");
                printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
                printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
                break;
            case 2 :
                printf(" A. Niveau 1 \n");
                printf(" B. Niveau 2 \n");
                printf(" C. Niveau 3 \n");
                scanf(" %s", niveauchoisi);
                getchar();


                switch (niveauchoisi[0]) {
                    case 'a' :
                        do {
                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[6][11] = 0xB;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[5][10] = 0x6;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);
                        } while (niveauchoisi[0] != 'a');

                        do {
                            touche = getchar();
                            touche = counter(touche);
                            Color(15, 0);
                            if (touche == 'z') {
                                if (x > 1) x = x - 1;
                            }

                            if (touche == 's') {
                                if (x < 10) x = x + 1;
                            }
                            if (touche == 'd') {
                                if (y < 20) y = y + 1;
                            }

                            if (touche == 'q') {
                                if (y > 1) y = y - 1;
                            }

                            if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    if (fin[0] != 1) jeu[1][1] = 0xE;
                                    if (fin[1] != 1) jeu[10][1] = 0xE;
                                    if (fin[2] != 1) jeu[1][20] = 0xE;
                                    if (fin[3] != 1) jeu[10][20] = 0xE;
                                    jeu[5][10] = 0x6;
                                    jeu[x][y] = 0xB;

                                    if (x == 1 && y == 1) fin[0] = 1;
                                    if (x == 10 && y == 1) fin[1] = 1;
                                    if (x == 1 && y == 20) fin[2] = 1;
                                    if (x == 10 && y == 20) fin[3] = 1;

                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            if (mort[0] != 1) printf("%c", 0x03);
                            if (mort[1] != 1) printf("%c", 0x03);
                            if (mort[2] != 1) printf("%c\n", 0x03);
                            if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                total = fin[0] + fin[1] + fin[2] + fin[3];
                                printf("vous avez %d oiseau(x)\n", total);
                            }
                            if (total == 4) {
                                printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                printf("Le mot de passe pour le niveau 2 est : SNOOPY");
                                return 0;
                            }

                            if (mort[2] == 1) {
                                printf("vous n'avez plus de vie, GAME OVER");
                            }
                        } while (touche != 'm' || mort[2] != 1);

                        break;

                    case 'b' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer);
                        getchar();

                        if (strcmp(motdepasseentrer,motdepasse1) == 0) {
                            do {
                                Color(11, 0);
                                printf("Appuyer sur : \n");
                                printf("\t - Z pour monter \n");
                                printf("\t - S pour descendre \n");
                                printf("\t - D pour aller a droite\n");
                                printf("\t - Q pour aller a gauche \n");
                                Color(15, 0);
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    jeu[6][11] = 0xB;
                                    jeu[1][1] = 0xE;
                                    jeu[10][1] = 0xE;
                                    jeu[1][20] = 0xE;
                                    jeu[10][20] = 0xE;
                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                printf("%c%c%c\n", 0x03, 0x03, 0x03);
                            } while (niveauchoisi[0] != 'b');

                            do {
                                touche = getchar();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 3 est : JEUVIDEO\n");
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' || mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                    case 'c' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer2[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer2);
                        getchar();

                        if (strcmp(motdepasseentrer2,motdepasse2) == 0) {
                            do {
                                Color(11, 0);
                                printf("Appuyer sur : \n");
                                printf("\t - Z pour monter \n");
                                printf("\t - S pour descendre \n");
                                printf("\t - D pour aller a droite\n");
                                printf("\t - Q pour aller a gauche \n");
                                Color(15, 0);
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    jeu[6][11] = 0xB;
                                    jeu[1][1] = 0xE;
                                    jeu[10][1] = 0xE;
                                    jeu[1][20] = 0xE;
                                    jeu[10][20] = 0xE;
                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                printf("%c%c%c\n", 0x03, 0x03, 0x03);
                            } while (niveauchoisi[0] != 'c');

                            do {
                                touche = getch();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (tolower(touche) == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (tolower(touche) == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (tolower(touche) == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' || mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                }
                break;
        }
    }
    while (choixmenu != 0);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;
char ligne1[22] = "|                    |";
char jeu[12][22] = {""};
int choixmenu;
char niveauchoisi[2];
int score = 0;



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    printf("%02d:%02d\n", minute, second);
}

int counter(int touche) {
    Color(5, 0);
    while (touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        second++;
        if (second > 59) {
            second = 0;
            minute++;

            if (minute == 2*(m+1)) {
                printf("Timer 120s, vous avez perdu une vie.\n");
                mort[m]=1;
                m=m+1;
            }
        }
        printData();
        sleep(1);

        touche =0;
        if (kbhit()){
            touche = getchar();
        }
    }
    return touche;
}

int main(void) {
    char motdepasse1 [20] = "SNOOPY";
    char motdepasse2 [20] ="JEUVIDEO";

    do {
        printf(" \n");
        printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
               "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
               "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
               "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
               "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
               "                                                                                                                     \n");
        printf(" Les regles du jeu sont les suivantes : \n");
        Color(4, 0);
        printf("MENU\n");
        printf("1. Les regles du jeu \n");
        printf("2. Les niveaux \n");
        printf("0. Quitter\n");
        scanf("%d", &choixmenu);
        getchar();

        switch (choixmenu) {
            case 1 :
                printf(" Les regles du jeu sont les suivantes : \n");
                printf(" \t - Initialement, vous possedez 3 vies \n");
                printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
                printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
                break;
            case 2 :
                printf(" A. Niveau 1 \n");
                printf(" B. Niveau 2 \n");
                printf(" C. Niveau 3 \n");
                scanf(" %s", niveauchoisi);
                getchar();


                switch (niveauchoisi[0]) {
                    case 'a' :
                        do {
                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[6][11] = 0xB;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[5][10] = 0x6;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);
                        } while (niveauchoisi[0] != 'a');

                        do {
                            touche = getchar();
                            touche = counter(touche);
                            Color(15, 0);
                            if (touche == 'z') {
                                if (x > 1) x = x - 1;
                            }

                            if (touche == 's') {
                                if (x < 10) x = x + 1;
                            }
                            if (touche == 'd') {
                                if (y < 20) y = y + 1;
                            }

                            if (touche == 'q') {
                                if (y > 1) y = y - 1;
                            }

                            if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    if (fin[0] != 1) jeu[1][1] = 0xE;
                                    if (fin[1] != 1) jeu[10][1] = 0xE;
                                    if (fin[2] != 1) jeu[1][20] = 0xE;
                                    if (fin[3] != 1) jeu[10][20] = 0xE;
                                    jeu[5][10] = 0x6;
                                    jeu[x][y] = 0xB;

                                    if (x == 1 && y == 1) fin[0] = 1;
                                    if (x == 10 && y == 1) fin[1] = 1;
                                    if (x == 1 && y == 20) fin[2] = 1;
                                    if (x == 10 && y == 20) fin[3] = 1;

                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            if (mort[0] != 1) printf("%c", 0x03);
                            if (mort[1] != 1) printf("%c", 0x03);
                            if (mort[2] != 1) printf("%c\n", 0x03);
                            if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                total = fin[0] + fin[1] + fin[2] + fin[3];
                                printf("vous avez %d oiseau(x)\n", total);
                            }
                            if (total == 4) {
                                printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                printf("Le mot de passe pour le niveau 2 est : SNOOPY");
                                int score1 = (2 * 60 - minute * 60 - second)*100;
                                score += score1;
                                printf("Pour le niveau 1 vos avez obtenu %d points",score1);
                                return 0;
                            }

                            if (mort[2] == 1) {
                                printf("vous n'avez plus de vie, GAME OVER");
                            }
                        } while (touche != 'm' || mort[2] != 1);


                        break;

                    case 'b' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer);
                        getchar();

                        if (strcmp(motdepasseentrer,motdepasse1) == 0) {
                            do {
                                Color(11, 0);
                                printf("Appuyer sur : \n");
                                printf("\t - Z pour monter \n");
                                printf("\t - S pour descendre \n");
                                printf("\t - D pour aller a droite\n");
                                printf("\t - Q pour aller a gauche \n");
                                Color(15, 0);
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    jeu[6][11] = 0xB;
                                    jeu[1][1] = 0xE;
                                    jeu[10][1] = 0xE;
                                    jeu[1][20] = 0xE;
                                    jeu[10][20] = 0xE;
                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                printf("%c%c%c\n", 0x03, 0x03, 0x03);
                            } while (niveauchoisi[0] != 'b');

                            do {
                                touche = getchar();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 3 est : JEUVIDEO\n");
                                    int score2 = (2 * 60 - minute * 60 - second)*100;
                                    score += score2;
                                    printf("Pour le niveau 2 vos avez obtenu %d points",score2);
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' || mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                    case 'c' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer2[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer2);
                        getchar();

                        if (strcmp(motdepasseentrer2,motdepasse2) == 0) {
                            do {
                                Color(11, 0);
                                printf("Appuyer sur : \n");
                                printf("\t - Z pour monter \n");
                                printf("\t - S pour descendre \n");
                                printf("\t - D pour aller a droite\n");
                                printf("\t - Q pour aller a gauche \n");
                                Color(15, 0);
                                for (j = 0; j < 16; j++) {
                                    jeu[0][j] = 0xF;
                                }
                                printf("%s\n", jeu[0]);

                                for (int i = 1; i < 11; i++) {
                                    strcpy(jeu[i], ligne1);
                                    jeu[i][0] = 0xF;
                                    jeu[i][21] = 0xF;
                                    jeu[6][11] = 0xB;
                                    jeu[1][1] = 0xE;
                                    jeu[10][1] = 0xE;
                                    jeu[1][20] = 0xE;
                                    jeu[10][20] = 0xE;
                                    printf("%s\n", jeu[i]);
                                }

                                for (j = 0; j < 16; j++) {
                                    jeu[11][j] = 0xF;
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                printf("%c%c%c\n", 0x03, 0x03, 0x03);
                            } while (niveauchoisi[0] != 'c');

                            do {
                                touche = getch();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (tolower(touche) == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (tolower(touche) == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (tolower(touche) == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    int score3 = (2 * 60 - minute * 60 - second)*100;
                                    score += score3;
                                    printf("Pour le niveau 3 vous avez obtenu %d points",score3);
                                    printf("Votre score total est de %d points",score);
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' || mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                }
                break;
        }
    }
    while (choixmenu != 0);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;
char ligne1[22] = "|                    |";
char jeu[12][22] = {""};
int choixmenu;
char niveauchoisi[2];
int score = 0;
char nomfichier[30];
char nomficentier[50];



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    printf("%02d:%02d\n", minute, second);
}

int counter(int touche) {
    Color(5, 0);
    while (touche != 'w' && touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        second++;
        if (second > 59) {
            second = 0;
            minute++;

            if (minute == 2*(m+1)) {
                printf("Timer 120s, vous avez perdu une vie.\n");
                mort[m]=1;
                m=m+1;
            }
        }
        printData();
        sleep(1);

        touche =0;
        if (kbhit()){
            touche = getchar();
        }
    }
    return touche;
}

void map (int x, int y){
    for (j = 0; j < 16; j++) {
        jeu[0][j] = 0xF;
    }
    printf("%s\n", jeu[0]);

    for (int i = 1; i < 11; i++) {
        strcpy(jeu[i], ligne1);
        jeu[i][0] = 0xF;
        jeu[i][21] = 0xF;
        jeu[1][1] = 0xE;
        jeu[10][1] = 0xE;
        jeu[1][20] = 0xE;
        jeu[10][20] = 0xE;
        jeu[5][10] = 0x6;
        jeu[x][y] = 0xB;
        printf("%s\n", jeu[i]);
    }

    for (j = 0; j < 16; j++) {
        jeu[11][j] = 0xF;
    }
    printf("%s\n", jeu[11]);
    printf("%d %d\n", x, y);
    printf("%c%c%c\n", 0x03, 0x03, 0x03);

}

int main(void) {
    char motdepasse1 [20] = "SNOOPY";
    char motdepasse2 [20] ="JEUVIDEO";

    do {
        printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
               "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
               "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
               "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
               "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
               "                                                                                                                     \n");
        Color(4, 0);
        printf("MENU\n");
        printf("1. Les regles du jeu \n");
        printf("2. Charger une partie \n");
        printf("3. Jouer une partie \n");
        printf("0. Quitter\n");
        scanf("%d", &choixmenu);
        getchar();

        switch (choixmenu) {
            case 1 :
                printf(" Les regles du jeu sont les suivantes : \n");
                printf(" \t - Initialement, vous possedez 3 vies \n");
                printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
                printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
                break;
            case 2:
            case 3 :
                if (choixmenu == 2) {
                    printf("Inscriver le nom du fichier : ");
                    scanf("%s", &nomfichier);
                    strcat(nomficentier, "./");
                    strcat(nomfichier, ".txt");
                    strcat(nomficentier, nomfichier);
                    FILE *pf = fopen(nomfichier, "r");
                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                    else {
                        fscanf(pf, "%c\n", &niveauchoisi[0]);
                        fscanf(pf, "%d\n", &x);
                        fscanf(pf, "%d\n", &y);
                        fscanf(pf, "%d\n", &minute);
                        fscanf(pf, "%d\n", &second);
                        fclose(pf);
                    }
                }
                else {
                    printf(" A. Niveau 1 \n");
                    printf(" B. Niveau 2 \n");
                    printf(" C. Niveau 3 \n");
                    scanf(" %s", niveauchoisi);
                    getchar();
                    x = 6;
                    y = 11;
                    minute=0;
                    second=0;
                }
                switch (niveauchoisi[0]) {
                    case 'a' :
                        Color(11, 0);
                        printf("Appuyer sur : \n");
                        printf("\t - Z pour monter \n");
                        printf("\t - S pour descendre \n");
                        printf("\t - D pour aller a droite\n");
                        printf("\t - Q pour aller a gauche \n");
                        printf("\t - W pour sauvegarder la partie \n");
                        Color(15, 0);

                        for (j = 0; j < 16; j++) {
                            jeu[0][j] = 0xF;
                        }
                        printf("%s\n", jeu[0]);

                        for (int i = 1; i < 11; i++) {
                            strcpy(jeu[i], ligne1);
                            jeu[i][0] = 0xF;
                            jeu[i][21] = 0xF;
                            jeu[1][1] = 0xE;
                            jeu[10][1] = 0xE;
                            jeu[1][20] = 0xE;
                            jeu[10][20] = 0xE;
                            jeu[5][10] = 0x6;
                            jeu[x][y] = 0xB;
                            printf("%s\n", jeu[i]);
                        }

                        for (j = 0; j < 16; j++) {
                            jeu[11][j] = 0xF;
                        }
                        printf("%s\n", jeu[11]);
                        printf("%d %d\n", x, y);
                        printf("%c%c%c\n", 0x03, 0x03, 0x03);

                        do {
                            touche = getchar();
                            touche = counter(touche);
                            Color(15, 0);
                            if (touche == 'w') {
                                printf("Inscriver le nom du fichier : \n");
                                scanf("%s",nomfichier);
                                strcat(nomficentier,"./");
                                strcat(nomfichier,".txt");
                                strcat(nomficentier,nomfichier);
                                FILE* pf = fopen(nomfichier, "w");
                                if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                else {
                                    fprintf(pf, "%s\n",niveauchoisi);
                                    printf("nom fichier : %s",nomficentier);
                                    fprintf(pf, "%d\n", x);
                                    fprintf(pf, "%d\n", y);
                                    fprintf(pf, "%d\n", minute);
                                    fprintf(pf, "%d\n", second);
                                    // ajouter la balle à sauvegarder
                                    fclose(pf);
                                }

                            }
                            else {

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 2 est : SNOOPY");
                                    int score1 = (2 * 60 - minute * 60 - second) * 100;
                                    score += score1;
                                    printf("Pour le niveau 1 vos avez obtenu %d points", score1);
                                    return 0;
                                }

                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            }
                        } while (touche != 'm' && touche != 'w' && mort[2] != 1);


                        break;

                    case 'b' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer);
                        getchar();

                        if (strcmp(motdepasseentrer,motdepasse1) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[x][y] = 0xB;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);


                            do {
                                touche = getchar();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 3 est : JEUVIDEO\n");
                                    int score2 = (2 * 60 - minute * 60 - second)*100;
                                    score += score2;
                                    printf("Pour le niveau 2 vos avez obtenu %d points",score2);
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                    case 'c' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer2[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer2);
                        getchar();

                        if (strcmp(motdepasseentrer2,motdepasse2) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[x][y] = 0xB;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);


                            do {
                                touche = getch();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (tolower(touche) == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (tolower(touche) == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (tolower(touche) == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    int score3 = (2 * 60 - minute * 60 - second)*100;
                                    score += score3;
                                    printf("Pour le niveau 3 vous avez obtenu %d points",score3);
                                    printf("Votre score total est de %d points",score);
                                    return 0;
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                }
                break;
        }
    }
    while (choixmenu != 0);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;
char ligne1[22] = "|                    |";
char jeu[12][22] = {""};
int choixmenu;
char niveauchoisi[2];
int score = 0;
char nomfichier[30];
char nomficentier[50];
int score1,score2,score3;



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    printf("%02d:%02d\n", minute, second);
}

int counter(int touche) {
    Color(5, 0);
    while (touche != 'w' && touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        second++;
        if (second > 59) {
            second = 0;
            minute++;

            if (minute == 2*(m+1)) {
                printf("Timer 120s, vous avez perdu une vie.\n");
                mort[m]=1;
                m=m+1;
            }
        }
        printData();
        sleep(1);

        touche =0;
        if (kbhit()){
            touche = getchar();
        }
    }
    return touche;
}

void map (int x, int y){
    for (j = 0; j < 16; j++) {
        jeu[0][j] = 0xF;
    }
    printf("%s\n", jeu[0]);

    for (int i = 1; i < 11; i++) {
        strcpy(jeu[i], ligne1);
        jeu[i][0] = 0xF;
        jeu[i][21] = 0xF;
        jeu[1][1] = 0xE;
        jeu[10][1] = 0xE;
        jeu[1][20] = 0xE;
        jeu[10][20] = 0xE;
        jeu[5][10] = 0x6;
        jeu[x][y] = 0xB;
        printf("%s\n", jeu[i]);
    }

    for (j = 0; j < 16; j++) {
        jeu[11][j] = 0xF;
    }
    printf("%s\n", jeu[11]);
    printf("%d %d\n", x, y);
    printf("%c%c%c\n", 0x03, 0x03, 0x03);

}

int main(void) {
    char motdepasse1 [20] = "SNOOPY";
    char motdepasse2 [20] ="JEUVIDEO";

    do {
        printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
               "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
               "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
               "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
               "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
               "                                                                                                                     \n");
        Color(4, 0);
        printf("MENU\n");
        printf("1. Les regles du jeu \n");
        printf("2. Charger une partie \n");
        printf("3. Jouer une partie \n");
        printf("0. Quitter\n");
        scanf("%d", &choixmenu);
        getchar();

        switch (choixmenu) {
            case 1 :
                printf(" Les regles du jeu sont les suivantes : \n");
                printf(" \t - Initialement, vous possedez 3 vies \n");
                printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
                printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
                break;
            case 2:
            case 3 :
                if (choixmenu == 2) {
                    printf("Inscriver le nom du fichier : ");
                    scanf("%s", &nomfichier);
                    strcat(nomficentier, "./");
                    strcat(nomfichier, ".txt");
                    strcat(nomficentier, nomfichier);
                    FILE *pf = fopen(nomfichier, "r");
                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                    else {
                        fscanf(pf, "%c\n", &niveauchoisi[0]);
                        fscanf(pf, "%d\n", &x);
                        fscanf(pf, "%d\n", &y);
                        fscanf(pf, "%d\n", &minute);
                        fscanf(pf, "%d\n", &second);
                        fclose(pf);
                    }
                }
                else {
                    printf(" A. Niveau 1 \n");
                    printf(" B. Niveau 2 \n");
                    printf(" C. Niveau 3 \n");
                    scanf(" %s", niveauchoisi);
                    getchar();
                    x = 6;
                    y = 11;
                    minute=0;
                    second=0;
                }
                switch (niveauchoisi[0]) {
                    case 'a' :
                        Color(11, 0);
                        printf("Appuyer sur : \n");
                        printf("\t - Z pour monter \n");
                        printf("\t - S pour descendre \n");
                        printf("\t - D pour aller a droite\n");
                        printf("\t - Q pour aller a gauche \n");
                        printf("\t - W pour sauvegarder la partie \n");
                        Color(15, 0);

                        for (j = 0; j < 16; j++) {
                            jeu[0][j] = 0xF;
                        }
                        printf("%s\n", jeu[0]);

                        for (int i = 1; i < 11; i++) {
                            strcpy(jeu[i], ligne1);
                            jeu[i][0] = 0xF;
                            jeu[i][21] = 0xF;
                            jeu[1][1] = 0xE;
                            jeu[10][1] = 0xE;
                            jeu[1][20] = 0xE;
                            jeu[10][20] = 0xE;
                            jeu[5][10] = 0x6;
                            jeu[x][y] = 0xB;
                            printf("%s\n", jeu[i]);
                        }

                        for (j = 0; j < 16; j++) {
                            jeu[11][j] = 0xF;
                        }
                        printf("%s\n", jeu[11]);
                        printf("%d %d\n", x, y);
                        printf("%c%c%c\n", 0x03, 0x03, 0x03);

                        do {
                            touche = getchar();
                            touche = counter(touche);
                            Color(15, 0);
                            if (touche == 'w') {
                                printf("Inscriver le nom du fichier : \n");
                                scanf("%s",nomfichier);
                                strcat(nomficentier,"./");
                                strcat(nomfichier,".txt");
                                strcat(nomficentier,nomfichier);
                                FILE* pf = fopen(nomfichier, "w");
                                if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                else {
                                    fprintf(pf, "%s\n",niveauchoisi);
                                    printf("nom fichier : %s",nomficentier);
                                    fprintf(pf, "%d\n", x);
                                    fprintf(pf, "%d\n", y);
                                    fprintf(pf, "%d\n", minute);
                                    fprintf(pf, "%d\n", second);
                                    fprintf(pf, "%d\n", score1);
                                    fprintf(pf, "%d\n", score2);
                                    fprintf(pf, "%d\n", score3);
                                    fprintf(pf,"%d\n",mort[0] );
                                    fprintf(pf,"%d\n",mort[1] );
                                    fprintf(pf,"%d\n",mort[2] );
                                    // ajouter la balle à sauvegarder
                                    fclose(pf);
                                }

                            }
                            else {

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 2 est : SNOOPY");
                                    score1 = (2 * 60 - minute * 60 - second) * 100;
                                    score += score1;
                                    printf("Pour le niveau 1 vos avez obtenu %d points", score1);
                                    touche = 'm';
                                }

                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            }
                        } while (touche != 'm' && touche != 'w' && mort[2] != 1);


                        break;

                    case 'b' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer);
                        getchar();

                        if (strcmp(motdepasseentrer,motdepasse1) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[x][y] = 0xB;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);


                            do {
                                touche = getchar();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        fprintf(pf, "%d\n", score1);
                                        fprintf(pf, "%d\n", score2);
                                        fprintf(pf, "%d\n", score3);
                                        fprintf(pf,"%d\n",mort[0] );
                                        fprintf(pf,"%d\n",mort[1] );
                                        fprintf(pf,"%d\n",mort[2] );
                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 3 est : JEUVIDEO\n");
                                    score2 = (2 * 60 - minute * 60 - second)*100;
                                    score += score2;
                                    printf("Pour le niveau 2 vos avez obtenu %d points",score2);
                                    touche = 'm';
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                    case 'c' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer2[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer2);
                        getchar();

                        if (strcmp(motdepasseentrer2,motdepasse2) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 16; j++) {
                                jeu[0][j] = 0xF;
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = 0xF;
                                jeu[i][21] = 0xF;
                                jeu[1][1] = 0xE;
                                jeu[10][1] = 0xE;
                                jeu[1][20] = 0xE;
                                jeu[10][20] = 0xE;
                                jeu[x][y] = 0xB;
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 16; j++) {
                                jeu[11][j] = 0xF;
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 0x03, 0x03, 0x03);


                            do {
                                touche = getch();
                                touche = counter(touche);
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        fprintf(pf, "%d\n", score1);
                                        fprintf(pf, "%d\n", score2);
                                        fprintf(pf, "%d\n", score3);
                                        fprintf(pf,"%d\n",mort[0]);
                                        fprintf(pf,"%d\n",mort[1]);
                                        fprintf(pf,"%d\n",mort[2]);
                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (tolower(touche) == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (tolower(touche) == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (tolower(touche) == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (j = 0; j < 16; j++) {
                                        jeu[0][j] = 0xF;
                                    }
                                    printf("%s\n", jeu[0]);

                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = 0xF;
                                        jeu[i][21] = 0xF;
                                        if (fin[0] != 1) jeu[1][1] = 0xE;
                                        if (fin[1] != 1) jeu[10][1] = 0xE;
                                        if (fin[2] != 1) jeu[1][20] = 0xE;
                                        if (fin[3] != 1) jeu[10][20] = 0xE;
                                        jeu[5][10] = 0x6;
                                        jeu[x][y] = 0xB;

                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;

                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 16; j++) {
                                        jeu[11][j] = 0xF;
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 0x03);
                                if (mort[1] != 1) printf("%c", 0x03);
                                if (mort[2] != 1) printf("%c\n", 0x03);
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    score3 = (2 * 60 - minute * 60 - second)*100;
                                    score += score3;
                                    printf("Pour le niveau 3 vous avez obtenu %d points",score3);
                                    printf("Votre score total est de %d points",score);
                                    touche = 'm';
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                        }
                        break;

                }
                break;
        }
    }
    while (choixmenu != 0);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

int second = 0;
int minute = 0;
int touche;
int j, x = 6, y = 11;
int fin[4] = {0};
int mort[3] = {0};
int total = 0;
int m=0;
char ligne1[22] = "|                    |";
char jeu[12][22] = {""};
int choixmenu;
char niveauchoisi[2];
int score = 0;
char nomfichier[30];
char nomficentier[50];
int score1, score2, score3;



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage decouleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void printData() {
    printf("%02d:%02d\n", minute, second);
}
int counter() {
    Color(5, 0);
    touche =' ';
    while (touche != 'w' && touche != 'q' && touche != 'd' && touche != 'z' && touche != 's' && mort[2]!=1){
        if (touche != 'p'){
            second++;
            if (second > 59) {
                second = 0;
                minute++;

                if (minute == 2*(m+1)) {
                    printf("Timer 120s, vous avez perdu une vie.\n");
                    mort[m]=1;
                    m=m+1;
                }
            }
            printData();
            sleep(1);
        }
        if (kbhit()) {
            touche =_getch();
        }
    }
    return touche;
}


int main(void) {
    char motdepasse1 [20] = "SNOOPY";
    char motdepasse2 [20] ="JEUVIDEO";

    do {
        printf("\n");
        printf(" _     ____    ____  _____ _     ____  _      ____  _     _____   ____  _____   ____  _      ____  ____  ____ ___  _\n"
               "/ \\   /  _ \\  /  __\\/  __// \\ |\\/  _ \\/ \\  /|/   _\\/ \\ /|/  __/  /  _ \\/  __/  / ___\\/ \\  /|/  _ \\/  _ \\/  __\\\\  \\//\n"
               "| |   | / \\|  |  \\/||  \\  | | //| / \\|| |\\ |||  /  | |_|||  \\    | | \\||  \\    |    \\| |\\ ||| / \\|| / \\||  \\/| \\  / \n"
               "| |_/\\| |-||  |    /|  /_ | \\// | |-||| | \\|||  \\__| | |||  /_   | |_/||  /_   \\___ || | \\||| \\_/|| \\_/||  __/ / /  \n"
               "\\____/\\_/ \\|  \\_/\\_\\\\____\\\\__/  \\_/ \\|\\_/  \\|\\____/\\_/ \\|\\____\\  \\____/\\____\\  \\____/\\_/  \\|\\____/\\____/\\_/   /_/   \n"
               "                                                                                                                     \n");
        Color(4, 0);
        printf("MENU\n");
        printf("1. Les regles du jeu \n");
        printf("2. Charger une partie \n");
        printf("3. Jouer une partie \n");
        printf("0. Quitter\n");
        scanf("%d", &choixmenu);
        getchar();

        switch (choixmenu) {
            case 1 :
                printf(" Les regles du jeu sont les suivantes : \n");
                printf(" \t - Initialement, vous possedez 3 vies \n");
                printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et \n           recommencez le niveau. \n");
                printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis\n           (si presents).\n");
                break;
            case 2:
            case 3 :
                if (choixmenu == 2) {
                    printf("Inscriver le nom du fichier : ");
                    scanf("%s", &nomfichier);
                    strcat(nomficentier, "./");
                    strcat(nomfichier, ".txt");
                    strcat(nomficentier, nomfichier);
                    FILE *pf = fopen(nomfichier, "r");
                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                    else {
                        fscanf(pf, "%c\n", &niveauchoisi[0]);
                        fscanf(pf, "%d\n", &x);
                        fscanf(pf, "%d\n", &y);
                        fscanf(pf, "%d\n", &minute);
                        fscanf(pf, "%d\n", &second);
                        fclose(pf);
                    }
                }
                else {
                    printf(" A. Niveau 1 \n");
                    printf(" B. Niveau 2 \n");
                    printf(" C. Niveau 3 \n");
                    scanf(" %s", niveauchoisi);
                    getchar();
                    x = 6;
                    y = 11;
                    minute=0;
                    second=0;
                }
                switch (niveauchoisi[0]) {
                    case 'a' :
                        Color(11, 0);
                        printf("Appuyer sur : \n");
                        printf("\t - Z pour monter \n");
                        printf("\t - S pour descendre \n");
                        printf("\t - D pour aller a droite\n");
                        printf("\t - Q pour aller a gauche \n");
                        printf("\t - W pour sauvegarder la partie \n");
                        printf("\t - M pour stopper la partie \n");
                        Color(15, 0);

                        for (j = 0; j < 22; j++) {
                            jeu[0][j] = '-';
                        }
                        printf("%s\n", jeu[0]);

                        for (int i = 1; i < 11; i++) {
                            strcpy(jeu[i], ligne1);
                            jeu[i][0] = '|';
                            jeu[i][21] = '|';
                            jeu[1][1] = 'O';
                            jeu[10][1] = 'O';
                            jeu[1][20] = 'O';
                            jeu[10][20] = 'O';
                            jeu[x][y] = 'S';
                            printf("%s\n", jeu[i]);
                        }

                        for (j = 0; j < 22; j++) {
                            jeu[11][j] = '-';
                        }
                        printf("%s\n", jeu[11]);
                        printf("%d %d\n", x, y);
                        printf("%c%c%c\n", 'V', 'V', 'V');

                        do {
                            touche = _getch();
                            touche = counter();
                            system("cls");
                            Color(15, 0);
                            if (touche == 'w') {
                                printf("Inscriver le nom du fichier : \n");
                                scanf("%s",nomfichier);
                                strcat(nomficentier,"./");
                                strcat(nomfichier,".txt");
                                strcat(nomficentier,nomfichier);
                                FILE* pf = fopen(nomfichier, "w");
                                if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                else {
                                    fprintf(pf, "%s\n",niveauchoisi);
                                    printf("nom fichier : %s",nomficentier);
                                    fprintf(pf, "%d\n", x);
                                    fprintf(pf, "%d\n", y);
                                    fprintf(pf, "%d\n", minute);
                                    fprintf(pf, "%d\n", second);
                                    fprintf(pf, "%d\n", score1);
                                    fprintf(pf, "%d\n", score2);
                                    fprintf(pf, "%d\n", score3);
                                    fprintf(pf,"%d\n",mort[0] );
                                    fprintf(pf,"%d\n",mort[1] );
                                    fprintf(pf,"%d\n",mort[2] );
                                    fprintf(pf,"%d\n",fin[0]);
                                    fprintf(pf,"%d\n",fin[1]);
                                    fprintf(pf,"%d\n",fin[2]);
                                    fprintf(pf,"%d\n",fin[3]);
                                    // ajouter la balle à sauvegarder
                                    fclose(pf);
                                }

                            }
                            else {

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = '|';
                                        jeu[i][21] = '|';
                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;
                                        if (fin[0] != 1) jeu[1][1] = 'O';
                                        if (fin[1] != 1) jeu[10][1] = 'O';
                                        if (fin[2] != 1) jeu[1][20] = 'O';
                                        if (fin[3] != 1) jeu[10][20] = 'O';
                                        jeu[x][y] = 'S';
                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 22; j++) {
                                        jeu[11][j] = '-';
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 'V');
                                if (mort[1] != 1) printf("%c", 'V');
                                if (mort[2] != 1) printf("%c\n", 'V');
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 2 est : SNOOPY");
                                    int score1 = (2 * 60 - minute * 60 - second) * 100;
                                    score += score1;
                                    printf("Pour le niveau 1 vos avez obtenu %d points", score1);
                                    touche = 'm';
                                }

                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                    touche = 'm';
                                }
                            }
                        } while (touche != 'm' && touche != 'w' && mort[2] != 1);


                        break;

                    case 'b' :
                        printf("Niveau 2 :\n");

                        char motdepasseentrer[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer);
                        getchar();

                        if (strcmp(motdepasseentrer,motdepasse1) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 22; j++) {
                                jeu[0][j] = '-';
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = '|';
                                jeu[i][21] = '|';
                                jeu[1][1] = 'O';
                                jeu[10][1] = 'O';
                                jeu[1][20] = 'O';
                                jeu[10][20] = 'O';
                                jeu[x][y] = 'S';
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 22; j++) {
                                jeu[11][j] = '-';
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 'V', 'V', 'V');


                            do {
                                touche = _getch();
                                touche = counter();
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        fprintf(pf, "%d\n", score1);
                                        fprintf(pf, "%d\n", score2);
                                        fprintf(pf, "%d\n", score3);
                                        fprintf(pf,"%d\n",mort[0] );
                                        fprintf(pf,"%d\n",mort[1] );
                                        fprintf(pf,"%d\n",mort[2] );
                                        fprintf(pf,"%d\n",fin[0]);
                                        fprintf(pf,"%d\n",fin[1]);
                                        fprintf(pf,"%d\n",fin[2]);
                                        fprintf(pf,"%d\n",fin[3]);

                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }

                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (touche == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (touche == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (touche == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = '|';
                                        jeu[i][21] = '|';
                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;
                                        if (fin[0] != 1) jeu[1][1] = 'O';
                                        if (fin[1] != 1) jeu[10][1] = 'O';
                                        if (fin[2] != 1) jeu[1][20] = 'O';
                                        if (fin[3] != 1) jeu[10][20] = 'O';
                                        jeu[x][y] = 'S';
                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 22; j++) {
                                        jeu[11][j] = '-';
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 'V');
                                if (mort[1] != 1) printf("%c", 'V');
                                if (mort[2] != 1) printf("%c\n", 'V');
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    printf("Le mot de passe pour le niveau 3 est : JEUVIDEO\n");
                                    int score2 = (2 * 60 - minute * 60 - second)*100;
                                    score += score2;
                                    printf("Pour le niveau 2 vos avez obtenu %d points",score2);
                                    touche = 'm';
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                    touche = 'm';
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                            touche = 'm';
                        }
                        break;

                    case 'c' :
                        printf("Niveau 3 :\n");

                        char motdepasseentrer2[20];
                        printf("Entrer le mot de passe : \n");
                        scanf("%s",motdepasseentrer2);
                        getchar();

                        if (strcmp(motdepasseentrer2,motdepasse2) == 0) {

                            Color(11, 0);
                            printf("Appuyer sur : \n");
                            printf("\t - Z pour monter \n");
                            printf("\t - S pour descendre \n");
                            printf("\t - D pour aller a droite\n");
                            printf("\t - Q pour aller a gauche \n");
                            Color(15, 0);
                            for (j = 0; j < 22; j++) {
                                jeu[0][j] = '-';
                            }
                            printf("%s\n", jeu[0]);

                            for (int i = 1; i < 11; i++) {
                                strcpy(jeu[i], ligne1);
                                jeu[i][0] = '|';
                                jeu[i][21] = '|';
                                jeu[1][1] = 'O';
                                jeu[10][1] = 'O';
                                jeu[1][20] = 'O';
                                jeu[10][20] = 'O';
                                jeu[x][y] = 'S';
                                printf("%s\n", jeu[i]);
                            }

                            for (j = 0; j < 22; j++) {
                                jeu[11][j] = '-';
                            }
                            printf("%s\n", jeu[11]);
                            printf("%d %d\n", x, y);
                            printf("%c%c%c\n", 'V', 'V', 'V');


                            do {
                                touche = _getch();
                                touche = counter();
                                Color(15, 0);
                                if (touche == 'w') {
                                    printf("Inscriver le nom du fichier : \n");
                                    scanf("%s", nomfichier);
                                    strcat(nomficentier, "./");
                                    strcat(nomfichier, ".txt");
                                    strcat(nomficentier, nomfichier);
                                    FILE *pf = fopen(nomfichier, "w");
                                    if (pf == NULL) printf("Erreur d'ouverture de fichier.");
                                    else {
                                        fprintf(pf, "%s\n", niveauchoisi);
                                        printf("nom fichier : %s", nomficentier);
                                        fprintf(pf, "%d\n", x);
                                        fprintf(pf, "%d\n", y);
                                        fprintf(pf, "%d\n", minute);
                                        fprintf(pf, "%d\n", second);
                                        fprintf(pf, "%d\n", score1);
                                        fprintf(pf, "%d\n", score2);
                                        fprintf(pf, "%d\n", score3);
                                        fprintf(pf,"%d\n",mort[0] );
                                        fprintf(pf,"%d\n",mort[1] );
                                        fprintf(pf,"%d\n",mort[2] );
                                        fprintf(pf,"%d\n",fin[0]);
                                        fprintf(pf,"%d\n",fin[1]);
                                        fprintf(pf,"%d\n",fin[2]);
                                        fprintf(pf,"%d\n",fin[3]);
                                        // ajouter la balle à sauvegarder
                                        fclose(pf);
                                    }
                                }
                                if (touche == 'z') {
                                    if (x > 1) x = x - 1;
                                }

                                if (tolower(touche) == 's') {
                                    if (x < 10) x = x + 1;
                                }
                                if (tolower(touche) == 'd') {
                                    if (y < 20) y = y + 1;
                                }

                                if (tolower(touche) == 'q') {
                                    if (y > 1) y = y - 1;
                                }

                                if (touche == 'q' || touche == 'd' || touche == 'z' || touche == 's') {
                                    for (int i = 1; i < 11; i++) {
                                        strcpy(jeu[i], ligne1);
                                        jeu[i][0] = '|';
                                        jeu[i][21] = '|';
                                        if (x == 1 && y == 1) fin[0] = 1;
                                        if (x == 10 && y == 1) fin[1] = 1;
                                        if (x == 1 && y == 20) fin[2] = 1;
                                        if (x == 10 && y == 20) fin[3] = 1;
                                        if (fin[0] != 1) jeu[1][1] = 'O';
                                        if (fin[1] != 1) jeu[10][1] = 'O';
                                        if (fin[2] != 1) jeu[1][20] = 'O';
                                        if (fin[3] != 1) jeu[10][20] = 'O';
                                        jeu[x][y] = 'S';
                                        printf("%s\n", jeu[i]);
                                    }

                                    for (j = 0; j < 20; j++) {
                                        jeu[11][j] = '-';
                                    }
                                }
                                printf("%s\n", jeu[11]);
                                printf("%d %d\n", x, y);
                                if (mort[0] != 1) printf("%c", 'V');
                                if (mort[1] != 1) printf("%c", 'V');
                                if (mort[2] != 1) printf("%c\n", 'V');
                                if (fin[0] == 1 || fin[1] == 1 || fin[2] == 1 || fin[3] == 1) {
                                    total = fin[0] + fin[1] + fin[2] + fin[3];
                                    printf("vous avez %d oiseau(x)\n", total);
                                }
                                if (total == 4) {
                                    printf("Vous avez tous vos oiseaux, le niveau est fini\n");
                                    int score3 = (2 * 60 - minute * 60 - second)*100;
                                    score += score3;
                                    printf("Pour le niveau 3 vous avez obtenu %d points",score3);
                                    printf("Votre score total est de %d points",score);
                                    touche = 'm';
                                }
                                if (mort[2] == 1) {
                                    printf("vous n'avez plus de vie, GAME OVER");
                                    touche = 'm';
                                }
                            } while (touche != 'm' && touche != 'w' && mort[2] != 1);
                        }
                        else {
                            printf("Mot de passe incorrect !");
                            touche = 'm';
                        }
                        break;

                }
                break;
        }
    }
    while (choixmenu != 0);
    return 0;
}