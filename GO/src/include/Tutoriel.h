/**
 * @file Tutoriel.h
 * @brief Fonctions pour le tutoriel du jeu de GO.
 */

#ifndef TUTORIEL_H_
#define TUTORIEL_H_

#include "Partie.h"

typedef struct Tutoriel* Tutoriel;

/**
 * Convertis le fichier texte Tutoriel.txt en Tutoriel.bin binaire.
 */
int Tutoriel_convertirTexteVersBinaire();

/**
 * Charge le tutoriel du fichier Tutoriel.bin et le retourne.
 *
 * @return Tutoriel : Retourne le tutoriel charg�
 */
Tutoriel Tutoriel_charger(int nbCharParPhrase);

/**
 * Inserer la chaine et le plateau dans le tutoriel en fonction du nombre de char par phrase.
 *
 * @param tutoriel
 * @param plateau
 * @param chaine
 * @param tailleChaine
 * @param nbCharParPhrase
 */
void Tutoriel_inserer(Tutoriel tutoriel, Plateau plateau, char* chaine, int tailleChaine, int nbCharParPhrase);

/**
 * Alloue un tutoriel
 *
 * @return tutoriel
 */
Tutoriel Tutoriel_creer();

/**
 * Desalloue un tutoriel
 *
 * @param tutoriel
 */
void Tutoriel_detruire(Tutoriel tutoriel);

/**
 * On se met au d�but du tutoriel
 *
 * @param tutoriel
 */
void Tutoriel_tete(Tutoriel tutoriel);

/**
 * On passe au suivant
 *
 * @param tutoriel
 * @return 1 si c'est possible, sinon 0
 */
int Tutoriel_suivant(Tutoriel tutoriel);

/**
 * On passe au pr�c�dent
 *
 * @param tutoriel
 * @return 1 si c'est possible, sinon 0
 */
int Tutoriel_precedent(Tutoriel tutoriel);

/**
 * Met le plateau et la chaine courant dans leur variable respective.
 *
 * @param tutoriel
 * @param plateau
 * @param chaines
 */
void Tutoriel_courant(Tutoriel tutoriel, Plateau *plateau, Liste *chaines);

/**
 * V�rifie si c'est la premi�re page du tutoriel.
 *
 * @param tutoriel
 * @return 1 si c'est la premi�re, 0 sinon.
 */
int Tutoriel_estPremier(Tutoriel tutoriel);

/**
 * V�rifie si on est � la derni�re page du tutoriel.
 *
 * @param tutoriel
 * @return 1 si c'est la derni�re page, 0 sinon.
 */
int Tutoriel_estDernier(Tutoriel tutoriel);

#endif /* TUTORIEL_H_ */
