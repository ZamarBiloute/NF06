#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"

int main(void) {
    Afficher_Menu_Demarrage();
    charger_stock();
    printf("Nom du produit 1 : %s\n", stock[0].nom);
    printf("Nom du produit 2 : %s\n", stock[1].nom);
    printf("Nom du produit 3 : %s\n", stock[2].nom);

}