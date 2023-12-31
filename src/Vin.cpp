#include "../include/Vin.hpp"
#include <iostream>
#include <fstream>

Vin::Vin(sqlite3* db) : db (db) {}

void Vin::ajouterVin(const std::string& nom, const std::string& region, const std::string& type, int millesime, int idVin) {
    std::string sql;
    sql = "INSERT INTO Vin (idVin, nom, region, type, millesime) VALUES (?, ?, ?, ?, ?)";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        
    }
    
    sqlite3_bind_int(stmt, 1, idVin);
    sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, region.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, millesime);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
       
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