#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"
#include "tools.h"
#include "const.h"

int main(void) {

    /* Variables locales */
    unsigned char choix_utilisateur = 0;
    /* Point d'entree */
    Afficher_Texte_Demarrage();

    if (charger_stock() == false) {
        fprintf(stderr, "Erreur lors du chargement du stock.\n");
        return EXIT_FAILURE;
    }
    // Affichage du nombre de produits chargés depuis le stock actuel
    printf(ANSI_VERT "Etat du stock actuel : %u produits chargés." ANSI_RESET "\n", nombre_produits);

    choix_utilisateur = Affiche_Et_Gere_Menu_Principal();
    switch (choix_utilisateur)
    {
        case CHOIX_MP_ESPACE_CLIENT:
        {
            Menu_Client();
        } break;

        case CHOIX_MP_ESPACE_ADMIN:
        {

        } break;

        case CHOIX_MP_QUITTER:
        {

        } break;        
    }
    /* Point de sortie */
    return EXIT_SUCCESS;
}