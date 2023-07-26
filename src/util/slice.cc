#include "boltdb/util/slice.hpp"

#include <algorithm>
#include <cstring>

#include "boltdb/util/util.hpp"

using namespace boltdb;

ByteSlice::ByteSlice() : _data(nullptr), _size(0), _cap(0) {}

ByteSlice::ByteSlice(Byte* data, std::size_t size) {
  // TODO(gc): validate data (NULL)
  auto& pool = MemoryPool.instance();

  // Add extra 1 to termainate.
  _size = std::min(strlen(data), size);
  _cap = round_up_to_power_of_two(_size + 1);
  _data = pool.allocate(_cap);
  std::strncpy(_data, data, _size);
}