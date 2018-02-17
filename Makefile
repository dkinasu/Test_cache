all:
	g++ -g -o a.out main.cpp trace.cpp process.cpp cache.cpp storage.cpp memory.cpp rbtree.cpp list.cpp new_map.cpp new_cache.cpp
#   g++ -g -o test test.cpp memory.cpp storage.cpp rbtree.cpp trace.cpp process.cpp main.cpp

test: test
#   g++ -g -o test test.cpp memory.cpp storage.cpp rbtree.cpp trace.cpp process.cpp main.cpp
