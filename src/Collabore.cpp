#include "../include/Collabore.hpp"

Collabore::Collabore(sqlite3* database) : db(database) {}

Collabore::~Collabore() {
    // Gestion de la fermeture de la connexion à la base de données si nécessaire
}

void Collabore::insererCollaboration(int idCave, int idFournisseur, int idVin, int quantite, double prixBase) {
    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    std::string checkSupplierQuery = "SELECT idFournisseur FROM Fournit WHERE idFournisseur = ? AND idVin = ?";
    sqlite3_stmt* checkSupplierStatement;
    int rc = sqlite3_prepare_v2(db, checkSupplierQuery.c_str(), -1, &checkSupplierStatement, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_int(checkSupplierStatement, 1, idFournisseur);
    sqlite3_bind_int(checkSupplierStatement, 2, idVin);

    rc = sqlite3_step(checkSupplierStatement);
    bool supplierHasWine = false;
    if (rc == SQLITE_ROW) {
        supplierHasWine = true;
    }
    sqlite3_finalize(checkSupplierStatement);

    if (!supplierHasWine) {
        std::cerr << "Le fournisseur ne possède pas ce vin." << std::endl;
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    std::string checkQuery = "SELECT quantite FROM Gere WHERE idCave = ? AND idVin = ?";
    sqlite3_stmt* checkStatement;
    rc = sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &checkStatement, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        return;
    }

    sqlite3_bind_int(checkStatement, 1, idCave);
    sqlite3_bind_int(checkStatement, 2, idVin);

    rc = sqlite3_step(checkStatement);
    bool existingWine = false;
    if (rc == SQLITE_ROW) {
        existingWine = true;
    }
    sqlite3_finalize(checkStatement);

    if (existingWine) {
        std::string updateQuery = "UPDATE Gere SET quantite = quantite + ? WHERE idCave = ? AND idVin = ?";
        sqlite3_stmt* updateStatement;
        rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &updateStatement, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_bind_int(updateStatement, 1, quantite);
        sqlite3_bind_int(updateStatement, 2, idCave);
        sqlite3_bind_int(updateStatement, 3, idVin);

        rc = sqlite3_step(updateStatement);
        if (rc != SQLITE_DONE) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_finalize(updateStatement);
    } else {
        Propose proposeInstance(db);
        proposeInstance.insererProposition(idCave, idVin, prixBase);

        std::string insertQuery = "INSERT INTO Gere (idCave, idVin, quantite) VALUES (?, ?, ?)";
        sqlite3_stmt* insertStatement;
        rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStatement, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_bind_int(insertStatement, 1, idCave);
        sqlite3_bind_int(insertStatement, 2, idVin);
        sqlite3_bind_int(insertStatement, 3, quantite);

        rc = sqlite3_step(insertStatement);
        if (rc != SQLITE_DONE) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_finalize(insertStatement);
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
}
