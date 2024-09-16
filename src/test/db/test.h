#pragma once

#include "../../db/document.h"

namespace test {

  void testStrictDocument();
  void testPage();
  void testCollection();
  void
  testStrictCollectionStress(int n,
                             std::vector<db::Document::KVPair_t> &queries);
}