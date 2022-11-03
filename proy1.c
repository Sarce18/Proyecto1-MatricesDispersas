#include <stdio.h>
#include "matriz.h"

int main() {
    FILE* Database = NULL;


    Matrix* M1 = InitMatrix(3, 3);
    Matrix* M2 = InitMatrix(3, 3);
    Matrix* M3 = InitMatrix(3, 3);

    printf("Este programa contiene tres matrices 3x3 inicializadas en cero que permitiran el uso de las funciones.");

    int opcion = -1;
    int selec, selec2 = -1;
    int i, j, e = -1;

    while (opcion != 0) {

        printf("\nIngrese lo que desea realizar\n");
        printf("1.- Crear una matriz\n");
        printf("2.- Obtener un elemento de una matriz\n");
        printf("3.- Asignar un elemento a una matriz\n");
        printf("4.- Imprimir una matriz\n");
        printf("5.- Hacer producto de un escalar por una matriz\n");
        printf("6.- Transponer una matriz\n");
        printf("7.- Sumar una matriz con otra\n");
        printf("8.- Obtener el producto de una matriz por otra\n");
        printf("0.- Salir del programa\n");
        scanf("%d", &opcion);


        if (opcion == 1) {
            printf("\nSeleccione la matriz que quiere crear\n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            scanf("%d", &selec);
            printf("\nSeleccione el modo en el que desea crear la matriz\n");
            printf("\n1.-Insertando una cantidad fija de elementos manualmente en posiciones deseadas\n");
            printf("\n2.-Insertando todos los elementos manualmente, incluyendo ceros\n");
            scanf("%d", &selec2);

            if (selec2 == 1) {
                if (selec == 1) M1 = GenMatrixSparce();
                else if (selec == 2) M2 = GenMatrixSparce();
                else printf("Seleccion invalida");
            }
            else if (selec2 == 2) {
                if (selec == 1) M1 = GenMatrixMan();
                else if (selec == 2) M2 = GenMatrixMan();
                else printf("Seleccion invalida");
            }
            else printf("Seleccion invalida");
        }
        else if (opcion == 2) {
            printf("\nSeleccione la matriz de la cual desea obtener un elemento; y la columna i, fila j en las que desea buscar. Recuerde que los puntos inician en 0,0\n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            printf("3.-Matriz 3\n");
            printf("matriz: ");
            scanf("%d", &selec);
            printf("i, j: \n");
            scanf("%d%d", &i, &j);

            if (selec == 1) printf("El elemento es: %d", ObtenerElemento(i, j, M1));

            else if (selec == 2)  printf("El elemento es: %d", ObtenerElemento(i, j, M2));

            else if (selec == 3) printf("El elemento es: %d", ObtenerElemento(i, j, M3));

            else printf("\nHa ingresado una opcion no valida.\n");
        }
        else if (opcion == 3) {
            printf("\nSeleccione la matriz a la cual le desea asignar un elemento; y la columna i, fila j en las que desea ingresarlo y el propio elemento. Recuerde que los puntos inician en 0,0\n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            printf("matriz: ");
            scanf("%d", &selec);
            printf("i, j, elemento: \n");
            scanf("%d%d%d", &i, &j, &e);

            if (selec == 1) {
                printf("\nMatriz anterior: \n");
                Imprimir(M1);
                AsignarElemento(i, j, e, M1);
                printf("\nMatriz Resultante: \n");
                Imprimir(M1);

            }
            else if (selec == 2) {
                printf("\nMatriz anterior: \n");
                Imprimir(M2);
                AsignarElemento(i, j, e, M2);
                printf("\nMatriz Resultante: \n");
                Imprimir(M2);
            }
            else printf("\nHa ingresado una opcion no valida.\n");

        }
        else if (opcion == 4) {
            printf("\nSeleccione la matriz que desea imprimir\n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            printf("3.-Matriz 3\n");
            printf("matriz: ");
            scanf("%d", &selec);
            if (selec == 1) Imprimir(M1);
            else if (selec == 2) Imprimir(M2);
            else if (selec == 3) Imprimir(M3);
            else printf("\nHa ingresado una opcion no valida.\n");
        }
        else if (opcion == 5) {
            printf("\nSeleccione la matriz que desea multiplicar por un escalar, ademas de dicho escalar. El resultado se guardara en la Matriz 3. \n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            printf("matriz: ");
            scanf("%d", &selec);
            printf("escalar: \n");
            scanf("%d", &e);

            if (selec == 1) {
                printf("\nMatriz anterior: \n");
                Imprimir(M1);
                M3 = ProductoPorEscalar(e, M1);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else if (selec == 2) {
                printf("\nMatriz anterior: \n");
                Imprimir(M1);
                M3 = ProductoPorEscalar(e, M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);

            }
            else printf("\nHa ingresado una opcion no valida.\n");
        }
        else if (opcion == 6) {
            printf("\nSeleccione la matriz que desea transponer. El resultado se guardara en la Matriz 3.\n");
            printf("1.-Matriz 1\n");
            printf("2.-Matriz 2\n");
            printf("matriz: ");
            scanf("%d", &selec);
            if (selec == 1) {
                printf("\nMatriz anterior: \n");
                Imprimir(M1);
                M3 = Transponer(M1);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else if (selec == 2) {
                printf("\nMatriz anterior: \n");
                Imprimir(M2);
                M3 = Transponer(M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else printf("\nHa ingresado una opcion no valida.\n");

        }
        else if (opcion == 7) {
            printf("Seleccione la suma que quiere realizar entre dos matrices. El resultado se guardara en la Matriz 3. ");
            printf("1.-Matriz 1 + Matriz 2\n");
            printf("2.-Matriz 2 + Matriz 2\n");
            printf("3.-Matriz 1 + Matriz 1\n");
            printf("matriz: ");
            scanf("%d", &selec);

            if (selec == 1) {
                printf("\nMatrices a sumar: \n");
                Imprimir(M1);
                printf("\n+\n");
                Imprimir(M2);
                M3 = Sumar(M1, M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else if (selec == 2) {
                printf("\nMatrices a sumar: \n");
                Imprimir(M2);
                printf("\n+\n");
                Imprimir(M2);
                M3 = Sumar(M2, M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);

            }
            else if (selec == 3) {
                printf("\nMatrices a sumar: \n");
                Imprimir(M1);
                printf("\n+\n");
                Imprimir(M1);
                M3 = Sumar(M1, M1);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else printf("\nHa ingresado una opcion no valida.\n");

        }
        else if (opcion == 8) {
            printf("\nSeleccione el producto que quiere realizar entre dos matrices. El resultado se guardara en la Matriz 3. \n");
            printf("1.-Matriz 1 * Matriz 2\n");
            printf("2.-Matriz 2 * Matriz 1\n");
            printf("3.-Matriz 1 * Matriz 1\n");
            printf("4.-Matriz 2 * Matriz 2\n");
            printf("matriz: ");
            scanf("%d", &selec);

            if (selec == 1) {
                printf("\nMatrices a multiplicar: \n");
                Imprimir(M1);
                printf("\n*\n");
                Imprimir(M2);
                M3 = Producto(M1, M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else if (selec == 2) {
                printf("\nMatrices a multiplicar: \n");
                Imprimir(M2);
                printf("\n*\n");
                Imprimir(M1);
                M3 = Producto(M2, M1);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else if (selec == 3) {
                printf("\nMatrices a multiplicar: \n");
                Imprimir(M1);
                printf("\n*\n");
                Imprimir(M1);
                M3 = Producto(M1, M1);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else  if (selec == 4) {
                printf("\nMatrices a multiplicar: \n");
                Imprimir(M2);
                printf("\n*\n");
                Imprimir(M2);
                M3 = Producto(M2, M2);
                printf("\nMatriz resultante: \n");
                Imprimir(M3);
            }
            else printf("\nHa ingresado una opcion no valida.\n");
        }
        else if (opcion == 0) printf("\nPrograma finalizado.\n");
        else printf("\nHa ingresado una opcion no valida.\n");

    }
    return 0;
}
