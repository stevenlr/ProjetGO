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

#endif
