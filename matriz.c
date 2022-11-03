#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

typedef struct nodeX NodeX;

typedef struct nodeY NodeY;

typedef struct matrix Matrix;

NodeY* GenNodeY(int pos) {
    NodeY* Newnode;
    Newnode = (NodeY*)malloc(sizeof(NodeY));
    Newnode->pos = pos;
    Newnode->below = NULL;
    Newnode->row = NULL;
    return Newnode;
}

NodeX* GenNodeX(int data, int column) {
    NodeX* Newnode;
    Newnode = (NodeX*)malloc(sizeof(NodeX));
    Newnode->data = data;
    Newnode->column = column;
    Newnode->next = NULL;
    return Newnode;
}

inline Matrix* InitMatrix(int X, int Y) {
    //Se  le da la memoria necesaria al puntero de matrix, y se inicializa su tamanio y llave/puntero a la matriz.
    Matrix* M = (Matrix*)malloc(sizeof(Matrix));
    M->key = NULL;
    M->X = X; M->Y = Y;
    return M;
}

Matrix* GenMatrixSparce(void) {
    Matrix* M;
    int X, Y, x, y, cant, e;
    printf("\nIngrese el orden de filas y columnas que desea en la matriz\n");
    scanf("%d%d", &Y, &X);
    M = InitMatrix(X, Y);
    printf("Ingrese la cantidad de elementos que desea ingresar.\n");
    scanf("%d", &cant);
    printf("Ahora ingrese los elementos que desea en la matriz en el formato 'i,j,elemento'. Tome en cuenta que las coordenadas inician en 0,0\n");
    for (int i = 1; i <= cant; i++) {
        printf("Elemento numero %d\n", i);
        scanf("%d%d%d", &y, &x, &e);
        AsignarElemento(y, x, e, M);
    }

    printf("\nMatriz creada: \n");
    Imprimir(M);

    return M;
}

Matrix* GenMatrixMan(void) {
    Matrix* M = (Matrix*)malloc(sizeof(Matrix));
    M->key = NULL;
    M->X = M->Y = 0; //El tamanio de la matriz se inicializa en 0,0

    printf("\nIngrese el tamanio que desea de la matriz, primero columnas y despues filas.\n");

    scanf("%d %d", &M->X, &M->Y);

    //Se verifica si el tamanio ingresado es mas que 0x0, o 0xn, que son iguales en el sentido que son adimencionales

    if (M->X > 0 && M->Y > 0) {
        NodeY* rowlist = NULL;
        NodeY* rowHead = NULL;
        //La lista de filas se crea usando M.Y como referencia
        for (register int i = 0; i < M->Y; i++) {
            NodeX* column = NULL;
            NodeX* columhead = NULL;

            //Se crean las columnas
            for (register int j = 0; j < M->X;j++) {
                int n;
                printf("\ningrese el valor de la fila %d, columna %d, [%d,%d]\n", i, j, i, j);
                scanf("%d", &n);

                //Se verifica que "n" es diferene que 0 para crear el nodo. Si es 0, no se crea.
                if (n != 0) {
                    //Si no existe ninguna columna creada para el momento, se crea su primera referencia y se guarda en un auxiliar. Si no, se crea al lado de la ultima columna actual.
                    if (columhead == NULL) {
                        column = GenNodeX(n, j);
                        columhead = column;
                    }
                    else {
                        column->next = GenNodeX(n, j);
                        column = column->next;
                    }
                }
            }
            //Se verifica si la columna creada es nula, es decir, si estan llenas de ceros.
            if (columhead != NULL) {
                //Como con las columnas, se verifica si el actual es el primer elemento de las filas.
                if (rowHead == NULL) {
                    rowlist = GenNodeY(i);
                    rowlist->row = columhead;
                    rowHead = rowlist;
                }
                else {
                    rowlist->below = GenNodeY(i);
                    rowlist = rowlist->below;
                    rowlist->row = columhead;
                }
            }
        }


        //Una vez las filas y columnas son creadas, se verifica si existe al menos una fila (y por tanto al menos una columna o elemento), es decir, si no es nula.
        if (rowHead != NULL)
            M->key = rowHead;
    }

    printf("\nMatriz creada: \n");
    Imprimir(M);

    return M;
}

