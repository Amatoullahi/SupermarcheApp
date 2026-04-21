#include "../lib/httplib.h"
#include "json_helper.h"
#include "serveur.h"
#include <iostream>

void Serveur::demarrer(Supermarche& sm) {
    httplib::Server srv;

    auto cors = [](httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    };

    srv.Get("/api/etat", [&](const httplib::Request&, httplib::Response& res) {
        json j = supermarcheToJson(sm);
        res.set_content(j.dump(), "application/json");
        cors(res);
    });

    srv.Get("/api/stats", [&](const httplib::Request&, httplib::Response& res) {
        json j = {{"totalServis", sm.getTotalClientsServis()}};
        res.set_content(j.dump(), "application/json");
        cors(res);
    });

    srv.Post("/api/client/ajouter", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.ajouterClient(body["nom"], body["nbArticles"]);
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
            cors(res);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
            cors(res);
        }
    });

    srv.Post("/api/caisse/ouvrir", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.ouvrirCaisse(body["numero"]);
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
            cors(res);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
            cors(res);
        }
    });

    srv.Post("/api/caisse/fermer", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.fermerCaisse(body["numero"]);
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
            cors(res);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
            cors(res);
        }
    });

    srv.Post("/api/caisse/servir", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json body = json::parse(req.body);
            sm.servirClient(body["numero"]);
            res.set_content(supermarcheToJson(sm).dump(), "application/json");
            cors(res);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(json{{"erreur", e.what()}}.dump(), "application/json");
            cors(res);
        }
    });

    srv.Options(".*", [&](const httplib::Request&, httplib::Response& res) {
        cors(res);
        res.status = 204;
    });

    if (!srv.set_mount_point("/", "./web")) {
        std::cerr << "ERREUR : dossier web/ introuvable !" << std::endl;
    }

    std::cout << "Serveur : http://localhost:8080" << std::endl;
    std::cout.flush();

    srv.listen("0.0.0.0", 8080);
}