#pragma once

// Definition des constantes utilisées dans le projet
#define MAX_PRODUITS 100
#define MAX_STR 100

// Liste des enumérations utilisées dans le projet
typedef struct {
    char nom[MAX_STR];
    char categorie[MAX_STR];
    float prix;
    int stock;
} Produit;

// Liste des varaibles globales utilisées dans le projet
Produit stock[MAX_PRODUITS];