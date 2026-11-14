#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Commande.h"

void init_file(File *f) {
    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
}

int est_vide(const File *f) {
    return (f->tete == NULL);
}

void Ajouter_une_commande(File *f, int id, const char *nom, const char *adr, float total, int priorite) {
    NoeudCommande *nouveau = malloc(sizeof(NoeudCommande));
    if (!nouveau) return;

    nouveau->id = id;
    strncpy(nouveau->nom_client, nom, MAX_STR - 1);
    nouveau->nom_client[MAX_STR - 1] = '\0';
    strncpy(nouveau->adresse, adr, MAX_STR - 1);
    nouveau->adresse[MAX_STR - 1] = '\0';
    nouveau->total = total;
    nouveau->priorite = priorite;
    nouveau->suivant = NULL;

    if (est_vide(f)) {
        f->tete = nouveau;
        f->queue = nouveau;
    } else {
        f->queue->suivant = nouveau;
        f->queue = nouveau;
    }
    f->taille++;
}

NoeudCommande* dequeue(File *f) {
    if (est_vide(f)) return NULL;

    NoeudCommande *temp = f->tete;
    f->tete = f->tete->suivant;
    if (f->tete == NULL) {
        f->queue = NULL;
    }
    temp->suivant = NULL;
    f->taille--;
    return temp;
}

void afficher_file(const File *f) {
    if (est_vide(f)) {
        printf(" (File vide)\n");
        return;
    }
    NoeudCommande *courant = f->tete;
    while (courant != NULL) {
        printf(" - Cmd #%d | Client: %s | Total: %.2f EUR\n",
               courant->id, courant->nom_client, courant->total);
        courant = courant->suivant;
    }
}

void liberer_file(File *f) {
    while (!est_vide(f)) {
        NoeudCommande *n = dequeue(f);
        free(n);
    }
}
