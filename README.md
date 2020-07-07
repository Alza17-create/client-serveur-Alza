## Compiler les script
Chaque dossier contient un CMakeLists.txt mais il vous faut en premier lieu commencer par la partie serveur, si vous êtes dans à la racine du projet

```
mkdir build     #pour créer un dossier nomé build(c'est là qu'on va construire notre programme)
cd build        #aller dans le dossier build que l'on viens de créer
cmake ..        #préparer tout les nécessaire dans le dossier build
make            #execution de la création du programme excecutable
./myServer      #lancé le programme pour le serveur
```

Chaque dossier contient un CMakeLists.txt mais il vous faut en premier lieu commencer par la partie client, si vous êtes dans à la racine du projet

```
mkdir build     #pour créer un dossier nomé build(c'est là qu'on va construire notre programme)
cd build        #aller dans le dossier build que l'on viens de créer
cmake ..        #préparer tout les nécessaire dans le dossier build
make            #execution de la création du programme excecutable
./myClient      #lancé le programme pour le client
```


```
