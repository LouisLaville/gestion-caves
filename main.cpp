#include "include/DataBaseManager.hpp"

int main() {
    DataBaseManager dbManager;

    // Appeler les fonctions de gestion de la base de données depuis dbManager
    dbManager.creerTablesSQLite();
    dbManager.sauvegarderBaseDeDonnees("ma_base_de_donnees.db3", "sauvegarde_ma_base_de_donnees.db3");
    dbManager.chargerBaseDeDonnees("sauvegarde_ma_base_de_donnees.db3", "ma_base_de_donnees.db3");

    return 0;
}
