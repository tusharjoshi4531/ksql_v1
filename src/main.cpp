#include <iostream>
#include <vector>
#include <cstdint>

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
  test::testStrictCollectionStress(n, queries);
  return 0;
}