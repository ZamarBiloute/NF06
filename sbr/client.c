#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "stock.h"
#include "data.h"
#include "tools.h"
#include "const.h"
#include "menu.h"

#include "client.h"

/**
 * @brief Affiche et gère l'espace client.
 *
 * @param[in]  Rien.
 *
 * @return Rien.
 */
void Client(void)
{
  ENUM_CHOIX choix_utilisateur = CHOIX_MP_UNDEF;

  while (choix_utilisateur != CHOIX_MC_ABANDONNER_ET_VIDER_PANIER)
  {
    choix_utilisateur = Menu(MENU_CLIENT);
    switch (choix_utilisateur)
    {
      case CHOIX_MC_AJOUTER_PRODUIT:
      {
        // Pour ajouter un produit, il faut d'abord afficher la liste des catégories
        // afin de permettre un filtre.
        // Il faut afficher la liste des categories grace à la variable IndexCategorie[] et nombre_categories
        for (unsigned int cpt = 0 ; cpt < nombre_categories ; cpt++)
        printf("%s\n",stock[IndexCategorie[cpt]].categorie);
        getchar();
        
        
      } break;
      
      case CHOIX_MC_AFFICHER_PANIER:
      {

      } break;

      case CHOIX_MC_VALIDER_PANIER:
      {

      } break;
      default:
      case CHOIX_MC_ABANDONNER_ET_VIDER_PANIER:
      {


      } break;

    }
  }

}

