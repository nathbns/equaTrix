# EquaTrix

## Informations du projet

### Équipe
- BARSAN Robert (p2305075)
- BEN SOUSSAN Nathan (p2300345)
- LAUTIN Renan (p2303036)

### Projet
- **Identifiant Forge**: https://forge.univ-lyon1.fr/p2300345/equaTrix
- **Module**: LIFAPCD 2024-2025
- **Tuteur**: LOUVET Nicolas

## Description
EquaTrix est une application mathématique multiplateforme permettant de manipuler des matrices, résoudre des systèmes d'équations linéaires, intégrer des fonctions et analyser des fonctions mathématiques.

## Architecture du projet

Le projet est organisé en deux parties principales :

- Un ensemble de classes C++ pour les calculs mathématiques (`Matrix`, `System`, `Function`, `Integral`)
- Une interface graphique utilisant le framework Qt pour interagir avec ces classes

### Structure des fichiers

```
equaTrix/
├── src/               # Code source
│   ├── backend/       # Calculs mathématiques
│   │   ├── Matrix.h/cpp   # Classe pour les opérations matricielles
│   │   ├── System.h/cpp   # Classe pour résoudre des systèmes d'équations
│   │   ├── Function.h/cpp # Classe pour évaluer des fonctions mathématiques
│   │   └── Integral.h/cpp # Classe pour calculer des intégrales
│   ├── qt/            # Interface graphique Qt
│   │   ├── mainQt.cpp     # Point d'entrée du programme Qt
│   │   ├── mainwindow.h/cpp # Fenêtre principale de l'interface Qt
│   │   ├── mainwindow.ui    # Fichier de design UI Qt
│   │   └── resources.qrc    # Ressources Qt (icônes, etc.)
│   └── antlr4/        # Fichiers générés par ANTLR
│       ├── CalcLexer.cpp/h
│       ├── CalcParser.cpp/h
│       ├── CalcVisitor.h
│       ├── CalcBaseVisitor.h
│       └── CalcListener.h
│   
├── build/             # Répertoire de compilation (généré)
├── bin/               # Exécutables compilés (généré)
├── obj/               # Fichiers objets intermédiaires (généré)
├── CMakeLists.txt     # Configuration CMake pour la compilation
└── makefile           # Makefile pour la version terminal
```

## Le Framework Qt dans EquaTrix

### Introduction à Qt

Qt est un framework C++ multiplateforme qui permet de créer des interfaces graphiques performantes et modernes. Voici les concepts clés utilisés dans notre application :

1. **Widgets** : Éléments d'interface utilisateur (boutons, champs de texte, etc.)
2. **Layouts** : Disposition des widgets dans l'interface
3. **Signaux et slots** : Mécanisme d'événements pour connecter l'interface aux fonctionnalités
4. **Meta-Object Compiler (MOC)** : Système qui enrichit C++ avec des fonctionnalités comme les signaux/slots

### Intégration des classes dans Qt

#### Classe Matrix dans l'interface Qt

La classe `Matrix` est intégrée dans l'onglet Matrix de l'interface graphique :

- Les matrices sont représentées visuellement par des tableaux modifiables (`QTableWidget`)
- Les opérations matricielles (addition, multiplication, etc.) sont effectuées en appelant directement les méthodes de la classe `Matrix`
- Processus d'intégration :
  1. L'utilisateur saisit les valeurs dans l'interface
  2. Les valeurs sont extraites et converties en objets `Matrix`
  3. Les opérations sont effectuées sur ces objets
  4. Les résultats sont reconvertis pour l'affichage dans l'interface

#### Classe System dans l'interface Qt

La classe `System` est intégrée dans l'onglet System de l'interface graphique :

- L'utilisateur peut entrer une matrice augmentée représentant un système d'équations linéaires
- L'application utilise `SystemSolver::analyzeSystem` pour déterminer le type de solution
- Les solutions sont affichées selon leur type (unique, infinies, aucune)

## Compilation et exécution

### Prérequis

- CMake 3.16 ou supérieur
- Compilateur C++ compatible C++17
- Qt 5 ou Qt 6 avec le module Widgets

#### Installation des prérequis

##### Sur macOS
```bash
# Installation via Homebrew
brew install cmake
brew install qt@6

# Ajouter Qt au PATH (ajouter dans ~/.zshrc ou ~/.bash_profile)
echo 'export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

##### Sur Linux (Ubuntu/Debian)
```bash
# Installation des outils de base
sudo apt update
sudo apt install build-essential cmake

# Installation de Qt6
sudo apt install qt6-base-dev qt6-base-private-dev
sudo apt install qt6-tools-dev qt6-tools-private-dev
sudo apt install qt6-declarative-dev qt6-declarative-private-dev

# Installation des modules Qt supplémentaires nécessaires
sudo apt install libqt6widgets6 qt6-tools-dev-tools
```

##### Sur Linux (Fedora)
```bash
# Installation des outils de base
sudo dnf install gcc-c++ cmake

# Installation de Qt6
sudo dnf install qt6-qtbase-devel
sudo dnf install qt6-qttools-devel
sudo dnf install qt6-qtdeclarative-devel

# Installation des modules Qt supplémentaires nécessaires
sudo dnf install qt6-qtwidgets qt6-qttools
```

##### Vérification de l'installation
Pour vérifier que Qt est correctement installé :
```bash
qmake6 --version
```

#### Avec CMake (recommandé pour Qt)
Executer le 
``` 
./build.sh 

```

### Compatibilité des plateformes

L'application est compatible avec :

- macOS
- Linux

Grâce à l'utilisation de Qt et CMake, la compilation et l'exécution suivent le même processus sur toutes les plateformes, avec seulement de légères différences dans les chemins d'exécution.

## Fonctionnalités

### Onglet Matrix

- Création et manipulation de matrices de taille variable
- Opérations : addition, soustraction, multiplication, comparaison
- Calcul de propriétés : déterminant, transposée, inverse, rang

### Onglet System

- Résolution de systèmes d'équations linéaires
- Détection du type de solution (unique, infinie, aucune)
- Affichage des solutions et historique des calculs

### Onglet Integration

- Calcul d'intégrales numériques de fonctions
- Plusieurs méthodes disponibles (rectangles, trapèzes)

### Onglet Function

- Analyse de fonctions mathématiques
- Calcul de dérivées et recherche de racines

# equaTrix
