#ifndef VIN_HPP
#define VIN_HPP
#include <sqlite3.h>
#include <string>
#include <vector>

class Vin {
    
    public:
        Vin(sqlite3* db);
        void ajouterVinGarde(const std::string& nom, const std::string& region, const std::string& type, int millesime, int idVin,int dureeAvantConso);
        void ajouterVinConso(const std::string& nom, const std::string& region, const std::string& type, int millesime, int idVin, int anneePrefConso);
        void supprimerVin(int idVin);
        void afficherVins();
        void afficherVin(int idVin);
        void afficherVinMeilleurPrix(const std::string& nomVin, int millesime);
        
    private: 
        sqlite3* db;
};
#endif
