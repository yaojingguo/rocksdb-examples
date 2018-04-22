include make_config.mk

ifndef DISABLE_JEMALLOC
	ifdef JEMALLOC
		PLATFORM_CXXFLAGS += -DROCKSDB_JEMALLOC -DJEMALLOC_NO_DEMANGLE
	endif
	EXEC_LDFLAGS := $(JEMALLOC_LIB) $(EXEC_LDFLAGS) -lpthread
	PLATFORM_CXXFLAGS += $(JEMALLOC_INCLUDE)
endif

ifneq ($(USE_RTTI), 1)
	CXXFLAGS += -fno-rtti
endif

.PHONY: clean librocksdb

all: simple_example column_families_example compact_files_example c_simple_example optimistic_transaction_example transaction_example compaction_filter_example options_file_example

simple_example: librocksdb simple_example.cc
	$(CXX) $(CXXFLAGS) $@.cc -o$@ -lrocksdb -I../include -O2 -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I../include

prefix_seek_example: librocksdb prefix_seek_example.cc
	rm -fr /tmp/prefix_seek_example
	$(CXX) $(CXXFLAGS) $@.cc -o$@ -lrocksdb -I../include -O2 -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

seek_example: librocksdb seek_example.cc
	rm -fr /tmp/seek_example
	$(CXX) $(CXXFLAGS) $@.cc -o$@ -lrocksdb -I../include -O2 -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

ingestion_example: librocksdb ingestion_example.cc
	$(CXX) $(CXXFLAGS) $@.cc -o$@ -lrocksdb -I../include -O2 -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

load: librocksdb load.cc
	$(CXX) $(CXXFLAGS) $@.cc -o$@ -lrocksdb -I../include -O2 -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

clean:
	rm -rf ./simple_example ./column_families_example ./compact_files_example ./compaction_filter_example ./c_simple_example c_simple_example.o ./optimistic_transaction_example ./transaction_example ./options_file_example
