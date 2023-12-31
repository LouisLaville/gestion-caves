#include "../include/Fournit.hpp"

Fournit::Fournit(sqlite3* database) : db(database) {}


void Fournit::insererFournit(int idFournisseur, int idVin, double prixBase, const std::string& reductions) {
    
    // Vérification de l'existence de l'ID du fournisseur
    std::string queryFournisseur = "SELECT COUNT(*) FROM Fournisseur WHERE idFournisseur = ?";
    sqlite3_stmt* statementFournisseur;
    int rcFournisseur = sqlite3_prepare_v2(db, queryFournisseur.c_str(), -1, &statementFournisseur, nullptr);
    if (rcFournisseur != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'ID du fournisseur : " << sqlite3_errmsg(db) << std::endl;
        return; 
    }

    sqlite3_bind_int(statementFournisseur, 1, idFournisseur);
    rcFournisseur = sqlite3_step(statementFournisseur);
    if (rcFournisseur != SQLITE_ROW || sqlite3_column_int(statementFournisseur, 0) == 0) {
        std::cerr << "ID du fournisseur inexistant dans la base de données." << std::endl;
        sqlite3_finalize(statementFournisseur);
        return; 
    }
    sqlite3_finalize(statementFournisseur);

    // Vérification de l'existence de l'ID du vin
    std::string queryVin = "SELECT COUNT(*) FROM Vin WHERE idVin = ?";
    sqlite3_stmt* statementVin;
    int rcVin = sqlite3_prepare_v2(db, queryVin.c_str(), -1, &statementVin, nullptr);
    if (rcVin != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'ID du vin : " << sqlite3_errmsg(db) << std::endl;
        return; 
    }

    sqlite3_bind_int(statementVin, 1, idVin);
    rcVin = sqlite3_step(statementVin);
    if (rcVin != SQLITE_ROW || sqlite3_column_int(statementVin, 0) == 0) {
        std::cerr << "ID du vin inexistant dans la base de données." << std::endl;
        sqlite3_finalize(statementVin);
        return; 
    }
    sqlite3_finalize(statementVin);

    // Vérification de doublons
    std::string queryDoublon = "SELECT COUNT(*) FROM Fournit WHERE idFournisseur = ? AND idVin = ?";
    sqlite3_stmt* statementDoublon;
    int rcDoublon = sqlite3_prepare_v2(db, queryDoublon.c_str(), -1, &statementDoublon, nullptr);
    if (rcDoublon != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de doublons : " << sqlite3_errmsg(db) << std::endl;
        return; 
    }

    sqlite3_bind_int(statementDoublon, 1, idFournisseur);
    sqlite3_bind_int(statementDoublon, 2, idVin);
    rcDoublon = sqlite3_step(statementDoublon);
    if (rcDoublon == SQLITE_ROW && sqlite3_column_int(statementDoublon, 0) > 0) {
        std::cerr << "Ce fournisseur possède déjà ce vin." << std::endl;
        sqlite3_finalize(statementDoublon);
        return; 
    }
    sqlite3_finalize(statementDoublon);
     std::string insertQuery = "INSERT INTO Fournit (idFournisseur, idVin, prixBase, reductions) VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête INSERT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idFournisseur);
    sqlite3_bind_int(statement, 2, idVin);
    sqlite3_bind_double(statement, 3, prixBase);
 

    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur lors de l'insertion dans la table Fournit : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(statement);
        return; 
    }

    std::cout << "Insertion dans la table Fournit réussie !" << std::endl;

    sqlite3_finalize(statement);
}

void supprimerFournit(sqlite3* db, int idFournisseur, int idVin) {
    std::string sql;
    sql = "DELETE FROM Fournit WHERE idFournisseur = ? AND idVin = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête DELETE : " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, idFournisseur);
    sqlite3_bind_int(stmt, 2, idVin);

    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur lors de la suppression dans la table Fournit : " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return; 
    }

    std::cout << "Suppression dans la table Fournit réussie !" << std::endl;

    sqlite3_finalize(stmt);
}

void Fournit::afficherFournits() {
    std::string sql;
    sql = "SELECT * FROM Fournit";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idFournisseur: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(stmt, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Fournit::afficherFournit(int idFournisseur, int idVin) {
    std::string sql;
    sql = "SELECT * FROM Fournit WHERE idFournisseur = ? AND idVin = ?";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, idFournisseur);
    sqlite3_bind_int(stmt, 2, idVin);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << "idFournisseur: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(stmt, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(stmt, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}