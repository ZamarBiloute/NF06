#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "version.h"
#include "const.h"
#include "tools.h"
//-------------------------------------------------------------------------------------------------------------------
// Liste de variable locale
//-------------------------------------------------------------------------------------------------------------------
unsigned char Numero_Choix_Selectionner = 1; // Variable globale pour suivre le choix sélectionné dans le menu principal

//-------------------------------------------------------------------------------------------------------------------
// Liste des constantes de texte et menu
//-------------------------------------------------------------------------------------------------------------------

// Texte de démarrage du programme
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

// Menu spécifique au menu de démarrage
const char *Menu_Principal_Options[] = {
    " 1. Espace client                        ",
    " 2. Espace administrateur                ",
    " 3. Enregistrer et quitter l’application ",
    NULL
};
#define MENU_PRINCIPAL_NOMBRE_LIGNE (sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0]))

// Menu spécifique au menu client
const char *Menu_Client_Options[] = {
  " 1. Ajouter un produit au panier  ",
  " 2. Afficher le panier            ",
  " 3. Valider le panier             ",
  " 4. Abandonner et vider le panier ",
  NULL
};
#define MENU_CLIENTL_NOMBRE_LIGNE (sizeof(Menu_Principal_Options) / sizeof(Menu_Principal_Options[0]))

// Déclaration des fonctions internes utilisées pour afficher les menus
void Afficher_Option_Menu(const char *message,bool selectionner);
static void Afficher_Texte(const char *TabTxt[]);

/**
 * @brief Affiche tous les textes lors du démarrage du programme.
 *
 * Configure la console de sortie en UTF-8 afin de pouvoir afficher les caractères spéciaux telle que les accents.
 * Efface l'écran et affiche les textes de démarrage prédéfinis?
 *
 * @param[in]  Rien.
 *
 * @return Rien
 */
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

/**
 * @brief Affiche un menu .
 *
 * @param[in]  const char contenant le texte des menus.
 *
 * @return Rien
 */

void Afficher_Menu(const char *TabTxt[]) {
  for (size_t i = 0; TabTxt[i] != NULL; i++) {
    if (i + 1 == Numero_Choix_Selectionner) {
      Afficher_Option_Menu(TabTxt[i], true);
    } else {
      Afficher_Option_Menu(TabTxt[i], false);
    }
  }
}

/**
 * @brief Affiche ligne par ligne tous les textes d'un tableau de texte.
 *
 * @param[in]  const char de texte.
 *
 * @return Rien
 */

static void Afficher_Texte(const char *TabTxt[]) {
  for (size_t i = 0; TabTxt[i] != NULL; i++) {
    Afficher_Option_Menu(TabTxt[i], false);
  }
}

/**
 * @brief Affiche ligne par ligne tous les textes d'un menu.
 *
 * @param[in]  const char de texte.
 * @param[in]  bool pour définir le choix du menu qui est selectionner.
 *
 * @return Rien
 */
void Afficher_Option_Menu(const char *message, bool selectionner) {
  
  if (selectionner) {
    printf(ANSI_NOIR_FOND_BLANC"%s"ANSI_RESET"\n", message);
  } else {
    printf("%s\n", message);
  }
}

/**
 * @brief Affiche le menu principal et le gère (gestion du curseur).
 *
 * @param[in]  Rien.
 *
 * @return ENUM_CHOIX_MP qui correspond au choix de valider par l'utilisateur.
 */

