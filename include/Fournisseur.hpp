#ifndef FOURNISSEUR_HPP
#define FOURNISSEUR_HPP
#include <sqlite3.h>
#include <string>
#include <vector>

struct FournisseurData {
    int idFournisseur;
    std::string nom;
    std::string adresse;
};

class Fournisseur {

    public:
        Fournisseur(sqlite3* db);  
        void ajouterFournisseur(const std::string& nom, const std::string& adresse, int idFournisseur);
        void supprimerFournisseur(int idFournisseur);
        void afficherFournisseurs();
        void afficherFournisseur(int idFournisseur);
        
    private: 
        sqlite3* db;
};

#endif