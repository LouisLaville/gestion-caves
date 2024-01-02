#include "../include/Cave.hpp"
#include <iostream>
#include <fstream>

Cave::Cave(sqlite3* db) : db (db){}

void Cave::ajouterCave(const std::string& nom, const std::string& adresse, int idCave) {
    // Vérification de l'existence de l'ID de la cave
    std::string checkIdQuery = "SELECT COUNT(*) FROM Cave WHERE idCave = ?";
    sqlite3_stmt* idStmt;
    int idExistence = 0;
    int rc = sqlite3_prepare_v2(db, checkIdQuery.c_str(), -1, &idStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(idStmt, 1, idCave);
        rc = sqlite3_step(idStmt);
        if (rc == SQLITE_ROW) {
            idExistence = sqlite3_column_int(idStmt, 0);
        }
    }
    sqlite3_finalize(idStmt);

    if (idExistence > 0) {
        // L'ID de la cave existe déjà, afficher un message d'erreur
        // Ici tu peux lancer une exception, afficher un message d'erreur, ou gérer autrement cette situation
        std::cout << "Cet ID existe déjà." << std::endl;
        return;
    }

    // Vérification de l'existence de la cave par nom et adresse
    std::string checkCaveQuery = "SELECT COUNT(*) FROM Cave WHERE nom = ? AND adresse = ?";
    sqlite3_stmt* caveStmt;
    int caveExistence = 0;
    rc = sqlite3_prepare_v2(db, checkCaveQuery.c_str(), -1, &caveStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(caveStmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(caveStmt, 2, adresse.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(caveStmt);
        if (rc == SQLITE_ROW) {
            caveExistence = sqlite3_column_int(caveStmt, 0);
        }
    }
    sqlite3_finalize(caveStmt);

    if (caveExistence > 0) {
        // La cave existe déjà avec cette combinaison de nom et adresse, afficher un message d'erreur
        // Ici tu peux lancer une exception, afficher un message d'erreur, ou gérer autrement cette situation
        std::cout << "Cette cave existe déjà." << std::endl;
        return;
    }

    // Si l'ID et la combinaison nom/adresse n'existent pas, insérer la cave
    std::string insertQuery = "INSERT INTO Cave (idCave, nom, adresse) VALUES (?, ?, ?)";
    sqlite3_stmt* insertStmt;
    rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(insertStmt, 1, idCave);
        sqlite3_bind_text(insertStmt, 2, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insertStmt, 3, adresse.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(insertStmt);
        if (rc != SQLITE_DONE) {
            // Gestion de l'échec de l'insertion, afficher un message d'erreur ou gérer autrement
            std::cout << "Échec de l'insertion." << std::endl;
        }
    }
    sqlite3_finalize(insertStmt);
}

void Cave::supprimerCave(int idCave) {
    
    std::string sql;
    sql = "DELETE FROM Cave WHERE idCave = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idCave);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}

void Cave::afficherCaves() {
    
    std::string sql;
    sql = "SELECT * FROM Cave";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "adresse: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Cave::afficherCave(int idCave) {
    
    std::string sql;
    sql = "SELECT * FROM Cave WHERE idCave = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idCave);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "adresse: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Cave::afficherVinStock(int idCave) {
    std::string query = "SELECT V.nom, G.quantite, F.nom, P.prixBase, G.marge "
                        "FROM Gere G "
                        "JOIN Vin V ON G.idVin = V.idVin "
                        "JOIN Propose P ON G.idVin = P.idVin AND P.idCave = G.idCave "
                        "JOIN Fournisseur F ON G.idFournisseur = F.idFournisseur "
                        "WHERE G.idCave = ? "
                        "ORDER BY G.marge DESC";
    sqlite3_stmt* statement;

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cout << "Erreur lors de la préparation de la requête." << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idCave);

    std::cout << "Vins dans la cave (nom, stock, fournisseur, prix de base, marge) :" << std::endl;

    rc = sqlite3_step(statement);
    while (rc == SQLITE_ROW) {
        const unsigned char* nomVin = sqlite3_column_text(statement, 0);
        int stock = sqlite3_column_int(statement, 1);
        const unsigned char* nomFournisseur = sqlite3_column_text(statement, 2);
        double prixBase = sqlite3_column_double(statement, 3);
        double marge = sqlite3_column_double(statement, 4);

        std::cout << "Vin : " << nomVin << ", Stock : " << stock << ", Fournisseur : " << nomFournisseur << ", Prix de base : " << prixBase << ", Marge : " << marge << std::endl;

        rc = sqlite3_step(statement);
    }

    sqlite3_finalize(statement);
}

