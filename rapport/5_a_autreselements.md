Autres éléments du programme
=======================

Eléments d'interface graphique
---------------------------------

### Les boutons

### Les boutons à choix multiple

### Les champ de texte
      
Les ramasses miettes
------------------------------

Afin de limiter le nombre d'allocations et de désallocations par unité de temps pour les structures qui en demandent beaucoup telles que `ElementListe` et `Position`, nous avons implémenté un ramasse miettes très simple nous permettant de recycler les précédents instances de ces types dont voici le fonctionnement. Chaque type à recycler possède son ramasse miettes.

Une ramasse miettes est configuré avec le nombre maximal d'instances recyclées stockées et la taille d'une structure à allouée. Au début, aucun pointeur n'est recyclé. Lors de l'allocation d'un élément, le ramasse miettes regarde si on a des pointeurs disponibles à recycler. Si c'est le cas, il retourne celui au dessus de la pile des pointeurs recyclés, dans le cas contraire il alloue un élément de la taille spécifiée à la création du ramasse miettes. Lors de la désallocation, si la pile d'éléments recyclés n'est pas pleine, il place le pointeur en haut de la pile et dans le cas contraire désalloue l'élément. À la fin de l'exécution du programme, tous les pointeurs recyclés restants dans la pile sont désalloués.
