#include "../include/DataBaseManager.hpp"
#include <iostream>
#include <fstream>


DataBaseManager::DataBaseManager() {
    
    int rc = sqlite3_open("ma_base_de_donnees.db3", &db);
    
    if (rc) {
        std::cerr << "Erreur lors de l'ouverture de la base de données: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    
    }
}

DataBaseManager::~DataBaseManager() {
    
    sqlite3_close(db);
}

sqlite3* DataBaseManager::getDb() const {
   
    return db;
}
int DataBaseManager::creerTablesSQLite() {
    
    sqlite3* db;
    int rc = sqlite3_open("ma_base_de_donnees.db3", &db);
    
    if (rc) {
    
        std::cerr << "Erreur lors de l'ouverture de la base de données: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    
    }

    const char* createCaveTable = "CREATE TABLE Cave (idCave INTEGER PRIMARY KEY, nom TEXT, adresse TEXT);";
    rc = sqlite3_exec(db, createCaveTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table Cave" << std::endl;
    }

    const char* createVinTable = "CREATE TABLE Vin (idVin INTEGER PRIMARY KEY, region TEXT, cru TEXT, nom TEXT, millesime INTEGER, type TEXT);";
    rc = sqlite3_exec(db, createVinTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table Vin" << std::endl;
    }

    const char* createFournisseurTable = "CREATE TABLE Fournisseur (idFournisseur INTEGER PRIMARY KEY, nom TEXT, adresse TEXT);";
    rc = sqlite3_exec(db, createFournisseurTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table Fournisseur" << std::endl;
    }

    const char* createFournitTable = "CREATE TABLE Fournit (idFournisseur INTEGER NOT NULL, idVin INTEGER NOT NULL, prixBase DECIMAL(10,2), reductions TEXT, PRIMARY KEY (idFournisseur, idVin), FOREIGN KEY (idFournisseur) REFERENCES Fournisseur (idFournisseur), FOREIGN KEY (idVin) REFERENCES Vin (idVin));";
    rc = sqlite3_exec(db, createFournitTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table Fournit" << std::endl;
    }

    const char* createCollaboreTable = "CREATE TABLE Collablre (idCave INTEGER NOT NULL, idFournisseur INTEGER NOT NULL, PRIMARY KEY (idCave, idFournisseur), FOREIGN KEY (idCave) REFERENCES Cave (idCave), FOREIGN KEY (idFournisseur) REFERENCES Fournisseur (idFournisseur));";
    rc = sqlite3_exec(db, createCollaboreTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table CaveFournisseur" << std::endl;
    }

    const char* createProposeTable = "CREATE TABLE Propose (idCave INTEGER NOT NULL, idVin INTEGER NOT NULL, prixBase DECIMAL(10,2), marge DECIMAL(5,2), stock INTEGER, PRIMARY KEY (idCave, idVin), FOREIGN KEY (idCave) REFERENCES Cave (idCave), FOREIGN KEY (idVin) REFERENCES Vin (idVin));";
    rc = sqlite3_exec(db, createProposeTable, nullptr, nullptr, nullptr);
    if (rc) {
        std::cerr << "Erreur lors de la création de la table Propose" << std::endl;
    }

    sqlite3_close(db);
    return 0;
}
    


int DataBaseManager::sauvegarderBaseDeDonnees(const std::string& nomFichierSource, const std::string& nomFichierDestination) {
    
    std::ifstream source(nomFichierSource, std::ios::binary);
    std::ofstream destination(nomFichierDestination, std::ios::binary);

    destination << source.rdbuf();

    source.close();
    destination.close();

    return 0;

}

int DataBaseManager::chargerBaseDeDonnees(const std::string& nomFichierSource, const std::string& nomFichierDestination) {

    std::ifstream source(nomFichierSource, std::ios::binary);
    std::ofstream destination(nomFichierDestination, std::ios::binary);

    destination << source.rdbuf();

    source.close();
    destination.close();

    return 0;

}
