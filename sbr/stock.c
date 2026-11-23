#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tools.h"
#include "stock.h"
#include "data.h"
#include "Const.h"

Produit * stock = NULL;
unsigned int * IndexCategorie = NULL;
unsigned int nombre_produits = 0;
unsigned int nombre_categories = 0;
FILE *file = NULL;

// Liste des fonctions internes à ce fichier
unsigned int OpenCheckStockFileAndReturnProductCount(void);
bool SetListOfCategorie(void);

/**
 * @brief Charge en mémoire (RAM) le stock qui est dans un fichier texte et gère l'espace client.
 *
 * @param[in]  Rien.
 *
 * @return true si le chargement s'est bien déroulé, sinon false
 */
bool Charger_Stock(void) {
  
  /* Variables locales */
  bool Result = true;

  /* Point d'entree */
  nombre_produits = OpenCheckStockFileAndReturnProductCount();
  if (nombre_produits > 0) 
  {
      // Allocation dynamique de mémoire pour le stock
      stock = malloc(nombre_produits * sizeof(Produit));
      if (stock == NULL) {
          AFF_DEBUG("Problème d'allocation mémoire pour le stock\n");
          fclose(file);
          Result = false;
      } else {
          for (unsigned int i = 0; i < nombre_produits; i++) {
              if (fscanf(file, "%99[^;];%99[^;];%f;%d\n", stock[i].nom, stock[i].categorie, &stock[i].prix, &stock[i].stock) != 4) {
                  // Les 4 champs n'ont pu etre lus correctement, donc on considère que le chargement a échoué
                  AFF_DEBUG("Problème de lecture du fichier\n");
                  Result = false;
                  break;
              }
          }
      }
  } else
  {
      AFF_DEBUG("Aucun produit dans le fichier\n");
      Result = false;
  }
  fclose(file);
  if (Result == false) {
      free(stock);
      stock = NULL;
  } else {
    if ( SetListOfCategorie() == false)
    {
      free(stock);
      stock = NULL;
    }
  }


  /* Point de sortie */
  return Result;
}
 
/**
 * @brief Permet d'ouvrir le fichier texte contenant le stock et de retourner le nombre de ligne.
 * Ce nombre de ligne correspond finalement au nombre de produit dans le stock.
 * @param[in]  Rien.
 *
 * @return unsigned int nombre de produit en stock.
 */
unsigned int OpenCheckStockFileAndReturnProductCount(void) {

  /* Variables locales */
  unsigned long size = 0;
  unsigned int nombre_lignes = 0;
  unsigned int nombre_caracteres = 0;
  char caractere, dernier_caractere;

  /* Point d'entree */
  file = fopen(NOM_FICHIER_STOCK, "r");

  if (file != NULL) {
    // Vérifier si le fichier est vide
    // pour cela, on se positionne à la fin du fichier et vérifie la position du curseur. 
    // Si la position est 0, le fichier est vide.
    if (fseek(file, 0, SEEK_END) == 0) {
      size = ftell(file);
      AFF_DEBUG("Taille du fichier %lu\n", size);
      if (size == 0) {
        AFF_DEBUG("Fichier vide\n");
        fclose(file);
      } else 
      {

        //Pour pouvoir déterminer le nombre de lignes dans le fichier, on se positionne au début du fichier
        rewind(file);

        // Afin de définir une allocation dynamique de mémoire pour le stock, il nous faut déterminer le nombre de produit et donc le nombre de ligne dans le fichier.
        // Remarque : il faut tenir compte du cas ou la dernier ligne ne se termine pas par EOF et donc il faut qu'elle soit comptabilisée
        while ((caractere = fgetc(file)) != EOF) {
          dernier_caractere = caractere;
          nombre_caracteres ++;
          if (caractere == '\n') {
              nombre_lignes++;
          }
        }
        if ( (dernier_caractere != EOF) && (size == nombre_caracteres) )
            nombre_lignes++;

        //Avant de quitter la fonction, on se positionne au début du fichier pour pouvoir le lire par la suite
        rewind(file);
      }
    }
  }

  /* Point de sortie */
  return nombre_lignes;
}

/**
 * @brief Depuis le stock en mémoire (RAM), détermine les indices des catégories uniques.
 * Ceci est necessaire pour ensuite pouvoir afficher cette liste.
 * @param[in]  Rien.
 *
 * @return true si le chargement s'est bien déroulé, sinon false
 */
bool SetListOfCategorie(void)
{
  /* Variables locales */
  bool CategorieDejaVu = false;
  
  if (stock == NULL)
    nombre_categories = 0;
  else{
    for (unsigned int i = 0 ; i < nombre_produits ; i++)
    {
      CategorieDejaVu = false;
      for (unsigned int j = 0 ; j < i ; j++ )
      {
        if (strcmp(stock[i].categorie,stock[j].categorie) == 0)
        {
          CategorieDejaVu = true;
          break;
        }
      }
      if ( CategorieDejaVu == false)
      {
        nombre_categories ++;
      }
    }
  }
  IndexCategorie = malloc(nombre_categories);

  if (IndexCategorie == NULL)
    return false;
  else
  {
    unsigned int Cpt = 0;
    for (unsigned int i = 0 ; i < nombre_produits ; i++)
    {
      CategorieDejaVu = false;
      for (unsigned int j = 0 ; j < i ; j++ )
      {
        if (strcmp(stock[i].categorie,stock[j].categorie) == 0)
        {
          CategorieDejaVu = true;
          break;
        }
      }
      if ( CategorieDejaVu == false)
      {
        IndexCategorie[Cpt++] = i;
      }
    }

    return true;
  }

}