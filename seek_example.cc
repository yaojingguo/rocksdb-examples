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

void loadKeyPrefix(DB* db) {
  Status s = db->Put(WriteOptions(), "key1", "value1");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key2", "value2");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key3", "value3");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key4", "value4");
  assert(s.ok());
  // s = db->Put(WriteOptions(), "key5", "value5");
  // assert(s.ok());
  s = db->Put(WriteOptions(), "key6", "value6");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key7", "value7");
  assert(s.ok());
  s = db->Put(WriteOptions(), "key8", "value8");
  assert(s.ok());
}

void loadKPrefix(DB* db) {
  WriteBatch batch;
  std::string keyPrefix = "k";
  std::string valPrefix = "v";
  for (int i = 0; i < 1000; i++) {
    std::string no = std::to_string(i);
    std::string key = keyPrefix + no;
    std::string val = valPrefix + no;
    batch.Put(key, val);
  }
  Status status = db->Write(WriteOptions(), &batch);
  assert(status.ok());
}
  
void loadData(DB* db) {
  loadKeyPrefix(db);
  // loadKPrefix(db);
}

void testSeek(DB* db) {
  std::cout << "Seek...\n";
  ReadOptions readOptions;
  auto iter = db->NewIterator(readOptions);
  std::cout << "Next\n";
  for (iter->Seek("key5"); iter->Valid(); iter->Next()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  iter->Refresh();
  std::cout << "Prev\n";
  for (iter->Seek("key5"); iter->Valid(); iter->Prev()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  delete iter;
}

void testSeekForPrev(DB* db) {
  std::cout << "SeekForPrev...\n";
  ReadOptions readOptions;
  auto iter = db->NewIterator(readOptions);
  std::cout << "Next\n";
  for (iter->SeekForPrev("key5"); iter->Valid(); iter->Next()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  iter->Refresh();
  std::cout << "Prev\n";
  for (iter->SeekForPrev("key5"); iter->Valid(); iter->Prev()) {
    std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  }
  delete iter;
}

void testSeekOthers(DB* db) {
  auto iter = db->NewIterator(ReadOptions());
  std::cout << "SeekToFirst\n";
  iter->SeekToFirst();
  std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
  iter->Refresh();
  std::cout << "SeekToLast\n";
  iter->SeekToLast();
  std::cout << iter->key().ToString() << ": " << iter->value().ToString() << std::endl;
}

void testSeekOps(DB* db) {
  testSeek(db);
  testSeekForPrev(db);
  testSeekOthers(db);
  // testRefresh(db);
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
  testSeekOps(db);
  // testRefresh(db);
  // testLogData(db);
  delete db;
  return 0;
}
