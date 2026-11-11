#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stock.h"
#include "file.h"
#include "client.h"
#include "admin.h"

int main(void) {
    const char *chemin_stock = "stock.txt";

    if (!charger_stock(chemin_stock)) {
        fprintf(stderr, "Erreur fatale : Impossible de charger le fichier %s.\n", chemin_stock);
        return EXIT_FAILURE;
    }
    printf("Initialisation : %d produits charges avec succes depuis %s.\n", nb_produits_global, chemin_stock);

    File file_prioritaire;
    File file_standard;
    init_file(&file_prioritaire);
    init_file(&file_standard);

    int id_commande = 1001;
    float chiffre_affaires = 0.0f;
    int option = 0;

    do {
        printf("\n================ SYSTEME DE GESTION DU MAGASIN ================\n");
        printf("1. Espace Client\n");
        printf("2. Espace Administrateur\n");
        printf("3. Enregistrer et Quitter\n");
        printf("Entrez votre choix : ");
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1:
                menu_client(&file_prioritaire, &file_standard, &id_commande);
                break;
            case 2:
                menu_admin(&file_prioritaire, &file_standard, &chiffre_affaires);
                break;
            case 3:
                printf("\nSauvegarde des modifications dans %s...\n", chemin_stock);
                if (sauvegarder_stock(chemin_stock)) {
                    printf("Sauvegarde terminee avec succes.\n");
                } else {
                    fprintf(stderr, "Erreur lors de la sauvegarde du stock.\n");
                }
                break;
            default:
                printf("Option invalide, veuillez reessayer.\n");
        }
    } while (option != 3);

    liberer_file(&file_prioritaire);
    liberer_file(&file_standard);
    free(stock_global);
    stock_global = NULL;
    nb_produits_global = 0;

    printf("Fermeture propre du programme.\n");
    return EXIT_SUCCESS;
}
