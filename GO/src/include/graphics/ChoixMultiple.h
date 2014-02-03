/**
 * @file ChoixMultiple.h
 * @brief Bouton à choix multiple en SDL.
 */

#ifndef CHOIXMULTIPLE_H_
#define CHOIXMULTIPLE_H_

#include <SDL/SDL.h>

/**
 * Maximum de choix contenus dans un choix multiple.
 */
#define MAXCHOIX 3

typedef struct ChoixMultiple* ChoixMultiple;

/**
 * Crée un choix multiple.
 *
 * @param x Abscisse du bouton.
 * @param y Ordonnée du bouton.
 * @param largeur Largueur d'un choix.
 * @param couleurNormal Couleur de fond du bouton.
 * @param couleurChoisi Couleur de fond du bouton losqu'il est choisi.
 * @param couleurTexte Couleur du texte.
 * @return La structure créée.
 */
ChoixMultiple ChoixMultiple_creer(int x, int y, int largeur, int couleurNormal, int couleurChoisi, int couleurTexte);

/**
 * Ajoute un choix au choix multiple.
 *
 * @param cm Bouton auquel ajouter le choix.
 * @param str Texte du choix.
 */
void ChoixMultiple_ajouterChoix(ChoixMultiple cm, char* str);

/**
 * Donne l'id du choix courant.
 *
 * @param cm Bouton choix multiple.
 * @return	ID choisi.
 */
int ChoixMultiple_getCourant(ChoixMultiple cm);

/**
 * Défini le choix actuel du bouton.
 *
 * @param cm Bouton à choix multiple.
 * @param choisi ID de choix.
 */
void ChoixMultiple_setCourant(ChoixMultiple cm, int choisi);

/**
 * Affiche un bouton à choix multiple.
 *
 * @param cm Bouton à choix multiple.
 * @param surface Surface SDL sur laquelle le placer.
 */
void ChoixMultiple_afficher(ChoixMultiple cm, SDL_Surface* surface);

/**
 * Simule un clique sur le bouton à choix multiple.
 *
 * @param cm Bouton à choix multiple.
 * @param x	Abscisse du clique.
 * @param y Ordonnée du clique.
 * @return	1 si on a bien cliqué dessus, 0 sinon.
 */
int ChoixMultiple_clique(ChoixMultiple cm, int x, int y);

/**
 * Détruit un bouton à choix multiple.
 *
 * @param cm Bouton à détruire.
 */
void ChoixMultiple_detruire(ChoixMultiple cm);

#endif
