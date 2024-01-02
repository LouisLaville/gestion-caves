#ifndef GERE_HPP
#define GERE_HPP

#include <sqlite3.h>
#include <iostream>

class Gere {
private:
    sqlite3* db;

public:
    Gere(sqlite3* database);

    void mettreAJourMarge(int idCave, int idVin, int idFournisseur);
};

#endif 
