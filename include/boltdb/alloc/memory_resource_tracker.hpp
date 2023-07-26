#ifndef BOLTDB_CPP_MEMORY_RESOURCE_TRACKER_HPP_
#define BOLTDB_CPP_MEMORY_RESOURCE_TRACKER_HPP_

// https://github.com/phalpern/CppCon2017Code/blob/master/test_resource.cpp

#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory_resource>
#include <vector>

namespace boltdb {

// MemoryResourceTracker keeps track of the memory allocation and deallocation.
// The main purpose is to detect memory leaks.
class MemoryResourceTracker : std::pmr::memory_resource {
 public:
  explicit MemoryResourceTracker(
      std::pmr::memory_resource* upstream = std::pmr::get_default_resource())
      : _upstream(upstream),
        _bytes_allocated(0),
        _bytes_outstanding(0),
        _bytes_highwater(0) {}

  // The total number of bytes has been allocated.
  std::size_t bytes_allocated() const { return _bytes_allocated; }

  // The total number of bytes has been deallocated.
  std::size_t bytes_deallocated() const {
    return _bytes_allocated - _bytes_outstanding;
  }

  // Returns the current number of outstanding allocated bytes (memory leak).
  std::size_t bytes_highwater() const { return _bytes_outstanding; }

  std::ostream& dump(std::ostream& os) {
    os << "[bytes allocated]:" << bytes_allocated() << '\n';
    os << "[bytes deallocated]:" << bytes_deallocated() << '\n';
    os << "[bytes high water]:" << bytes_highwater() << '\n';

    return os;
  }

 protected:
  void* do_allocate(std::size_t nbytes, std::size_t alignment) override {
    void* p = _upstream->allocate(nbytes, alignment);

    _blocks.push_back(Block{p, nbytes, alignment});
    _bytes_allocated += nbytes;
    _bytes_outstanding += nbytes;
    _bytes_highwater = std::max(_bytes_highwater, _bytes_outstanding);

    return p;
  }

  void do_deallocate(void* p, std::size_t nbytes,
                     std::size_t alignment) override {
    // Check that deallocation args exactly match allocation args.
    // arguments. Note that, this check may not be necessary when this tracker
    // is used solely for internal purposes.
    auto i = std::find_if(_blocks.begin(), _blocks.end(),
                          [p](Block& block) { return block.ptr == p; });
    if (i == _blocks.end()) {
      throw std::invalid_argument("do_deallocate: Invalid pointer.");
    } else if (i->nbytes != nbytes) {
      throw std::invalid_argument("do_deallocate: Size mismatch.");
    } else if (i->alignment != alignment) {
      throw std::invalid_argument("do_deallocate: Alignment mismatch.");
    }

    _upstream->deallocate(p, i->nbytes, i->alignment);
    _blocks.erase(i);
    _bytes_outstanding -= nbytes;
  }

  bool do_is_equal(
      const std::pmr::memory_resource& other) const noexcept override {
    return this == &other;
  }

 private:
  struct Block {
    void* ptr;
    std::size_t nbytes;
    std::size_t alignment;
  };

  std::pmr::memory_resource* _upstream;
  std::pmr::vector<Block> _blocks;
  std::size_t _bytes_allocated;
  std::size_t _bytes_outstanding;
  std::size_t _bytes_highwater;
};

}  // namespace boltdb
#endif  // BOLTDB_CPP_MEMORY_RESOURCE_TRACKER_HPP_
