#ifndef __Rn_H__
#define __Rn_H__

#include <iostream>
#include <array>
#include <type_traits>
#include <cstddef>

#include "types.h"

using namespace std;
void RnVectorSpace();

template <typename... Args>
class RnVector  {
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
        for (auto value : data_) {
            cout << value << " ";
        }
        cout << endl;
    }

};

#endif // __Rn_H__