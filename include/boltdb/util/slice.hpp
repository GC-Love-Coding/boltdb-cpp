#ifndef BOLTDB_CPP_UTIL_SLICE_H_
#define BOLTDB_CPP_UTIL_SLICE_H_

#include <cstddef>
#include <string>

#include "boltdb/alloc/memory_pool.hpp"
#include "boltdb/util/common.hpp"

namespace boltdb {

class ByteSlice {
 public:
  ByteSlice();
  ByteSlice(Byte* data, std::size_t size);
  explicit ByteSlice(Byte* data);
  explicit ByteSlice(std::string data);

 private:
  Byte* _data;
  std::size_t _size;
  std::size_t _cap;
};

}  // namespace boltdb

#endif  // BOLTDB_CPP_UTIL_SLICE_H_
