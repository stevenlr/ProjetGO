#ifndef PLATEAU_H_
#define PLATEAU_H_

typedef Matrice* Plateau;

Plateau Plateau_creer(int taille);

void Plateau_detruire(Plateau plateau);

Couleur Plateau_get(Plateau plateau, int i, int j);

void Plateau_set(Plateau plateau, int i, int j, Couleur couleur);

int Plateau_estIdentique(Plateau plateau, Plateau ancienPlateau);

void Plateau_copier(Plateau from, Plateau to);

void Plateau_sauvegarder(Plateau plateau,FILE* fichier);

void Plateau_charger(FILE* fichier);

#endif
