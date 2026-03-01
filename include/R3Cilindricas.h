#ifndef __R3CILINDRICAS_H__
#define __R3CILINDRICAS_H__

#include <cmath>
#include <iostream>
#include "types.h"
#include "R3.h"

class R3Cilindricas {
public:
    // Aquí puedes implementar la clase R3Cilindricas con sus métodos y atributos
    explicit R3Cilindricas(Radius r, Theta theta, Z z) : r_(r), theta_(theta), z_(z) {
    if (r < 0)
        throw std::invalid_argument("El radio no puede ser negativo");
    }

    // Accesores
    Radius  r()     const { return r_; }
    Theta   theta() const { return theta_; }
    Z       z()     const { return z_; }

    // Conversión a cartesianas (R3)
    R3 toCartesian() const {
        return R3(
            r_ * cos(theta_),       // x
            r_ * sin(theta_),       // y
            z_                      // z
        );
    }

    // Conversión desde cartesianas (R3)
    static R3Cilindricas fromCartesian(const R3& v) {
        Radius r     = sqrt(v.x() * v.x() + v.y() * v.y());
        Theta theta = atan2(v.y(), v.x());
        Z z         = v.z();
        return R3Cilindricas(r, theta, z);
    }

    // Norma en coordenadas cilíndricas
    Radius norm() const {
        return sqrt(r_ * r_ + z_ * z_);
    }

    void print(std::ostream& os) const {
        os << "(r, theta, z) = (" << r_ << ", " << theta_ << ", " << z_ << ")\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const R3Cilindricas& v) {
        v.print(os);
        return os;
    }

private:
    Radius r_;
    Theta theta_;
    Z z_;
};


#endif // __R3CILINDRICAS_H__