#pragma once
#include <vector>
#include "caisse.h"
#include <ctime>

struct EntreeHistorique {
    std::string nomClient;
    int         nbArticles;
    int         numeroCaisse;
    std::time_t heureService;
};

class Supermarche {
public:
    Supermarche();
    void initialiser(int nbCaisses); // crée les caisses + 1 caisse express fixe
    void ouvrirCaisse(int numero);
    void fermerCaisse(int numero);
    void ajouterClient(const std::string& nom, int nbArticles);
    void servirClient(int numeroCaisse);
    std::vector<Caisse>& getCaisses();
    std::vector<EntreeHistorique> getHistorique() const;
    int getTotalClientsServis() const;

private:
    std::vector<Caisse> caisses;
    int compteurId;
    int totalServis;
    Caisse& choisirCaisse(int nbArticles); // logique d'orientation
    std::vector<EntreeHistorique> historique;
};