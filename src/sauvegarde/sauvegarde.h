//
// Created by Ewan Kapoor on 13/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../game/game.h"

#ifndef SNOOPY_SAUVEGARDE
#define SNOOPY_SAUVEGARDE

int sauvegarde_id_valide(char *id);
struct ModeleNiveau charger_sauvegarde(char *id, int code);
void sauvegarder_partie(struct ModeleNiveau modele, int temps_restant, char *chemin);
char *demande_sauvegarde_id();

#endif //SNOOPY_SAUVEGARDE

