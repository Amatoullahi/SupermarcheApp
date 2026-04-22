#include "caisse.h"

Caisse::Caisse(int numero, bool estExpress)
    : numero(numero), ouvert(true), express(estExpress) {}

void Caisse::ajouterClient(const Client& c) {
    file.push(c);
}

Client Caisse::servirClient() {
    if (file.empty())
        throw std::runtime_error("La file est vide !");
    Client c = file.front();
    file.pop();
    return c;
}

bool Caisse::estVide() const {
    return file.empty();
}

int Caisse::getTailleFile() const {
    return (int)file.size();
}

int Caisse::getTempsAttente() const {
    // Parcourir la file pour sommer les articles × 5 secondes
    std::queue<Client> copie = file;
    int total = 0;
    while (!copie.empty()) {
        total += copie.front().getNbArticles() * 5;
        copie.pop();
    }
    return total;
}

bool Caisse::estOuverte() const {
    return ouvert;
}

bool Caisse::isExpress() const {
    return express;
}

int Caisse::getNumero() const {
    return numero;
}

void Caisse::ouvrir() {
    ouvert = true;
}

void Caisse::fermer() {
    if (!file.empty())
        throw std::runtime_error("Impossible de fermer : file non vide !");
    ouvert = false;
}