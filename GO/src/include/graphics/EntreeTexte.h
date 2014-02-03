/**
 * @file EntreeTexte.h
 * @brief Entr�e de texte en SDL.
 */

#ifndef ENTREETEXTE_H_
#define ENTREETEXTE_H_

typedef struct EntreeTexte* EntreeTexte;

/**
 * Cr�e un champ de texte.
 *
 * @param x Abscisse.
 * @param y Ordonn�e.
 * @param largeur Largeur.
 * @param couleurFond Couleur de fond.
 * @param couleurTexte Couleur du texte.
 * @param tailleMax Taille maximale du texte contenu.
 * @return Le champ cr��.
 */
EntreeTexte EntreeTexte_creer(int x, int y, int largeur, int couleurFond, int couleurTexte, int tailleMax);

/**
 * D�truit un champ de texte.
 *
 * @param entree Champ � d�truire.
 */
void EntreeTexte_detruire(EntreeTexte entree);

/**
 * Affiche un champ de texte.
 *
 * @param entree Champ � afficher.
 * @param surface Surface SDL sur laquelle l'afficher.
 */
void EntreeTexte_afficher(EntreeTexte entree, SDL_Surface* surface);

/**
 * Change le texte contenu dans le champ. (effectue une copie)
 *
 * @param entree Le champ.
 * @param str Texte � copier.
 */
void EntreeTexte_setTexte(EntreeTexte entree, char* str);

/**
 * Retourne le texte contenu dans le champ.
 *
 * @param entree Champ de texte.
 * @return Texte contenu.
 */
char* EntreeTexte_getTexte(EntreeTexte entree);

/**
 * Simule un clique sur le champ. Lui donne le focus si le texte est dessus, sinon le lui enl�ve.
 *
 * @param entree Champ de texte.
 * @param x Abscisse du clique.
 * @param y Ordonn�e du clique.
 */
void EntreeTexte_clique(EntreeTexte entree, int x, int y);

/**
 * Change l'�tat d'activation du champ.
 *
 * @param entree Champ de texte.
 * @param focus 1 si il dois avoir le focus, 0 s'il faut le lui enlever.
 */
void EntreeTexte_setFocus(EntreeTexte entree, int focus);

/**
 * Retourne l'�tat actuel du champ.
 *
 * @param entree Champ de texte.
 * @return Etat du champ : 1 s'il a le focus, 0 sinon.
 */
int EntreeTexte_getFocus(EntreeTexte entree);

/**
 * Supprime un caract�re du champ.
 *
 * @param entree Champ de texte.
 */
void EntreeTexte_retour(EntreeTexte entree);

/**
 * Tente d'ins�rer un caract�re au champ.
 *
 * @param entree Champ de texte.
 * @param c Caract�re � ins�rer.
 */
void EntreeTexte_inserer(EntreeTexte entree, char c);

#endif
