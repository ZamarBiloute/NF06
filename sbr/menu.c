#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "version.h"
#include "const.h"

unsigned char Numero_Choix_Selectionner = 1; // Variable globale pour suivre le choix sélectionné dans le menu principal
char *Menu_Principal_Options[] = {
    "1.Espace client                       ",
    "2.Espace administrateur               ",
    "3.Enregistrer et quitter l’application"
};

// Déclaration des fonctions internes utilisées pour afficher les menus
void Afficher_Menu(char *message,bool selectionner);

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

void Afficher_Menu_Principal(void) {
  for (unsigned char i = 0; i < sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0]); i++) {
    if (i + 1 == Numero_Choix_Selectionner) {
      Afficher_Menu(Menu_Principal_Options[i], true);
    } else {
      Afficher_Menu(Menu_Principal_Options[i], false);
    }
  }
}

void Afficher_Menu(char *message, bool selectionner) {
  
  if (selectionner) {
    printf(ANSI_NOIR_FOND_BLANC"%s"ANSI_RESET"\n", message);
  } else {
    printf("%s\n", message);
  }
}

unsigned char Affiche_Et_Gere_Menu_Principal(void) {

  Afficher_Menu_Principal();
  while (1) {
    int touche = _getch();
    if (touche == TOUCHE_SPECIALE)
    {
      int code_touche = _getch();
      switch (code_touche) {
        case TOUCHE_FLECHE_HAUT:
            if (Numero_Choix_Selectionner - 1 > 0) {
                Numero_Choix_Selectionner--;
            } else {
                Numero_Choix_Selectionner = sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0]);
            }
            break;
        case TOUCHE_FLECHE_BAS:
            if (Numero_Choix_Selectionner < sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0])) {
                Numero_Choix_Selectionner++;
            } else {
                Numero_Choix_Selectionner = 1;
            }
            break;
        default:
            break;
      }
      system("cls");
      Afficher_Menu_Demarrage();
      Afficher_Menu_Principal();

    }

    printf("Touche appuyée : %d\n", touche); // Affiche le code de la touche appuyée pour le débogage

  }
}