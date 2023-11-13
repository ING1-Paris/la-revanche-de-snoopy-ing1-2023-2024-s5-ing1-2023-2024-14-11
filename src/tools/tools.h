//
// Created by Ewan Kapoor on 13/11/2023.
//

#ifndef SNOOPY_TOOLS
#define SNOOPY_TOOLS

struct Coordonnees {
    int x;
    int y;
};

void afficher_fichier(char *path);
char *concat(char* chaines[], int taille);
void COULEUR(int couleurDuTexte,int couleurDeFond);

#endif //SNOOPY_TOOLS
