#ifndef PROPOSE_HPP
#define PROPOSE_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>

class Propose {
private:
    sqlite3* db;

public:
    Propose(sqlite3* database);

    void insererProposition(int idCave, int idVin, double prixBase);
    void supprimerProposition(int idCave, int idVin);
    void afficherPropositions();
    void afficherPropositionVin(int idVin);
    void afficherPropositionCave(int idCave);
    void afficherProposition(int idCave, int idVin);

};

#endif // PROPOSE_HPP
