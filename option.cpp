#include "option.h"

namespace boltdb {

Option::Option() {}

Option& Option::timeout(std::chrono::duration<uint64_t> timeout) noexcept {
  timeout_ = timeout;

  return *this;
}

Option& Option::no_grow_sync(bool no_grow_sync) noexcept {
  no_grow_sync_ = no_grow_sync;

  return *this;
}

Option& Option::read_only(bool read_only) noexcept {
  read_only_ = read_only;

  return *this;
}

Option& Option::mmap_flag(int mmap_flag) noexcept {
  mmap_flags_ = mmap_flag;

  return *this;
}

Option& Option::initial_mmap_size(int initial_mmap_size) noexcept {
  initial_mmap_size_ = initial_mmap_size;

  return *this;
}

auto Option::timeout() const noexcept -> std::chrono::duration<uint64_t> {
  return timeout_;
}

auto Option::no_grow_sync() const noexcept -> bool { return no_grow_sync_; }

auto Option::read_only() const noexcept -> bool { return read_only_; }

auto Option::mmap_flag() const noexcept -> int { return mmap_flags_; }

auto Option::initial_mmap_size() const noexcept -> int {
  return initial_mmap_size_;
}

}  // namespace boltdb