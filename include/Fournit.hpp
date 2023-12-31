#ifndef FOURNIT_HPP
#define FOURNIT_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>

class Fournit {
private:
    sqlite3* db;

public:
    Fournit(sqlite3* database);

    void insererFournit(int idFournisseur, int idVin, double prixBase, const std::string& reductions);
    void supprimerFournit(int idFournisseur, int idVin);
    void afficherFournits();
    void afficherFournit(int idFournisseur, int idVin);

};

#endif 
