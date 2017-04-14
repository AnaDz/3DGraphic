# 3DGraphic

Pour lancer le jeu, saisir les commandes suivantes :
mkdir build/
cd build/
cmake ..
make -j9
./main

Le jeu est une boule de neige qui descend une pente. Il s'y trouve des
bonshommes de neige, des arbres, et des chalets.
Rouler sur un bonhomme de neige rapporte 5 points.
Rouler sur un arbre rapporte 1 point.
Percuter un chalet fait exploser la boule de neige et termine la partie.
La pente est limitée par des barrières.

Les premières secondes de jeu sont vides d'obstacles, afin que le joueur puisse
prendre en main la boule de neige.

Pour se déplacer, le joueur peut utiliser les touches directionnelles droite et gauche.
Les touches directionnelles avant et arrière n'ont aucun effet.

Il est demandé au joueur de ne pas utiliser la souris pour dévier l'angle de la caméra.
