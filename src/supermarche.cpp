#include "supermarche.h"
#include <stdexcept>

Supermarche::Supermarche() : compteurId(1), totalServis(0) {
}

void Supermarche::initialiser(int nbCaisses) {
    if (nbCaisses <= 0)
        throw std::runtime_error("Le nombre de caisses doit etre positif !");
    caisses.clear();
    for (int i = 1; i <= nbCaisses; ++i)
        caisses.push_back(Caisse(i, i == 1));
}

void Supermarche::ouvrirCaisse(int numero) {
    for (auto& c : caisses) {
        if (c.getNumero() == numero) { c.ouvrir(); return; }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::fermerCaisse(int numero) {
    for (auto& c : caisses) {
        if (c.getNumero() == numero) {
            if (c.isExpress())
                throw std::runtime_error("La caisse express ne peut pas etre fermee !");
            c.fermer(); return;
        }
    }
    throw std::runtime_error("Caisse introuvable !");
}

void Supermarche::fermerCaisseAvecRepartition(int numero) {
    Caisse* cible = nullptr;
    for (auto& c : caisses)
        if (c.getNumero() == numero) { cible = &c; break; }
    if (!cible)
        throw std::runtime_error("Caisse introuvable !");
    if (cible->isExpress())
        throw std::runtime_error("La caisse express ne peut pas etre fermee.");

    while (!cible->estVide()) {
        Client cl = cible->servirClient();
        Caisse* meilleure = nullptr;
        for (auto& c : caisses) {
            if (c.getNumero() == numero) continue;
            if (!c.estOuverte() || c.isExpress()) continue;
            if (!meilleure || c.getTailleFile() < meilleure->getTailleFile())
                meilleure = &c;
        }
        if (!meilleure)
            throw std::runtime_error("Aucune caisse disponible pour la redistribution !");
        meilleure->ajouterClient(cl);
    }
    cible->fermer();
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
            Client cl = c.servirClient();
            totalServis++;
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
    if (caisses.empty())
        throw std::runtime_error("Aucune caisse disponible !");
    if (nbArticles <= 10) {
        for (auto& c : caisses)
            if (c.isExpress() && c.estOuverte()) return c;
        throw std::runtime_error("Caisse express introuvable !");
    }
    Caisse* meilleure = nullptr;
    for (auto& c : caisses)
        if (!c.isExpress() && c.estOuverte())
            if (!meilleure || c.getTailleFile() < meilleure->getTailleFile())
                meilleure = &c;
    if (!meilleure)
        throw std::runtime_error("Aucune caisse ordinaire ouverte disponible !");
    return *meilleure;
}