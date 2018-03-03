#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <rocksdb/slice.h>
#include <rocksdb/iterator.h>
#include <rocksdb/utilities/transaction.h>
#include <rocksdb/utilities/transaction_db.h>
#include <rocksdb/slice_transform.h>

#include <stdio.h>
#include <iostream>
#include <string>

using namespace rocksdb;

std::string kDBPath = "/tmp/seek_example";

int main() {
  DB* db;
  Options options;
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  options.create_if_missing = true;
  // options.prefix_extractor.reset(NewFixedPrefixTransform(3));

  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  s = db->Put(WriteOptions(), "key1", "value1");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key2", "value2");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key3", "value3");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key4", "value4");
  assert(s.ok());


  ReadOptions readOptions;
  readOptions.prefix_same_as_start = true;
  auto iter = db->NewIterator(readOptions);
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  delete iter;
  delete db;
  return 0;
}
