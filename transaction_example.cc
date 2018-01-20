// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#ifndef ROCKSDB_LITE

#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <rocksdb/slice.h>
#include <rocksdb/iterator.h>
#include <rocksdb/utilities/transaction.h>
#include <rocksdb/utilities/transaction_db.h>

#include <stdio.h>
#include <iostream>
#include <string>

using namespace rocksdb;

std::string kDBPath = "/tmp/rocksdb_transaction_example";

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

  int count = 9;
  
  for (int i = 0; i < count; i++) {
    int idx = i + 1;
    std::string key = "key" + std::to_string(idx);
    std::string val = "val" + std::to_string(idx);
    s = db->Put(WriteOptions(), key, val);
    assert(s.ok());
  }

  std::string val;
  for (int i = 0; i < count; i++) {
    int idx  = i + 1;
    std::string key = "key" + std::to_string(idx);
    s = db->Get(ReadOptions(), key, &val);
    assert(s.ok());
    std::cout << "key: " << key << ", val: " << val << std::endl;
  }

  std::cout << std::endl << "SeekToFirst: "<< std::endl;
  Iterator* it = db->NewIterator(ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }
  assert(it->status().ok());

  std::cout << std::endl << "Seek: " << std::endl;
  for (it->Seek("key2");
       it->Valid() && it->key().ToString() < "key5";
       it->Next()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }
  assert(it->status().ok());

  std::cout << std::endl << "SeekToLast: " << std::endl;
  for (it->SeekToLast(); it->Valid(); it->Prev()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }

  std::cout << std::endl << "SeekForPrev: " << std::endl;
  for (it->SeekForPrev("key8");
       it->Valid() && it->key().ToString() > "key1";
       it->Prev()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
  }


  delete db;
  return 0;
}

#endif  // ROCKSDB_LITE
