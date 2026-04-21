#include "supermarche.h"
#include <stdexcept>

Supermarche::Supermarche() : compteurId(1), totalServis(0) {}

void Supermarche::initialiser(int nbCaisses) {
    caisses.clear();
    // Caisse express toujours en position 0, numéro 0
    caisses.push_back(Caisse(0, true));
    // Caisses ordinaires numérotées 1 à nbCaisses
    for (int i = 1; i <= nbCaisses; i++)
        caisses.push_back(Caisse(i, false));
}

Caisse& Supermarche::choisirCaisse(int nbArticles) {
    // Client express (≤ 10 articles) → toujours la caisse 0
    if (nbArticles <= 10)
        return caisses[0];

    // Sinon : caisse ordinaire ouverte avec le moins de clients
    Caisse* meilleure = nullptr;
    for (auto& c : caisses) {
        if (!c.isExpress() && c.estOuverte()) {
            if (meilleure == nullptr || c.getTailleFile() < meilleure->getTailleFile())
                meilleure = &c;
        }
    }
    if (meilleure == nullptr)
        throw std::runtime_error("Aucune caisse ordinaire ouverte !");
    return *meilleure;
}

void Supermarche::ajouterClient(const std::string& nom, int nbArticles) {
    if (nom.empty())
        throw std::runtime_error("Le nom du client ne peut pas etre vide !");
    if (nbArticles <= 0)
        throw std::runtime_error("Le nombre d'articles doit etre positif !");
    
    Caisse& c = choisirCaisse(nbArticles);
    c.ajouterClient(Client(compteurId++, nom, nbArticles));
}

void Supermarche::servirClient(int numeroCaisse) {
    for (auto& c : caisses) {
        if (c.getNumero() == numeroCaisse) {
            c.servirClient();
            totalServis++;
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::ouvrirCaisse(int numero) {
    for (auto& c : caisses) {
        if (c.getNumero() == numero) {
            c.ouvrir();
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::fermerCaisse(int numero) {
    for (auto& c : caisses) {
        if (c.getNumero() == numero) {
            c.fermer(); // lève exception si non vide
            return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

std::vector<Caisse>& Supermarche::getCaisses() {
    return caisses;
}

int Supermarche::getTotalClientsServis() const {
    return totalServis;
}