#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"
#include "tools.h"

int main(void) {

    /* Variables locales */

    /* Point d'entree */
    Afficher_Menu_Demarrage();
    if (charger_stock() == false) {
        fprintf(stderr, "Erreur lors du chargement du stock.\n");
        return EXIT_FAILURE;
    }
    printf("Etat du stock actuel : %u produits chargés.\n", nombre_produits);
    
    /* Point de sortie */
    return EXIT_SUCCESS;
}