#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"
#include "tools.h"
#include "const.h"

int main(void) {

    /* Variables locales */
    ENUM_CHOIX choix_utilisateur = CHOIX_MP_UNDEF;
    
    /* Point d'entree */

    if (charger_stock() == false) {
        fprintf(stderr, "Erreur lors du chargement du stock.\n");
        return EXIT_FAILURE;
    }
    
    choix_utilisateur = Menu(MENU_PRINCIPAL);

    /* Point de sortie */
    return EXIT_SUCCESS;
}