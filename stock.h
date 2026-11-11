#ifndef STOCK_H
#define STOCK_H

#include "types.h"

extern Produit *stock_global;
extern int nb_produits_global;

int charger_stock(const char *chemin);
int sauvegarder_stock(const char *chemin);
void lister_categories(void);
void afficher_stock_par_categorie(const char *categorie);

#endif
