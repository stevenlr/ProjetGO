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

/**
 * Retourne l'�l�ment courant de la liste.
 *
 * @param liste
 * @return L'�l�ment courant.
 */
void* Liste_courant(Liste liste);

/**
 * Se d�place � l'�lement suivant dans la liste.
 *
 * @param liste
 * @return 0 si il n'y avait pas d'�l�ment suivant, 1 sinon.
 */
int Liste_suivant(Liste liste);

/**
 * Se d�place � l'�l�ment pr�c�dent dans la liste.
 *
 * @param liste
 * @return 0 si il n'y avait pas d'�l�ment pr�c�dent, 1 sinon.
 */
int Liste_precedent(Liste liste);

/**
 * Ins�re un �l�ment apr�s l'�l�ment courant, et en fait le courant.
 *
 * @param liste
 * @param ptr Pointeur vers la donn�e � stocker.
 */
void Liste_insererCourant(Liste liste, void* ptr);

/**
 * Supprime l'�l�ment courant et rend courant l'�l�ment suivant, ou pr�c�dent si on est en fin de liste.
 *
 * @param liste
 */
void Liste_supprimerCourant(Liste liste);

#endif
