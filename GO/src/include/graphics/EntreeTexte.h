/**
 * @file EntreeTexte.h
 * @brief Entrée de texte en SDL.
 */

#ifndef ENTREETEXTE_H_
#define ENTREETEXTE_H_

typedef struct EntreeTexte* EntreeTexte;

/**
 * Crée un champ de texte.
 *
 * @param x Abscisse.
 * @param y Ordonnée.
 * @param largeur Largeur.
 * @param couleurFond Couleur de fond.
 * @param couleurTexte Couleur du texte.
 * @param tailleMax Taille maximale du texte contenu.
 * @return Le champ créé.
 */
EntreeTexte EntreeTexte_creer(int x, int y, int largeur, int couleurFond, int couleurTexte, int tailleMax);

/**
 * Détruit un champ de texte.
 *
 * @param entree Champ à détruire.
 */
void EntreeTexte_detruire(EntreeTexte entree);

/**
 * Affiche un champ de texte.
 *
 * @param entree Champ à afficher.
 * @param surface Surface SDL sur laquelle l'afficher.
 */
void EntreeTexte_afficher(EntreeTexte entree, SDL_Surface* surface);

/**
 * Change le texte contenu dans le champ. (effectue une copie)
 *
 * @param entree Le champ.
 * @param str Texte à copier.
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
 * Simule un clique sur le champ. Lui donne le focus si le texte est dessus, sinon le lui enlève.
 *
 * @param entree Champ de texte.
 * @param x Abscisse du clique.
 * @param y Ordonnée du clique.
 */
void EntreeTexte_clique(EntreeTexte entree, int x, int y);

/**
 * Change l'état d'activation du champ.
 *
 * @param entree Champ de texte.
 * @param focus 1 si il dois avoir le focus, 0 s'il faut le lui enlever.
 */
void EntreeTexte_setFocus(EntreeTexte entree, int focus);

/**
 * Retourne l'état actuel du champ.
 *
 * @param entree Champ de texte.
 * @return Etat du champ : 1 s'il a le focus, 0 sinon.
 */
int EntreeTexte_getFocus(EntreeTexte entree);

/**
 * Supprime un caractère du champ.
 *
 * @param entree Champ de texte.
 */
void EntreeTexte_retour(EntreeTexte entree);

/**
 * Tente d'insérer un caractère au champ.
 *
 * @param entree Champ de texte.
 * @param c Caractère à insérer.
 */
void EntreeTexte_inserer(EntreeTexte entree, char c);

#endif