int ObtenerElemento(int i, int j, Matrix* M) {

    //se verifica si las coordenadas dadas existen en M

    if (i > M->Y || j > M->X) {
        printf("\nlas coordenadas ingresadas son mayores a las dimensiones de la matriz y por ello no se puede encontrar el elemento. Se va a retornar cero.");
        return 0;
    }

    if (i < 0 || j < 0) {
        printf("\nlas coordenadas ingresadas son menores a cero, y la estructura no soporta indices negativos. Se va a retornar 0");
        return 0;
    }

    //se verifica si la lista es nula, o el primer nodoY tiene una posicion mayor a la "i" buscada, por lo que no existe, y por tanto se sabe que es cero. Se retorna 0.
    if (M->key == NULL || M->key->pos > i)
        return 0;

    NodeY* Yauxp = M->key;

    //se recorre unicamente hasta que la posicion del siguiente de las filas sea menor a la buscada, o bien, no se encuentra ningun elemento mayor aun habiendo recorrido todos (se vuelve nulo)

    int k = 0;
    while ((Yauxp) && (Yauxp->pos < i)) {
        Yauxp = Yauxp->below;
        k++;
    }



    //se ha recorrido hasta el punto que se supone debe estar detras de la fila buscada. Se verifica, en orden:

      //si el nodo Yauxp existe, pero su posicion es mayor a la deseada (i)

      //si el nodo es nulo (se llego al final de la lista de filas), pero se contaron una cantidad k de elementos menor al total de filas posibles dadas por M.Y

    if ((Yauxp && Yauxp->pos > i) || (!Yauxp && k < M->Y)) {
        return 0;
    }
    else { // sino, se sabe que el elemento siguiente es aquella fila buscada
        k = 0;
        NodeX* Auxp = Yauxp->row;
        // se realiza el mismo procedimiento de verificación con las columnas que con las filas, saltandose la revisión nula, pues ya se sabe que existe al menos un elemento por el funcionamiento de la estructura

        if (Auxp->column > j)
            return 0;

        while ((Auxp) && (Auxp->column < j)) {
            Auxp = Auxp->next;
            k++;
        }

        if ((Auxp && Auxp->column > j) || (!Auxp && k < M->X))
            return 0;
        else
            return Auxp->data;
    }

}

