#include <stdbool.h>
#include "stock.h"
#include "data.h"

// Fonction qui permet de charger en mémoire le stock qui est defini 
// dans le fichier stock.txt
// ------------------------------------------------------------------
// Voici le format du fichier stock.txt :
// Nom de la catégorie;Nom du produit;Prix;Stock
// Exemple : Electronique;Smartphone;699.99;50
// ------------------------------------------------------------------
// Paramètre d'entrée : aucun
// Paramètre de sortie : true si le chargement s'est bien déroulé, sinon false
// ------------------------------------------------------------------

bool charger_stock(void) {
    // Variable locales
    bool Result = true;

    // Implémentation de la fonction pour charger le stock
    stock[0] = (Produit){"Produit1", "Categorie1", 10.0, 100};
    stock[1] = (Produit){"Produit2", "Categorie2", 20.0, 200};
    stock[2] = (Produit){"Produit3", "Categorie3", 30.0, 300};
    return Result;
}