#include "document.h"
#include "../common/util.h"
#include "../common/id_generator.h"

namespace db {
  Document::Document()
      : Document(util::createEmptyPairs<std::string, data::DataType *>()) {}

  Document::Document(std::vector<KVPair_t> values)
      : Document(util::createEmptyPairs<std::string, int>(), values) {}

  Document::Document(ConstraintStore_t constraints,
                     std::vector<KVPair_t> values)
      : Document(util::mapToVec<std::string, int>(constraints), values) {}

  Document::Document(std::vector<ConstraintPair_t> constraints,
                     std::vector<KVPair_t> values) {
    this->id = util::IdGenerator::generateInt();
    for(auto &[k, v] : constraints) {
      this->constraints[k] = v;
    }
    for(auto &[k, v] : values) {
      this->values[k] = v;
    }
  }

  Document::Document(KVStore_t values)
      : Document(util::mapToVec<std::string, data::DataType *>(values)) {}

  Document::Document(ConstraintStore_t constraints, KVStore_t values)
      : Document(constraints,
                 util::mapToVec<std::string, data::DataType *>(values)) {}

  Document::Document(std::vector<ConstraintPair_t> constraints,
                     KVStore_t values)
      : Document(constraints,
                 util::mapToVec<std::string, data::DataType *>(values)) {
    ;
  }

  Document::~Document() {
    for(auto [_, value] : this->values) {
      delete value;
    }
  }

  data::DataType *Document::get(std::string key) { return this->values[key]; }

  std::vector<std::string> Document::getKeys() {
    std::vector<std::string> keys;
    for(auto [k, _] : this->values) {
      keys.push_back(k);
    }
    return keys;
  }

  void Document::set(std::string key, data::DataType *value) {
    this->values[key] = value;
  }
}