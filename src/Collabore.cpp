#include "../include/Collabore.hpp"
#include "../include/Propose.hpp"
Collabore::Collabore(sqlite3* database) : db(database) {}

Collabore::~Collabore() {
    // Gestion de la fermeture de la connexion à la base de données si nécessaire
}

void Collabore::insererCollaboration(int idCave, int idFournisseur, int idVin, int quantite, double prixBase, int reduction) {
    sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    // Vérification que le fournisseur possède le vin
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

    // Vérification si la cave possède déjà le vin
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
    int currentQuantity = 0;
    if (rc == SQLITE_ROW) {
        existingWine = true;
        currentQuantity = sqlite3_column_int(checkStatement, 0);
    }
    sqlite3_finalize(checkStatement);

    if (existingWine) {
        // Si la cave possède déjà le vin, incrémenter la quantité dans Gere
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
        // Si la cave ne possède pas encore le vin, l'ajouter à Propose et à Gere et à collabore
        Propose propose(db);
        propose.insererProposition(idCave, idVin, prixBase);
        
        // Inserer dans collabore 
         std::string insertCollaboreQuery = "INSERT INTO Collabore (idCave, idFournisseur, idVin, quantite, reduction) VALUES (?, ?, ?, ?, ?)";
        sqlite3_stmt* insertCollaboreStatement;
        rc = sqlite3_prepare_v2(db, insertCollaboreQuery.c_str(), -1, &insertCollaboreStatement, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
         }

        sqlite3_bind_int(insertCollaboreStatement, 1, idCave);
        sqlite3_bind_int(insertCollaboreStatement, 2, idFournisseur);
        sqlite3_bind_int(insertCollaboreStatement, 3, idVin);
        sqlite3_bind_int(insertCollaboreStatement, 4, quantite);
        sqlite3_bind_int(insertCollaboreStatement, 5, reduction);

        rc = sqlite3_step(insertCollaboreStatement);
        if (rc != SQLITE_DONE) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        // Insérer dans Gere
        std::string insertGereQuery = "INSERT INTO Gere (idCave, idVin, idFournisseur, quantite) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* insertGereStatement;
        rc = sqlite3_prepare_v2(db, insertGereQuery.c_str(), -1, &insertGereStatement, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_bind_int(insertGereStatement, 1, idCave);
        sqlite3_bind_int(insertGereStatement, 2, idVin);
        sqlite3_bind_int(insertGereStatement, 3, idFournisseur);
        sqlite3_bind_int(insertGereStatement, 4, quantite);

        rc = sqlite3_step(insertGereStatement);
        if (rc != SQLITE_DONE) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return;
        }

        sqlite3_finalize(insertGereStatement);
    }

    sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
}

