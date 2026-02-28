#ifndef __utils_H__
#define __utils_H__ 

#include <iostream>
#include <cmath>

#include "types.h"
#include "Rn.h"
#include "R3.h"

using value_type = Real;
#define PI 3.14159265358979323846

template <typename... Args>
Angle angle(const RnVector<Args ...>& v1, const RnVector<Args ...>& v2) {
    value_type dot_product = v1 * v2;
    value_type norms_product = v1.norm() * v2.norm();
    if (norms_product == 0) return 0; // Evita división por cero
    value_type cos_theta = dot_product / norms_product;
    //return std::acos(std::clamp(cos_theta, -1.0, 1.0)); // Asegura rango válido para acos
    return 180.0 * acos(cos_theta) / PI; // Retorna el ángulo en grados sexagesimales
}

R3 cartesian_to_spherical(const R3& cartesian) {
    Real x = cartesian.x();
    Real y = cartesian.y();
    Real z = cartesian.z();

    Real r = std::sqrt(x*x + y*y + z*z);
    Theta theta = std::acos(z / r); // Ángulo polar
    Phi phi = std::atan2(y, x);   // Ángulo azimutal

    return R3(r, theta, phi);
}


#endif // __utils_H__