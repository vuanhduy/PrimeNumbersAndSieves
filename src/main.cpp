#define MILLION(x)  ((x) * 1000000)
#define BILLION(x)  ((x) * 1000000000)

#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>
#include <chrono>

#include "SoE.h"

using namespace std;

unique_ptr<bool[]> create_SoE_v1(const size_t &n) {
    unique_ptr<bool[]> primes{ make_unique<bool[]>(n+1)};
    fill_n(primes.get(), n+1, true);
    // 0 and 1 are not considered as prime numbers
    primes[0] = false;
    primes[1] = false;

    for(size_t i = 3; i <= n; i++) {
        if(primes[i] == true) {
            for(size_t j = 2*i; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    return move(primes);
}

unique_ptr<bool[]> create_SoE_v2(const size_t &n) {
    unique_ptr<bool[]> primes{ make_unique<bool[]>(n+1)};
    fill_n(primes.get(), n+1, true);
    // 0 and 1 are not considered as prime numbers
    primes[0] = false;
    primes[1] = false;

    size_t sqrt_n = static_cast<size_t>(sqrt(n));
    for(size_t i = 2; i <= sqrt_n; i++) {
        if(primes[i] == true) {
            for(size_t j = 2*i; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }

    return move(primes);
}

int main() {
    vector<size_t> numbers;
    for (size_t i = MILLION(5); i < BILLION(2); i+=MILLION(5)){
        numbers.push_back(i);
    }

    for (auto &n: numbers) {
        auto begin = std::chrono::steady_clock::now();
        { create_SoE_v1(n); }
        auto end = std::chrono::steady_clock::now();

        cout << "n: " << n << ", times: "
             << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << ", ";

        begin = std::chrono::steady_clock::now();
        { create_SoE_v2(n); }
        end = std::chrono::steady_clock::now();
        cout << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << ", ";

        begin = std::chrono::steady_clock::now();
        { SoE sieve3(n); }
        end = std::chrono::steady_clock::now();
        cout << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << ", ";
        cout << endl;
    }
    return 0;
}
