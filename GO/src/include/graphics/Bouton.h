/**
 * @file Bouton.h
 * @brief 
 */

#ifndef BOUTON_H_
#define BOUTON_H_

typedef struct Bouton* Bouton;

/**
 * Cr�e un bouton.
 *
 * @param texte
 * @param x1
 * @param x2
 * @param y1
 * @param y2
 * @return Bouton cr��.
 */
Bouton Bouton_creer(char* texte, int x1, int x2, int y1, int y2, int couleurBouton, int couleurTexte);

/**
 * Affiche un bouton.
 *
 * @param surface Surface sur laquelle l'afficher.
 */
void Bouton_afficher(Bouton bouton, SDL_Surface* surface);

/**
 * D�termine si on est sur un bouton.
 *
 * @param bouton
 * @param x
 * @param y
 * @return 1 si on clique dessus, 0 sinon.
 */
int Bouton_clique(Bouton bouton, int x, int y);

/**
 * D�truit un bouton.
 *
 * @param bouton
 */
void Bouton_detruire(Bouton bouton);

#endif
