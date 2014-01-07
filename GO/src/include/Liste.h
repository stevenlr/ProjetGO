/**
 * @file Liste.h
 * @brief En-tête de liste doublement chaînée.
 */

#ifndef LISTE_H_
#define LISTE_H_

typedef struct Liste* Liste;

/**
 * Créé une liste vide.
 *
 * @return La liste ! NULL en cas de problème. (ça devrait pas arriver mais bon...)
 */
Liste Liste_creer();

/**
 * Détruit une liste.
 * Attention à désallouer les éléments (si besoin est) avant pour pas avoir de grosses fuites mémoire...
 *
 * @param liste La liste à désallouer.
 */
void Liste_detruire(Liste liste);

/**
 * Se place en début de liste.
 *
 * @param liste
 */
void Liste_tete(Liste liste);

/**
 * Se place en fin liste.
 *
 * @param liste
 */
void Liste_queue(Liste liste);

/**
 * Vérifie si une liste est vide.
 *
 * @param liste
 * @return 1 si la liste est vide, 0 sinon.
 */
int Liste_estVide(Liste liste);

/**
 * Retourne l'élément courant de la liste.
 *
 * @param liste
 * @return L'élément courant.
 */
void* Liste_courant(Liste liste);

/**
 * Se déplace à l'élement suivant dans la liste.
 *
 * @param liste
 * @return 0 si il n'y avait pas d'élément suivant, 1 sinon.
 */
int Liste_suivant(Liste liste);

/**
 * Se déplace à l'élément précédent dans la liste.
 *
 * @param liste
 * @return 0 si il n'y avait pas d'élément précédent, 1 sinon.
 */
int Liste_precedent(Liste liste);

/**
 * Insère un élément après l'élément courant, et en fait le courant.
 *
 * @param liste
 * @param ptr Pointeur vers la donnée à stocker.
 */
void Liste_insererCourant(Liste liste, void* ptr);

/**
 * Supprime l'élément courant et rend courant l'élément suivant, ou précédent si on est en fin de liste.
 *
 * @param liste
 */
void Liste_supprimerCourant(Liste liste);

#endif
