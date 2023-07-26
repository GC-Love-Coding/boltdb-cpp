#pragma once
#include <chrono>

namespace boltdb {

// Options represents the options that can be set when opening a database.
class Option {
 public:
  Option();
  Option(Option const&) = default;
  Option(Option&&) = default;
  Option& operator=(Option const&) = default;
  Option& operator=(Option&&) = default;

  Option& timeout(std::chrono::duration<uint64_t> timeout) noexcept;
  Option& no_grow_sync(bool no_grow_sync) noexcept;
  Option& read_only(bool read_only) noexcept;
  Option& mmap_flag(int mmap_flag) noexcept;
  Option& initial_mmap_size(int initial_mmap_size) noexcept;

  auto timeout() const noexcept -> std::chrono::duration<uint64_t>;
  auto no_grow_sync() const noexcept -> bool;
  auto read_only() const noexcept -> bool;
  auto mmap_flag() const noexcept -> int;
  auto initial_mmap_size() const noexcept -> int;

 private:
  // Timeout is the amount of time to wait to obtain a file lock.
  // When set to zero it will wait indefinitely. This option is only
  // available on Darwin and Linux.
  std::chrono::duration<uint64_t> timeout_;
  // Sets the DB.NoGrowSync flag before memory mapping the file.
  bool no_grow_sync_;
  // Open database in read-only mode. Uses flock(..., LOCK_SH |LOCK_NB) to
  // grab a shared lock (UNIX).
  bool read_only_;
  // Sets the DB.MmapFlags flag before memory mapping the file.
  int mmap_flags_;
  // InitialMmapSize is the initial mmap size of the database
  // in bytes. Read transactions won't block write transaction
  // if the InitialMmapSize is large enough to hold database mmap
  // size. (See DB.Begin for more information)
  //
  // If <=0, the initial map size is 0.
  // If initialMmapSize is smaller than the previous database size,
  // it takes no effect.
  int initial_mmap_size_;
};

}  // namespace boltdb