/**
 * @file EcranGuide.h
 * @brief Ecran de tutoriel du jeu.
 */

#ifndef ECRANGUIDE_H_
#define ECRANGUIDE_H_

/**
 * Charge le tutoriel et pr�pare les �tats de l'�cran.
 * @return 0 en cas d'erreur, 1 sinon.
 */
int EcranGuide_init();

/**
 * D�truit les �tats courant de l'�cran de tutoriel.
 */
void EcranGuide_detruire();

/**
 * Logique de l'�cran de tutoriel.
 */
void EcranGuide_main();

/**
 * Retourne la fonction d'entr�e de l'�cran de tutoriel.
 * @return
 */
FonctionEntreeEcran EcranGuide_getEntreeFct();

/**
 * Retourne la fonction de sortie de l'�cran de tutoriel.
 * @return
 */
FonctionSortieEcran EcranGuide_getSortieFct();

/**
 * Ev�nement : fermeture de l'�cran de tutoriel.
 * @param menu 1 si on doit revenir au menu, 0 si on doit compl�tement fermer le jeu.
 */
void EcranGuide_eventQuitter(int menu);

/**
 * Ev�nement : revenir � la page pr�c�dente du tutoriel.
 */
void EcranGuide_eventPrecedent();

/**
 * Ev�nement : revenir � la page suivante du tutoriel.
 */
void EcranGuide_eventSuivant();

#endif
