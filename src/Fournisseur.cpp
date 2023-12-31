#include "../include/Fournisseur.hpp"
#include <iostream>
#include <fstream>

Fournisseur::Fournisseur(sqlite3* db) : db (db) {
    
}

void Fournisseur::ajouterFournisseur(const std::string& nom, const std::string& adresse, int idFournisseur) {
    
    std::string sql;
    sql = "INSERT INTO Fournisseur (idFournisseur, nom, adresse) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }

    sqlite3_bind_int(stmt, 1, idFournisseur);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, adresse.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
    }
    sqlite3_finalize(stmt);
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