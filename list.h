#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct my_list;

typedef struct page {
  struct page *next;
  struct page *prev;
  struct my_list *l;
  int addr;
} page;

page *page_create (long long addr);
void page_free (page *p);

typedef struct my_list {
  page *head;
  page *tail;
  size_t size;
} my_list;

my_list *list_create ();
void list_free (my_list *l);
page *list_remove (my_list *l, page *p);
page *list_pop_back (my_list *l);
void list_push_front (my_list *l, page *p);


#endif

