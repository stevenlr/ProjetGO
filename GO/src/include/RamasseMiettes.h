/**
 * @file RamasseMiettes.h
 * @brief Un simple ramasse miettes.
 */

#ifndef RAMASSEMIETTES_H_
#define RAMASSEMIETTES_H_

typedef struct RamasseMiettes* RamasseMiettes;

/**
 * Cr�e un ramasse miettes.
 *
 * @param nbElements Nombre maximal d'�l�ments � recycler.
 * @param tailleElement Taille d'un �l�ment.
 * @return Le ramasse miettes cr��.
 */
RamasseMiettes RamasseMiettes_creer(int nbElements, int tailleElement);

/**
 * D�truit un ramasse miettes. Ne pas oublier de le vider avant.
 *
 * @param gc
 */
void RamasseMiettes_detruire(RamasseMiettes gc);

/**
 * Alloue un �l�ment depuis le ramasse miettes.
 *
 * @param gc
 * @return L'�l�ment allou�. NULL en cas d'erreur.
 */
void* RamasseMiettes_allouer(RamasseMiettes gc);

/**
 * D�salloue un �l�ment et le recycle si besoin.
 *
 * @param gc
 * @param ptr El�ment � d�sallouer.
 */
void RamasseMiettes_desallouer(RamasseMiettes gc, void* ptr);

/**
 * D�salloue tous les �l�ments du ramasse miettes.
 *
 * @param gc
 */
void RamasseMiettes_vider(RamasseMiettes gc);

#endif
