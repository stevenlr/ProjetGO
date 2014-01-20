/**
 * @file Texte.h
 * @brief 
 */

#ifndef TEXTE_H_
#define TEXTE_H_

/**
 * Style de texte.
 */
typedef enum {
	NORMAL = 0,  //!< NORMAL
	GRAS = 1,    //!< GRAS
	ITALIQUE = 2,//!< ITALIQUE
	GRAND = 4    //!< GRAND
} StyleTexte;

/**
 * Alignement du texte.
 */
typedef enum {
	CENTRE_X = 1,//!< CENTRE_X
	CENTRE_Y = 2,//!< CENTRE_Y
	DROITE = 4,  //!< DROITE
	GAUCHE = 8   //!< GAUCHE
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
 * @param alignement
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
