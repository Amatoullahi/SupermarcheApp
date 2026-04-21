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
mingw32-make
```

## Lancement

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