#pragma once

// Definition des constantes utilisées dans le projet
#define NOM_FICHIER_STOCK "./Stock/stock.txt"

// true pour activer le mode debug, false pour le désactiver
// Le mode debug permet d'afficher des informations supplémentaires pour aider au débogage du programme.
#define DEBUG_ACTIF true

// Liste des codes ANSI pour la couleur du texte dans la console
#define ANSI_RESET "\x1b[0m"
#define ANSI_NOIR_FOND_BLANC "\x1b[30;47m"
#define ANSI_VERT "\x1b[32m"

//Liste des codes ANSI pour se déplacer dans la console
#define ANSI_DEPLACEMENT_HAUT(n) printf("\x1b[%dA", (n))
#define ANSI_DEPLACEMENT_BAS "\x1b[B"
#define ANSI_DEPLACEMENT_DROITE "\x1b[C"
#define ANSI_DEPLACEMENT_GAUCHE "\x1b[D"
#define ANSI_DEPLACEMENT_LIGNE_DEBUT "\x1b[1000D"
#define ANSI_DEPLACEMENT_LIGNE_FIN "\x1b[1000C"
#define ANSI_DEPLACEMENT_LIGNE_SUIVANTE "\x1b[1E"
#define ANSI_DEPLACEMENT_LIGNE_PRECEDENTE "\x1b[1F"
#define ANSI_ALLER_A_LA_POSITION(position) "\x1b[" #position "H" // Utilisation : printf(ANSI_ALLER_A_LA_POSITION, ligne, colonne);
#define ANSI_ALLER_AU_DEBUT_DE_LA_LIGNE(ligne) printf("\x1b[%d;1H", (ligne))

//Liste des codes de touches pour la navigation dans le menu
#define TOUCHE_SPECIALE 224
#define TOUCHE_FLECHE_HAUT 72
#define TOUCHE_FLECHE_BAS 80
#define TOUCHE_ENTREE 13
#define TOUCHE_3 51
#define TOUCHE_2 50
#define TOUCHE_1 49

