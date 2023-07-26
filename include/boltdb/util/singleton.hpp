#ifndef BOLTDB_CPP_UTIL_SINGLETON_HPP_
#define BOLTDB_CPP_UTIL_SINGLETON_HPP_

#include "boltdb/util/common.hpp"

namespace boltdb {

template <typename Subject>
struct Singleton {
 public:
  static Subject& instance() {
    static Subject instance;

    return instance;
  }

 protected:
  Singleton() = default;

 private:
  DISALLOW_COPY(Singleton);
};

}  // namespace boltdb

#endif  // BOLTDB_CPP_UTIL_SINGLETON_HPP_
