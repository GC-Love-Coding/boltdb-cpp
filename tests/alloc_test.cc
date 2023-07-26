#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "boltdb/alloc/memory_pool.hpp"

using namespace boltdb;

TEST_CAST("Allocate small size", "[Memory Pool]") {
  auto& pool = MemoryPool.instance();

  int expected = 0;
  std::vector<Byte*> byte_ptrs;

  for (int i = 1; i <= 10; i++) {
    Byte* p = pool.allocate(i);
    byte_ptrs.push_back(p);
    expected += i;
  }

  REQUIRE(pool.bytes_allocated() == expected);
}