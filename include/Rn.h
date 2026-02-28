/**
 * @file    Rn.h
 * @brief   Definición de la clase base RnBase y la clase template RnVector
 *          para representar vectores en espacios euclídeos de dimensión arbitraria.
 * @date    Febrero 2026
 *
 * @details Este archivo define dos clases principales:
 *          - @ref RnBase : interfaz polimórfica abstracta común a todos los vectores.
 *          - @ref RnVector : implementación template que representa un vector en R^n,
 *            donde n se determina automáticamente por el número de argumentos.
 *
 * @par Jerarquía de clases:
 * @code
 *   RnBase                    ← interfaz abstracta (polimorfismo)
 *     └── RnVector<Args...>   ← implementación genérica (n dimensiones)
 *           ├── R2            ← especialización para R^2
 *           └── R3            ← especialización para R^3
 * @endcode
 *
 * @par Ejemplo de uso básico:
 * @code
 *   RnVector v1(1.0, 2.0, 3.0);   // vector en R^3 (dim deducida automáticamente)
 *   RnVector v2(4.0, 5.0, 6.0);
 *
 *   auto v3  = v1 + v2;           // suma       → (5, 7, 9)
 *   auto v4  = 2.0 * v1;          // escalado   → (2, 4, 6)
 *   Real d   = v1 * v2;           // producto interno → 32
 *   Real n   = v1.norm();         // norma      → 3.7416
 *   auto u   = v1.unit_vector();  // normalizado
 *   cout << v1;                   // impresión  → RnVector<3>: (1, 2, 3)
 * @endcode
 *
 * @note Requiere C++20 o superior por el uso de concepts y fold expressions.
 * @see R2.h, R3.h
 */

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

// ════════════════════════════════════════════════════════════════════════════
//  CLASE BASE ABSTRACTA
// ════════════════════════════════════════════════════════════════════════════

/**
 * @class   RnBase
 * @brief   Interfaz polimórfica abstracta para vectores en R^n.
 *
 * @details Define el contrato que deben cumplir todas las clases de vectores,
 *          independientemente de su dimensión. Permite almacenar punteros a
 *          vectores de distintas dimensiones en una misma colección:
 *
 * @par Uso con colecciones heterogéneas:
 * @code
 *   // Arreglo de vectores de distinta dimensión
 *   unique_ptr<RnBase> vectors[3];
 *   vectors[0] = make_unique<RnVector<Real,Real>>(1.0, 2.0);           // R^2
 *   vectors[1] = make_unique<RnVector<Real,Real,Real>>(1.0, 2.0, 3.0); // R^3
 *   vectors[2] = make_unique<R3>(0.0, 1.0, 0.0);                      // R3
 *
 *   for (auto& v : vectors)
 *       cout << *v << " dim=" << v->size() << "\n";   // polimorfismo ✅
 * @endcode
 *
 * @note No se puede instanciar directamente — es una clase abstracta pura.
 *       Todos sus métodos son virtuales puros y deben implementarse en las
 *       clases derivadas.
 *
 * @warning No incluir @c unit_vector() aquí ya que retornaría un objeto por
 *          valor de tipo abstracto, lo cual es inválido en C++. Solo pueden
 *          ser virtuales los métodos que retornan tipos primitivos o @c void.
 */

class RnBase {
    public:
        /**
         * @brief Destructor virtual.
         *
         * Debe ser virtual para garantizar que el destructor de la clase
         * derivada se llame correctamente al eliminar mediante un puntero base.
         *
         * @par Sin destructor virtual:
         * @code
         *   RnBase* p = new RnVector<Real,Real,Real>(1.0, 2.0, 3.0);
         *   delete p;  // ❌ sin virtual → solo llama ~RnBase(), leak de RnVector
         *              // ✅ con virtual → llama ~RnVector() correctamente
         * @endcode
         */
        virtual         ~RnBase()                               = default;
        
        /**
         * @brief Devuelve la dimensión del vector (número de componentes).
         * @return Número de componentes como @c std::size_t.
         * @par Ejemplo:
         * @code
         *   RnVector v(1.0, 2.0, 3.0);
         *   v.size();  // → 3
         * @endcode
         */
        virtual         size_t size()                           const = 0;