void AsignarElemento(int i, int j, int x, Matrix* M) {
    //se verifica si las coordenadas ingresadas son coherentes con la matriz.
    if (i >= M->Y || j >= M->X) return;
    //existen distintos casos para poder ingresar un elemento
    // la matriz es nula.
    if (!M->key) {
        //No existe matriz alguna y se quiere ingresar un cero. no se retorna nada.
        if (x == 0) return;
        // el elemento no es cero. se crea una primera fila y columna con el elemento a ingresar.
        M->key = GenNodeY(i);
        M->key->row = GenNodeX(x, j);
        return;
    }

    //-------------------La matriz no es nula.------------------------//


    //se verifica si se quiere eliminar la primera fila

    //se debe verificar la fila que se quiere ubicar

    NodeY* Yauxp = M->key;



    // el primer nodo de la matriz es mayor a la posicion buscada
    if (Yauxp->pos > i) {
        if (x != 0) {
            NodeY* NewNode = GenNodeY(i);
            NewNode->row = GenNodeX(x, j);
            NewNode->below = Yauxp;
            Yauxp->below = NULL;
            M->key = NewNode;
        }
        return;
    }


    //se recorre la lista y se guarda la referencia al anterior en caso de que se quiera ingresar un cero y se deba eliminar y reconectar nodos.
    NodeY* AntYaux = Yauxp;
    while ((Yauxp->below) && (Yauxp->below->pos <= i)) {
        AntYaux = Yauxp;
        Yauxp = Yauxp->below;
    }

    //no se quiere ingresar cero.
    if (x != 0) {
        //El nodo de fila no existe pero su posicion es mayor a la ultima fila actual
        if (!Yauxp->below && Yauxp->pos != i) {

            Yauxp->below = GenNodeY(i);
            Yauxp->below->row = GenNodeX(x, j);
            return;
        }

        //el nodo de fila no existe pero su posicion se encuentra entre varios nodos.

        if (Yauxp->pos < i) {
            NodeY* NewNode = GenNodeY(i);
            NewNode->row = GenNodeX(x, j);
            NewNode->below = Yauxp->below;
            Yauxp->below = NewNode;
            return;
        }
    }
    else return;


    //el nodo de fila existe, y por lo tanto existe al menos una columna

    //----------sector de las columnas --------//

    NodeX* Xauxp = Yauxp->row;

    //la primera columna es mayor a la buscada
    if (Xauxp->column > j) {
        if (x != 0) {
            NodeX* NewNode = GenNodeX(x, j);
            NewNode->next = Xauxp;
            Yauxp->row = NewNode;
        }
        return;
    }

    //se recorre la lista y se guarda la referencia al anterior en caso de ser necesario.
    NodeX* AntXaux = Xauxp;
    while ((Xauxp->next) && (Xauxp->next->column <= j)) {
        AntXaux = Xauxp;
        Xauxp = Xauxp->next;
    }


    if (x != 0) {
        //Existe la fila, y tambien la columna. Solamente se cambia el valor.
        if (Xauxp->column == j) {
            Xauxp->data = x;
            return;
        }
        //nodo de columna no existe pero su posicion es mayor a la ultima fila actual
        if (!Xauxp->next && Xauxp->column != j) {

            Xauxp->next = GenNodeX(x, j);
            return;
        }
        //nodo de columna no existe pero su posicion se encuentra entre varios nodos.
        if (Xauxp->column < j) {
            NodeX* NewNode = GenNodeX(x, j);
            NewNode->next = Xauxp->next;
            Xauxp->next = NewNode;
            return;
        }
    }
    else { // caso contrario, se quiere ingresar un cero.

        //Se verifica si se quiere eliminar la primera fila
        //Se verifica si la columna actual es la que se esta buscando
        if (Xauxp->column == j) {
            //Se verifica si Solo existe una columna en la fila actual
            if (Xauxp == AntXaux) {
                //Se verifica si la fila actual es la unica aexistente
                if (Yauxp == M->key) {
                    //Se libera la fila y su columna.
                    free(Xauxp);
                    free(M->key);
                    M->key = NULL;
                    return;
                }
                else { //Existe mas de una fila. Se elimina la columna, se reconectan los nodos y se elimina la fila.
                    free(Xauxp);
                    AntYaux->below = Yauxp->below;
                    free(Yauxp);
                    return;
                }
            } //Existe mas de una columna en la fila.
            else {
                //se reconectan los nodos y se elimina la columna.
                AntXaux->next = Xauxp->next;
                free(Xauxp);
                return;
            }
        }
    }
    return;
}

