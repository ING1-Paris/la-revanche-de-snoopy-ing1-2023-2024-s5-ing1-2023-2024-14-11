#include <stdio.h>
#include <string.h>

int main(void) {
    int touche;

    printf(" La revanche de Snoopy \n");
    printf(" Les regles du jeu sont les suivantes : \n");
    printf(" \t - Initialement, vous possedez 3 vies \n");
    printf(" \t - Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, vous perdez une vie et recommencez le niveau. \n");
    printf(" \t - Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par la balle et/ou les ennemis (si presents).\n");
    printf(" Cliquer sur A et entrer pour acceder aux niveaux\n");

    char ligne0[22] = "____________________";
    char ligne1[22] = "|                    |";
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

            strcpy(jeu[0], ligne0);
            printf("%s\n", jeu[0]);

            for (i = 1; i < 11; i++) {
                strcpy(jeu[i], ligne1);
                jeu[6][11] = 0xB;
                jeu[1][1] = 0xE;
                jeu[10][1] = 0xE;
                jeu[1][20] = 0xE;
                jeu[10][20] = 0xE;
                jeu[5][10] = 0x6;
                printf("%s\n", jeu[i]);
            }
            strcpy(jeu[11], ligne0);
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

            strcpy(jeu[0], ligne0);
            printf("%s\n", jeu[0]);
            for (i = 1; i < 11; i++) {
                strcpy(jeu[i], ligne1);
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
            strcpy(jeu[11], ligne0);
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