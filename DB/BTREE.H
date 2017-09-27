#ifndef __btree_h__
#define __btree_h__

typedef struct node
{
  long key;
  void *data;
  struct node *parent;
  struct node *left;
  struct node *right;
  int weight;
} bnode;

bnode* btree_init(void);

int btree_insert(bnode *root, void *data, long key);

void btree_change(bnode *root, void *data, long key);

void btree_search(bnode *root, void* data, long key);

bnode *btree_next(bnode *curr);

void btree_delete(bnode *root, long key);

void btree_nuke(bnode *root);

#endif