void Imprimir(Matrix* M) {

    //Si no existe referencia a una fila, entonces es una matriz nula y se imprime una cantidad X*Y de ceros.
    if (M->key == NULL) {
        for (register int i = 0; i < M->Y; i++) {
            for (register int j = 0; j < M->X; j++)
                printf("%4d", 0);
            printf("\n");
        }
        return;
    }

    NodeY* Y = M->key;
    int upper = -1;

    while (Y) {
        int gap = 0;
        NodeX* X = Y->row;
        //Se verifica si el espacio (gap) entre upper y below es mas de uno (por ejemplo, 5-3 =2, por lo que existe un espacio. 4-3 = 1, no hay espacio).
        //Si existe un gap, se imprimen tantos ceros como sean necesarios.
        if ((gap = Y->pos - upper) > 1) {
            for (register int i = 1; i < gap; i++) {
                for (register int j = 0; j < M->X; j++)
                    printf("%4d", 0);
                printf("\n");
            }
        }

        //se imprimen las columnas
        int Xlast = -1;
        while (X) {
            int Xgap = 0;

            //se verifica si existe un gap o Cero en la matriz
            if ((Xgap = X->column - Xlast) > 1) {
                for (register int i = 1; i < Xgap; i++)
                    printf("%4d", 0);
            }


            Xlast = X->column;
            printf("%4d", X->data);
            X = X->next;
        }

        //no se conoce si existen columnas después de la actual, por lo que se verifica al final de la linea

        if (Xlast += 1 < M->X)
            for (register int i = Xlast; i < M->X; i++)
                printf("%4d", 0);

        printf("\n");
        upper = Y->pos;
        Y = Y->below;
    }

    // no se conoce si existen filas por debajo de la actual, por lo que se verifica finalmente

    if (upper += 1 < M->Y)        //se suma uno al contarse desde el 0
        for (register int i = upper; i < M->Y; i++) {
            for (register int j = 0; j < M->X; j++)
                printf("%4d", 0);
            printf("\n");
        }
}

Matrix* copyMatrix(Matrix* M) {

    //Se inicializa la matriz con los tamaños que se quiere copiar
    Matrix* NewM = InitMatrix(M->X, M->Y);
    NodeY* Yaux = M->key;

    //se recorre cada nodo y se asigna el elemento con las coordenadas indicadas y el dato del nodo.
    while (Yaux) {
        NodeX* Xaux = Yaux->row;
        while (Xaux)
        {
            AsignarElemento(Yaux->pos, Xaux->column, Xaux->data, NewM);
            Xaux = Xaux->next;
        }
        Yaux = Yaux->below;
    }

    return NewM;
}

Matrix* ProductoPorEscalar(int e, Matrix* M) {
    //Se inicializa una nueva matriz
    Matrix* NewM = InitMatrix(M->X, M->Y);

    //Se verifica si se multiplica una matriz por cero o la matriz multiplicada es nula, siendo ambos casos en los que el resultado sera una matriz nula, por lo que se devuelve directamente
    if (!e || !M->key)
        return NewM;

    NodeY* Yaux = M->key;

    //Se recorre la matriz, y el dato enviado se multiplica por "e", el escalar.
    while (Yaux) {
        NodeX* Xaux = Yaux->row;
        while (Xaux) {
            AsignarElemento(Yaux->pos, Xaux->column, Xaux->data * e, NewM);
            Xaux = Xaux->next;
        }
        Yaux = Yaux->below;
    }
    return NewM;
}

Matrix* Transponer(Matrix* M) {


    Matrix* NewM = InitMatrix(M->Y, M->X);

    //Caso 0: la matriz esta vacia, por lo que su traspuesta es identica, solo que con las columnas y filas cambiadas.
    if (!M->key)
        return NewM;


    NodeY* Yaux = M->key;

    //Se copia la matriz, pero intercambiando la posicion en X con la de Y, es decir, la posicion de las filas con la de las columnas.
    while (Yaux) {
        NodeX* Xaux = Yaux->row;
        while (Xaux) {
            AsignarElemento(Xaux->column, Yaux->pos, Xaux->data, NewM);
            Xaux = Xaux->next;
        }
        Yaux = Yaux->below;
    }
    return NewM;

}

