#include <stdio.h>
#include "stock.h"

int main() {
    
    int choice;
    printf("1. Client ");
    printf("2. Administrateur ");
    printf("3. Quitter ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Pas fini mais voici le mode client. ");
            break;
        case 2:
            printf("Pas fini mais voici le mode administrateur. ");
            break;
        case 3:
            printf("Fin de la simulation. ");
            return 0;
            break;
    }
}
