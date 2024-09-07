#include "data_type.h"

namespace data {

  DataType::DataType(int type) { this->type = type; }
  int DataType::getType() { return this->type; }
}