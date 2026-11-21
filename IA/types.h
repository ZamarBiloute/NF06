#ifndef TYPES_H
#define TYPES_H

#define MAX_STR 64
#define MAX_ARTICLES_PANIER 50

typedef struct {
    char nom[MAX_STR];
    char categorie[MAX_STR];
    float prix;
    int stock;
} Produit;

typedef struct {
    int index_produit;
    int quantite;
} ArticlePanier;

typedef struct NoeudCommande {
    int id;
    char nom_client[MAX_STR];
    char adresse[MAX_STR];
    float total;
    int priorite;
    struct NoeudCommande *suivant;
} NoeudCommande;

typedef struct {
    NoeudCommande *tete;
    NoeudCommande *queue;
    int taille;
} File;

#endif
