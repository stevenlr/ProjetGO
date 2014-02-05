
Intelligence Artificielle
-----------------------------

Une intelligence artificielle relativement simple (mais non naïve) a été implémentée. Son exécution se déroule en plusieurs phase : la phase de passage de tour, de défense, d'attaque et de jeu naïf.

### Passage de tour

Si l'adversaire vient de passer son tour, alors l'ordinateur a une chance sur quatre de faire de même. Celà permet, lorsqu'un humain joue contre l'ordinateur, de terminer le jeu dans des temps raisonnables si le joueur décide qu'il ne peut plus rien faire qui pourrait l'avantager. En effet, cette IA ne réfléchira pas directement à la possibilité de passer son tour si elle n'a plus l'avantage nul part sur le plateau.

Si l'ordinateur n'a pas décidé de passer, alors la phase de défense commence.

### Phase de défense

L'ordinateur va commencer par vérifier s'il est en danger quelque part sur le goban : si une de ses chaînes ne possède plus qu'une liberté. Si c'est le cas, il va placer un pion sur cette liberté afin d'essayer de se libérer. Le système de placement de pion permet de s'assurer que si le coup joué résulte en une chaîne n'ayant plus de libertés pour l'ordinateur lui-même, alors le coup est annulé, car illégal.

Si l'ordinateur n'a pas joué défensivement, il va passer à l'offensive.

### Phase d'attaque

L'ordinateur va alors chercher sur le goban toutes les chaînes ennemies et sélectionner celle possédant le moins de libertés. S'il en trouve une, il va placer un pion sur une de ses libertés.

Si l'ordinateur n'a pas pu jouer de coup offensif, alors il va passer à la phase naïve.

### Phase naïve

Le dernier recours de l'ordinateur est alors de placer un pion au hasard sur les cases restantes du goban. S'il n'a pas réussi à en placer, alors il passe son tour.

