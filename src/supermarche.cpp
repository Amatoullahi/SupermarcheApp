#include "supermarche.h"
#include <stdexcept>

Supermarche::Supermarche() : compteurId(1), totalServis(0) {
}

void Supermarche::initialiser(int nbCaisses) {
    if (nbCaisses <= 0) {
        throw std::runtime_error("Le nombre de caisses doit etre positif !");
    }

    caisses.clear();

    for (int i = 1; i <= nbCaisses; ++i) {
        bool estExpress = (i == 1);
        caisses.push_back(Caisse(i, estExpress));
    }
}

void Supermarche::ouvrirCaisse(int numero) {
    for (auto& caisse : caisses) {
        if (caisse.getNumero() == numero) {
            caisse.ouvrir();
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::fermerCaisse(int numero) {
    for (auto& caisse : caisses) {
        if (caisse.getNumero() == numero) {
            if (caisse.isExpress()) {
                throw std::runtime_error("La caisse express ne peut pas etre fermee !");
            }
            caisse.fermer();
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::fermerCaisseAvecRepartition(int numero) {
    // Trouver la caisse à fermer
    Caisse* cibleFermeture = nullptr;
    for (auto& c : caisses) {
        if (c.getNumero() == numero) {
            cibleFermeture = &c;
            break;
        }
    }
    if (!cibleFermeture)
        throw std::runtime_error("Caisse introuvable !");
    if (cibleFermeture->isExpress())
        throw std::runtime_error("La caisse express ne peut pas être fermée.");

    // Redistribuer les clients vers les autres caisses ouvertes
    while (!cibleFermeture->estVide()) {
        Client cl = cibleFermeture->servirClient();
        // Chercher la caisse ouverte la moins chargée (hors celle qu'on ferme)
        Caisse* meilleure = nullptr;
        for (auto& c : caisses) {
            if (c.getNumero() == numero) continue;
            if (!c.estOuverte()) continue;
            if (c.isExpress()) continue; // on ne veut pas envoyer de clients à la caisse express
            if (!meilleure || c.getTailleFile() < meilleure->getTailleFile())
                meilleure = &c;
        }
        if (!meilleure)
            throw std::runtime_error("Aucune caisse disponible pour la redistribution !");
        meilleure->ajouterClient(cl);
    }

    // Maintenant vide → fermeture propre
    cibleFermeture->fermer();
}

void Supermarche::ajouterClient(const std::string& nom, int nbArticles) {
    if (nom.empty()) {
        throw std::runtime_error("Le nom du client ne peut pas etre vide !");
    }
    if (nbArticles <= 0) {
        throw std::runtime_error("Le nombre d'articles doit etre positif !");
    }

    Caisse& caisseChoisie = choisirCaisse(nbArticles);
    Client client(compteurId++, nom, nbArticles);
    caisseChoisie.ajouterClient(client);
}

void Supermarche::servirClient(int numeroCaisse) {
    for (auto& caisse : caisses) {
        if (caisse.getNumero() == numeroCaisse) {
            Client cl = caisse.servirClient(); // ← récupère le client avant de le perdre
            totalServis++;

            // Enregistrement dans l'historique
            EntreeHistorique entry;
            entry.nomClient    = cl.getNom();
            entry.nbArticles   = cl.getNbArticles();
            entry.numeroCaisse = numeroCaisse;
            entry.heureService = std::time(nullptr);
            historique.push_back(entry);

            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

std::vector<Caisse>& Supermarche::getCaisses() {
    return caisses;
}

std::vector<EntreeHistorique> Supermarche::getHistorique() const {
    return historique;
}

int Supermarche::getTotalClientsServis() const {
    return totalServis;
}

Caisse& Supermarche::choisirCaisse(int nbArticles) {
    if (caisses.empty()) {
        throw std::runtime_error("Aucune caisse disponible !");
    }

    if (nbArticles <= 10) {
        for (auto& caisse : caisses) {
            if (caisse.isExpress() && caisse.estOuverte()) {
                return caisse;
            }
        }
        throw std::runtime_error("Caisse express introuvable !");
    }

    Caisse* meilleure = nullptr;

    for (auto& caisse : caisses) {
        if (!caisse.isExpress() && caisse.estOuverte()) {
            if (meilleure == nullptr || caisse.getTailleFile() < meilleure->getTailleFile()) {
                meilleure = &caisse;
            }
        }
    }

    if (meilleure == nullptr) {
        throw std::runtime_error("Aucune caisse ordinaire ouverte disponible !");
    }

    return *meilleure;
}