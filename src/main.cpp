#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>

#include "test/db/test.h"
#include "data/integer.h"

int main() {
  // test::testDouble();
  // test::testString();
  int n = 1000;
  std::vector<db::Document::KVPair_t> queries
    = {{"first", new data::Integer(0)},
       {"first", new data::Integer(n / 4)},
       {"first", new data::Integer(n / 2)},
       {"first", new data::Integer(n + 3)}};

  auto start = std::chrono::high_resolution_clock::now();
  test::testStrictCollectionStress(n, queries);
  auto fin = std::chrono::high_resolution_clock::now();

  auto duration
    = std::chrono::duration_cast<std::chrono::milliseconds>(fin - start)
        .count();

  std::cout << "Execution Time: " << duration << "ms" << std::endl;
  return 0;
}