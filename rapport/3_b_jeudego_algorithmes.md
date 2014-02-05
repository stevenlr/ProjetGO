Algorithmes
-------------------------

###  Déterminer les libertés

L'objectif est de déterminer les libertés de la chaîne passée en paramètre.
Pour ceci, l'algorithme consiste à parcourir chaque pion de la chaîne. À chaque fois, on fait l'exécution suivante :

 - On regarde s'il y a une case vide autour de ce pion (Au dessus, en dessous, à sa gauche ou à sa droite).
 - Si une case vide est trouvée, on vérifie si cette dernière ne fait pas déjà partie de la liste de libertés en cours de détermination de cette chaîne.
 - Si ce n'est pas le cas, on ajoute cette case à la liste de libertés.

Une fois le parcours terminé, on obtient ainsi la liste de libertés de la chaîne.

###  Déterminer territoire

L'objectif est de déterminer le territoire auquel la position passée en paramètre appartient. Cette position doit correspondre à une case vide du plateau. Pour ceci, l'algorithme consiste en l'utilisation d'une pile qui contient au départ la position passée en paramètre. À chaque fois on fait l'exécution suivante :

 - On dépile une position de la pile et on verifie s'il y a une case vide autour. (Au dessus, en dessous, à sa gauche ou à sa droite).
 - Si une case vide est trouvée, on vérifie si cette dernière ne fait pas déjà partie du territoire en cours de détermination.
     - Si ce n'est pas le cas, on ajoute la position de cette case au territoire et on l'empile.
 - Si une case non vide est trouvée, on vérifie que le territoire a une couleur d'un des deux joueurs.
     - Si ce n'est pas le cas, on lui donne la couleur du pion.
	 - Si c'est le cas, et si la couleur n'est pas celle du territoire alors on déclare ce territoire neutre.
 - On s'arrête une fois la pile vide.

Une fois le parcours terminé, on obtient ainsi un territoire auquel appartient la position passée en paramètre.

###  Déterminer séki

L'objectif est, à partir d'un territoire passé en paramètre, de savoir si ce dernier est un séki ou non. Ce territoire doit avoir la couleur VIDE et n'être constitué que de deux cases. Ce territoire étant de couleur VIDE, cela implique qu'il est au moins entourée par deux chaînes de couleur différentes. L'algorithme s'exécute donc ainsi :

 - On détermine les chaînes qui entourent le territoire.
 - Pour chaque chaîne, on verifie que ses libertés appartiennent au territoire. Le cas échéant, on renvoie que ce n'est pas un séki.
 - Si les libertés de chaque chaîne sont toutes comprises dans le territoire, alors ce dernier est un séki.

###  Déterminer les yeux d'une chaîne

L'objectif est, à partir d'une chaîne, de déterminer les libertés de la chaîne qui sont des yeux. Pour cela, l'algorithme consiste à parcourir les libertés de la chaîne et vérifier pour chacune si c'est un oeil. A chaque fois, on fait l'exécution suivante :

 - On regarde si la liberté est entourée par un pion de la couleur de la chaîne ou un bord. (Au dessus, en dessous, à gauche et à droite)
 - On regarde si la liberté a au plus un pion de la couleur opposée ou vide adjacent en diagonale. (Les coins donc du carré entourant la liberté).
 - Si les deux conditions sont vérifiées, c'est un oeil. Sinon ce n'en est pas un.

On obtient donc la liste des yeux d'une chaîne.

###  Déterminer une chaîne

L'objectif est de déterminer une chaîne à partir d'une position appartenant à cette chaîne. Pour ceci, l'algorithme consiste à utiliser une pile qui contient au départ la position passée en paramètre. A chaque fois on fait l'exécution suivante :
 - On dépile une position de la pile et on verifie s'il y a un pion de la couleur de la chaîne autour. (Au dessus, en dessous, à sa gauche ou à sa droite)
 - Si un tel pion est trouvé, on vérifie si ce dernier ne fait pas déjà partie de la chaîne en cours de détermination.
 - Si ce n'est pas le cas, on ajoute la position de ce pion à la chaîne et on l'empile.
 - On s'arrête une fois la pile vide.

Une fois le parcours terminé, on obtient ainsi une chaîne auquel appartient la position passée en paramètre.

###  Réaliser une capture

L'objectif est de verifier si la pose d'un pion entraîne une capture ou davantage et la ou les captures réalisées. Pour ceci, l'algorithme consiste à vérifier si la pose du pion entraîne la capture d'une des chaînes situés au dessus, en dessous, à gauche ou à droite. Pour chacune des 4 positions autour du pion posé, on fait l'exécution suivante :

 - On verifie si la position appartient déjà à une des chaînes à capturer.
 - Si ce n'est pas le cas, on détermine la chaîne correspondant à cette position ainsi que ses libertés.
 - Si cette chaîne n'a pas de liberté, on l'ajoute à la liste des chaînes à capturer.
 - Une fois ces 4 positions étudiées, et si la liste des chaînes à capturer n'est pas vide, on réalise la capture de ces chaînes.

###  Déterminer les chaînes entourant un territoire

L'objectif est de déterminer les chaînes entourant un territoire. Pour cela, l'algorithme va parcourir toutes les positions du territoire. À chaque fois, il fait l'exécution suivante :

 - Il verifie si au dessus, en dessous, à gauche ou à droite il y a un pion.
 - Pour chaque pion trouvé, il va vérifier si ce pion n'appartient pas déjà à une des chaînes autour du territoire en cours de détermination.
 - Si c'est le cas, il va déterminer la chaîne à laquelle ce pion appartient et l'ajouter à la liste des chaînes autour du territoire.

Une fois le parcours terminé, on obtient ainsi les chaînes qui entourent ce territoire.

###  Calcul du score

L'objectif est de calculer le score final de la partie à partir d'un plateau. Pour ceci, l'algorithme ajoute d'abord le komi au bon joueur puis parcourt le tableau. Pour chaque position, il fait l'exécution suivante : 

 - On verifie si la position a déjà été traitée. Si c'est le cas, on passe à la suivante.
 - On verifie si la position correspond à un pion. Si c'est le cas, on ajoute 1 point au score du joueur de la couleur du pion et on ajoute la position aux positions déjà traitées.
 - Sinon, la case est vide, on détermine alors le territoire qui lui est associé.
 - On verifie si le territoire appartient à un des deux joueurs. Si c'est le cas, on ajoute le nombre de cases du territoire au joueur de la couleur du territoire.
 - On ajoute toutes les positions des cases aux cases déjà traitées.

Une fois le plateau parcouru, on obtient le score de chaque joueur.

