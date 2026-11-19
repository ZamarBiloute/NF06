#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"

int main(void) {
    Afficher_Menu_Demarrage();
    if (charger_stock() == false) {
        fprintf(stderr, "Erreur lors du chargement du stock.\n");
        return EXIT_FAILURE;
    }
    printf("Nom du produit 1 : %s\n", stock[0].nom);
    return EXIT_SUCCESS;
}