#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <sqlite3.h>
#include <string>

class DataBaseManager {
public:
    DataBaseManager();
    ~DataBaseManager();

    int creerTablesSQLite();
    int sauvegarderBaseDeDonnees(const std::string& nomFichierSource, const std::string& nomFichierDestination);
    int chargerBaseDeDonnees(const std::string& nomFichierSource, const std::string& nomFichierDestination);

private:
    sqlite3* db;
};

#endif 

