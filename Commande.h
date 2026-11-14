#ifndef COMMANDE_H
#define COMMANDE_H

#include "types.h"

void init_file(File *f);
int est_vide(const File *f);
void Ajouter_une_commande(File *f, int id, const char *nom, const char *adr, float total, int priorite);
NoeudCommande* dequeue(File *f);
void afficher_file(const File *f);
void liberer_file(File *f);

#endif
