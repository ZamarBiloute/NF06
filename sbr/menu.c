#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "version.h"
#include "const.h"
#include "tools.h"

unsigned char Numero_Choix_Selectionner = 1; // Variable globale pour suivre le choix sélectionné dans le menu principal
const char *Menu_Principal_Options[] = {
    "1. Espace client                       ",
    "2. Espace administrateur               ",
    "3. Enregistrer et quitter l’application"
};
#define MENU_PRINCIPAL_NOMBRE_LIGNE (sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0]))

const char *Texte_Demarrage[] = {
    "╔═════════════════════════════════════════════════════════════════════════════════╗",
    "║            Projet - système de gestion des livraisons e-commerce en C           ║",
    "╠═════════════════════════════════════════════════════════════════════════════════╣",
    "║ Auteur : BOUAMAR Bilel                                                          ║",
    "║ Etudiant UTT 2026-2027                                                          ║",
    "╠═════════════════════════════════════════════════════════════════════════════════╣",
    "║ Utiliser les flèches pour déplacer la selection, puis valider (Entrée)          ║",
    "║ ou appuyer sur le chiffre correspondant au choix                                ║",
    "╚═════════════════════════════════════════════════════════════════════════════════╝",
    "",
    NULL
};
#define TEXTE_DEMARRAGE_NOMBRE_LIGNE (sizeof(Texte_Demarrage) / sizeof(Texte_Demarrage[0]))

// Déclaration des fonctions internes utilisées pour afficher les menus
void Afficher_Menu(const char *message,bool selectionner);
static void Afficher_Texte(const char *TabTxt[]);

void Afficher_Texte_Demarrage(void) {

  // Permet de définir l'encodage de la console en UTF-8 pour afficher correctement les caractères spéciaux telle que les accents.
  if (!SetConsoleOutputCP(CP_UTF8)) {
      fprintf(stderr, "Impossible de configurer la console en UTF-8 (erreur %lu).\n",
              (unsigned long)GetLastError());
      return;
  }

  system("cls");
  Afficher_Texte(Texte_Demarrage);

}

static void Afficher_Texte(const char *TabTxt[]) {
  for (size_t i = 0; TabTxt[i] != NULL; i++) {
    Afficher_Menu(TabTxt[i], false);
  }
}

void Afficher_Menu_Principal(void) {
  for (unsigned char i = 0; i < MENU_PRINCIPAL_NOMBRE_LIGNE; i++) {
    if (i + 1 == Numero_Choix_Selectionner) {
      Afficher_Menu(Menu_Principal_Options[i], true);
    } else {
      Afficher_Menu(Menu_Principal_Options[i], false);
    }
  }
}

void Afficher_Menu(const char *message, bool selectionner) {
  
  if (selectionner) {
    printf(ANSI_NOIR_FOND_BLANC"%s"ANSI_RESET"\n", message);
  } else {
    printf("%s\n", message);
  }
}

unsigned char Affiche_Et_Gere_Menu_Principal(void) {

  bool Sortie = false;
  bool Maj = false;

  Afficher_Menu_Principal();
  while (Sortie == false) {
    int touche = _getch();
    switch (touche) 
    {
      case TOUCHE_SPECIALE:
      {
        int code_touche = _getch();
          switch (code_touche) {
            case TOUCHE_FLECHE_HAUT:
            {
              Maj = true;
                if (Numero_Choix_Selectionner - 1 > 0) {
                    Numero_Choix_Selectionner--;
                } else {
                    Numero_Choix_Selectionner = MENU_PRINCIPAL_NOMBRE_LIGNE;
                }
            } break;
            case TOUCHE_FLECHE_BAS:
            {
              Maj = true;
                if (Numero_Choix_Selectionner < MENU_PRINCIPAL_NOMBRE_LIGNE) {
                    Numero_Choix_Selectionner++;
                } else {
                    Numero_Choix_Selectionner = 1;
                }
            } break;
            
            default:
            break;
          }
          if (Maj) {
            Maj = false;
            ANSI_DEPLACEMENT_HAUT((unsigned int)MENU_PRINCIPAL_NOMBRE_LIGNE);
            Afficher_Menu_Principal();
          }
      } break;
      case TOUCHE_1:
      {
        Numero_Choix_Selectionner = 1;
        Sortie = true;
      } break;
      case TOUCHE_2:
      {
        Numero_Choix_Selectionner = 2;
        Sortie = true;
      } break;
      case TOUCHE_3:
      {
        Numero_Choix_Selectionner = 3;
        Sortie = true;
      } break;
      case TOUCHE_ENTREE:
      {
        Sortie = true;
      } break;
    }
  }

  return Numero_Choix_Selectionner;
}