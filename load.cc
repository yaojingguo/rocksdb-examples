// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>

#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>

using namespace rocksdb;

std::string kDBPath = "db";

int main() {
  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  // Put key-value

  // std::string value;
  //
  // WriteOptions writeOptions;
  // std::string keySuffix = "key";
  // std::string valSuffix = "val";
  // for (int i = 1; i < 1000; i++) {
  //   std::string no = std::to_string(i);
  //   s = db->Put(WriteOptions(), no + keySuffix , no + valSuffix);
  //   assert(s.ok());
  // }
  // db->Flush(FlushOptions());

  // get value
  // s = db->Get(ReadOptions(), "key1", &value);
  // assert(s.ok());
  // assert(value == "value");

  // // atomically apply a set of updates
  // {
  //   WriteBatch batch;
  //   batch.Delete("key1");
  //   batch.Put("key2", value);
  //   s = db->Write(WriteOptions(), &batch);
  // }
  //
  // s = db->Get(ReadOptions(), "key1", &value);
  // assert(s.IsNotFound());
  //
  // db->Get(ReadOptions(), "key2", &value);
  // assert(value == "value");

  // {
  //   PinnableSlice pinnable_val;
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  //   assert(pinnable_val == "value");
  // }

  // {
  //   std::string string_val;
  //   // If it cannot pin the value, it copies the value to its internal buffer.
  //   // The intenral buffer could be set during construction.
  //   PinnableSlice pinnable_val(&string_val);
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  //   assert(pinnable_val == "value");
  //   // If the value is not pinned, the internal buffer must have the value.
  //   assert(pinnable_val.IsPinned() || string_val == "value");
  // }

  // PinnableSlice pinnable_val;
  // db->Get(ReadOptions(), db->DefaultColumnFamily(), "key1", &pinnable_val);
  // assert(s.IsNotFound());
  // // Reset PinnableSlice after each use and before each reuse
  // pinnable_val.Reset();
  // db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  // assert(pinnable_val == "value");
  // pinnable_val.Reset();
  // // The Slice pointed by pinnable_val is not valid after this point

  delete db;

  return 0;
}
