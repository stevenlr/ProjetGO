
Autres éléments du programme
=======================

Eléments d'interface graphique
---------------------------------

Afin de faciliter les entrées utilisateurs, des structures ont été créées pour faciliter l'affichage et la gestion des éléments d'interface graphique. Chaque élément est instancié lors de la création du contexte graphique et stocké dans une variable globale afin de pouvoir être utilisé plus tard.

### Les boutons

Le premier élément d'interface graphique est le bouton. Il lui est spécifié une taille, une position, un texte, une couleur de fond et une couleur de texte. Une fois créé il est possible lors d'un clique de souris de tester si celui-ci était sur le bouton afin d'engendrer d'autres événements.

### Les boutons à choix multiple

Le second élément est un bouton à choix multiple. Il permet à l'utilisateur de choisir une option parmi une liste proposée. Il lui est spécifié une taille par choix, une position, des couleurs de fond pour l'état sélectionné et normal d'un choix et la couleur du texte. Les différents choix (au nombre maximal de 3) sont ensuite ajoutés. Une fois créé, on peut lors d'un clique de souris tester si celui-ci était sur le bouton à choix multiple et si c'est le cas, déterminer quelle option était choisie. Il est alors possible de récupérer le numéro de l'option choisie. Ces boutons sont utilisés lorsque l'utilisateur a un choix fini. Exemple : humain ou ordinateur, taille du plateau.

### Les champs de texte

Enfin, le champ de texte permet à l'utilisateur d'entrer du texte au clavier après l'avoir sélectionné à la souris, comme avec une interface graphique classique. Une barre indique que le champ est prêt à être utilisé. La taille du texte contenu est limité, il n'est possible d'effacer des caractères depuis la fin uniquement et certains caractères spéciaux ne sont pas acceptés. Ces champs sont utilisés pour entrer le nom des joueurs.

Deux autres utilitaires plus simples existent : un pour gérer les textures (chargées lors de la création du contexte graphique) et un pour écrire du texte à l'écran, permettant de gérer le style et l'alignement du texte.
      
Les ramasse-miettes
------------------------------

Afin de limiter le nombre d'allocations et de désallocations par unité de temps pour les structures qui en demandent beaucoup telles que `ElementListe` et `Position`, nous avons implémenté un ramasse-miettes très simple nous permettant de recycler les précédentes instances de ces types dont voici le fonctionnement. Chaque type à recycler possède son ramasse-miettes.

Un ramasse-miettes est configuré avec le nombre maximal d'instances recyclées stockées et la taille d'une structure à allouer. Au début, aucun pointeur n'est recyclé. Lors de l'allocation d'un élément, le ramasse-miettes regarde si on a des pointeurs disponibles à recycler. Si c'est le cas, il retourne celui au dessus de la pile des pointeurs recyclés, dans le cas contraire il alloue un élément de la taille spécifiée à la création du ramasse-miettes. Lors de la désallocation, si la pile d'éléments recyclés n'est pas pleine, il place le pointeur en haut de la pile et dans le cas contraire désalloue l'élément. À la fin de l'exécution du programme, tous les pointeurs recyclés restants dans la pile sont désalloués.
