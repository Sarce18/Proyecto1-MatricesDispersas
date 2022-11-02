#ifndef HEAD_H_
#define HEAD_H_


typedef struct nodeX {
    int data;
    int column;
    struct nodeX* next;
} NodeX;

typedef struct nodeY {
    int pos;
    NodeX* row;
    struct nodeY* below;
} NodeY;

typedef struct matrix {
    int X, Y;
    NodeY* key;
} Matrix;

NodeY* GenNodeY(int pos);

NodeX* GenNodeX(int data, int column);

Matrix* InitMatrix(int X, int Y);

Matrix* GenMatrixMan(void);

//Devuelve el elemento de la fila i y la columna j de la matriz M.
int ObtenerElemento(int i, int j, Matrix* M);

// Asigna x al elemento de la fila i y la columna j de la matriz M.
void AsignarElemento(int i, int j, int x, Matrix* M);

// Devuelve la matriz resultante de sumar M1 y M2, las matrices M1 y M2 deben tener la misma dimensión
Matrix* Sumar(Matrix* M1, Matrix* M2);

//Devuelve la matriz resultante de multiplicar M1 por el escalar e.
Matrix* ProductoPorEscalar(int e, Matrix* M);

// Devuelve la matriz resultante de multiplicar M1 y M2, el número de columnas de M1 debe ser igual al número de filas de M2.La matriz resultante tiene el mismo número de filas de M1 y el mismo número de columnas de M2.
Matrix* Producto(Matrix* M1, Matrix* M2);

//Devuelve la transpuesta de M
Matrix* Transponer(Matrix* M);

//Muestra la matriz M
void Imprimir(Matrix* M);

//copia una matriz de una forma u otra dependiendo de donde se llame
Matrix* copyMatrix(Matrix* M);

#endif
