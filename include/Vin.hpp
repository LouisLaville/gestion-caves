#ifndef VIN_HPP
#define VIN_HPP
#include <sqlite3.h>
#include <string>
#include <vector>

struct VinData {
    int idVin;
    std::string nom;
    std::string region;
    std::string type;
    int millesime;
};

class Vin {

    public:
        Vin(sqlite3* db);
        void ajouterVin(const std::string& nom, const std::string& region, const std::string& type, int millesime, int idVin);
        void supprimerVin(int idVin);
        void afficherVins();
        void afficherVin(int idVin);
        
    private: 
        sqlite3* db;
};
#endif
