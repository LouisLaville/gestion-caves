#ifndef COLLABORE_HPP
#define COLLABORE_HPP

#include <sqlite3.h>
#include <iostream>
#include <string>

class Collabore {
private:
    sqlite3* db;

public:
    Collabore(sqlite3* database);
    ~Collabore();

    void insererCollaboration(int idCave, int idFournisseur, int idVin, int quantite, double prixBase,int reduction);

};

#endif 
