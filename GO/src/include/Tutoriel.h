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
 * @return Tutoriel : Retourne le tutoriel chargé
 */
Tutoriel Tutoriel_charger(Partie partie, int nbCharParPhrase);

void Tutoriel_inserer(Tutoriel tutoriel, Plateau plateau, char* chaine, int nbCharParPhrase);

Tutoriel Tutoriel_creer();

void Tutoriel_detruire(Tutoriel tutoriel);

#endif /* TUTORIEL_H_ */
