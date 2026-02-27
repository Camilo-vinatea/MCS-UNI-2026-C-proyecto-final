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

class RnBase {
    public:
        virtual         ~RnBase()                               = default;

        virtual         std::size_t size()                      const = 0;
        virtual         Real norm()                             const = 0;
        virtual void    printVector()                           const = 0;
        virtual void    printVector2()                          const = 0;
        virtual void    PrintVector3()                          const = 0;
        virtual void    printVectorToOstream(ostream& os)       const = 0;
        friend ostream& operator<<(ostream& os, const RnBase& v) {
            v.printVectorToOstream(os);
            return os;
        }
};

template <typename... Args>
class RnVector: public RnBase {
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

        std::size_t size() const override { return dim; }

    public:
        // Puntero modificable (si el objeto NO es const)
        value_type* data() noexcept {
            return data_.data();   // -> &data_[0]
        }

        // Puntero solo-lectura (si el objeto ES const)
        const value_type* data() const noexcept {
            return data_.data();
        }
    
    void printVector() const override {
        cout << "RnVector<" << dim << ">: (";
        for (size_t i = 0; i < dim; ++i) {
            cout << data_[i];
            if (i < dim - 1) cout << ", ";
        }
        cout << ")" << endl;
    }

    void printVector2() const override {
        const value_type* ptr = data();  // obtiene puntero interno

        cout << "(";
        for (size_t i = 0; i < dim; ++i) {
            cout << ptr[i];
            if (i + 1 < dim)
                cout << ", ";
        }
        cout << ")" << endl;
    }

    void PrintVector3() const override{
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

    value_type norm() const override {
        return std::sqrt(*this * *this);
    }

    /**
     * @brief Acceso por índice con verificación de rango.
     *
     * Devuelve una referencia modificable al componente en la posición @p i,
     * permitiendo tanto lectura como escritura.
     *
     * @param i Índice del componente (base 0).
     * @return Referencia al componente @p i.
     *
     * @throws std::out_of_range Si @p i >= dim.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(1.0, 2.0, 3.0);
     *   v[0] = 5.0;       // escritura
     *   Real x = v[1];    // lectura
     * @endcode
 */    
    value_type& operator[](std::size_t i) {
        if (i >= dim)
            throw std::out_of_range(
                "Índice " + std::to_string(i) + 
                " fuera de rango [0, " + std::to_string(dim) + ")");
        return data_[i];
    }

    /**
     * @brief Acceso por índice con verificación de rango (versión const).
     *
     * Devuelve una referencia de solo lectura al componente en la posición @p i.
     * Se invoca automáticamente cuando el objeto está declarado como @c const.
     *
     * @param i Índice del componente (base 0).
     * @return Referencia constante al componente @p i.
     *
     * @throws std::out_of_range Si @p i >= dim.
     *
     * @par Ejemplo:
     * @code
     *   const RnVector v(1.0, 2.0, 3.0);
     *   Real x = v[0];    // ✅ solo lectura
     *   v[0] = 5.0;       // ❌ error de compilación — objeto const
     * @endcode
 */
    const value_type& operator[](std::size_t i) const {
        if (i >= dim)
            throw std::out_of_range(
                "Índice " + std::to_string(i) + 
                " fuera de rango [0, " + std::to_string(dim) + ")");
        return data_[i];
    }

    RnVector unit_vector() const {
        value_type n = norm();
        if (n == 0) throw std::runtime_error("No se puede normalizar el vector cero");
        return *this / n;
    }

    friend ostream &operator<<(ostream &os, const RnVector &v) {
        v.printVectorToOstream(os);
        return os;
    }

    virtual void printVectorToOstream(ostream& os) const override {
        os << "RnVector<" << dim << ">: (";
        for (size_t i = 0; i < dim; ++i) {
            os << data_[i];
            if (i < dim - 1) os << ", ";
        }
        os << ")";
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