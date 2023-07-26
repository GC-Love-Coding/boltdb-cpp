#include "node.h"

namespace boltdb {

auto node::root() const -> const node* {
  if (parent == nullptr) {
    return this;
  }

  return parent->root();
}

auto node::minKeys() const -> int {
  if (is_leaf) {
    return 1;
  }

  return 2;
}

}  // namespace boltdb