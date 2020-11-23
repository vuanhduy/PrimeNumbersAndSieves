//
// Created by dvu4 on 2020-11-23.
//

#ifndef SIEVEOFERATOSTHENES_SRC_SOE_H_
#define SIEVEOFERATOSTHENES_SRC_SOE_H_

#include <iostream>
#include <memory>
#include <cstddef>

using namespace std;
class SoE {
 public:
  SoE(const size_t &n);
  SoE(const SoE &) = delete;
  SoE(const SoE &&) = delete;

  SoE &operator=(const SoE &) = delete;
  SoE &operator=(const SoE &&) = delete;

/**
 * Check if the given n is prime or not.
 */
  bool is_prime(const size_t &n);

/**
 * Count the number of prime numbers
 */
  size_t count();

 private:
  size_t m_upper_bound;
  unique_ptr<byte[]> m_primes;
};

#endif //SIEVEOFERATOSTHENES_SRC_SOE_H_
