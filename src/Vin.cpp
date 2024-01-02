#include "../include/Vin.hpp"
#include <iostream>
#include <fstream>

Vin::Vin(sqlite3* db) : db (db) {}

void Vin::ajouterVinGarde(const std::string& nom, const std::string& region, const std::string& cru, int millesime, int idVin, int dureeAvantConso) {
    std::string sql;
    sql = "INSERT INTO Vin (idVin, nom, region, cru, millesime, type, dureeAvantConsommation) VALUES (?, ?, ?, ?, ?, 'garde', ?)";
    
    // Vérification de l'existence de l'ID du vin
    std::string checkIdQuery = "SELECT COUNT(*) FROM Vin WHERE idVin = ?";
    sqlite3_stmt* idStmt;
    int idExistence = 0;
    int rc = sqlite3_prepare_v2(db, checkIdQuery.c_str(), -1, &idStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(idStmt, 1, idVin);
        rc = sqlite3_step(idStmt);
        if (rc == SQLITE_ROW) {
            idExistence = sqlite3_column_int(idStmt, 0);
        }
    }
    sqlite3_finalize(idStmt);

    if (idExistence > 0) {
        // L'ID du vin existe déjà, gérer cette situation (ex: afficher un message d'erreur)
        std::cout << "Cet ID de vin existe déjà." << std::endl;
        return;
    }

    // Vérification de l'existence du vin par nom, type, millesime et region
    std::string checkVinQuery = "SELECT COUNT(*) FROM Vin WHERE nom = ? AND type = 'garde' AND millesime = ? AND region = ?";
    sqlite3_stmt* vinStmt;
    int vinExistence = 0;
    rc = sqlite3_prepare_v2(db, checkVinQuery.c_str(), -1, &vinStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(vinStmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(vinStmt, 2, millesime);
        sqlite3_bind_text(vinStmt, 3, region.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(vinStmt);
        if (rc == SQLITE_ROW) {
            vinExistence = sqlite3_column_int(vinStmt, 0);
        }
    }
    sqlite3_finalize(vinStmt);

    if (vinExistence > 0) {
        // Le vin existe déjà avec cette combinaison de nom, type, millesime et region, gérer cette situation (ex: afficher un message d'erreur)
        std::cout << "Ce vin de garde existe déjà." << std::endl;
        return;
    }

    // Si l'ID et la combinaison nom/type/millesime/region n'existent pas, insérer le vin de garde
    sqlite3_stmt* stmt;
    sql = "INSERT INTO Vin (idVin, nom, region, cru, millesime, type, dureeAvantConsommation) VALUES (?, ?, ?, ?, ?, 'garde', ?)";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        // Gestion de l'erreur de préparation de la requête
        return;
    }
    
    sqlite3_bind_int(stmt, 1, idVin);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, region.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, cru.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, millesime);
    sqlite3_bind_int(stmt, 6, dureeAvantConso);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        // Gestion de l'échec de l'exécution de la requête
    }

    sqlite3_finalize(stmt);
}
void Vin::ajouterVinConso(const std::string& nom, const std::string& region, const std::string& cru, int millesime, int idVin, int anneePrefConso) {
    std::string sql;
    sql = "INSERT INTO Vin (idVin, nom, region, cru, millesime, type, anneePreferableConsommation) VALUES (?, ?, ?, ?, ?, 'conso', ?)";
    
    // Vérification de l'existence de l'ID du vin
    std::string checkIdQuery = "SELECT COUNT(*) FROM Vin WHERE idVin = ?";
    sqlite3_stmt* idStmt;
    int idExistence = 0;
    int rc = sqlite3_prepare_v2(db, checkIdQuery.c_str(), -1, &idStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(idStmt, 1, idVin);
        rc = sqlite3_step(idStmt);
        if (rc == SQLITE_ROW) {
            idExistence = sqlite3_column_int(idStmt, 0);
        }
    }
    sqlite3_finalize(idStmt);

    if (idExistence > 0) {
        // L'ID du vin existe déjà, gérer cette situation (ex: afficher un message d'erreur)
        std::cout << "Cet ID de vin existe déjà." << std::endl;
        return;
    }

    // Vérification de l'existence du vin par nom, type, millesime et region
    std::string checkVinQuery = "SELECT COUNT(*) FROM Vin WHERE nom = ? AND type = 'conso' AND millesime = ? AND region = ?";
    sqlite3_stmt* vinStmt;
    int vinExistence = 0;
    rc = sqlite3_prepare_v2(db, checkVinQuery.c_str(), -1, &vinStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(vinStmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(vinStmt, 2, millesime);
        sqlite3_bind_text(vinStmt, 3, region.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(vinStmt);
        if (rc == SQLITE_ROW) {
            vinExistence = sqlite3_column_int(vinStmt, 0);
        }
    }
    sqlite3_finalize(vinStmt);

    if (vinExistence > 0) {
        // Le vin existe déjà avec cette combinaison de nom, type, millesime et region, gérer cette situation (ex: afficher un message d'erreur)
        std::cout << "Ce vin de consommation existe déjà." << std::endl;
        return;
    }

    // Si l'ID et la combinaison nom/type/millesime/region n'existent pas, insérer le vin de consommation
    sqlite3_stmt* stmt;
    sql = "INSERT INTO Vin (idVin, nom, region, cru, millesime, type, anneePreferableConsommation) VALUES (?, ?, ?, ?, ?, 'conso', ?)";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        // Gestion de l'erreur de préparation de la requête
        return;
    }
    
    sqlite3_bind_int(stmt, 1, idVin);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, region.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, cru.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, millesime);
    sqlite3_bind_int(stmt, 6, anneePrefConso);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        // Gestion de l'échec de l'exécution de la requête
    }

    sqlite3_finalize(stmt);
}