ENUM_CHOIX_MP Affiche_Et_Gere_Menu_Principal(void) {

  bool Sortie = false;
  bool Maj = false;
  ENUM_CHOIX_MP Choix = CHOIX_MP_UNDEF;

  Afficher_Menu(Menu_Principal_Options);
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
                    Numero_Choix_Selectionner = MENU_PRINCIPAL_NOMBRE_LIGNE - 1;
                }
            } break;
            case TOUCHE_FLECHE_BAS:
            {
              Maj = true;
                if (Numero_Choix_Selectionner < MENU_PRINCIPAL_NOMBRE_LIGNE - 1) {
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
            ANSI_DEPLACEMENT_HAUT((unsigned int)MENU_PRINCIPAL_NOMBRE_LIGNE-1);
            Afficher_Menu(Menu_Principal_Options);
          }
      } break;
      case TOUCHE_1:
      {
        Choix = CHOIX_MP_ESPACE_CLIENT;
        Sortie = true;
      } break;
      case TOUCHE_2:
      {
        Choix = CHOIX_MP_ESPACE_ADMIN;
        Sortie = true;
      } break;
      case TOUCHE_3:
      {
        Choix = CHOIX_MP_QUITTER;
        Sortie = true;
      } break;
      case TOUCHE_ENTREE:
      {
        switch (Numero_Choix_Selectionner)
        {
          case 1: Choix = CHOIX_MP_ESPACE_CLIENT; break;
          case 2: Choix = CHOIX_MP_ESPACE_ADMIN; break;
          case 3: Choix = CHOIX_MP_QUITTER; break;
          default: Choix = CHOIX_MP_UNDEF; break;
        }

        Sortie = true;
      } break;
    }
  }

  return Choix;
}

/**
 * @brief Affiche le menu principal et le gère (gestion du curseur).
 *
 * @param[in]  Rien.
 *
 * @return ENUM_CHOIX_MP qui correspond au choix de valider par l'utilisateur.
 */

ENUM_CHOIX_MC Affiche_Et_Gere_Menu_Client(void) {

  bool Sortie = false;
  bool Maj = false;
  ENUM_CHOIX_MC Choix = CHOIX_MC_UNDEF;

  system("cls");
  Afficher_Menu(Menu_Client_Options);
  // while (Sortie == false) {
  //   int touche = _getch();
  //   switch (touche) 
  //   {
  //     case TOUCHE_SPECIALE:
  //     {
  //       int code_touche = _getch();
  //         switch (code_touche) {
  //           case TOUCHE_FLECHE_HAUT:
  //           {
  //             Maj = true;
  //               if (Numero_Choix_Selectionner - 1 > 0) {
  //                   Numero_Choix_Selectionner--;
  //               } else {
  //                   Numero_Choix_Selectionner = MENU_PRINCIPAL_NOMBRE_LIGNE;
  //               }
  //           } break;
  //           case TOUCHE_FLECHE_BAS:
  //           {
  //             Maj = true;
  //               if (Numero_Choix_Selectionner < MENU_PRINCIPAL_NOMBRE_LIGNE) {
  //                   Numero_Choix_Selectionner++;
  //               } else {
  //                   Numero_Choix_Selectionner = 1;
  //               }
  //           } break;
            
  //           default:
  //           break;
  //         }
  //         if (Maj) {
  //           Maj = false;
  //           ANSI_DEPLACEMENT_HAUT((unsigned int)MENU_PRINCIPAL_NOMBRE_LIGNE);
  //           Afficher_Menu_Principal();
  //         }
  //     } break;
  //     case TOUCHE_1:
  //     {
  //       Choix = CHOIX_MP_ESPACE_CLIENT;
  //       Sortie = true;
  //     } break;
  //     case TOUCHE_2:
  //     {
  //       Choix = CHOIX_MP_ESPACE_ADMIN;
  //       Sortie = true;
  //     } break;
  //     case TOUCHE_3:
  //     {
  //       Choix = CHOIX_MP_QUITTER;
  //       Sortie = true;
  //     } break;
  //     case TOUCHE_ENTREE:
  //     {
  //       switch (Numero_Choix_Selectionner)
  //       {
  //         case TOUCHE_1: Choix = CHOIX_MP_ESPACE_CLIENT; break;
  //         case TOUCHE_2: Choix = CHOIX_MP_ESPACE_ADMIN; break;
  //         case TOUCHE_3: Choix = CHOIX_MP_QUITTER; break;
  //         default: Choix = CHOIX_MP_UNDEF; break;
  //       }

  //       Sortie = true;
  //     } break;
  //   }
  // }

  return Choix;
}