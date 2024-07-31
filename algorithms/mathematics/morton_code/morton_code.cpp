#include <iostream>

uint32_t Morton10(uint32_t x) {
  x &= 0x3ff;
  x = (x | x << 16) & 0x30000ff;
  x = (x | x << 8) & 0x300f00f;
  x = (x | x << 4) & 0x30c30c3;
  x = (x | x << 2) & 0x9249249;
  return x;
}

uint64_t Morton21(uint64_t x) {
  x &= 0x1fffff;
  x = (x | x << 32) & 0x1f00000000ffff;
  x = (x | x << 16) & 0x1f0000ff0000ff;
  x = (x | x << 8) & 0x100f00f00f00f00f;
  x = (x | x << 4) & 0x10c30c30c30c30c3;
  x = (x | x << 2) & 0x1249249249249249;
  return x;
}

int main() {
  for (uint32_t i = 0; i < 10; i++) {
    std::cout << Morton21(i) << std::endl;
  }
  return 0;
}