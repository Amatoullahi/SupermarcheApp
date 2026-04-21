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