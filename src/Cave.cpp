#include "../include/Cave.hpp"
#include <iostream>
#include <fstream>

Cave::Cave(sqlite3* db) : db (db){}

void Cave::ajouterCave(const std::string& nom, const std::string& adresse, int idCave) {
    
    std::string sql;
    sql = "INSERT INTO Cave (idCave, nom, adresse) VALUES (?, ?, ?)";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idCave);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, adresse.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
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

