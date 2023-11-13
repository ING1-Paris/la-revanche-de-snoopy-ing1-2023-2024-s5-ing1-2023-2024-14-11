//
// Created by Ewan Kapoor on 13/11/2023.
//

#include <time.h>
#include "timer.h"


int pause = 0;

clock_t start_time_jeu;
clock_t current_time_jeu;
current_time_jeu = clock();

clock_t last_balle = current_time_jeu;
clock_t last_affich = current_time_jeu;

float elapsed_time_jeu = 0;
float arret_clock_jeu;
float *pause_time = &arret_clock_jeu;

start_time_jeu = clock();           //initialisation du timer

//temps si pas de pause, le chrono s'ecoule normalement

if (paused == 0) {

current_time_jeu = clock();
elapsed_time_jeu = (float) (current_time_jeu - start_time_jeu) / CLOCKS_PER_SEC;
niveau.time_left = 120 - (float) elapsed_time_jeu;
}

//temps si on a mis pause
if (paused == 1) {
current_time_jeu = clock();
elapsed_time_jeu = (float) (current_time_jeu - start_time_jeu) / CLOCKS_PER_SEC;
niveau.time_left = 120 - (float) elapsed_time_jeu - arret_clock_jeu;
}