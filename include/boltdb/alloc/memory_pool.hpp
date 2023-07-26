#ifndef BOLTDB_CPP_MEMORY_POOL_HPP_
#define BOLTDB_CPP_MEMORY_POOL_HPP_

#include <cstddef>
#include <memory_resource>
#include <sstream>
#include <string>

#include "boltdb/alloc/memory_resource_tracker.hpp"
#include "boltdb/util/common.hpp"

namespace boltdb {

// The MemoryPool class provides memory allocation and deallocation services.
// It utilizes the Singleton Pattern to ensure a single instance of the pool
// exists. The MemoryPool attempts to allocate small-sized blocks (< PageSize/4)
// to the stack and large-sized blocks to the heap. However, due to the upstream
// resource being 'new_delete_resource', small-sized blocks may also be
// allocated to the heap if the total size exceeds 1MB.
class MemoryPool {
 public:
  static constexpr int kPageSize = (1 << 10);        // 4096
  static constexpr int kInitBufferSize = (1 << 20);  // 1 M

  // Get a singleton pool instance.
  static MemoryPool& instance() {
    static MemoryPool pool;

    return pool;
  }

  // Allocate a block of memory with the specified number of bytes.
  // Returns a pointer to the allocated memory block.
  // Note: the caller is responsible for managing the lifetime of the allocated
  // memory.
  Byte* allocate(std::size_t nbytes) {
    if (is_small_size(nbytes)) {
      return _stack_pool.allocate(nbytes);
    }

    return _heap_pool.allocate(nbytes);
  }

  // Deallocate a previously allocated memory block specified by the pointer 'p'
  // and the number of bytes 'nbytes'. It is essential to deallocate exactly the
  // same pointer and bytes returned by the corresponding `allocate` method.
  // Otherwise, an 'invalid_argument' exception will be thrown. Users are
  // responsible for ensuring proper deallocation to avoid memory-related
  // issues.
  void deallocate(Byte* p, std::size_t nbytes) {
    if (is_small_size(nbytes)) {
      return _stack_pool.deallocate(p, nbytes);
    }

    _heap_pool.deallocate(p, nbytes);
  }

  // The total number of bytes has been allocated.
  std::size_t bytes_allocated() const {
    return _stack_tracker.bytes_allocated() + _heap_tracker.bytes_allocated();
  }

  // The total number of bytes has been deallocated.
  std::size_t bytes_deallocated() const {
    return _stack_tracker.bytes_deallocated() +
           _heap_tracker.bytes_deallocated();
  }

  // Get statistic information, including number of bytes have been allocated
  // and deallocated, and high water bytes.
  std::string statistic() const {
    std::ostringstream oss;

    oss << "=== stack allocation info ===\n";
    _stack_tracker.dump(oss);

    oss << "=== heap allocation info ===\n";
    _heap_tracker.dump(oss);

    return oss.str();
  }

 protected:
  MemoryPool()
      : _buffer(kInitBufferSize),
        _stack_tracker(&_buffer),
        _heap_tracker(std::get_default_resource()),
        _stack_pool(&_stack_tracker),
        _heap_pool(&_heap_tracker) {}

 private:
  static bool is_small_size(std::size_t nbytes) {
    return nbytes < (kPageSize / 4);
  }

  std::pmr::monotonic_buffer_resource _buffer;
  MemoryResourceTracker _stack_tracker;
  MemoryResourceTracker _heap_tracker;
  std::pmr::polymorphic_allocator<Byte> _stack_pool;
  std::pmr::polymorphic_allocator<Byte> _heap_pool;
};

}  // namespace boltdb

#endif  // BOLTDB_CPP_MEMORY_POOL_HPP_
