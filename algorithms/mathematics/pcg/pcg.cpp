#include <cstdint>
#include <iostream>

constexpr uint64_t STATE = 0x4d595df4d0f33173ULL;
constexpr uint64_t MULTIPLIER = 6364136223846793005ULL;
constexpr uint64_t INCREMENT = 1442695040888963407ULL;

class Random {
public:
  Random() : state_(STATE), increment_(INCREMENT) {}

  uint32_t pcg32();

  void Advance(int64_t delta);

private:
  uint64_t state_;
  uint64_t increment_;
};

uint32_t rotr32(uint32_t x, uint32_t r) { return (x >> r) | (x << (-r & 31)); }

uint32_t Random::pcg32() {
  uint64_t x = state_;
  state_ = x * MULTIPLIER + increment_;
  uint32_t count = (uint32_t)(x >> 59U);
  return rotr32((uint32_t)((x ^ (x >> 18U)) >> 27U), count);
}

void Random::Advance(int64_t delta) {
  uint64_t accumulator_multiplier = 1u;
  uint64_t accumulator_plus = 0u;
  uint64_t current_multiplier = MULTIPLIER;
  uint64_t current_plus = increment_;
  while (delta > 0) {
    if (delta & 1) {
      accumulator_multiplier *= current_multiplier;
      accumulator_plus = accumulator_plus * current_multiplier + current_plus;
    }
    current_plus = (current_multiplier + 1) * current_plus;
    current_multiplier *= current_multiplier;
    delta /= 2;
  }
  state_ = accumulator_multiplier * state_ + accumulator_plus;
}

int main() {

  Random random1;
  Random random2;

  for (int32_t i = 0; i < 20; i++) {
    std::cout << random1.pcg32() << std::endl;
  }

  random2.Advance(10);

  for (int32_t i = 0; i < 10; i++) {
    std::cout << random2.pcg32() << std::endl;
  }

  return 0;
}