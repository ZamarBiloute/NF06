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
    
    while (choix_utilisateur != CHOIX_MP_QUITTER)
    {
      choix_utilisateur = Menu(MENU_PRINCIPAL);
      switch (choix_utilisateur)
      {
        case CHOIX_MP_ESPACE_CLIENT:
        {
          Menu(MENU_CLIENT);
        } break;
        
        case CHOIX_MP_ESPACE_ADMIN:
        {

        } break;
        default:
        case CHOIX_MP_QUITTER:
        {

        } break;

      }
    }

    /* Point de sortie */
    return EXIT_SUCCESS;
}