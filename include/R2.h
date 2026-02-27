#ifndef __R2_H__
#define __R2_H__

#include "Rn.h"
#include "types.h"

/**
 * @brief Espacio vectorial R2 — vector de 2 componentes reales.
 * Hereda directamente de RnVector<Real, Real>.
 */
class R2 : public RnVector<Real, Real> {
public:
    using Base = RnVector<Real, Real>;

    // ── Constructor — delega al padre ────────────────────────────────
    explicit R2(Real x = 0, Real y = 0) : Base(x, y) {}

    // ── Constructor desde RnVector ────────────────────────────────────
    explicit R2(const Base& v) : Base(v) {}

    // ── Destructor ────────────────────────────────────────────────────
    ~R2() = default;

    // ── Accesores semánticos ──────────────────────────────────────────
    Real  x() const { return (*this)[0]; }
    Real  y() const { return (*this)[1]; }
    Real& x()       { return (*this)[0]; }
    Real& y()       { return (*this)[1]; }

    // ── Operadores — devuelven R2 en lugar de RnVector ────────────────
    R2 operator+(const R2& o) const { return R2(Base::operator+(o)); }
    R2 operator-(const R2& o) const { return R2(Base::operator-(o)); }
    R2 operator*(Real scalar) const { return R2(Base::operator*(scalar)); }
    R2 operator/(Real scalar) const { return R2(Base::operator/(scalar)); }
    R2 unit_vector()          const { return R2(Base::unit_vector()); }

    friend R2 operator*(Real scalar, const R2& v) { return v * scalar; }

    // ── Print ─────────────────────────────────────────────────────────
    void print() const {
        std::cout << "R2(" << x() << ", " << y() << ")\n";
    }
};


#endif // __R2_H__