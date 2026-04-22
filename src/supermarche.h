#pragma once
#include <vector>
#include "caisse.h"

class Supermarche {
public:
    Supermarche();
    void initialiser(int nbCaisses); // crée les caisses + 1 caisse express fixe
    void ouvrirCaisse(int numero);
    void fermerCaisse(int numero);
    void ajouterClient(const std::string& nom, int nbArticles);
    void servirClient(int numeroCaisse);
    std::vector<Caisse>& getCaisses();
    int getTotalClientsServis() const;

private:
    std::vector<Caisse> caisses;
    int compteurId;
    int totalServis;
    Caisse& choisirCaisse(int nbArticles); // logique d'orientation
};