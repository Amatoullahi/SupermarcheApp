#pragma once
#include <queue>
#include <stdexcept>
#include "client.h"

class Caisse {
public:
    Caisse(int numero, bool estExpress = false);

    void ajouterClient(const Client& c);
    Client servirClient();       // lève std::runtime_error si file vide
    bool estVide() const;
    int getTailleFile() const;
    int getTempsAttente() const; // estimation : 5 sec par article
    bool estOuverte() const;
    bool isExpress() const;
    int getNumero() const;
    void ouvrir();
    void fermer();               // lève std::runtime_error si file non vide

private:
    int numero;
    bool ouvert;
    bool express;
    std::queue<Client> file;
};