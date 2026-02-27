#include <iostream>
#include "RnLibs.h"

using namespace std;

void RnVectorSpace() {
    // Aquí puedes implementar la lógica para el espacio vectorial Rn
    cout << "Implementando el espacio vectorial Rn..." << endl;
    RnVector v1(1, 1, 1); // Vector en R^3
    RnVector v2(-3, 2.71, 0.5); // vector en R^3

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


    // Ejemplo de operador de división por escalar sobrecargado
    RnVector v7 = v1 / 3.14; // División de v1 por escalar 2.0
    cout << "\nDivision de v1 / 3.14:" << endl;
    v7.printVector();

    // Ejemplo de método de norma de un vector
    Real norma = v1.norm();
    cout << "\nNorma de v1: " << norma << endl;

    // Ejemplo de ángulo entre 2 vectores
    RnVector v8(0,0,1);
    RnVector v9(0,1,0);
    Angle angulo = angle(v8, v9);
    cout << "\nAngulo entre v8 y v9: " << angulo << "deg" << endl;
    

    // Ejemplo de vector R3
    R3 r3_vector(1.0, 2.0, 3.0);
    cout << "\nVector R3:" << endl;
    r3_vector.printVector();

    // Ejemplo de vector R3
    R3 r3_vector2(4.0, 5.0, 6.0);
    cout << "\nVector2 R3:" << endl;
    r3_vector2.printVector();

    // Ejemplo de producto vectorial en R3
    R3 cross_product = r3_vector.cross(r3_vector2);
    cout << "\nProducto vectorial de r3_vector y r3_vector2:" << endl;
    cross_product.printVector();

    // Ejemplo de vector unitario en R3
    R3 unit_vector = r3_vector.unit_vector();
    cout << "\nVector unitario de r3_vector:" << endl;
    unit_vector.printVector();
    cout << "\nNorma del vector unitario: " << unit_vector.norm() << endl; // Debería ser 1.0   

    // Ejemplo de vector unitario en Rn (con dimensión arbitraria)
    RnVector v10(5,-6,1,5,2.71); // Vector en R^5
    cout << "\nVector en R^5:" << endl;
    v10.printVector();
    RnVector unit_vector_5d = v10.unit_vector();
    cout << "\nVector unitario en R5, v10:" << endl;
    unit_vector_5d.printVector();
    cout << "\nNorma del vector unitario: " << unit_vector_5d.norm() << endl; // Debería ser 1.0   

    // Ejemplo de vector en R2
    R2 r2_vector(3.0, 4.0);
    cout << "\nVector R2:" << endl;
    r2_vector.print();
    cout << "\nNorma del vector R2: " << r2_vector.norm() << endl; // Debería ser 5.0
    cout << "\nVector unitario de r2_vector:" << endl;
    R2 unit_vector_r2 = r2_vector.unit_vector();
    unit_vector_r2.print();
    cout << "\nNorma del vector unitario R2: " << unit_vector_r2.norm() << endl; // Debería ser 1.0
}