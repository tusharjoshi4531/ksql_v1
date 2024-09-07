#pragma once

#include <map>
#include <vector>

namespace util {
  // Converts a std::map<K, V> to a std::vector<std::pair<K, V>>.
  template <typename K, typename V>
  std::vector<std::pair<K, V>> mapToVec(std::map<K, V> &store) {
    std::vector<std::pair<K, V>> pairs(store.begin(), store.end());
    return pairs;
  }

  // Returns an empty std::vector<std::pair<K, V>>.
  template <typename K, typename V>
  std::vector<std::pair<K, V>> createEmptyPairs() {
    std::vector<std::pair<K, V>> val;
    return val;
  }
}