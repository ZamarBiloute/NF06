#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"
#include "tools.h"
#include "const.h"

int main(void) {

    /* Variables locales */

    /* Point d'entree */
    Afficher_Menu_Demarrage();
    if (charger_stock() == false) {
        fprintf(stderr, "Erreur lors du chargement du stock.\n");
        return EXIT_FAILURE;
    }
    // Affichage du nombre de produits chargés depuis le stock actuel
    printf(ANSI_VERT "Etat du stock actuel : %u produits chargés." ANSI_RESET "\n", nombre_produits);

    if (Affiche_Et_Gere_Menu_Principal() == 0) {
        return EXIT_FAILURE;
    }
    /* Point de sortie */
    return EXIT_SUCCESS;
}