#ifndef __R3_H__
#define __R3_H__

#include "Rn.h"
#include "types.h"

using namespace std;

class R3 : public RnVector<Real, Real, Real> {
    public:
        using Base = RnVector<Real, Real, Real>;

        // ── Constructor — delega al padre ────────────────────────────────────────
        explicit R3(Real x = 0.0, Real y = 0.0, Real z = 0.0) : Base(x, y, z) {}

        // ── Constructor desde RnVector (conversión) ───────────────────────────── 
        explicit R3(const Base& v) : Base(v) {} 

        // ── Destructor de clase ────────────────────────────────────────────
        virtual ~R3() = default;

        // ── Accesores semánticos ──────────────────────────────────────────────────
        Real x() const { return (*this)[0]; }
        Real y() const { return (*this)[1]; }
        Real z() const { return (*this)[2]; }

        Real& x() { return (*this)[0]; }
        Real& y() { return (*this)[1]; }
        Real& z() { return (*this)[2]; }
        
        // ── Producto vectorial (exclusivo de R3) ──────────────────────────────────
        /**
         * @brief Producto vectorial entre dos vectores en R3.
         * @param o Vector con el que se calcula el producto vectorial.
         * @return Nuevo R3 perpendicular a ambos vectores.
         */
        [[nodiscard]] R3 cross(const R3& o) const {
            return R3(
                y() * o.z() - z() * o.y(),
                z() * o.x() - x() * o.z(),
                x() * o.y() - y() * o.x()
            );
        }

        // ── Operadores heredados devuelven R3 en lugar de RnVector ────────────────
        R3 operator+(const R3& o) const { return R3(Base::operator+(o)); }
        R3 operator-(const R3& o) const { return R3(Base::operator-(o)); }
        R3 operator/(Real scalar) const { return R3(Base::operator/(scalar)); }
        R3 operator*(Real scalar) const { return R3(Base::operator*(scalar)); }
        friend R3 operator*(Real scalar, const R3& v) { return v * scalar; }
        R3 unit_vector() const {
            return R3(Base::unit_vector());  // reutiliza la lógica del padre
        }
};


    
#endif // __R3_H__