//
// Created by dvu4 on 2020-11-23.
//

#include "SoE.h"
#include <memory>
#include <cstddef>
#include <cmath>

using namespace std;

bool SoE::is_prime(const size_t &n) {
    if (n > m_upper_bound || n < 2)
        throw runtime_error("Out of bounds");

    // check if n is an even number.
    if (n == 2)
        return true;
    if ((n & 0x1) == 0)
        return false;

    size_t block_index = ((n >> 1) - 1) >> 3;
    size_t offset = ((n >> 1) - 1) & 0x7;
    byte mask{0x80};
    mask >>= offset;
    return to_integer<int>(m_primes[block_index] & mask) > 0;
}

SoE::SoE(const size_t &n) : m_upper_bound(n) {
    size_t number_of_blocks = (((n >> 1) - 1) >> 3) + 1;
    m_primes = make_unique<byte[]>(number_of_blocks);
    fill_n(m_primes.get(), number_of_blocks, static_cast<byte>(0xFF));

    // a lambda to check whether number at index is prime
    auto check = [&](const size_t &index) {
      size_t block_index = ((index >> 1) - 1) >> 3;
      size_t offset = ((index >> 1) - 1) & 0x7;
      byte mask{0x80};
      mask >>= offset;
      return to_integer<int>(m_primes[block_index] & mask) > 0;
    };

    // a lambda to clear the bit at index
    auto mark = [&](const size_t &index) {
      size_t block_index = ((index >> 1) - 1) >> 3;
      size_t offset = ((index >> 1) - 1) & 0x7;
      byte mask{0x80};
      mask >>= offset;
      m_primes[block_index] &= ~mask;
    };

    // Clear trailing bits
    size_t last_group_size = ((n >> 1) - 1) & 0x7;
    byte mask{0xFF};
    mask >>= last_group_size;
    m_primes[number_of_blocks - 1] ^= mask;

    // Mark non-prime numbers
    size_t sqrt_n = static_cast<size_t>(sqrt(n));
    for (size_t i = 3; i <= sqrt_n; i += 2) {
        if (check(i)) {
            for (size_t j = 3 * i; j <= n; j += 2*i) {
                mark(j);
            }
        }
    }
}

size_t SoE::count() {
    size_t number_of_blocks = (((m_upper_bound >> 1) - 1) >> 3) + 1;
    auto count_each_byte = [](const byte &b) {
      auto value = to_integer<int>(b);
      if (value == 0)
          return 0;
      int _ans = 0;
      for (size_t i = 0; i < 8; i++) {
          if (((value >> i) & 0x1) == 1)
              _ans += 1;
      }

      return _ans;
    };

    size_t ans = 0;
    for (size_t i = 0; i < number_of_blocks; i++) {
        ans += count_each_byte(m_primes[i]);
    }

    return ans + 1;
}