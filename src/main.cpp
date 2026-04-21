#include <iostream>
#include "supermarche.h"
#include "serveur.h"

int main() {
    Supermarche sm;
    sm.initialiser(3); // 3 caisses ordinaires + 1 express

    Serveur srv;
    srv.demarrer(sm);

    return 0;
}