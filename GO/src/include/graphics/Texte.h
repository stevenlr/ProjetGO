/**
 * @file Texte.h
 * @brief 
 */

#ifndef TEXTE_H_
#define TEXTE_H_

/**
 * Styles de texte.
 */
typedef enum {
	NORMAL = 0,
	GRAS = 1,
	ITALIQUE = 2,
	GRAND = 4
} StyleTexte;

typedef enum {
	CENTRE_X = 1,
	CENTRE_Y = 2,
	DROITE = 4,
	GAUCHE = 8
} AlignementTexte;

/**
 * Affiche du texte à l'écran.
 *
 * @param surface
 * @param x
 * @param y
 * @param chaine
 * @param style
 * @param couleur Exemple : 0xffffff pour blanc.
 */
void Texte_afficherChaine(SDL_Surface* surface, int x, int y, char* chaine, StyleTexte style, int couleur, AlignementTexte alignement);

/**
 * Charge toutes les fontes nécessaires.
 *
 * @return 1 si tout esr ok, 0 sinon.
 */
int Texte_chargerFontes();

/**
 * Décharge les fontes allouées.
 */
void Texte_libererFontes();

#endif
