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

// Liste des variables globales utilisées dans le projet

// Pointeur de type Produit pour stocker le stock de produits
extern Produit * stock;

// Variable globale pour stocker le nombre de produits dans le stock
extern unsigned int nombre_produits;