        /**
         * @brief Devuelve la norma euclídea del vector.
         *
         * La norma euclídea se define como:
         * @code
         *   ||v|| = sqrt(v[0]² + v[1]² + ... + v[n-1]²)
         * @endcode
         *
         * @return Norma del vector como @c Real.
         * @par Ejemplo:
         * @code
         *   RnVector v(3.0, 4.0);
         *   v.norm();  // → 5.0
         * @endcode
         */
        virtual         Real norm()                             const = 0;

        /**
         * @brief Escribe el vector sobre un stream de salida dado.
         *
         * Método auxiliar requerido por @ref operator<< para soportar
         * polimorfismo: el operador llama a este método virtual, que en
         * tiempo de ejecución despacha a la implementación correcta.
         *
         * @param os Stream de salida sobre el que se escribe.
         */
        virtual void    printVectorToOstream(ostream& os)       const = 0;

        /**
         * @brief Sobrecarga del operador de inserción en stream (@c <<).
         *
         * Declarado @c friend en @c RnBase para que funcione con punteros
         * y referencias a la clase base, habilitando polimorfismo en la salida.
         * Delega en @ref printVectorToOstream() que es virtual.
         *
         * @param os Stream de salida.
         * @param v  Referencia a @c RnBase (puede ser cualquier clase derivada).
         * @return   Referencia al stream @p os para encadenamiento.
         *
         * @par Ejemplo con polimorfismo:
         * @code
         *   unique_ptr<RnBase> p = make_unique<R3>(1.0, 2.0, 3.0);
         *   cout << *p << endl;   // llama a R3::printVectorToOstream() ✅
         * @endcode
         */
        friend ostream& operator<<(ostream& os, const RnBase& v) {
            v.printVectorToOstream(os);
            return os;
        }
};

// ════════════════════════════════════════════════════════════════════════════
//  CLASE TEMPLATE RnVector
// ════════════════════════════════════════════════════════════════════════════

/**
 * @class   RnVector
 * @brief   Vector en el espacio euclídeo R^n de dimensión arbitraria.
 *
 * @tparam  Args Pack de tipos que determina la dimensión del vector.
 *               Todos deben ser tipos aritméticos: @c int, @c float, @c double...
 *               En la práctica siempre se normalizan a @c Real mediante el
 *               @ref deduction_guide "deduction guide".
 *
 * @details La dimensión @c n se deduce automáticamente del número de argumentos
 *          pasados al constructor, gracias al deduction guide definido al final
 *          del archivo. No es necesario especificarla manualmente.
 *
 * @par Deducción automática de dimensión:
 * @code
 *   RnVector v1(1.0, 2.0);           // dim = 2 → RnVector<Real, Real>
 *   RnVector v2(1.0, 2.0, 3.0);      // dim = 3 → RnVector<Real, Real, Real>
 *   RnVector v3(1.0, 2.0, 3.0, 4.0); // dim = 4 → RnVector<Real, Real, Real, Real>
 * @endcode
 *
 * @note Los tipos mixtos se normalizan automáticamente a @c Real:
 * @code
 *   RnVector v(-3, 2.71, 0.5f);  // int, double, float → Real, Real, Real ✅
 * @endcode
 *
 * @see RnBase, R2, R3
 */
template <typename... Args>
class RnVector: public RnBase {
    public:
        /** @brief Número de dimensiones del vector. Calculado en tiempo de compilación. */
        static constexpr size_t dim = sizeof...(Args);

        /** @brief Tipo de los elementos almacenados internamente (siempre @c Real). */
        using value_type = Real;

    private:
        /** @brief Array interno de tamaño fijo que almacena las componentes del vector. */
        array<value_type, dim> data_;

        /**
         * @brief Restricción estática: todos los tipos del pack deben ser aritméticos.
         *
         * Se evalúa en tiempo de compilación. Si se pasa un tipo no aritmético
         * (e.g. @c std::string), el compilador emite un error descriptivo.
         *
         * @par Fold expression usada:
         * @code
         *   (std::is_arithmetic_v<Args> && ...)
         *   // equivale a: is_arithmetic<A0> && is_arithmetic<A1> && ...
         * @endcode
         */
        static_assert((is_arithmetic_v<Args> && ...), 
                    "Todos los argumentos deben ser tipos numéricos");

    public:
        // ── Constructor ───────────────────────────────────────────────────────

