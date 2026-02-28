#ifndef __R3POLAR_H__
#define __R3POLAR_H__

#include <cmath>
#include <iostream>
#include "types.h"
#include "R3.h"

/**
 * @file    R3Polar.h
 * @brief   Clase para representar vectores en R3 usando coordenadas esféricas.
 *
 * @details Modela un vector en el espacio tridimensional mediante tres parámetros:
 *          radio @p r, ángulo polar @p theta y ángulo azimutal @p phi.
 *          Provee conversión bidireccional con la representación cartesiana R3.
 *
 * @par Relación con coordenadas cartesianas:
 * @code
 *   x = r · sin(θ) · cos(φ)
 *   y = r · sin(θ) · sin(φ)
 *   z = r · cos(θ)
 * @endcode
 *
 * @par Rangos válidos:
 * @code
 *   r     ∈ [0, ∞)    radio (distancia al origen)
 *   theta ∈ [0, π]    ángulo polar    (desde el eje Z)
 *   phi   ∈ [0, 2π]   ángulo azimutal (desde el eje X)
 * @endcode
 *
 * @note Esta clase NO hereda de R3 ya que representa un sistema de coordenadas
 *       distinto, no una especialización. La relación entre ambas se establece
 *       mediante conversiones explícitas: @ref toCartesian() y @ref fromCartesian().
 *
 * @see R3
 */
class R3Polar {
public:
    /**
     * @brief Constructor principal desde coordenadas esféricas.
     *
     * @param r     Radio o distancia al origen. Debe ser >= 0.
     * @param theta Ángulo polar en radianes, medido desde el eje Z. Rango: [0, π].
     * @param phi   Ángulo azimutal en radianes, medido desde el eje X. Rango: [0, 2π].
     *
     * @throws std::invalid_argument Si @p r es negativo.
     *
     * @par Ejemplo:
     * @code
     *   R3Polar v(1.0, M_PI/2, M_PI/4);   // r=1, θ=90°, φ=45°
     *   R3Polar origen(0.0, 0.0, 0.0);    // vector nulo
     * @endcode
     */
    explicit R3Polar(Radius r, Theta theta, Phi phi)
        : r_(r), theta_(theta), phi_(phi) {
        if (r < 0)
            throw std::invalid_argument("El radio no puede ser negativo");
    }

    // ── Accesores ─────────────────────────────────────────────────────
    /**
     * @brief Devuelve el radio del vector (distancia al origen).
     * @return Valor de @c r_ como @c Radius (solo lectura).
     */
    Radius r()     const { return r_;     }
    /**
     * @brief Devuelve el ángulo polar θ (medido desde el eje Z).
     * @return Valor de @c theta_ como @c Theta en radianes (solo lectura).
     */
    Theta  theta() const { return theta_; }
    /**
     * @brief Devuelve el ángulo azimutal φ (medido desde el eje X en el plano XY).
     * @return Valor de @c phi_ como @c Phi en radianes (solo lectura).
     */
    Phi    phi()   const { return phi_;   }

    // ── Conversión a cartesianas (R3) ─────────────────────────────────
    /**
     * @brief Convierte el vector esférico a coordenadas cartesianas (R3).
     *
     * Aplica las fórmulas de transformación esférica → cartesiana:
     *
     * @par Fórmulas:
     * @code
     *   x = r · sin(θ) · cos(φ)
     *   y = r · sin(θ) · sin(φ)
     *   z = r · cos(θ)
     * @endcode
     *
     * @return Nuevo objeto @c R3 con las componentes cartesianas equivalentes.
     *
     * @par Ejemplo:
     * @code
     *   R3Polar vp(1.0, M_PI/2, 0.0);
     *   R3 vc = vp.toCartesian();   // → R3(1, 0, 0)
     * @endcode
     */
    R3 toCartesian() const {
        return R3(
            r_ * sin(theta_) * cos(phi_),   // x
            r_ * sin(theta_) * sin(phi_),   // y
            r_ * cos(theta_)                // z
        );
    }

    // ── Conversión desde cartesianas (R3) ─────────────────────────────
    /**
     * @brief Construye un @c R3Polar a partir de un vector cartesiano R3.
     *
     * Aplica las fórmulas de transformación cartesiana → esférica:
     *
     * @par Fórmulas:
     * @code
     *   r     = ||v||                         (norma euclídea)
     *   theta = acos(z / r)                   (0 si r == 0)
     *   phi   = atan2(y, x)                   (ángulo en el plano XY)
     * @endcode
     *
     * @param v Vector cartesiano @c R3 a convertir.
     * @return Nuevo @c R3Polar equivalente al vector @p v.
     *
     * @note Si @p v es el vector nulo, @c theta y @c phi se definen como 0
     *       para evitar división por cero.
     *
     * @note Declarado @c static porque no necesita un objeto @c R3Polar
     *       existente — su propósito es construir uno nuevo.
     *
     * @par Ejemplo:
     * @code
     *   R3 vc(0.0, 0.0, 1.0);
     *   R3Polar vp = R3Polar::fromCartesian(vc);  // r=1, θ=0, φ=0
     * @endcode
     *
     * @see toCartesian()
     */
    static R3Polar fromCartesian(const R3& v) {
        Radius r     = v.norm();
        Theta theta = (r == 0) ? 0 : acos(v.z() / r);
        Phi phi   = atan2(v.y(), v.x());
        return R3Polar(r, theta, phi);
    }

    // ── Norma — trivialmente es r ─────────────────────────────────────
    /**
     * @brief Devuelve la norma (módulo) del vector.
     *
     * En coordenadas esféricas la norma es trivialmente el radio @c r_.
     * No requiere cálculo adicional a diferencia de las coordenadas cartesianas.
     *
     * @return Valor del radio @c r_ como @c Radius.
     *
     * @par Ejemplo:
     * @code
     *   R3Polar v(3.0, M_PI/2, 0.0);
     *   Radius n = v.norm();   // → 3.0
     * @endcode
     */
    Radius norm() const { return r_; }

    // ── Salida ─────────────────────────────────────────────────────────
    /**
     * @brief Imprime el vector en formato @c (r, theta, phi) sobre un stream.
     *
     * @param os Stream de salida sobre el que se escribe (e.g. @c std::cout).
     *
     * @par Ejemplo de salida:
     * @code
     *   (r, theta, phi) = (1, 1.5708, 0.7854)
     * @endcode
     *
     * @see operator
     */
    void print(std::ostream& os) const {
        os << "(r, theta, phi) = (" << r_ << ", " << theta_ << ", " << phi_ << ")\n";
    }
    /**
     * @brief Sobrecarga del operador de inserción en stream (@c <<).
     *
     * Permite usar @c cout << v de forma natural.
     * Delega internamente en @ref print().
     *
     * @param os Stream de salida.
     * @param v  Vector @c R3Polar a imprimir.
     * @return Referencia al stream @p os para permitir encadenamiento.
     *
     * @par Ejemplo:
     * @code
     *   R3Polar v(1.0, M_PI/2, M_PI/4);
     *   cout << v << endl;
     *   // Salida: (r, theta, phi) = (1, 1.5708, 0.7854)
     * @endcode
     */
    friend std::ostream& operator<<(std::ostream& os, const R3Polar& v) {
        v.print(os);
        return os;
    }

private:
    Radius r_;      ///< Radio: distancia al origen. Siempre >= 0.
    Theta  theta_;  ///< Ángulo polar en radianes: medido desde el eje Z. Rango [0, π].
    Phi    phi_;    ///< Ángulo azimutal en radianes: medido desde el eje X. Rango [0, 2π].
};

#endif // __R3POLAR_H__