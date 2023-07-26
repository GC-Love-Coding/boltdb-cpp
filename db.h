#pragma once

#include <fstream>
#include <string>

namespace boltdb {

// DB represents a collection of buckets persisted to a file on disk.
// All data access is performed through transactions which can be obtained
// through the DB. All the functions on DB will return a ErrDatabaseNotOpen if
// accessed before Open() is called.
class DB {
 public:
 private:
  // When enabled, the database will perform a Check() after every commit.
  // A panic is issued if the database is in an inconsistent state. This
  // flag has a large performance impact so it should only be used for
  // debugging purposes.
  bool strict_mode_;

  // Setting the NoSync flag will cause the database to skip fsync()
  // calls after each commit. This can be useful when bulk loading data
  // into a database and you can restart the bulk load in the event of
  // a system failure or database corruption. Do not set this flag for
  // normal use.
  //
  // If the package global IgnoreNoSync constant is true, this value is
  // ignored.  See the comment on that constant for more details.
  //
  // THIS IS UNSAFE. PLEASE USE WITH CAUTION.
  bool no_sync_;

  // When true, skips the truncate call when growing the database.
  // Setting this to true is only safe on non-ext3/ext4 systems.
  // Skipping truncation avoids preallocation of hard drive space and
  // bypasses a truncate() and fsync() syscall on remapping.
  //
  // https://github.com/boltdb/bolt/issues/284
  bool no_grow_sync_;

  // If you want to read the entire database fast, you can set MmapFlag to
  // syscall.MAP_POPULATE on Linux 2.6.23+ for sequential read-ahead.
  int mmap_flags_;

  // MaxBatchSize is the maximum size of a batch. Default value is
  // copied from DefaultMaxBatchSize in Open.
  //
  // If <=0, disables batching.
  //
  // Do not change concurrently with calls to Batch.
  int max_batch_size_;

  // MaxBatchDelay is the maximum delay before a batch starts.
  // Default value is copied from DefaultMaxBatchDelay in Open.
  //
  // If <=0, effectively disables batching.
  //
  // Do not change concurrently with calls to Batch.
  long max_batch_delay_;

  // AllocSize is the amount of space allocated when the database
  // needs to create new pages. This is done to amortize the cost
  // of truncate() and fsync() when growing the data file.
  int alloc_size_;

  std::string path_;
};

}  // namespace boltdb