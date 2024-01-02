#include "src/DataBaseManager.cpp"
#include "src/Cave.cpp"
#include "src/Vin.cpp"
#include "src/Fournisseur.cpp"
#include "src/Propose.cpp"
#include "src/Fournit.cpp"
#include "src/Collabore.cpp"
#include "src/Gere.cpp"

int main() {

    DataBaseManager dbManager;
   
}


// POUR RUN LE PROGRAMME : 
// SE METTRE DANS LE DOSSIER DU PROJET DANS LE TERMINAL 
// SAISIR : g++ -I include main.cpp -o mon_programme -lsqlite3
// PUIS : ./mon_programme 


// NE PAS OUBLIER D'INSTALLER SQLITE. POUR CELA :
// LINUX : sudo apt-get install sqlite3 libsqlite3-dev  
// WINDOWS : https://www.sqlite.org/download.html 
// MAC : brew install sqlite3 ( en utilisant homebrew )

// DANS VISUAL STUDIO 
// INSTALLER L'EXTENSION SQLite et SQLite Viewer afin de pouvoir visualier la base de données