#include <stdio.h>
#include "head.h"

int main() {

    Matrix* m1;
    Matrix* m2;
    Matrix* m3;


    int opcion = -1;
    while (opcion != 0)
    {
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
        int op = -1;
        int e = -1;

        switch (opcion)
        {
        case 1:
            printf("\nIngrese la matriz que quiere declarar\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            scanf("%d", &op);
            if (op == 1)
                m1 = GenMatrixMan();
            else if (op == 2)
                m2 = GenMatrixMan();
            break;
        case 2:
            printf("\nIngrese la matriz de la cual desea obtener el elemento\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            scanf("%d", &op);
            printf("\nIngrese la posicion (X,Y) que desea obtener\n");
            int X, Y;
            scanf("%d%d", &X, &Y);
            if (op == 1)
                e = ObtenerElemento(Y, X, m1);
            else if (op == 2)
                e = ObtenerElemento(Y, X, m2);
            printf("el elemento es: %d", e);
            break;
        case 3:
            printf("\nIngrese la matriz a la cual desea ingresar un elemento\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            scanf("%d", &op);
            printf("Ingrese el elemento que quiere asignar, y la posicion (x,y) en el que lo desea asignar");
            int x, y;
            scanf("%d%d%d", &x, &y, &e);
            if (op == 1)
                AsignarElemento(y, x, e, m1);
            else if (op == 2)
                AsignarElemento(y, x, e, m2);
            break;
        case 4:
            printf("\nIngrese la matriz que desea imprimir\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            printf("3.- Matriz 3\n");
            scanf("%d", &op);
            if (op == 1)
                Imprimir(m1);
            else if (op == 2)
                Imprimir(m2);
            else if (op == 3)
                Imprimir(m3);
            break;
        case 5:
            printf("\nIngrese la matriz la cual desea multiplicar por un escalar. Se guardara en Matriz 3\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            scanf("%d", &op);
            printf("Ingrese el escalar con el que quiere multiplicar la matriz");
            scanf("%d", &e);
            if (op == 1)
                m3 = ProductoPorEscalar(e, m1);
            else if (op == 2)
                m3 = ProductoPorEscalar(e, m2);
            break;
        case 6:
            printf("\nIngrese la matriz que desea transponer. Se guardara en Matriz 3\n");
            printf("1.- Matriz 1\n");
            printf("2.- Matriz 2\n");
            scanf("%d", &op);
            if (op == 1)
                m3 = Transponer(m1);
            else if (op == 2)
                m3 = Transponer(m2);
            break;
        case 7:
            printf("\nSe sumara la matriz m1 + m2, y se asignara en m3. esta deauerdo? 1:si; 2: no\n");
            scanf("%d", &op);
            if (op == 1)
                m3 = Sumar(m1, m2);
            break;
        case 8:
            printf("\nIngrese el orden con el que quiere multiplicar las matrices m1 y m2. Se asignara el resultado a Matriz 3\n");
            printf("1.- m1 * m2\n");
            printf("2.- m2 * m1\n");
            scanf("%d", &op);
            if (op == 1)
                m3 = Producto(m1, m2);
            if (op == 2)
                m3 = Producto(m2, m1);
            break;
        case 0:
            printf("gracias por usar el programa!");
            break;

        default:
            printf("se ha ingresado una opcion no valida. intente de nuevo. \n\n");
            break;
        }
    }

    return 0;
}
