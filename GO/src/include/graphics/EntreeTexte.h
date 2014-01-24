/**
 * @file EntreeTexte.h
 * @brief 
 */

#ifndef ENTREETEXTE_H_
#define ENTREETEXTE_H_

typedef struct EntreeTexte* EntreeTexte;

EntreeTexte EntreeTexte_creer(int x, int y, int largeur, int couleurFond, int couleurTexte, int tailleMax);
void EntreeTexte_detruire(EntreeTexte entree);

void EntreeTexte_afficher(EntreeTexte entree, SDL_Surface* surface);

void EntreeTexte_setTexte(EntreeTexte entree, char* str);
char* EntreeTexte_getTexte(EntreeTexte entree);

void EntreeTexte_clique(EntreeTexte entree, int x, int y);

void EntreeTexte_setFocus(EntreeTexte entree, int focus);
int EntreeTexte_getFocus(EntreeTexte entree);

void EntreeTexte_retour(EntreeTexte entree);
void EntreeTexte_inserer(EntreeTexte entree, char c);

#endif
