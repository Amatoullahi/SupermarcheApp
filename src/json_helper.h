#pragma once
#include "../lib/json.hpp"
#include "caisse.h"
#include "supermarche.h"

using json = nlohmann::json;

// Convertir une Caisse en JSON
inline json caisseToJson(const Caisse& c) {
    return {
        {"numero",       c.getNumero()      },
        {"ouverte",      c.estOuverte()     },
        {"express",      c.isExpress()      },
        {"nbClients",    c.getTailleFile()  },
        {"tempsAttente", c.getTempsAttente()}
    };
}

// Convertir l'état complet du Supermarche en JSON
inline json supermarcheToJson(Supermarche& sm) {
    json caisses = json::array();
    for (auto& c : sm.getCaisses())
        caisses.push_back(caisseToJson(c));
    return {
        {"caisses",       caisses                    },
        {"totalServis",   sm.getTotalClientsServis()  }
    };
}
inline json historiqueToJson(const std::vector<EntreeHistorique>& hist) {
    json arr = json::array();
    for (const auto& e : hist) {
        char buf[20];
        std::strftime(buf, sizeof(buf), "%H:%M:%S",
                      std::localtime(&e.heureService));
        arr.push_back({
            {"nom",      e.nomClient},
            {"articles", e.nbArticles},
            {"caisse",   e.numeroCaisse},
            {"heure",    std::string(buf)}
        });
    }
    return arr;
}