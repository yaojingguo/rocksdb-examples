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

DB* createDB() {
  DB* db;
  Options options;
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  options.create_if_missing = true;

  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());
  return db;
}

void loadData(DB* db) {
  Status s = db->Put(WriteOptions(), "key1", "value1");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key2", "value2");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key3", "value3");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key4", "value4");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key6", "value6");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key8", "value8");
  assert(s.ok());
}

void testSeek(DB* db) {
  ReadOptions readOptions;
  auto iter = db->NewIterator(readOptions);
  for (iter->SeekForPrev("key5"); iter->Valid(); iter->Next()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  delete iter;
}

void scan(Iterator* iter) {
  std::cout << "scanning..." << std::endl;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
}

void testRefresh(DB* db) {
  auto iter = db->NewIterator(ReadOptions());
  scan(iter);

  auto s = db->Put(WriteOptions(), "key7", "value7");
  assert(s.ok());

  scan(iter);

  iter->Refresh();
  scan(iter);
}

class MyHandler: public rocksdb::WriteBatch::Handler {
public:
  virtual void Put(const Slice& key, const Slice& value) override {
    std::cout << "Put: " << key.ToString() << ", " << value.ToString() << std::endl;
  }
  virtual void LogData(const Slice& blob) override {
    std::cout << "LogData: " << blob.ToString() << std::endl;
  }
};

void testLogData(DB* db) {
  WriteBatch batch;
  batch.Put("name1", "xiaoyu");
  batch.PutLogData("logData1");
  batch.Put("name2", "jingguo");
  batch.Put("name3", "xuyang");
  batch.PutLogData("logData2");
  MyHandler handler;
  batch.Iterate(&handler);
  auto s = db->Write(WriteOptions(), &batch);
  assert(s.ok());
}

int main() {
  DB* db = createDB();
  loadData(db);
  // testRefresh(db);
  testLogData(db);
  delete db;
  return 0;
}
