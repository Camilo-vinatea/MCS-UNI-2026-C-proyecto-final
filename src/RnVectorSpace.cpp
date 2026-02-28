#include <iostream>
#include <memory>
#include "RnLibs.h"

using namespace std;


void RnVectorSpace() {
    // Aquí puedes implementar la lógica para el espacio vectorial Rn
    cout << "Implementando el espacio vectorial Rn..." << endl;
    RnVector v1(1, 1, 1); // Vector en R^3
    RnVector v2(-3, 2.71, 0.5); // vector en R^3

    cout << "\nImprimiendo usando sobrecarga de operador <<:" << endl;
    cout << v1 << endl;
    cout << v2 << endl;


    // Ejemplo de operador de suma sobrecargado
    RnVector v3 = v1 + v2; // Suma de dos vectores v1 & v2
    cout << "\nSuma de v1 pero+ v2:" << endl;
    cout << v3 << endl;

    // Ejemplo de operador de resta sobrecargado
    RnVector v4 = v1 - v2; // Resta de dos vectores v1 & v2
    cout << "\nResta de v1 - v2:" << endl;
    cout << v4 << endl;

    // Ejemplo de operador de multiplicación por escalar sobrecargado
    RnVector v5 = v1 * 2.0; // Multiplicación de v1 por escalar 2.0
    cout << "\nMultiplicacion de v1 * 2.0:" << endl;
    cout << v5 << endl;

    // Ejemplo de operador de multiplicación por escalar sobrecargado
    RnVector v6 = 2.0 * v1; // Multiplicación de escalar 2.0 por vector v1
    cout << "\nMultiplicacion de 2.0 * v1:" << endl;
    cout << v6 << endl;

    // Ejemplo de operador de multiplicación escalar de 2 vectores
    Real prod_escalar = v1 * v2; // Producto interno entre vectores v1 & v2
    cout << "\nProducto interno de v1 * v2: " << prod_escalar << endl;


    // Ejemplo de operador de división por escalar sobrecargado
    RnVector v7 = v1 / 3.14; // División de v1 por escalar 2.0
    cout << "\nDivision de v1 / 3.14:" << endl;
    cout << v7 << endl;

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
    cout << r3_vector << endl; // Usando operador << sobrecargado

    // Ejemplo de vector R3
    R3 r3_vector2(4.0, 5.0, 6.0);
    cout << "\nVector2 R3:" << endl;
    cout << r3_vector2 << endl;

    // Ejemplo de producto vectorial en R3
    R3 cross_product = r3_vector.cross(r3_vector2);
    cout << "\nProducto vectorial de r3_vector y r3_vector2:" << endl;
    cout << cross_product << endl;

    // Ejemplo de vector unitario en R3
    R3 unit_vector = r3_vector.unit_vector();
    cout << "\nVector unitario de r3_vector:" << endl;
    cout << unit_vector << endl;
    cout << "\nNorma del vector unitario: " << unit_vector.norm() << endl; // Debería ser 1.0   

    // Ejemplo de vector unitario en Rn (con dimensión arbitraria)
    RnVector v10(5,-6,1,5,2.71); // Vector en R^5
    cout << "\nVector en R^5:" << endl;
    cout << v10 << endl;
    RnVector unit_vector_5d = v10.unit_vector();
    cout << "\nVector unitario en R5, v10:" << endl;
    cout << unit_vector_5d << endl;
    cout << "\nNorma del vector unitario: " << unit_vector_5d.norm() << endl; // Debería ser 1.0   

    // Ejemplo de vector en R2
    R2 r2_vector(3.0, 4.0);
    cout << "\nVector R2:" << endl;
    cout << r2_vector << endl;
    cout << "\nNorma del vector R2: " << r2_vector.norm() << endl; // Debería ser 5.0
    cout << "\nVector unitario de r2_vector:" << endl;
    R2 unit_vector_r2 = r2_vector.unit_vector();
    cout << unit_vector_r2 << endl;
    cout << "\nNorma del vector unitario R2: " << unit_vector_r2.norm() << endl; // Debería ser 1.0

    // Ejemplo de sobrecarga de operador << para imprimir vector Rn en OStream
    cout << "\nImprimiendo v1 usando operador << sobrecargado:" << endl;
    cout << v1 << endl;

    // Ejemplo de arreglo de punteros apuntando a diferentes vectores en Rn con distintas dimensiones
    constexpr int size = 13;
    unique_ptr<RnBase> vectors[size];

    vectors[0] = make_unique<decltype(v1)>(v1); // RnVector en R3
    vectors[1] = make_unique<decltype(v2)>(v2); // RnVector en R3
    vectors[2] = make_unique<decltype(v3)>(v3); // RnVector en R3
    vectors[3] = make_unique<decltype(v4)>(v4); // RnVector en R3
    vectors[4] = make_unique<decltype(v5)>(v5); // RnVector en R3
    vectors[5] = make_unique<decltype(v6)>(v6); // RnVector en R3
    vectors[6] = make_unique<decltype(v7)>(v7); // RnVector en R3
    vectors[7] = make_unique<decltype(v8)>(v8); // RnVector en R3
    vectors[8] = make_unique<decltype(v9)>(v9); // RnVector en R3  
    vectors[9] = make_unique<decltype(v10)>(v10); // RnVector en R5
    vectors[10] = make_unique<decltype(r3_vector)>(r3_vector); // R3
    vectors[11] = make_unique<decltype(r3_vector2)>(r3_vector2); // R3
    vectors[12] = make_unique<decltype(r2_vector)>(r2_vector); // R2    

    cout << "\nImprimiendo vector desde arreglo de punteros a RnBase:" << endl;
    for (auto& vec : vectors)
        cout << "Vector: " << *vec << endl; // Llama al operador << sobrecargado, que a su vez llama a printVectorToOstream()

    // Ejemplo de conversión entre coordenadas cartesianas y esféricas
    R3 r3_vector3 (0, 0, -1);
    cout << "\nVector R3 para conversion a coordenadas esfericas:" << r3_vector3 << endl;;
    R3Polar r3_vector3_polar = R3Polar::fromCartesian(r3_vector3);
    cout << "Vector R3 convertido a coordenadas esfericas:" << r3_vector3_polar << endl;

}