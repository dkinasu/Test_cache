/*
 * new_map.h
 *
 *  Created on: Feb 6, 2018
 *      Author: dkinasu
 */

#ifndef NEW_MAP_H_
#define NEW_MAP_H_
//#include "memory.h"

// default number of buckets
#define MAP_NUM_BUCKET 1024

typedef struct bucket {
  int key;
  void *value;
//  struct fp_node *value;
  struct bucket *next;
} bucket;

typedef struct my_map{
  bucket **b;  // array of bucket pointers
  size_t n;    // number of buckets
  size_t size; // how many element are currently stored
} my_map;

my_map *map_create();
my_map *map_create_n(int n);
void map_free(my_map *m);

void map_set(my_map *m, long long  key, void *value);
void map_unset(my_map *m, long long  key);

void *map_get(my_map *m, long long  key);
int map_has(my_map *m, long long key);



#endif /* NEW_MAP_H_ */