void Vin::supprimerVin(int idVin) {
    std::string sql;
    sql = "DELETE FROM Vin WHERE idVin = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idVin);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}

void Vin::afficherVins() {
    std::string sql;
    sql = "SELECT * FROM Vin";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idVin: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "region: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << "type: " << sqlite3_column_text(stmt, 3) << std::endl;
        std::cout << "millesime: " << sqlite3_column_int(stmt, 4) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Vin::afficherVin(int idVin) {
    std::string sql;
    sql = "SELECT * FROM Vin WHERE idVin = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idVin);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idVin: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "region: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << "type: " << sqlite3_column_text(stmt, 3) << std::endl;
        std::cout << "millesime: " << sqlite3_column_int(stmt, 4) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Vin::afficherVinMeilleurPrix(const std::string& nomVin, int millesime) {
    std::string query = "SELECT C.nom, MIN(P.prixBase) FROM Propose P "
                        "JOIN Vin V ON P.idVin = V.idVin "
                        "JOIN Cave C ON P.idCave = C.idCave "
                        "WHERE V.nom = ? AND V.millesime = ? "
                        "GROUP BY C.nom "
                        "ORDER BY MIN(P.prixBase) LIMIT 1";
    sqlite3_stmt* statement;
    
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        // Gestion de l'erreur de préparation de la requête
        std::cout << "Erreur lors de la préparation de la requête." << std::endl;
        return;
    }
    
    sqlite3_bind_text(statement, 1, nomVin.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 2, millesime);
    
    std::cout << "Meilleur prix du vin '" << nomVin << "' du millesime " << millesime << " dans la cave :" << std::endl;
    
    rc = sqlite3_step(statement);
    if (rc == SQLITE_ROW) {
        const unsigned char* nomCave = sqlite3_column_text(statement, 0);
        double prix = sqlite3_column_double(statement, 1);
        
        std::cout << "Cave : " << nomCave << ", Prix : " << prix << std::endl;
    }
    
    sqlite3_finalize(statement);
}
