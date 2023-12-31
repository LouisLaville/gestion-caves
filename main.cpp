#include "src/DataBaseManager.cpp"
#include "src/Cave.cpp"
#include "src/Vin.cpp"
#include "src/Fournisseur.cpp"
#include "src/Propose.cpp"
#include "src/Fournit.cpp"
#include "src/Collabore.cpp"

int main() {

    DataBaseManager dbManager;   
    // Creer Cave / Vin / Fournisseur 
    Cave cave(dbManager.getDb());
    Vin vin(dbManager.getDb());
    Fournisseur fournisseur(dbManager.getDb());

    // Ajouter Cave / Vin / Fournisseur
    cave.ajouterCave("Cave1", "Adresse1", 1);
    cave.ajouterCave("Cave2", "Adresse2", 2);
    fournisseur.ajouterFournisseur("Fournisseur1", "Adresse1", 1);
    fournisseur.ajouterFournisseur("Fournisseur2", "Adresse2", 2);
    vin.ajouterVin("Region1", "Cru1", "Nom1", 2000, 1);
    vin.ajouterVin("Region2", "Cru2", "Nom2", 2001, 2);

    // Creer propose 
    Propose propose(dbManager.getDb());

    // Ajouter Propose
    propose.insererProposition(1, 1, 10);
    propose.insererProposition(1, 2, 20);
    propose.insererProposition(2, 1, 30);

    // Afficher propose 
    propose.afficherPropositions();
    propose.afficherPropositionVin(1);
    propose.afficherPropositionCave(1);
}


// POUR RUN LE PROGRAMME : 
// SE METTRE DANS LE DOSSIER DU PROJET
// SAISIR : g++ -Iinclude main.cpp -o mon_programme -lsqlite3
// PUIS : ./mon_programme 


// NE PAS OUBLIER D'INSTALLER SQLITE. POUR CELA :
// LINUX : sudo apt-get install sqlite3 libsqlite3-dev  
// WINDOWS : https://www.sqlite.org/download.html 
// MAC : brew install sqlite3 ( en utilisant homebrew )