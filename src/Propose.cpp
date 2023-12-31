#include "../include/Propose.hpp"
#include <iostream>
#include <fstream>

Propose::Propose(sqlite3* db) : db (db) {}

void Propose::insererProposition(int idCave, int idVin, double prixBase) {
    // Vérification de l'existence du vin
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
        std::cerr << "ID du vin inexistant dans la table Vin." << std::endl;
        sqlite3_finalize(statementVin);
        return;
    }
    sqlite3_finalize(statementVin);

    // Vérification de l'existence de la cave
    std::string queryCave = "SELECT COUNT(*) FROM Cave WHERE idCave = ?";
    sqlite3_stmt* statementCave;
    int rcCave = sqlite3_prepare_v2(db, queryCave.c_str(), -1, &statementCave, nullptr);
    if (rcCave != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'ID de la cave : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statementCave, 1, idCave);
    rcCave = sqlite3_step(statementCave);
    if (rcCave != SQLITE_ROW || sqlite3_column_int(statementCave, 0) == 0) {
        std::cerr << "ID de la cave inexistant dans la table Cave." << std::endl;
        sqlite3_finalize(statementCave);
        return;
    }
    sqlite3_finalize(statementCave);

    // Vérification des doublons
    std::string queryDoublon = "SELECT COUNT(*) FROM Propose WHERE idCave = ? AND idVin = ?";
    sqlite3_stmt* statementDoublon;
    int rcDoublon = sqlite3_prepare_v2(db, queryDoublon.c_str(), -1, &statementDoublon, nullptr);
    if (rcDoublon != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de doublons : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statementDoublon, 1, idCave);
    sqlite3_bind_int(statementDoublon, 2, idVin);
    rcDoublon = sqlite3_step(statementDoublon);
    if (rcDoublon == SQLITE_ROW && sqlite3_column_int(statementDoublon, 0) > 0) {
        std::cerr << "Cette proposition existe déjà pour cette cave et ce vin." << std::endl;
        sqlite3_finalize(statementDoublon);
        return;
    }
    sqlite3_finalize(statementDoublon);

    std::string insertQuery = "INSERT INTO Propose (idCave, idVin, prixBase) VALUES (?, ?, ?);";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête INSERT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idCave);
    sqlite3_bind_int(statement, 2, idVin);
    sqlite3_bind_double(statement, 3, prixBase);

    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur lors de l'insertion dans la table Propose : " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(statement);
}

void Propose::supprimerProposition(int idCave, int idVin) {
    // Vérification de l'existence de la proposition
    std::string queryProposition = "SELECT COUNT(*) FROM Propose WHERE idCave = ? AND idVin = ?";
    sqlite3_stmt* statementProposition;
    int rcProposition = sqlite3_prepare_v2(db, queryProposition.c_str(), -1, &statementProposition, nullptr);
    if (rcProposition != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'existence de la proposition : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statementProposition, 1, idCave);
    sqlite3_bind_int(statementProposition, 2, idVin);
    rcProposition = sqlite3_step(statementProposition);
    if (rcProposition != SQLITE_ROW || sqlite3_column_int(statementProposition, 0) == 0) {
        std::cerr << "Cette proposition n'existe pas." << std::endl;
        sqlite3_finalize(statementProposition);
        return;
    }
    sqlite3_finalize(statementProposition);

    // Suppression de la proposition si la vérification est réussie
    std::string deleteQuery = "DELETE FROM Propose WHERE idCave = ? AND idVin = ?;";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, deleteQuery.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête DELETE : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idCave);
    sqlite3_bind_int(statement, 2, idVin);

    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur lors de la suppression dans la table Propose : " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(statement);
}

void Propose::afficherPropositions() {
    std::string query = "SELECT * FROM Propose;";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(statement, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(statement, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(statement, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(statement);
}

void Propose::afficherProposition(int idCave, int idVin) {
    // Vérification de l'existence de la proposition
    std::string queryProposition = "SELECT COUNT(*) FROM Propose WHERE idCave = ? AND idVin = ?";
    sqlite3_stmt* statementProposition;
    int rcProposition = sqlite3_prepare_v2(db, queryProposition.c_str(), -1, &statementProposition, nullptr);
    if (rcProposition != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'existence de la proposition : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statementProposition, 1, idCave);
    sqlite3_bind_int(statementProposition, 2, idVin);
    rcProposition = sqlite3_step(statementProposition);
    if (rcProposition != SQLITE_ROW || sqlite3_column_int(statementProposition, 0) == 0) {
        std::cerr << "Cette proposition n'existe pas." << std::endl;
        sqlite3_finalize(statementProposition);
        return;
    }
    sqlite3_finalize(statementProposition);

    // Affichage de la proposition si la vérification est réussie
    std::string query = "SELECT * FROM Propose WHERE idCave = ? AND idVin = ?;";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idCave);
    sqlite3_bind_int(statement, 2, idVin);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(statement, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(statement, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(statement, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(statement);
}

void Propose::afficherPropositionCave(int idCave) {
    // Vérification de l'existence de la cave
    std::string queryCave = "SELECT COUNT(*) FROM Cave WHERE idCave = ?";
    sqlite3_stmt* statementCave;
    int rcCave = sqlite3_prepare_v2(db, queryCave.c_str(), -1, &statementCave, nullptr);
    if (rcCave != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête de vérification de l'ID de la cave : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statementCave, 1, idCave);
    rcCave = sqlite3_step(statementCave);
    if (rcCave != SQLITE_ROW || sqlite3_column_int(statementCave, 0) == 0) {
        std::cerr << "ID de la cave inexistant dans la table Cave." << std::endl;
        sqlite3_finalize(statementCave);
        return;
    }
    sqlite3_finalize(statementCave);

    // Affichage des propositions si la vérification est réussie
    std::string query = "SELECT * FROM Propose WHERE idCave = ?;";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idCave);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(statement, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(statement, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(statement, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(statement);
}

void Propose::afficherPropositionVin(int idVin){
    // Vérification de l'existence du vin
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
        std::cerr << "ID du vin inexistant dans la table Vin." << std::endl;
        sqlite3_finalize(statementVin);
        return;
    }
    sqlite3_finalize(statementVin);

    // Affichage des propositions si la vérification est réussie
    std::string query = "SELECT * FROM Propose WHERE idVin = ?;";
    
    sqlite3_stmt* statement;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête SELECT : " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(statement, 1, idVin);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        std::cout << "idCave: " << sqlite3_column_int(statement, 0) << std::endl;
        std::cout << "idVin: " << sqlite3_column_int(statement, 1) << std::endl;
        std::cout << "prixBase: " << sqlite3_column_double(statement, 2) << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(statement);
}