#include "../include/Gere.hpp"

Gere::Gere(sqlite3* database) : db(database) {}


void Gere::mettreAJourMarge(int idCave, int idVin, int idFournisseur) {
    // Récupérer les prix et les réductions nécessaires
    double prixBasePropose = 0.0;
    double prixBaseFournisseur = 0.0;
    double reductionCollabore = 0.0;

    // Récupérer PrixBase de Propose
    std::string queryPropose = "SELECT prixBase FROM Propose WHERE idCave = ? AND idVin = ?";
    sqlite3_stmt* stmtPropose;
    int rc = sqlite3_prepare_v2(db, queryPropose.c_str(), -1, &stmtPropose, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête Propose" << std::endl;
        return;
    }
    sqlite3_bind_int(stmtPropose, 1, idCave);
    sqlite3_bind_int(stmtPropose, 2, idVin);

    rc = sqlite3_step(stmtPropose);
    if (rc == SQLITE_ROW) {
        prixBasePropose = sqlite3_column_double(stmtPropose, 0);
    }
    sqlite3_finalize(stmtPropose);

    // Récupérer Réduction de Collabore
    std::string queryCollabore = "SELECT reduction FROM Collabore WHERE idFournisseur = ? AND idVin = ?";
    sqlite3_stmt* stmtCollabore;
    rc = sqlite3_prepare_v2(db, queryCollabore.c_str(), -1, &stmtCollabore, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête Collabore" << std::endl;
        return;
    }
    sqlite3_bind_int(stmtCollabore, 1, idFournisseur);
    sqlite3_bind_int(stmtCollabore, 2, idVin);

    rc = sqlite3_step(stmtCollabore);
    if (rc == SQLITE_ROW) {
        reductionCollabore = sqlite3_column_double(stmtCollabore, 0); // Récupération de la réduction
    }
    sqlite3_finalize(stmtCollabore);

    // Recuperer prix base fournisseur dans fournit 
    std::string queryFournit = "SELECT prixBase FROM Fournit WHERE idFournisseur = ? AND idVin = ?";
    sqlite3_stmt* stmtFournit;
    rc = sqlite3_prepare_v2(db, queryFournit.c_str(), -1, &stmtFournit, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête Fournit" << std::endl;
        return;
    }
    sqlite3_bind_int(stmtFournit, 1, idFournisseur);
    sqlite3_bind_int(stmtFournit, 2, idVin);
    rc = sqlite3_step(stmtFournit);
    if (rc == SQLITE_ROW) {
        prixBaseFournisseur = sqlite3_column_double(stmtFournit, 0);
    }
    sqlite3_finalize(stmtFournit);

    // Calculer la marge
    double marge = prixBasePropose - (prixBaseFournisseur - ((prixBaseFournisseur * reductionCollabore)/100));

    // Mettre à jour la table Gere avec la marge calculée
    std::string updateQuery = "UPDATE Gere SET marge = ? WHERE idCave = ? AND idVin = ? AND idFournisseur = ?";
    sqlite3_stmt* stmtUpdate;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmtUpdate, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête UPDATE Gere" << std::endl;
        return;
    }
    sqlite3_bind_double(stmtUpdate, 1, marge);
    sqlite3_bind_int(stmtUpdate, 2, idCave);
    sqlite3_bind_int(stmtUpdate, 3, idVin);
    sqlite3_bind_int(stmtUpdate, 4, idFournisseur);

    rc = sqlite3_step(stmtUpdate);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erreur lors de la mise à jour de la marge dans la table Gere" << std::endl;
        return;
    }
    sqlite3_finalize(stmtUpdate);
}