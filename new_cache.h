#ifndef NEW_CACHE_H
#define NEW_CACHE_H

#define CACHE_SIZE 2000 /*unit is pages*/


#include <stdlib.h>

#include "new_map.h"
#include "list.h"
#include "trace.h"

typedef enum { LRU, ARC, DAF } cache_type;

typedef struct {
  my_list *l;
  my_map *pages;
  int capacity;
} cache_lru;

typedef struct {
  my_list *t1, *t2, *b1, *b2;
  my_map *ghosts, *pages;
  double p;
  int capacity;
} cache_arc;

typedef struct {

  cache_type t;//LRC, ARC

  union {
    cache_lru *lru;
    cache_arc *arc;
  } data;

  unsigned long requests; //equals accesses. means total access times
  unsigned long hits;
  unsigned long adjusts;
  unsigned long accesses;

} cache;

cache *cache_create (cache_type t, int capacity);

extern cache *lru;
extern cache *arc;
extern cache *daf;


void cache_free (cache *c);

int cache_get(cache *c, long long i);//check & adjust cache
int cache_search(cache *c, long long addr);//check cache. if hit, return 1, otherwise return 0
void cache_print_stats(cache *c);


//initial LRU cache.
void Init_F_cache(int i);
//int Check_F_cache(int i, struct traceline *T_line);
void Free_F_cache(int i);
void Print_F_cache(int i);

#endif











