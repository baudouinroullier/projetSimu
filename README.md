# projetSimu

Liste de liens utiles:

Depot du projet : https://github.com/baudouinroullier/projetSimu

Feuille excel : https://docs.google.com/spreadsheets/d/1MrfwoxVlFF4Z6S7hiM5UAF3z679gkJSpMlotT8RZev4/edit#gid=0

Arbre des trucs a faire : http://demo.redmine.org/projects/the-game/activity


Apprendre a utiliser Git : https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control (chapitres 1 à 3 suffisants)

Apprendre le C++ : https://openclassrooms.com/courses/programmez-avec-le-langage-c (parties 1, 2 et 4)

Apprendre la SFML : https://openclassrooms.com/courses/creez-des-applications-2d-avec-sfml

Diagramme UML : Je propose ArgoUML (http://argouml.tigris.org/). Si vous pensez a un autre soft ou site dites-le. J'ai fait un exemple rapide non complet pour montrer ce que ca donne.


# Installation et compilation

## OSX
Ouvrez un terminal et placez-vous dans un répertoire approprié.
Installez Homebrew :
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
Installez la SFML et CMake :
```
brew install sfml
brew install cmake
```
Puis suivez les instructions pour Linux.

## Linux

Installez la sfml avec votre gestionnaire de paquet (libsfml-dev)

Allez dans le dossier où vous voulez cloner le projet.

```
git clone https://github.com/baudouinroullier/projetSimu.git
cd projetSimu
mkdir build
cd build
cmake ..
make
./projetSimu
```

## Windows

### Version facile

Installez linux puis cf plus haut.

### Version difficile

Trouvez dans votre playlist favorite la musique la plus relaxante possible et mettez-la en boucle. Préparez également un cachet d'aspirine. Je ne suis pas responsable des éventuelles séquelles psychologiques que vous subirez en suivant ces étapes. Suivez ces étapes à vos risques et périls.

Installez une GUI pour git (https://git-scm.com/downloads/guis, celle que vous voulez, sauf GitHub Desktop).

Installez cmake (https://cmake.org/files/v3.5/cmake-3.5.1-win32-x86.msi)

Installez mingw 32 bits depuis le site que vous trouverez grâce à votre moteur de recherche favori (en fait je trouve plus le site. Avec Camille il est possible qu'on ait juste pris le mingw qui est empaqueté avec code blocks ici : http://codeblocks-16.01mingw-setup.exe)

Installez un IDE au choix, par exemple Code Blocks ou Qt Creator. Si vous préférez ne pas installer d'IDE, installez linux, c'est fait pour.

Téléchargez la SFML (http://www.sfml-dev.org/files/SFML-2.3.2-windows-gcc-4.9.2-mingw-32-bit.zip) et dézippez le dossier où bon vous semble.

Ouvrez votre GUI pour git et trouvez comment on clone un dépôt. Clonez https://github.com/baudouinroullier/projetSimu.git dans le dossier de votre choix.

Ajoutez le chemin vers mingw dans la variable d'environnement PATH de windows (par exemple http://superuser.com/questions/949560/how-do-i-set-system-environment-variables-in-windows-10) (plus de détails à venir)

Lancez cmake et créez un dossier build dans la racine de votre dépôt local. Indiquez à cmake la racine pour le code source et le dossier build pour construire les binaires. S'il y a des options pour lesquelles vous n'êtes pas sûr, demandez par mail et on verra. Je mettrai à jour ce README.

Ensuite, il faut faire des trucs magiques avec la SFML suivant cette page : http://www.sfml-dev.org/tutorials/2.3/start-cb.php. En théorie, c'est là que ça marchera pas et qu'on en rediscutera par mail/skype/discord plus tard. Si ça marche, bravo, mais c'est pas fini. Suivez les étapes pour linker dynamiquement, et pas statiquement.

Vous venez en théorie de créer un nouveau projet SFML. Il faut faire les même manips pour le projet qui a été cloné. Cmake devrait avoir crée un fichier .cbp que code blocks peut lire pour charger le projet, donc ça devrait être à peu près les mêmes étapes que sur le tuto SFML.

Buildez et runnez les tests, s'il y a un rond vert dans une fenêtre noire ou bien du vomi visuel qui s'affiche, c'est que tout est bien configuré.

Bravo ! C'est presque fini. Il ne vous reste qu'à prendre votre aspirine et aller dormir 48h. Si au réveil votre mal de tête n'est toujours pas parti, la seule solution est d'installer linux et d'oublier windows à tout jamais.