Matrix* Sumar(Matrix* M1, Matrix* M2) {
    //se verifica si las matrices son del mismo tamanio

    if (M1->X != M2->X && M1->Y != M2->Y) {
        printf("las matrices no son del mismo tamanio. Se retornara nulo.");
        return NULL;
    }

    //Las matrices son iguales. Se declara la nueva matriz con el tamanio de ambos y con una llave apuntando a nulo.
    Matrix* M3 = (Matrix*)malloc(sizeof(Matrix));
    M3->X = M1->X;
    M3->Y = M2->Y;
    M3->key = NULL;

    //Caso 1: Una de las matrices es nula.

    if (!M1->key || !M2->key)
        return (M1->key ? copyMatrix(M1) : copyMatrix(M2));

    //Caso 2: Las matrices no son nulas, 


    NodeY* Yaux1 = M1->key;
    NodeY* Yaux2 = M2->key;


    while (Yaux1 && Yaux2) {
        if (Yaux1->pos == Yaux2->pos) {// son la misma fila, por lo que se puede operar en ellas
            NodeX* Xaux1 = Yaux1->row;
            NodeX* Xaux2 = Yaux2->row;

            while (Xaux1 && Xaux2)
            {
                if (Xaux1->column == Xaux2->column) {
                    int data = Xaux1->data + Xaux2->data;
                    if (data != 0) {
                        AsignarElemento(Yaux1->pos, Xaux1->column, data, M3);
                    }
                    Xaux1 = Xaux1->next;
                    Xaux2 = Xaux2->next;
                }
                else {
                    //Se verifica cual es el que tiene la menor posicion, lo que permite conocer cual se debe copiar en la nueva matriz.
                    NodeX* MinorXaux = Xaux1->column < Xaux2->column ? Xaux1 : Xaux2;
                    AsignarElemento(Yaux1->pos, MinorXaux->column, MinorXaux->data, M3);
                    if (MinorXaux == Xaux1) Xaux1 = Xaux1->next;
                    else Xaux2 = Xaux2->next;
                }
            }
            if (Xaux1 || Xaux2) { //Se verifica si aun existe un Xaux "no nulo"
                for (NodeX* RemXaux = Xaux1 ? Xaux1 : Xaux2; RemXaux; RemXaux = RemXaux->next) //Si existe, se realiza un loop que recorrera el Xaux existente, asignandole este a RemXaux al preguntar si existe Xaux; si existe, se le asigna, si no, por descarte existe Xaux2, y se le asigna.
                    AsignarElemento(Yaux1->pos, RemXaux->column, RemXaux->data, M3);
            }
            Yaux1 = Yaux1->below;
            Yaux2 = Yaux2->below;
        }
        else { //Al igual que con las columnas, se verifica el Yaux con la menor posicion, que permite conocer cual se debe copiar en la nueva matriz.
            NodeY* MinorYaux = Yaux1->pos < Yaux2->pos ? Yaux1 : Yaux2;
            for (NodeX* Xaux = MinorYaux->row; Xaux; Xaux = Xaux->next)
                AsignarElemento(MinorYaux->pos, Xaux->column, Xaux->data, M3);
            if (MinorYaux == Yaux1) Yaux1 = Yaux1->below;
            else Yaux2 = Yaux2->below;
        }
    }
    //Al igual que con los auxiliares Xaux, se verifica si sigue existiendo algun Yaux y se aplica la misma logica, recorriendo cada fila y columna restante para copiarla en la nueva matriz M3.
    if (Yaux1 || Yaux2)
        for (NodeY* RemYaux = Yaux1 ? Yaux1 : Yaux2; RemYaux; RemYaux = RemYaux->below)
            for (NodeX* Xaux = RemYaux->row; Xaux; Xaux = Xaux->next)
                AsignarElemento(RemYaux->pos, Xaux->column, Xaux->data, M3);


    return M3;
}

