#pragma once

#include "const.h"

// Liste des enum
typedef enum {
  MENU_PRINCIPAL,
  MENU_CLIENT,
  MENU_ADMIN
} MENU;

// Liste des fonctions

ENUM_CHOIX Menu(MENU Menu);