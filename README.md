<<<<<<< HEAD
# Système de Gestion de Caisse de Supermarché

Application complète de gestion de caisses développée en C++ (serveur HTTP)
et JavaScript (interface navigateur). Projet de fin d'année — Licence 2
Informatique, Groupe ISI 2024-2025.

## Membres du groupe

| Prénom | Nom  | Matricule    |
|--------|------|--------------|
| Coumba | Diaw |L2GLcj-26-1188|

## Prérequis

- g++ >= 9 (MinGW-W64 sur Windows)
- mingw32-make
- git
- Chrome ou Firefox
- Bibliothèques dans `lib/` : `httplib.h` (v0.14.3), `json.hpp`

## Installation

```bash
# 1. Cloner le dépôt
git clone https://github.com/Amatoullahi/SupermarcheApp.git
cd SupermarcheApp

# 2. Télécharger les bibliothèques dans lib/
curl -L https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.14.3/httplib.h \
     -o lib/httplib.h
curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp \
     -o lib/json.hpp

# 3. Compiler
=======
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
>>>>>>> develop
mingw32-make
```

## Lancement

<<<<<<< HEAD
```bash
mingw32-make run
```

Ouvrir ensuite **http://127.0.0.1:8080** dans Chrome ou Firefox.

## Fonctionnalités

| Ref | Fonctionnalité | Description |
|-----|----------------|-------------|
| F01 | Gestion des caisses | Ouvrir/fermer des caisses numérotées |
| F02 | Ajout de clients | Orientation automatique vers la caisse la moins chargée |
| F03 | Caisse express | Clients ≤ 10 articles → caisse express automatiquement |
| F04 | Service d'un client | Retire le premier client de la file |
| F05 | Statistiques temps réel | Nb clients, temps d'attente, total servis |
| F06 | Interface navigateur | Page web sans rechargement (Fetch API) |
| F07 | Échange JSON | Communication serveur C++ ↔ navigateur en JSON |

## Architecture
SupermarcheApp/
├── lib/ # Bibliothèques header-only
│ ├── httplib.h # Serveur HTTP (cpp-httplib v0.14.3)
│ └── json.hpp # Sérialisation JSON (nlohmann/json)
├── src/ # Code C++
│ ├── client.h / client.cpp
│ ├── caisse.h / caisse.cpp
│ ├── supermarche.h / supermarche.cpp
│ ├── serveur.h / serveur.cpp
│ ├── json_helper.h
│ └── main.cpp
├── web/ # Interface navigateur
│ ├── index.html
│ ├── style.css
│ └── app.js
├── Makefile
└── README.md

## Routes API

| Méthode | Route | Description |
|---------|-------|-------------|
| GET | /api/etat | État complet de toutes les caisses |
| POST | /api/client/ajouter | Ajouter un client `{nom, nbArticles}` |
| POST | /api/caisse/ouvrir | Ouvrir une caisse `{numero}` |
| POST | /api/caisse/fermer | Fermer une caisse vide `{numero}` |
| POST | /api/caisse/servir | Servir le premier client `{numero}` |
| GET | /api/stats | Total clients servis |

## Compilation — notes Windows

Le projet utilise MinGW-W64 sur Windows. Les flags spéciaux sont nécessaires
pour la compatibilité réseau :

```makefile
-D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN -lws2_32 -lpthread -static-libgcc -static-libstdc++
```
=======
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
>>>>>>> develop
