Le jeu de Go
==============================

Structures de données
---------------------------------

L’implémentation des types a été réalisée suivant les conventions du cours d’Algorithmique et, le cas échéant, selon les conventions données dans le document Projet GO 2013.

Les types Liste, Pile, Position, Pion, Chaîne, Territoire, Plateau, Partie et Tutoriel sont, chacun, un pointeur sur la structure lui correspondant. Le type ElementListe est une structure. Le type Couleur est une énumération. 

### ElementListe

Cette structure est définie dans Liste.c et correspond au type "cellule" vu en cours d'algorithmique. Ce type est très utilisé, on a donc créé un ramasse-miettes pour ce type.

###  Liste

Ce type permet de définir les types Pile et Chaine utilisés par le Jeu de Go.

###  Pile

Pile est un typedef de Liste. Ce type est utilisé pour les fonctions de détermination de Chaines et de Territoires.

###  Position

Ce type est utilisé pour indiquer la position d'un pion, d'une case sur un plateau. Il est donc très utilisé. Ainsi, un ramasse-miettes a également été créé pour ce type.

###  Couleur

C’est une énumération contenant les couleurs de cases/pions suivantes : VIDE, BLANC, NOIR, AURAVIDE, AURABLANC, AURANOIR. Les couleurs AURA nous permettent de mettre en évidence certains pions ou cases. L’utilisation de ces mises en évidence est faite dans le tutoriel.

###  Pion

La structure Pion contient une couleur et une position. Son utilisation est limitée et on aurait pu en faire abstraction. En effet, son unique utilisation est faite dans la fonction Plateau_capturerChaines.

###  Chaîne

La structure Chaine contient une liste de positions et une couleur. Il correspond à une chaîne de pions d'une même couleur sur un plateau de jeu de GO. Le type Chaine est utilisé ainsi par les fonctions Plateau_determinerChaine et Territoire_determinerTerritoire.

###  Territoire

Territoire est un typedef de Chaine. C'est une chaîne de cases vides uniquement.

###  Plateau

Ce type est un plateau de jeu de Go auquel on a ajouté des informations sur le nombre de pions de chaque couleur.

###  Partie

Ce type gère une partie de jeu de Go. Il stocke l'historique des plateaux, le komi, la taille du plateau, le handicap et le numéro du tour actuel. Il contient aussi les informations sur les joueurs, c'est-à-dire leur pseudonyme, et leur type (ordinateur ou humain).

###  Tutoriel

Ce type gère la partie tutoriel du jeu de Go. Il stocke une liste de plateaux-exemples ainsi qu'un commentaire pour chaque exemple.

