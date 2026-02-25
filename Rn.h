#ifndef __Rn_H__
#define __Rn_H__

#include <iostream>
#include <array>
#include <type_traits>
#include <cstddef>
#include <cmath>

#include "types.h"

using namespace std;
void RnVectorSpace();

template <typename... Args>
class RnVector {
    public:
        static constexpr std::size_t dim = sizeof...(Args);
        using value_type = Real;

    private:
        std::array<value_type, dim> data_;

        // Helper: verifica que todos los tipos sean aritméticos
        static_assert((std::is_arithmetic_v<Args> && ...), 
                    "Todos los argumentos deben ser tipos numéricos");
    public:
        // ── Constructor desde valores ────────────────────────────────────────────
        explicit RnVector(Args... args) : data_{static_cast<value_type>(args)...} {}

        // ── Destructor de clase ────────────────────────────────────────────
        ~RnVector() = default;

    public:
        // Puntero modificable (si el objeto NO es const)
        value_type* data() noexcept {
            return data_.data();   // -> &data_[0]
        }

        // Puntero solo-lectura (si el objeto ES const)
        const value_type* data() const noexcept {
            return data_.data();
        }
    
    void printVector() const {
        cout << "RnVector<" << dim << ">: (";
        for (size_t i = 0; i < dim; ++i) {
            cout << data_[i];
            if (i < dim - 1) cout << ", ";
        }
        cout << ")" << endl;
    }

    void printVector2() const {
        const value_type* ptr = data();  // obtiene puntero interno

        cout << "(";
        for (size_t i = 0; i < dim; ++i) {
            cout << ptr[i];
            if (i + 1 < dim)
                cout << ", ";
        }
        cout << ")" << endl;
    }

    void PrintVector3() const {
        cout << "(";
        for (auto value : data_) {
            cout << value;
            if (value == data_.back()) // Si es el último elemento, no imprimir coma
                break;
            cout << ", ";
        }
        cout << ")" << endl;
    }

    RnVector operator+(const RnVector& o) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] += o.data_[i];
        return result;
    }

    RnVector operator-(const RnVector& o) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] -= o.data_[i];
        return result;
    }

    RnVector operator*(value_type scalar) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] *= scalar;
        return result;
    }

    /**
     * @brief Multiplicación escalar por vector (escalar a la izquierda).
     *
     * Sobrecarga no miembro que permite la forma `escalar * vector`.
     * Delega internamente en el `operator*(value_type)` del propio vector.
     *
     * @param scalar Valor escalar por el que se multiplica.
     * @param v      Vector a escalar.
     * @return Nuevo `RnVector` con cada componente multiplicada por @p scalar.
     *
     * @note Declarado como `friend` para acceder a miembros privados y
     *       residir en el scope del namespace, que es donde el compilador
     *       busca el operador cuando el operando izquierdo es un escalar.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(1.0, 2.0, 3.0);
     *   auto v2 = 2.0 * v;  // → R3(2.0, 4.0, 6.0)
     * @endcode
     */
    friend RnVector operator*(value_type scalar, const RnVector& v) {
        return v * scalar;  // reutiliza el operator* ya definido
    }

    value_type operator*(const RnVector& o) const {
        value_type result = 0;
        for (std::size_t i = 0; i < dim; ++i) result += data_[i] * o.data_[i];
        return result;
    }

    RnVector operator/(value_type scalar) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] /= scalar;
        return result;
    };

    value_type norm() const {
        return std::sqrt(*this * *this);
    }

};

/**
 * @brief Deduction guide para RnVector.
 *
 * Normaliza todos los tipos aritméticos del pack @p Args a @c double,
 * evitando incompatibilidades entre vectores construidos con distintos
 * tipos literales (e.g. @c int vs @c double).
 *
 * @tparam Args Tipos de los argumentos del constructor (int, float, double...).
 *
 * @note Sin esta guía, `RnVector v(-3, 2.71)` deduciría
 *       `RnVector<int, double>` en lugar de `RnVector<Real, Real>`,
 *       haciendo fallar operaciones como `operator+` entre vectores.
 *
 * @par Transformación aplicada:
 * @code
 *   RnVector v(-3, 2.71, 0.5f)
 *   Args             →  { int,    double,  float  }
 *   is_arithmetic?   →    true    true     true
 *   resultado        →  { Real, Real,  Real }
 * @endcode
 */
template <typename... Args>
RnVector(Args...) -> RnVector<std::conditional_t<std::is_arithmetic_v<Args>, Real, Args>...>;

#endif // __Rn_H__