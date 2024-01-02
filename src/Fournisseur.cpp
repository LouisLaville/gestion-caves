#include "../include/Fournisseur.hpp"
#include <iostream>
#include <fstream>

Fournisseur::Fournisseur(sqlite3* db) : db (db) {
    
}

void Fournisseur::ajouterFournisseur(const std::string& nom, const std::string& adresse, int idFournisseur) {
    // Vérification de l'existence de l'ID du fournisseur
    std::string checkIdQuery = "SELECT COUNT(*) FROM Fournisseur WHERE idFournisseur = ?";
    sqlite3_stmt* idStmt;
    int idExistence = 0;
    int rc = sqlite3_prepare_v2(db, checkIdQuery.c_str(), -1, &idStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(idStmt, 1, idFournisseur);
        rc = sqlite3_step(idStmt);
        if (rc == SQLITE_ROW) {
            idExistence = sqlite3_column_int(idStmt, 0);
        }
    }
    sqlite3_finalize(idStmt);

    if (idExistence > 0) {
        // L'ID du fournisseur existe déjà, afficher un message d'erreur ou gérer cette situation
        std::cout << "Cet ID de fournisseur existe déjà." << std::endl;
        return;
    }

    // Vérification de l'existence du fournisseur par nom et adresse
    std::string checkFournisseurQuery = "SELECT COUNT(*) FROM Fournisseur WHERE nom = ? AND adresse = ?";
    sqlite3_stmt* fournisseurStmt;
    int fournisseurExistence = 0;
    rc = sqlite3_prepare_v2(db, checkFournisseurQuery.c_str(), -1, &fournisseurStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(fournisseurStmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(fournisseurStmt, 2, adresse.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(fournisseurStmt);
        if (rc == SQLITE_ROW) {
            fournisseurExistence = sqlite3_column_int(fournisseurStmt, 0);
        }
    }
    sqlite3_finalize(fournisseurStmt);

    if (fournisseurExistence > 0) {
        // Le fournisseur existe déjà avec cette combinaison de nom et adresse, afficher un message d'erreur ou gérer cette situation
        std::cout << "Ce fournisseur existe déjà." << std::endl;
        return;
    }

    // Si l'ID et la combinaison nom/adresse n'existent pas, insérer le fournisseur
    std::string insertQuery = "INSERT INTO Fournisseur (idFournisseur, nom, adresse) VALUES (?, ?, ?)";
    sqlite3_stmt* insertStmt;
    rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, nullptr);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(insertStmt, 1, idFournisseur);
        sqlite3_bind_text(insertStmt, 2, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insertStmt, 3, adresse.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(insertStmt);
        if (rc != SQLITE_DONE) {
            // Gestion de l'échec de l'insertion, afficher un message d'erreur ou gérer autrement
            std::cout << "Échec de l'insertion du fournisseur." << std::endl;
        }
    }
    sqlite3_finalize(insertStmt);
}


void Fournisseur::supprimerFournisseur(int idFournisseur) {
    std::string sql;
    sql = "DELETE FROM Fournisseur WHERE idFournisseur = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idFournisseur);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}

void Fournisseur::afficherFournisseurs() {
    std::string sql;
    sql = "SELECT * FROM Fournisseur";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idFournisseur: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "adresse: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}

void Fournisseur::afficherFournisseur(int idFournisseur) {
    std::string sql;
    sql = "SELECT * FROM Fournisseur WHERE idFournisseur = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idFournisseur);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idFournisseur: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "nom: " << sqlite3_column_text(stmt, 1) << std::endl;
        std::cout << "adresse: " << sqlite3_column_text(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}