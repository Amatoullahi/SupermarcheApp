#include <iostream>
#include "client.h"
#include "caisse.h"

int main() {
    // Test 1 : créer 3 clients et afficher toString
    std::cout << "=== Test 1 : toString ===" << std::endl;
    Client c1(1, "Ali", 5);
    Client c2(2, "Fatou", 12);
    Client c3(3, "Moussa", 8);
    std::cout << c1.toString() << std::endl;
    std::cout << c2.toString() << std::endl;
    std::cout << c3.toString() << std::endl;

    // Test 2 : ajouter 5 clients, en servir 2 → getTailleFile = 3
    std::cout << "\n=== Test 2 : file d'attente ===" << std::endl;
    Caisse caisse1(1);
    for (int i = 1; i <= 5; i++)
        caisse1.ajouterClient(Client(i, "Client" + std::to_string(i), 3));
    caisse1.servirClient();
    caisse1.servirClient();
    std::cout << "Taille file (attendu 3) : " << caisse1.getTailleFile() << std::endl;

    // Test 3 : fermer une caisse non vide → exception
    std::cout << "\n=== Test 3 : fermer caisse non vide ===" << std::endl;
    try {
        caisse1.fermer();
    } catch (const std::exception& e) {
        std::cout << "Exception capturée (OK) : " << e.what() << std::endl;
    }

    return 0;
}