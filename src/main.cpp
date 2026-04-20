#include <iostream>
#include "client.h"
#include "caisse.h"
#include "supermarche.h"

int main() {
    // Test 1 : toString
    std::cout << "=== Test 1 : toString ===" << std::endl;
    Client c1(1, "Ali", 5);
    Client c2(2, "Fatou", 12);
    Client c3(3, "Moussa", 8);
    std::cout << c1.toString() << std::endl;
    std::cout << c2.toString() << std::endl;
    std::cout << c3.toString() << std::endl;

    // Test 2 : file d'attente
    std::cout << "\n=== Test 2 : file d'attente ===" << std::endl;
    Caisse caisse1(1);
    for (int i = 1; i <= 5; i++)
        caisse1.ajouterClient(Client(i, "Client" + std::to_string(i), 3));
    caisse1.servirClient();
    caisse1.servirClient();
    std::cout << "Taille file (attendu 3) : " << caisse1.getTailleFile() << std::endl;

    // Test 3 : fermer caisse non vide
    std::cout << "\n=== Test 3 : fermer caisse non vide ===" << std::endl;
    try {
        caisse1.fermer();
    } catch (const std::exception& e) {
        std::cout << "Exception OK : " << e.what() << std::endl;
    }

    // Test 4 : client <= 10 articles → caisse express
    std::cout << "\n=== Test 4 : orientation caisse express ===" << std::endl;
    Supermarche sm;
    sm.initialiser(3);
    sm.ajouterClient("Cheikh", 5);
    std::cout << "Taille caisse express (attendu 1) : "
              << sm.getCaisses()[0].getTailleFile() << std::endl;

    // Test 5 : client > 10 articles → caisse ordinaire
    std::cout << "\n=== Test 5 : orientation caisse ordinaire ===" << std::endl;
    sm.ajouterClient("Mariama", 15);
    int totalOrdinaires = 0;
    for (auto& c : sm.getCaisses())
        if (!c.isExpress()) totalOrdinaires += c.getTailleFile();
    std::cout << "Total caisses ordinaires (attendu 1) : "
              << totalOrdinaires << std::endl;

    std::cout << "\n=== Phase 1 complete ! ===" << std::endl;
    return 0;
}