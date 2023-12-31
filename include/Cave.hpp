#ifndef CAVE_HPP
#define CAVE_HPP
#include <sqlite3.h>
#include <string>
#include <vector>

struct CaveData {
    int idCave;
    std::string nom;
    std::string adresse;
};

class Cave {

    public:
        Cave(sqlite3* db);  
        void ajouterCave(const std::string& nom, const std::string& adresse, int idCave);
        void supprimerCave(int idCave);
        void afficherCaves();
        void afficherCave(int idCave);
        
    private: 
        sqlite3* db;

};

#endif