#include <iostream>
#include "Rn.h"
#include "types.h"

using namespace std;

void RnVectorSpace() {
    // Aquí puedes implementar la lógica para el espacio vectorial Rn
    cout << "Implementando el espacio vectorial Rn..." << endl;
    RnVector v1(0.15, 1.2, 3.14); // Vector en R^3
    RnVector v2(-3, 2.71, 0.5); // Otro vector en R^3

    cout << "\nImprimiendo usando printVector():" << endl;
    v1.printVector();
    v2.printVector();

    cout << "\nImprimiendo usando printVector2():" << endl;  
    v1.printVector2();
    v2.printVector2();

    cout << "\nImprimiendo usando printVector3():" << endl;  
    v1.PrintVector3();
    v2.PrintVector3();

    // Ejemplo de operador de suma sobrecargado
    RnVector v3 = v1 + v2; // Suma de dos vectores v1 & v2
    cout << "\nSuma de v1 + v2:" << endl;
    v3.printVector();

    // Ejemplo de operador de resta sobrecargado
    RnVector v4 = v1 - v2; // Resta de dos vectores v1 & v2
    cout << "\nResta de v1 - v2:" << endl;
    v4.printVector();

    // Ejemplo de operador de multiplicación por escalar sobrecargado
    RnVector v5 = v1 * 2.0; // Multiplicación de v1 por escalar 2.0
    cout << "\nMultiplicacion de v1 * 2.0:" << endl;
    v5.printVector();

    // Ejemplo de operador de multiplicación por escalar sobrecargado
    RnVector v6 = 2.0 * v1; // Multiplicación de escalar 2.0 por vector v1
    cout << "\nMultiplicacion de 2.0 * v1:" << endl;
    v6.printVector();

    // Ejemplo de operador de multiplicación escalar de 2 vectores
    Real prod_escalar = v1 * v2; // Producto interno entre vectores v1 & v2
    cout << "\nProducto interno de v1 * v2: " << prod_escalar << endl;

}