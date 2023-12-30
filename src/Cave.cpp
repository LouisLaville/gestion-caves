#include "../include/Cave.hpp"
#include "../include/DataBaseManager.hpp"
#include <iostream>
#include <fstream>

Cave::Cave(sqlite3* db) : db (db){}
void Cave::ajouterCave(const std::string& nom, const std::string& adresse, int idCave) {
    std::string sql;
    if (idCave == -1) {
        sql = "INSERT INTO Cave (nom, adresse) VALUES (?, ?)";
    } else {
        sql = "INSERT INTO Cave (idCave, nom, adresse) VALUES (?, ?, ?)";
    }

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        
    }

    if (idCave != -1) {
        sqlite3_bind_int(stmt, 1, idCave);
        sqlite3_bind_text(stmt, 2, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, adresse.c_str(), -1, SQLITE_STATIC);
    } else {
        sqlite3_bind_text(stmt, 1, nom.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, adresse.c_str(), -1, SQLITE_STATIC);
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
       
    }

    sqlite3_finalize(stmt);
}


