#include <stdio.h>
#include <string.h>
#include "client.h"
#include "stock.h"
#include "file.h"

void menu_client(File *f1, File *f2, int *id_compteur) {
    ArticlePanier panier[MAX_ARTICLES_PANIER];
    int nb_panier = 0;
    int choix = 0;

    do {
        printf("\n================ ESPACE CLIENT ================\n");
        printf("1. Consulter les produits par categorie\n");
        printf("2. Ajouter un produit au panier\n");
        printf("3. Consulter mon panier\n");
        printf("4. Valider et payer la commande\n");
        printf("5. Abandonner et vider le panier\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choix == 1) {
            lister_categories();
            char cat[MAX_STR];
            printf("Saisissez le nom de la categorie : ");
            while (getchar() != '\n');
            if (fgets(cat, sizeof(cat), stdin)) {
                cat[strcspn(cat, "\r\n")] = 0;
                lister_produit_par_categorie(cat);
            }
        } else if (choix == 2) {
            if (nb_panier >= MAX_ARTICLES_PANIER) {
                printf("Panier plein (limite de 50 articles distincts atteinte).\n");
                continue;
            }

            int idx, qte;
            printf("Index du produit a ajouter : ");
            if (scanf("%d", &idx) != 1 || idx < 0 || idx >= nb_produits_global) {
                printf("Index invalide.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Quantite souhaitee : ");
            if (scanf("%d", &qte) != 1 || qte <= 0) {
                printf("Quantite invalide.\n");
                while (getchar() != '\n');
                continue;
            }

            if (stock_global[idx].stock < qte) {
                printf("Stock insuffisant ! Disponible uniquement : %d\n", stock_global[idx].stock);
            } else {
                stock_global[idx].stock -= qte;
                panier[nb_panier].index_produit = idx;
                panier[nb_panier].quantite = qte;
                nb_panier++;
                printf("Article ajoute au panier avec succes.\n");
            }
        } else if (choix == 3) {
            printf("\n--- Recapitulatif du Panier ---\n");
            if (nb_panier == 0) {
                printf("Votre panier est vide.\n");
            } else {
                float total = 0.0f;
                for (int i = 0; i < nb_panier; i++) {
                    int p_idx = panier[i].index_produit;
                    float sous_total = stock_global[p_idx].prix * panier[i].quantite;
                    printf("- %s x%d : %.2f EUR (%.2f EUR/unite)\n",
                           stock_global[p_idx].nom, panier[i].quantite, sous_total, stock_global[p_idx].prix);
                    total += sous_total;
                }
                printf("Montant total estimatif : %.2f EUR\n", total);
            }
        } else if (choix == 4) {
            if (nb_panier == 0) {
                printf("Impossible de commander : le panier est vide.\n");
                continue;
            }

            char nom[MAX_STR], adr[MAX_STR];
            int priorite;
            float total = 0.0f;

            for (int i = 0; i < nb_panier; i++) {
                total += stock_global[panier[i].index_produit].prix * panier[i].quantite;
            }

            while (getchar() != '\n');
            printf("Nom du destinataire : ");
            if (fgets(nom, sizeof(nom), stdin)) nom[strcspn(nom, "\r\n")] = 0;

            printf("Adresse de livraison : ");
            if (fgets(adr, sizeof(adr), stdin)) adr[strcspn(adr, "\r\n")] = 0;

            printf("Type de livraison (1: Prioritaire Express, 2: Standard) : ");
            if (scanf("%d", &priorite) != 1 || (priorite != 1 && priorite != 2)) {
                priorite = 2;
            }

            int id = (*id_compteur)++;
            if (priorite == 1) {
                Ajouter_une_commande(f1, id, nom, adr, total, priorite);
            } else {
                Ajouter_une_commande(f2, id, nom, adr, total, priorite);
            }

            printf("\nCommande #%d validee et inseree dans la file d'expedition !\n", id);
            nb_panier = 0;
            break;
        } else if (choix == 5) {
            for (int i = 0; i < nb_panier; i++) {
                stock_global[panier[i].index_produit].stock += panier[i].quantite;
            }
            nb_panier = 0;
            printf("Panier annule. Les quantites ont ete remises en stock.\n");
        }
    } while (choix != 5);

    return;
}
