#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "admin.h"
#include "file.h"
#include "stock.h"

static void nom_fichier_journalier(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, size, "%d-%m-%Y.txt", tm_info);
}

static void archiver_commande(const NoeudCommande *cmd) {
    char nom_fichier[32];
    nom_fichier_journalier(nom_fichier, sizeof(nom_fichier));

    FILE *f = fopen(nom_fichier, "a");
    if (!f) return;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char horodatage[16];
    strftime(horodatage, sizeof(horodatage), "%H:%M:%S", tm_info);

    fprintf(f, "%d;%s;%s;%.2f;%d;%s\n",
            cmd->id, cmd->nom_client, cmd->adresse, cmd->total, cmd->priorite, horodatage);
    fclose(f);
}

static void expedier_commande(File *f, float *ca) {
    NoeudCommande *cmd = dequeue(f);
    if (!cmd) return;

    archiver_commande(cmd);
    *ca += cmd->total;

    printf("Expedition reussie -> Cmd #%d (%s) | Total: %.2f EUR\n",
           cmd->id, cmd->nom_client, cmd->total);
    free(cmd);
}

static void ordonnancer_livraisons(File *f1, File *f2, float *ca) {
    if (est_vide(f1) && est_vide(f2)) {
        printf("Aucune commande en attente d'expedition.\n");
        return;
    }

    printf("\n--- Traitement des commandes (Politique 2 P1 pour 1 P2) ---\n");

    int traite_p1 = 0;
    while (!est_vide(f1) && traite_p1 < 2) {
        printf("[P1 - Express] ");
        expedier_commande(f1, ca);
        traite_p1++;
    }

    if (!est_vide(f2)) {
        printf("[P2 - Standard] ");
        expedier_commande(f2, ca);
    } else if (traite_p1 == 0 && !est_vide(f1)) {
        printf("[P1 - Express] ");
        expedier_commande(f1, ca);
    }
}

static void reapprovisionner(void) {
    int idx, qte;
    printf("\nIndex du produit a reapprovisionner : ");
    if (scanf("%d", &idx) != 1 || idx < 0 || idx >= nb_produits_global) {
        printf("Index invalide.\n");
        while (getchar() != '\n');
        return;
    }
    printf("Quantite a ajouter : ");
    if (scanf("%d", &qte) != 1 || qte <= 0) {
        printf("Quantite invalide.\n");
        while (getchar() != '\n');
        return;
    }

    stock_global[idx].stock += qte;
    printf("Reapprovisionnement effectue. Nouveau stock pour %s : %d\n",
           stock_global[idx].nom, stock_global[idx].stock);
}

void menu_admin(File *f1, File *f2, float *ca) {
    int choix = 0;
    do {
        printf("\n================ PANNEAU ADMIN ================\n");
        printf("1. Visualiser les files d'attente (P1 & P2)\n");
        printf("2. Traiter le prochain lot d'expeditions (2 P1 / 1 P2)\n");
        printf("3. Afficher le chiffre d'affaires cumule\n");
        printf("4. Reapprovisionner un produit\n");
        printf("5. Retour au menu principal\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1:
                printf("\nFile Prioritaire (P1 - %d cmd):\n", f1->taille);
                afficher_file(f1);
                printf("\nFile Standard (P2 - %d cmd):\n", f2->taille);
                afficher_file(f2);
                break;
            case 2:
                ordonnancer_livraisons(f1, f2, ca);
                break;
            case 3:
                printf("\nChiffre d'affaires cumule de la session : %.2f EUR\n", *ca);
                break;
            case 4:
                reapprovisionner();
                break;
            case 5:
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 5);
}
