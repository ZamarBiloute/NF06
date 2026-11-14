#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

Produit *stock_global = NULL;
int nb_produits_global = 0;

int charger_stock(const char *chemin) {
    FILE *f = fopen(chemin, "r");
    if (!f) return 0;

    int capacite = 20;
    stock_global = malloc(capacite * sizeof(Produit));
    if (stock_global == NULL) {
        fclose(f);
        return 0;
    }
    nb_produits_global = 0;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        if (ligne[0] == '\n' || ligne[0] == '\r') continue;

        if (nb_produits_global >= capacite) {
            capacite *= 2;
            Produit *temp = realloc(stock_global, capacite * sizeof(Produit));
            if (!temp) break;
            stock_global = temp;
        }

        Produit *p = &stock_global[nb_produits_global];
        ligne[strcspn(ligne, "\r\n")] = 0;

        char *token = strtok(ligne, ";");
        if (token) strncpy(p->nom, token, MAX_STR - 1);

        token = strtok(NULL, ";");
        if (token) strncpy(p->categorie, token, MAX_STR - 1);

        token = strtok(NULL, ";");
        if (token) p->prix = (float)atof(token);

        token = strtok(NULL, ";");
        if (token) p->stock = atoi(token);

        nb_produits_global++;
    }

    fclose(f);
    return 1;
}

int sauvegarder_stock(const char *chemin) {
    FILE *f = fopen(chemin, "w");
    if (!f) return 0;

    for (int i = 0; i < nb_produits_global; i++) {
        fprintf(f, "%s;%s;%.2f;%d\n", stock_global[i].nom, stock_global[i].categorie, stock_global[i].prix, stock_global[i].stock);
    }

    fclose(f);
    return 1;
}

void lister_categories(void) {
    char categories[100][MAX_STR];
    int nb_cat = 0;

    printf("\n--- Categories Disponibles ---\n");
    for (int i = 0; i < nb_produits_global; i++) {
        int trouve = 0;
        for (int j = 0; j < nb_cat; j++) {
            if (strcmp(categories[j], stock_global[i].categorie) == 0) {
                trouve = 1;
                break;
            }
        }
        if (!trouve && nb_cat < 100) {
            strncpy(categories[nb_cat], stock_global[i].categorie, MAX_STR - 1);
            printf("- %s\n", categories[nb_cat]);
            nb_cat++;
        }
    }
}

void lister_produit_par_categorie(const char *categorie) {
    printf("\n--- Produits [%s] ---\n", categorie);
    for (int i = 0; i < nb_produits_global; i++) {
        if (strcmp(stock_global[i].categorie, categorie) == 0) {
            printf("[%d] %s | Prix: %.2f EUR | En stock: %d\n",
                   i, stock_global[i].nom, stock_global[i].prix, stock_global[i].stock);
        }
    }
}
