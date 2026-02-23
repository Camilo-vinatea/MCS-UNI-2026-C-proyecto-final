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

    void printVector() const {
        cout << "RnVector<" << dim << ">: (";
        for (size_t i = 0; i < dim; ++i) {
            cout << data_[i];
            if (i < dim - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
};

#endif // __Rn_H__