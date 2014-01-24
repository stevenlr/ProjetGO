/**
 * @file ChoixMultiple.h
 * @brief 
 */

#ifndef CHOIXMULTIPLE_H_
#define CHOIXMULTIPLE_H_

#include <SDL/SDL.h>

typedef struct ChoixMultiple* ChoixMultiple;

ChoixMultiple ChoixMultiple_creer(int x, int y, int largeur, int couleurNormal, int couleurChoisi, int couleurTexte);

void ChoixMultiple_ajouterChoix(ChoixMultiple cm, char* str);

int ChoixMultiple_getCourant(ChoixMultiple cm);
void ChoixMultiple_setCourant(ChoixMultiple cm, int choisi);

void ChoixMultiple_afficher(ChoixMultiple cm, SDL_Surface* surface);
int ChoixMultiple_clique(ChoixMultiple cm, int x, int y);

void ChoixMultiple_detruire(ChoixMultiple cm);

#endif