Matrix* Producto(Matrix* M1, Matrix* M2) {
    //se verifica si las columnas de M1 son iguales a las filas de M2

    if (M1->X != M2->Y) {
        printf("Las columnas de la primera matriz no son iguales a las filas de la segunda. se va a retornar nulo.");
        return 0;
    }

    Matrix* M3 = InitMatrix(M2->X, M1->X);


    //Caso 0: Una de las matrices es nula, por lo que su multiplicacion es nula
    if (!M1->key || !M2->key)
        return M3;

    // Caso 1: Ninguna matriz es nula, se debe proceder a multiplicar

    NodeY* Yaux1 = M1->key;

    //se crea un arreglo de auxiliares con la segunda matriz para lograr un acceso comodo a traves de columnas.

    // primero se cuenta la cantidad de columnas que tiene la segunda matriz
    int Cont = 0;

    for (NodeY* aux = M2->key; aux; aux = aux->below)
        Cont++;


    NodeY* HeadColumnaux[Cont];

    // se inicializa el arreglo Headcolumnaux con todas las filas de la segunda matriz para poder tener la referencia a todas las primeras posiciones, pues se necesita usar varias veces.

    {
        NodeY* Aux = M2->key;
        for (register int k = 0; k < Cont; k++) {
            HeadColumnaux[k] = Aux;
            Aux = Aux->below;

        }
    }

    //se inicializan dos variables que van a representar la posicion en la nueva matriz M3
    int X = 0;
    int Y = 0;

    while (Yaux1) {
        NodeX* Columnaux[Cont]; // se inicializan las columnas cada vez que se necesita acceder a las columnas de M2
        for (register int k = 0; k < Cont; k++)
            Columnaux[k] = HeadColumnaux[k]->row;

        //Se inicializa un puntero a la cabeza de la fila actual de Yaux, es decir, de las filas de M1
        NodeX* HeadXaux1 = Yaux1->row;

        //Se inicializa un Xaux con HeadAux para no modificar este ultimo
        NodeX* Xaux1 = HeadXaux1;

        //Se verifica si la posicion actual de filas de M1 es igual a su posicion actual en Y, esto es, porque si existe una disparidad, la fila actual de M1 es nula, y una fila nula siempre crea otra fila nula en su producto.
        if (Yaux1->pos == Y) {

            //Mientras no se rellenen todas las columnas de la matriz producto M3, no se va a dejar de ejecutar
            while (X < M3->X) {
                int i = 0;
                int Value = 0;

                //Se recorre columna por columna la primera matriz
                while (Xaux1)
                {
                    //Se verifica que se esten multiplicando correctamente las filas con las columnas correspondientes
                    if (Xaux1->column == HeadColumnaux[i]->pos && Columnaux[i]->column == X) {
                        //Si se corresponden, se acumula el multiplo de cada nodo y se recorren
                        Value += Xaux1->data * Columnaux[i]->data;
                        i++;
                        Xaux1 = Xaux1->next;
                        //Dado caso que no se correspondan, se avanza una de las dos dependiendo de cual esta atrasada.
                    }
                    else if (Xaux1->column > HeadColumnaux[i]->pos) {
                        i++;
                    }
                    else Xaux1 = Xaux1->next;

                }
                //Finalmente hechas todas las multiplicaciones, se asigna el elemento X,Y con el valor acumulado a M3
                AsignarElemento(Y, X, Value, M3);
                //se retorna al inicio de la fila actual usando la referencia guardada en HeadXaux1
                Xaux1 = HeadXaux1;
                X++;
                //se recorre en una columna todas las filas guardadas en el arreglo, unicamente si son congruente posicion Yaux1 actual (filas de M1).
                for (register int j = 0; j < Cont; j++) {
                    if (Columnaux[j]->next && Columnaux[j]->column <= Yaux1->pos)
                        Columnaux[j] = Columnaux[j]->next;
                }
            }
            //Una vez terminada la primera fila de M1, se pasa a la segunda y se reinicia el contador de X, repitiendo el ciclo.
            Yaux1 = Yaux1->below;
            X = 0;
        }
        //Se aunenta el contador de Y al aberse terminado de crear la primera fila de M3
        Y++;
    }
    return M3;
}