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

std::string file_path = "file1.sst";

std::string kDBPath = "db_for_ingestion";

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


int create_ingestion_file() {
  Options options;
  SstFileWriter sst_file_writer(EnvOptions(), options, options.comparator);

  // Path to where we will write the SST file
  std::string file_path = "file1.sst";

  // Open the file for writing
  Status s = sst_file_writer.Open(file_path);
  if (!s.ok()) {
    printf("Error while opening file %s, Error: %s\n", file_path.c_str(), s.ToString().c_str());
    return 1;
  }

  // Insert rows into the SST file, note that inserted keys must be
  // strictly increasing (based on options.comparator)
  std::string keyPrefix = "k";
  std::string valPrefix = "v";
  for (int i = 1; i <= 10; i++) {
    std::string no = std::to_string(i);
    std::string key = keyPrefix + no;
    std::string val = valPrefix + no;
    s = sst_file_writer.Put(key, val);
    if (!s.ok()) {
      printf("Error while adding Key: %s, Error: %s\n", key.c_str(),
          s.ToString().c_str());
      return 1;
    }
  }

  // Close the file
  s = sst_file_writer.Finish();
  if (!s.ok()) {
    printf("Error while finishing file %s, Error: %s\n", file_path.c_str(),
        s.ToString().c_str());
    return 1;
  }

  return 0;
}

int ingestion(DB* db) {
  IngestExternalFileOptions ifo;
  // Ingest the 2 passed SST files into the DB
  Status s = db->IngestExternalFile({file_path}, ifo);
  if (!s.ok()) {
    printf("Error while adding file %s, Error %s\n", file_path.c_str(), s.ToString().c_str());
    return 1;
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  assert(create_ingestion_file() == 0);
  DB* db = createDB();
  assert(ingestion(db) == 0);
  return 0;
}
