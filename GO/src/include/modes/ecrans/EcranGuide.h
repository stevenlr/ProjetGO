/**
 * @file EcranGuide.h
 * @brief Ecran de tutoriel du jeu.
 */

#ifndef ECRANGUIDE_H_
#define ECRANGUIDE_H_

/**
 * Charge le tutoriel et prépare les états de l'écran.
 * @return 0 en cas d'erreur, 1 sinon.
 */
int EcranGuide_init();

/**
 * Détruit les états courant de l'écran de tutoriel.
 */
void EcranGuide_detruire();

/**
 * Logique de l'écran de tutoriel.
 */
void EcranGuide_main();

/**
 * Retourne la fonction d'entrée de l'écran de tutoriel.
 * @return
 */
FonctionEntreeEcran EcranGuide_getEntreeFct();

/**
 * Retourne la fonction de sortie de l'écran de tutoriel.
 * @return
 */
FonctionSortieEcran EcranGuide_getSortieFct();

/**
 * Evénement : fermeture de l'écran de tutoriel.
 * @param menu 1 si on doit revenir au menu, 0 si on doit complètement fermer le jeu.
 */
void EcranGuide_eventQuitter(int menu);

/**
 * Evénement : revenir à la page précédente du tutoriel.
 */
void EcranGuide_eventPrecedent();

/**
 * Evénement : revenir à la page suivante du tutoriel.
 */
void EcranGuide_eventSuivant();

#endif
