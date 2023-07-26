#ifndef BOLTDB_CPP_UTIL_COMMON_HPP_
#define BOLTDB_CPP_UTIL_COMMON_HPP_

namespace boltdb {

// TODO(gc): why not use std::byte
using Byte = unsigned char;

#define DISALLOW_COPY(Typename) \
  Typename(const Typename&);    \
  void operator=(const Typename&)

}  // namespace boltdb

#endif  // BOLTDB_CPP_UTIL_COMMON_HPP_