        /**
         * @brief Constructor variádico — inicializa el vector con n valores.
         *
         * Cada argumento se convierte a @c value_type (@c Real) mediante
         * @c static_cast, garantizando consistencia de tipos internamente.
         *
         * @param args Valores de las componentes del vector.
         *             La dimensión @c n = sizeof...(args) se deduce automáticamente.
         *
         * @par Ejemplo:
         * @code
         *   RnVector v1(1.0, 2.0, 3.0);    // R^3
         *   RnVector v2(-3, 2.71, 0.5f);   // int y float → convertidos a Real
         * @endcode
         */
        explicit RnVector(Args... args) : data_{static_cast<value_type>(args)...} {}

        /**
         * @brief Destructor por defecto.
         *
         * El compilador genera el destructor automáticamente.
         * @c std::array gestiona su propia memoria, no hay recursos que liberar.
         */
        ~RnVector() = default;

        /**
         * @brief Devuelve la dimensión del vector.
         * @return @c dim — número de componentes, calculado en compilación.
         */
        size_t size() const override { return dim; }

    public:
        // ── Acceso al array interno ─────────────────────────

        /**
         * @brief Devuelve puntero modificable al inicio del array de datos.
         *
         * Útil para interoperabilidad con APIs de bajo nivel (OpenGL, BLAS, etc.)
         * que esperan un puntero a un array contiguo de @c double.
         *
         * @return Puntero @c value_type* al primer elemento de @c data_.
         * @note Solo disponible en objetos no- @c const.
         *
         * @par Ejemplo:
         * @code
         *   RnVector v(1.0, 2.0, 3.0);
         *   Real* ptr = v.data();
         *   ptr[0] = 99.0;   // modifica v[0] directamente
         * @endcode
         */
        value_type* data() noexcept {
            return data_.data();   // -> &data_[0]
        }

        /**
         * @brief Devuelve puntero de solo lectura al inicio del array de datos.
         *
         * Se invoca automáticamente cuando el objeto es @c const.
         *
         * @return Puntero @c const @c value_type* al primer elemento.
         * @note Solo permite lectura — no se puede modificar el contenido.
         *
         * @par Ejemplo:
         * @code
         *   const RnVector v(1.0, 2.0, 3.0);
         *   const Real* ptr = v.data();
         *   cout << ptr[1];   // lectura ✅
         *   ptr[1] = 5.0;     // ❌ error de compilación
         * @endcode
         */
        const value_type* data() const noexcept {
            return data_.data();
        }

        // ── Operadores aritméticos ────────────────────────────────────────────

