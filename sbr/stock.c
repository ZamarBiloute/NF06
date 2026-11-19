#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stock.h"
#include "data.h"
#include "Const.h"

Produit * stock = NULL;

// Fonction qui permet de charger en mémoire le stock qui est defini 
// dans le fichier stock.txt
// ------------------------------------------------------------------
// Voici le format du fichier stock.txt :
// Nom de la catégorie;Nom du produit;Prix;Stock
// Exemple : Electronique;Smartphone;699.99;50
// ------------------------------------------------------------------
// Paramètre d'entrée : aucun
// Paramètre de sortie : true si le chargement s'est bien déroulé, sinon false
// ------------------------------------------------------------------

bool charger_stock(void) {
    // Variable locales
    bool Result = true;
    int nombre_lignes = 0;
    int nombre_caracteres = 0;
    char caractere, dernier_caractere;
    long size = 0;


    // Implémentation de la fonction pour charger le stock
    // stock[0] = (Produit){"Produit1", "Categorie1", 10.0, 100};
    // stock[1] = (Produit){"Produit2", "Categorie2", 20.0, 200};
    // stock[2] = (Produit){"Produit3", "Categorie3", 30.0, 300};
    FILE *file = fopen(NOM_FICHIER_STOCK, "r");
    if (file == NULL) {
        printf("Pb pour ouvrir le fichier %s\n", NOM_FICHIER_STOCK);
        Result = false;
    } else {

        // Vérifier si le fichier est vide
        // pour cela, on se positionne à la fin du fichier et vérifie la position du curseur. 
        // Si la position est 0, le fichier est vide.
        if (fseek(file, 0, SEEK_END) == 0) {
            size = ftell(file);
            printf("Taille du fichier %ld\n",size);
            if (size == 0) {
                printf("Fichier %s vide\n", NOM_FICHIER_STOCK);
                Result = false;
                fclose(file);
                return Result;
            }
        }

        //Pour pouvoir lire le fichier, on se positionne au début du fichier
        rewind(file);

        // Afin de définir une allocation dynamique de mémoire pour le stock, il nous faut déterminer le nombre de produit et donc le nombre de ligne dans le fichier.
        // Remarque : il faut tenir compte du cas ou la dernier ligne ne se termine pas par EOF et donc il faut qu'elle soit comptabilisée
        while ((caractere = fgetc(file)) != EOF) {
            dernier_caractere = caractere;
            nombre_caracteres ++;
            if (caractere == '\n') {
                nombre_lignes++;
            }
        }
        if ( (dernier_caractere != EOF) && (size == nombre_caracteres) )
            nombre_lignes++;

        //Pour pouvoir lire le fichier, on se positionne au début du fichier
        rewind(file);

        // Allocation dynamique de mémoire pour le stock
        stock = malloc(nombre_lignes * sizeof(Produit));
        if (stock == NULL) {
            printf("Problème d'allocation mémoire pour le stock\n");
            fclose(file);
            Result = false;
        } else {
            for (int i = 0; i < nombre_lignes; i++) {
                if (fscanf(file, "%99[^;];%99[^;];%f;%d\n", stock[i].categorie, stock[i].nom, &stock[i].prix, &stock[i].stock) != 4) {
                    // Les 4 champs n'ont pu etre lus correctement, donc on considère que le chargement a échoué
                    printf("Problème de lecture du fichier %s\n", NOM_FICHIER_STOCK);
                    Result = false;
                    break;
                }
            }
        }
        if (Result == false) {
            fclose(file);
            free(stock);
            stock = NULL;
        }

        fclose(file);
    }
    return Result;
}