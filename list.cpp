#include "list.h"

page *page_create (long long addr) {
  page *p = (page*)malloc(sizeof(page));
  p->addr = addr;
  p->next = NULL;
  p->prev = NULL;
  p->l = NULL;
  return p;
}

void page_free (page *p) {
  free(p);
}

my_list *list_create () {
	my_list *l = (my_list*)malloc(sizeof(my_list));
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
  return l;
}

void list_free (my_list *l) {
  page *temp = l->head, *next;

  while (temp != NULL) {
    next = temp->next;
    page_free(temp);
    temp = next;
  }

  free(l);
}

page *list_remove (my_list *l, page *p) {

  // remove p from list
  if (l->size == 1) {
    l->head = NULL;
    l->tail = NULL;
  } else {
    if (l->tail == p) {
      l->tail = p->prev;
      l->tail->next = NULL;
    } else if (l->head == p) {
      l->head = p->next;
      l->head->prev = NULL;
    } else {
      p->prev->next = p->next;
      p->next->prev = p->prev;
    }
  }

  p->l = NULL;

  l->size--;

  return p;
}

page *list_pop_back (my_list *l) {
  if (l->size == 0) {
    return NULL;
  } else {
    return list_remove(l, l->tail);
  }
}

void list_push_front (my_list *l, page *p) {

  // insert at front
  if (l->size == 0) {
    l->head = p;
    l->tail = p;
  } else {
    p->next = l->head;
    l->head->prev = p;
    l->head = p;
    p->prev = NULL;
  }

  p->l = l;

  l->size++;
}


