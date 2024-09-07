#pragma once

#include <cstdint>

namespace util {
  class IdGenerator {
  private:
    static uint64_t id;

  public:
    static int generateInt() {
      return id++;
    }
  };

  uint64_t IdGenerator::id = 0;
}