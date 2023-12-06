//
// Created by Ewan Kapoor on 06/12/2023.
//

#ifndef SNOOPYFINAL_KEYBOARD_H
#define SNOOPYFINAL_KEYBOARD_H

// Ce fichier contient les déclarations de fonctions liées à la gestion des événements clavier.

// Inclure les bibliothèques nécessaires
#include "../tools/tools.h"
#include "../gameplay/gameplay.h"

// Déclarations des fonctions de gestion des touches
void handleKeypress(struct ModeleNiveau *modele, int *chrono, int *pause, int *menu_principal, char *derniere_direction);
void handlePause(struct ModeleNiveau *modele, int *chrono, int *pause);
void handleSauvegarder(struct ModeleNiveau *modele, int *chrono, int *pause, int *menu_principal);
void handleAbandonner(int *pause, int *menu_principal);
void handleRecommencer(struct ModeleNiveau *modele, int *chrono, int *pause, int *menu_principal, char *derniere_direction);
void handleEspace(struct ModeleNiveau *modele, int *pause, char *derniere_direction);
void handleArrowKeys(struct ModeleNiveau *modele, int *pause, char *derniere_direction);

// Fonctions de déplacement et manipulation du niveau
void deplacer(struct ModeleNiveau *modele, char direction, char *derniere_direction);
void casse_bloc(struct ModeleNiveau *modele, const char *direction);
void deplacer_balle(struct ModeleNiveau *modele, int i);

#endif //SNOOPYFINAL_KEYBOARD_H
