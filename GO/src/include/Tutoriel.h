/**
 * @file Tutoriel.h
 */

#ifndef TUTORIEL_H_
#define TUTORIEL_H_

typedef struct Tutoriel* Tutoriel;

/**
 * Convertis le fichier texte Tutoriel.txt en Tutoriel.bin binaire.
 */
void Tutoriel_convertirTexteVersBinaire();

/**
 * Charge le tutoriel du fichier Tutoriel.bin et le retourne.
 *
 * @return Tutoriel : Retourne le tutoriel chargé
 */
Tutoriel Tutoriel_charger();

#endif /* TUTORIEL_H_ */
