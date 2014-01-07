/**
 * @file Liste.h
 * @brief En-t�te de liste doublement cha�n�e.
 */

#ifndef LISTE_H_
#define LISTE_H_

typedef struct Liste* Liste;

/**
 * Cr�� une liste vide.
 *
 * @return La liste ! NULL en cas de probl�me. (�a devrait pas arriver mais bon...)
 */
Liste Liste_creer();

/**
 * D�truit une liste.
 * Attention � d�sallouer les �l�ments (si besoin est) avant pour pas avoir de grosses fuites m�moire...
 *
 * @param liste La liste � d�sallouer.
 */
void Liste_detruire(Liste liste);

/**
 * Se place en d�but de liste.
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
 * V�rifie si une liste est vide.
 *
 * @param liste
 * @return 1 si la liste est vide, 0 sinon.
 */
int Liste_estVide(Liste liste);

#endif
