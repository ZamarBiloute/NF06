#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "version.h"


void Afficher_Menu_Demarrage(void) {

  // Permet de définir l'encodage de la console en UTF-8 pour afficher correctement les caractères spéciaux telle que les accents.
  if (!SetConsoleOutputCP(CP_UTF8)) {
      fprintf(stderr, "Impossible de configurer la console en UTF-8 (erreur %lu).\n",
              (unsigned long)GetLastError());
      return;
  }

  system("cls");
  printf("Programme e-commerce version %d.%d.%d\n", VERSION_MAJEUR, 
                                                    VERSION_MINEUR, 
                                                    VERSION_PATCH);
  printf("Projet - système de gestion des livraisons e-commerce en C\n");
  printf("------------------------------------------------------------\n");
  printf("Auteur : BOUAMAR Bilel\n");
  printf("Etudiant UTT 2026-2027\n");
  printf("------------------------------------------------------------\n");
  printf("\n");
  printf("Cette application permet aux clients de consulter les produits,\n");
  printf("de passer commande et de valider\n");
  printf("Un administrateur peut gérer les commandes pour les consulter et les livrées\n");   
  printf("\n");

}