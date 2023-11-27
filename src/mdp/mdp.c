//
// Created by Ewan Kapoor on 13/11/2023.
//

#include "mdp.h"

int motdepasse() {

    char mdp[20];
    char buffer[30];

    printf("Veuillez entrer le mot de passe");
    scanf("%19s", mdp);

    int mdp1 = strcmp(mdp, "NIV1");
    int mdp2 = strcmp(mdp, "NIV2");
    int mdp3 = strcmp(mdp, "NIV3");

    if(mdp1 == 0) {

        printf("Niveau 1");

    } else {

        if(mdp2 == 0) {

            printf("Niveau 2");

        } else {

            if(mdp3 == 0) {

                printf("Niveau 3");

            } else {

                printf("MDP incorrect");
            }
        }
    }


}