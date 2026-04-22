# SupermarcheApp — Système de Gestion de Caisse

Projet de fin d'année — Licence 2 Informatique  
Institut Supérieur d'Informatique (ISI) — Dakar, 2024-2025

Application complète de gestion de caisses de supermarché.  
Architecture client-serveur : serveur HTTP en C++17 + interface navigateur HTML/CSS/JavaScript.

---

## Fonctionnalités

### Obligatoires
| Ref. | Fonctionnalité | Description |
|------|---------------|-------------|
| F01 | Gestion des caisses | Ouvrir et fermer des caisses |
| F02 | Ajout de clients | Orientation automatique vers la caisse la moins chargée |
| F03 | Caisse express | Clients ≤ 10 articles → caisse express automatiquement |
| F04 | Service d'un client | Retire le premier client de la file |
| F05 | Statistiques temps réel | Nb clients, temps d'attente, total servis |
| F06 | Interface navigateur | Toutes les opérations via page web (Fetch API) |
| F07 | Échange JSON | Communication serveur C++ ↔ navigateur en JSON |

### Bonus
- ✅ Historique des clients servis avec horodatage
- ✅ Alerte visuelle si une file dépasse 5 clients
- ✅ Répartition automatique à la fermeture d'une caisse non vide
- ✅ Graphique temps réel de la charge par caisse (Chart.js)
- ✅ Mode simulation : clients aléatoires à intervalle régulier

---

## Prérequis

- Windows avec [MinGW-w64](https://www.mingw-w64.org/) installé
- `g++` ≥ 9 avec support C++17
- `mingw32-make`
- Navigateur Chrome ou Firefox
- Git

---

## Installation

```bash
git clone https://github.com/Amatoullahi/SupermarcheApp.git
cd SupermarcheApp
```

Les bibliothèques `httplib.h` et `json.hpp` sont déjà incluses dans `lib/`.  
Aucune installation système supplémentaire n'est nécessaire.

---

## Compilation

```bash
mingw32-make
```

Pour recompiler depuis zéro :

```bash
mingw32-make clean
mingw32-make
```

---

## Lancement

```bash
# Sur Windows (depuis cmd.exe ou PowerShell)
supermarche.exe

# Ou double-clic sur supermarche.exe dans l'explorateur
```

Le serveur démarre sur `http://localhost:8080`.  
Ouvre cette URL dans ton navigateur pour accéder à l'interface.

---

## Structure du projet
SupermarcheApp/
├── lib/
│ ├── httplib.h # Bibliothèque serveur HTTP (header-only)
│ └── json.hpp # Bibliothèque JSON nlohmann (header-only)
├── src/
│ ├── client.h / .cpp # Classe Client
│ ├── caisse.h / .cpp # Classe Caisse (file d'attente)
│ ├── supermarche.h/.cpp # Classe Supermarche (logique métier)
│ ├── serveur.h / .cpp # Serveur HTTP + routes
│ ├── json_helper.h # Sérialisation C++ → JSON
│ └── main.cpp # Point d'entrée
├── web/
│ ├── index.html # Interface navigateur
│ ├── style.css # Feuille de style
│ └── app.js # Logique JavaScript (Fetch API)
├── Makefile
├── .gitignore
└── README.md

---

## Routes API

| Méthode | Route | Description |
|---------|-------|-------------|
| GET | `/api/etat` | État complet de toutes les caisses |
| POST | `/api/client/ajouter` | Ajouter un client `{nom, nbArticles}` |
| POST | `/api/caisse/ouvrir` | Ouvrir une caisse `{numero}` |
| POST | `/api/caisse/fermer` | Fermer une caisse vide `{numero}` |
| POST | `/api/caisse/fermer-redistribuer` | Fermer + redistribuer les clients `{numero}` |
| POST | `/api/caisse/servir` | Servir le prochain client `{numero}` |
| GET | `/api/historique` | Historique des clients servis |
| GET | `/api/stats` | Statistiques globales |
| GET | `/` | Interface web (index.html) |

---

## Organisation Git

main ← livraison finale
└── develop ← branche de travail principale
├── feature/cpp-core
├── feature/cpp-server
├── feature/web-interface
├── feature/bonus-historique
├── feature/bonus-alerte
├── feature/bonus-graphique
├── feature/bonus-repartition
├── feature/bonus-simulation
└── feature/integration

---

## Technologies utilisées

- **C++17** — POO, files d'attente (`std::queue`), exceptions
- **cpp-httplib** — Serveur HTTP embarqué (header-only)
- **nlohmann/json** — Sérialisation JSON (header-only)
- **JavaScript ES6** — Fetch API, mise à jour dynamique sans rechargement
- **Chart.js** — Graphique temps réel (CDN)
- **Git / GitHub** — Versionnement, branches, commits structurés