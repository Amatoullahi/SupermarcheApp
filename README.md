# SupermarcheApp

## Présentation

SupermarcheApp est une application de gestion de caisses de supermarché développée en C++ avec une architecture client-serveur locale. Elle permet d’ouvrir et fermer des caisses, d’ajouter des clients, de les orienter automatiquement vers la caisse appropriée, de servir les clients en file d’attente et d’afficher l’état du supermarché en temps réel dans une interface web. [file:1]

Le projet s’appuie sur la programmation orientée objet en C++, l’utilisation de files d’attente, un serveur HTTP embarqué avec `cpp-httplib`, des échanges JSON avec `nlohmann/json` et une interface navigateur en HTML, CSS et JavaScript. [file:1]

## Membres du groupe

- Nom Prénom — Matricule
- Nom Prénom — Matricule

> Remplace cette section par les vraies informations de ton groupe. Le sujet exige explicitement les prénoms, noms et matricules des membres. [file:1]

## Fonctionnalités

- Gestion des caisses : ouverture et fermeture des caisses.
- Ajout de clients avec orientation automatique.
- Caisse express pour les clients ayant 10 articles ou moins.
- Service du premier client de chaque file.
- Affichage du nombre de clients par caisse.
- Estimation du temps d’attente.
- Total des clients servis en temps réel.
- Interface web dynamique sans rechargement de page.
- Communication entre le serveur C++ et l’interface au format JSON. [file:1]

## Architecture du projet

Le projet respecte l’organisation demandée dans le sujet, avec les bibliothèques dans `lib/`, le code C++ dans `src/` et l’interface web dans `web/`. [file:1]

```text
SupermarcheApp/
├── lib/
│   ├── httplib.h
│   └── json.hpp
├── src/
│   ├── client.h
│   ├── client.cpp
│   ├── caisse.h
│   ├── caisse.cpp
│   ├── supermarche.h
│   ├── supermarche.cpp
│   ├── serveur.h
│   ├── serveur.cpp
│   ├── jsonhelper.h
│   └── main.cpp
├── web/
│   ├── index.html
│   ├── style.css
│   └── app.js
├── Makefile
├── README.md
└── .gitignore
```

## Prérequis

Avant de lancer le projet, il faut disposer de :

- `g++` avec support C++17 minimum,
- `make` ou `mingw32-make` selon l’environnement,
- `git`,
- un navigateur moderne comme Chrome ou Firefox. [file:1]

## Bibliothèques utilisées

Ce projet utilise deux bibliothèques header-only intégrées directement dans le dossier `lib/` :

- `cpp-httplib` : serveur HTTP léger en C++,
- `nlohmann/json` : sérialisation et désérialisation JSON. [file:1]

Aucune installation système supplémentaire n’est nécessaire pour ces bibliothèques si les fichiers `httplib.h` et `json.hpp` sont déjà présents dans `lib/`. [file:1]

## Installation

### 1. Cloner le dépôt

```bash
git clone https://github.com/Amatoullahi/SupermarcheApp.git
cd SupermarcheApp
```

### 2. Vérifier la présence des bibliothèques

S’assurer que les fichiers suivants sont bien présents :

- `lib/httplib.h`
- `lib/json.hpp` [file:1]

### 3. Compiler le projet

Sous Linux/macOS :

```bash
make
```

Sous Git Bash / MinGW sous Windows :

```bash
mingw32-make
```

## Lancement

Après compilation, lancer l’application.

Sous Linux/macOS :

```bash
./supermarche
```

Sous Windows / MinGW :

```bash
./supermarche.exe
```

Ensuite, ouvrir le navigateur à l’adresse :

```text
http://localhost:8080
```

Le sujet précise que le serveur doit répondre localement sur le port `8080` et servir l’interface web directement. [file:1]

## Exemples d’utilisation

### Ajouter un client

- Saisir un nom.
- Saisir un nombre d’articles.
- Cliquer sur **Ajouter un client**.

Si le client a 10 articles ou moins, il est dirigé automatiquement vers la caisse express. Sinon, il est orienté vers la caisse ordinaire la moins chargée. [file:1]

### Servir un client

- Saisir le numéro de la caisse.
- Cliquer sur le bouton de service.

Le premier client de la file est retiré, conformément au fonctionnement en file d’attente FIFO. [file:1]

### Fermer une caisse

- Une caisse vide peut être fermée.
- Une caisse non vide ne doit pas être fermée et une erreur doit être signalée sans faire planter le serveur. [file:1]

## API HTTP

Le serveur expose les routes suivantes :

- `GET /api/etat` : retourne l’état complet du supermarché.
- `POST /api/client/ajouter` : ajoute un client.
- `POST /api/caisse/ouvrir` : ouvre une caisse.
- `POST /api/caisse/fermer` : ferme une caisse si elle est vide.
- `POST /api/caisse/servir` : sert le premier client d’une caisse.
- `GET /api/stats` : retourne les statistiques globales. [file:1]

## Tests réalisés

Les tests suivants ont été validés :

- compilation du projet sans erreur,
- démarrage du serveur HTTP,
- affichage des caisses dans le navigateur,
- ajout d’un client en caisse express si `nbArticles <= 10`,
- ajout d’un client en caisse ordinaire sinon,
- service du premier client,
- refus de fermeture d’une caisse non vide,
- mise à jour dynamique de l’interface,
- dépôt Git propre. [file:1]

## Fonctionnalités bonus

Si vous avez implémenté des bonus, ajoutez-les ici. Par exemple :

- historique des clients servis avec horodatage,
- alerte visuelle si une file dépasse 5 clients,
- répartition automatique lors de la fermeture d’une caisse,
- graphique en temps réel,
- mode simulation. [file:1]

## Commandes Git utiles

```bash
git status
git add .
git commit -m "feat: description"
git push origin develop
```

Le sujet impose un travail par branches avec `develop` comme branche principale de travail, puis une fusion finale vers `main` quand tout le projet fonctionne. [file:1]

## Livraison finale

Quand le projet est totalement finalisé :

```bash
git checkout main
git merge develop
git push origin main
```

La fusion vers `main` ne doit se faire qu’en fin de projet, lorsque l’application est prête pour la démonstration et la livraison finale. [file:1]