    /**
     * @brief Suma componente a componente de dos vectores de igual dimensión.
     *
     * @param o Vector sumando de la misma dimensión y tipo.
     * @return Nuevo @c RnVector con cada componente igual a @c this[i] + @c o[i].
     *
     * @par Ejemplo:
     * @code
     *   RnVector v1(1.0, 2.0, 3.0);
     *   RnVector v2(4.0, 5.0, 6.0);
     *   auto v3 = v1 + v2;   // → (5, 7, 9)
     * @endcode
     */        
    RnVector operator+(const RnVector& o) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] += o.data_[i];
        return result;
    }

    /**
     * @brief Resta componente a componente de dos vectores de igual dimensión.
     *
     * @param o Vector sustraendo de la misma dimensión y tipo.
     * @return Nuevo @c RnVector con cada componente igual a @c this[i] - @c o[i].
     *
     * @par Ejemplo:
     * @code
     *   RnVector v1(5.0, 7.0, 9.0);
     *   RnVector v2(1.0, 2.0, 3.0);
     *   auto v3 = v1 - v2;   // → (4, 5, 6)
     * @endcode
     */    
    RnVector operator-(const RnVector& o) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] -= o.data_[i];
        return result;
    }

    /**
     * @brief Multiplicación del vector por un escalar (vector a la izquierda).
     *
     * @param scalar Valor escalar por el que se multiplica cada componente.
     * @return Nuevo @c RnVector con cada componente multiplicada por @p scalar.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(1.0, 2.0, 3.0);
     *   auto v2 = v * 3.0;   // → (3, 6, 9)
     * @endcode
     *
     * @see operator*(value_type, const RnVector&) para escalar a la izquierda.
     */    
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

    /**
     * @brief Producto interno entre dos vectores.
     *
     * Calcula la suma de los productos de las componentes correspondientes:
     * @code
     *   v1 · v2 = v1[0]*v2[0] + v1[1]*v2[1] + ... + v1[n-1]*v2[n-1]
     * @endcode
     *
     * @param o Vector con el que se calcula el producto interno.
     * @return Escalar @c value_type resultado del producto interno.
     *
     * @note También se usa internamente para calcular la norma:
     *       @c norm() = @c sqrt(v * v).
     *
     * @par Ejemplo:
     * @code
     *   RnVector v1(1.0, 2.0, 3.0);
     *   RnVector v2(4.0, 5.0, 6.0);
     *   Real d = v1 * v2;   // → 1*4 + 2*5 + 3*6 = 32
     * @endcode
     */    
    value_type operator*(const RnVector& o) const {
        value_type result = 0;
        for (std::size_t i = 0; i < dim; ++i) result += data_[i] * o.data_[i];
        return result;
    }

    /**
     * @brief División del vector por un escalar.
     *
     * @param scalar Divisor. No debe ser 0 (sin verificación — comportamiento
     *               indefinido si @p scalar == 0).
     * @return Nuevo @c RnVector con cada componente dividida por @p scalar.
     *
     * @warning No verifica división por cero. Usar con precaución.
     *          @ref unit_vector() sí verifica norma cero antes de dividir.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(2.0, 4.0, 6.0);
     *   auto v2 = v / 2.0;   // → (1, 2, 3)
     * @endcode
     */    
    RnVector operator/(value_type scalar) const {
        RnVector result(*this);
        for (std::size_t i = 0; i < dim; ++i) result.data_[i] /= scalar;
        return result;
    };

    /**
     * @brief Calcula la norma euclídea del vector.
     *
     * Implementación: @c sqrt(v·v) usando el @c operator* interno.
     *
     * @return Norma del vector como @c value_type ( @c Real ).
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(3.0, 4.0);
     *   v.norm();   // → 5.0  (triángulo 3-4-5)
     * @endcode
     */    
    value_type norm() const override {
        return std::sqrt(*this * *this);
    }

    // ── Acceso por índice ─────────────────────────────────────────────────

    /**
     * @brief Acceso por índice con verificación de rango.
     *
     * Devuelve una referencia modificable al componente en la posición @p i,
     * permitiendo tanto lectura como escritura.
     *
     * @param i Índice del componente (base 0).
     * @return Referencia al componente @p i.
     *
     * @throws std::out_of_range Si @p i>=dim.
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

    // ── Normalización ─────────────────────────────────────────────────────

    /**
     * @brief Devuelve el vector unitario (normalizado) en la misma dirección.
     *
     * Calcula @c v / ||v||. El vector resultante tiene norma 1.
     *
     * @return Nuevo @c RnVector con norma 1 y misma dirección que @c *this.
     *
     * @throws std::runtime_error Si el vector es nulo (@c norm() == 0),
     *         ya que no está definida su dirección.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(3.0, 4.0);
     *   auto u = v.unit_vector();   // → (0.6, 0.8)
     *   u.norm();                   // → 1.0
     * @endcode
     */
    RnVector unit_vector() const {
        value_type n = norm();
        if (n == 0) throw std::runtime_error("No se puede normalizar el vector cero");
        return *this / n;
    }

    // ── Salida en stream ──────────────────────────────────────────────────

    /**
     * @brief Sobrecarga del operador @c << para @c RnVector.
     *
     * Complementa al @c operator<< de @c RnBase: cuando el objeto es
     * conocido como @c RnVector (no como @c RnBase*), este operador
     * se invoca directamente sin necesidad de despacho virtual.
     *
     * @param os Stream de salida.
     * @param v  Vector @c RnVector a imprimir.
     * @return   Referencia al stream @p os.
     *
     * @par Ejemplo:
     * @code
     *   RnVector v(1.0, 2.0, 3.0);
     *   cout << v << endl;   // → RnVector<3>: (1, 2, 3)
     * @endcode
     */    
    friend ostream &operator<<(ostream &os, const RnVector &v) {
        v.printVectorToOstream(os);
        return os;
    }

    /**
     * @brief Escribe el vector sobre un stream en formato @c RnVector<n>:(x1,...,xn).
     *
     * Implementación virtual de @ref RnBase::printVectorToOstream.
     * Es llamado por ambos @c operator<< (el de @c RnBase y el de @c RnVector)
     * para garantizar consistencia en la salida.
     *
     * @param os Stream de salida sobre el que se escribe.
     *
     * @par Salida de ejemplo:
     * @code
     *   RnVector<3>: (1, 2, 3)
     * @endcode
     */    
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