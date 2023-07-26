#pragma once

#include <cstddef>
#include <vector>

#include "page.h"

namespace boltdb {

class Bucket;

// inode represents an internal node inside of a node.
// It can be used to point to elements in a page or point
// to an element which hasn't been added to a page yet.
struct inode {
  uint32_t flags;
  pgid pgid;
  std::vector<std::byte> key;
  std::vector<std::byte> value;
};

// node represents an in-memory, deserialized page.
struct node {
  // root returns the top-level node this node is attached to.
  auto root() const -> const node*;

  // minKeys returns the minimum number of inodes this node should have.
  auto minKeys() const -> int;

  Bucket* bucket;
  bool is_leaf;
  bool unbalanced;
  bool spilled;
  std::vector<std::byte> key;
  pgid pgid;
  node* parent;
  std::vector<node*> children;
  std::vector<inode> inodes;
};

}  // namespace boltdb