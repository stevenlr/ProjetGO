/**
 * @file RamasseMiettes.h
 * @brief Un simple ramasse miettes.
 */

#ifndef RAMASSEMIETTES_H_
#define RAMASSEMIETTES_H_

typedef struct RamasseMiettes* RamasseMiettes;

/**
 * Crée un ramasse miettes.
 *
 * @param nbElements Nombre maximal d'éléments à recycler.
 * @param tailleElement Taille d'un élément.
 * @return Le ramasse miettes créé.
 */
RamasseMiettes RamasseMiettes_creer(int nbElements, int tailleElement);

/**
 * Détruit un ramasse miettes. Ne pas oublier de le vider avant.
 *
 * @param gc
 */
void RamasseMiettes_detruire(RamasseMiettes gc);

/**
 * Alloue un élément depuis le ramasse miettes.
 *
 * @param gc
 * @return L'élément alloué. NULL en cas d'erreur.
 */
void* RamasseMiettes_allouer(RamasseMiettes gc);

/**
 * Désalloue un élément et le recycle si besoin.
 *
 * @param gc
 * @param ptr Elément à désallouer.
 */
void RamasseMiettes_desallouer(RamasseMiettes gc, void* ptr);

/**
 * Désalloue tous les éléments du ramasse miettes.
 *
 * @param gc
 */
void RamasseMiettes_vider(RamasseMiettes gc);

#endif
