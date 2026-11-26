#include <stdlib.h>
#include <stdio.h>
#include "stock.h"

#define Max_taille 256

typedef struct Produit{
    char Category[Max_taille];
    char Name[Max_taille];
    float Price;
    int Quantity;
}Produit;

Produit * setup(){
    FILE *file = fopen("stock.txt", "r");
    if (file == NULL){
        printf("Erreur lors de l'ouverture du fichier. ");
        return NULL;
    }
    int capa = 3;
    Produit * stock = (Produit*)malloc(capa*sizeof(Produit));
    if (stock==NULL){
        printf("Erreur dans la création de tableau. ");
        fclose(file);
        return NULL;
    }
    int nbprod = 0;
    char category[Max_taille];
    char name[Max_taille];
    float price;
    int quantity;
    while(fscanf(file, "%s %s %f %d", category, name, &price, &quantity)== 4){
        if (nbprod >= capa){
            capa*=2;
            Produit *temp = realloc(stock, capa*sizeof(Produit));
            if(temp == NULL){
                printf("Erreur d'allocation. ");
                free(stock);
                fclose(file);
                return NULL;
            }
            stock = temp;
        }
        strcpy(stock[nbprod].Category, category);
        strcpy(stock[nbprod].Name, name);
        stock[nbprod].Price = price;
        stock[nbprod].Quantity = quantity;
        nbprod++;
    }
    fclose(file);
    return stock;
} 