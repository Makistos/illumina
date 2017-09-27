/*************************************************************************
 *
 *     !! DO NOT REMOVE THIS DISCLAIMER
 *
 *     DISCLAIMER:
 *
 *     User assumes all risks associated with the use of this module
 *     and understands said risk may include, but is not limited to,
 *     the following:
 *
 *     (1) Corruption of user data, other software applications,
 *     and/or operating software on hardware systems using this
 *     software.
 *
 *     (2) Incorrect operation of software that uses this source code.
 *
 *     (3) Corruption of user data, other software applications, and/or
 *     operating software on hardware systems using software that includes
 *     this module.
 *
 *     (4) Loss of time or resources associated with the use of
 *     this module.
 *
 *
 *     This module is written by:
 *
 *     Marko Poutiainen
 *     Rakentajantie 5D602
 *     90570 Oulu
 *     Finland
 *
 *     Tel.: +358 81 5563982
 *     Email: mep@phoenix.oulu.fi
 *     WWW: http://phoenix.oulu.fi/Åmep/
 *************************************************************************/

/*************************************************************************
 *
 *N Module BTREE
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This module contains functions to handle a balanced binary tree.
 *
 *    A balanced binary tree (btree) is a data structure in which each
 *    element has two and exactly two children and one parent. Every
 *    branch ends in NULL. The tree is balanced, when there are exactly
 *    the same amount of nodes on each side of (any) node. I.e. There
 *    are n nodes to the right of root and n nodes to the left of root.
 *    And so on.
 *
 *    A balanced btree looks like:
 *
 *                          <root>
 *                            |
 *                       -----------
 *                       |         |
 *                    <node>    <node>
 *                       |         |
 *                   --------   --------
 *                   |      |   |      |
 *                  ...    ... ...    ...
 *              ---
 *              |
 *            <node>
 *              |
 *          ---------
 *          |       |
 *         NULL    NULL
 *
 *
 *  Not all of the functions are meant to be used outside this module.
 *  External functions are named as btree_<something>.Only use these.
 *
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Compatibility
 *C
 *    This module should be ANSI C compatible.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994
 *E
 *************************************************************************/

#include <string.h>

#include "heap.h"
#include "btree.h"

/* If you don't have HEAP.H use the following lines:

#include <alloc.h>

#define my_alloc(x) malloc(x)

*/

/* Intermodule prototypes */
void insert(bnode *node,bnode *root, long size);
bnode* nodeSearch(bnode *root, long key);
void balance(bnode *root);

/*************************************************************************
 *
 *N btree_init()
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    Initializes the tree structure. Allocates memory for the first
 *    node (root).
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out> == Root of the tree.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  External Functions
 *X
 *    my_alloc  HEAP.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                           BC++ 3.1 ANSI C
 *E
 *************************************************************************/
bnode* btree_init()
{
  bnode *tmp;

  tmp=(bnode*)my_alloc(sizeof(bnode));

  tmp->parent=NULL;
  tmp->left=NULL;
  tmp->right=NULL;
  tmp->weight=0;
  tmp->key=0;
  tmp->data=NULL;

  return tmp;
}

/*************************************************************************
 *
 *N btree_insert
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    Use this function to insert nodes to the tree. This function then
 *    calls insert() to actually add the node. This function allocates
 *    memory to the node (unless it's the root).
 *E
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *A
 *    return <out>  == (int) Returns 0 if succesfull, otherwise -1.
 *    root <inout>  == (bnode*) Root of the tree.
 *    data <in>     == (void *) The data to be inserted.
 *E
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *  External Functions
 *X
 *    my_alloc  HEAP.H
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/

int btree_insert(bnode *root, void *data, long key)
{
  bnode node;
  int retval;

  if (root->left!=NULL || root->right!=NULL)
  {
    node.data=(void*)my_alloc(sizeof(data));
    if (!node.data)
      retval=-1;
    else retval=0;
    memcpy(data,node.data,sizeof(data));
    node.parent=NULL;
    node.left=NULL;
    node.right=NULL;
    node.weight=0;
    node.key=key;
    insert(&node,root,sizeof(data));
  }
  else
  {
    root->data=(void*)my_alloc(sizeof(data));
    if (!root->data)
      retval=-1;
    else retval=0;

    memcpy(data,root->data,sizeof(data));

    return retval;
  }
  balance(root);
  return retval;
}

void insert(bnode *node, bnode *root, long size)
{
  if (root==NULL)
  {
    node->parent=root;
    return;
  }

  if (root->key<node->key)
  {
    /* Insert to right */
    root->weight++;
    insert(node,root->right,size);
  }

  if (root->key>node->key)
  {
    /* Insert to left */
    root->weight--;
    insert(node,root->left,size);
  }

  if(root->key==node->key)
  {
    /* Trying to insert the same one again */
    return;
  }
}

/*************************************************************************
 *
 *N btree_change
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    Use this function to change the contents of a node's data.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    root <in> == (bnode *) The root of the tree.
 *    data <in> == (void *) The new data.
 *    key <in>  == (long) Key of the node that's data is to be changed.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/

void btree_change(bnode *root, void *data, long key)
{
  bnode *tmp;

  tmp=nodeSearch(root,key);

  if (tmp!=NULL)
    memcpy(&(tmp->data),data,sizeof(data));
  else data=NULL;
}

/*************************************************************************
 *
 *N btree_search
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    Use this function to search a node from the tree.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    root <in>    == (bnode *) Root of the tree.
 *    data <inout> == (bnode *) This is where the data from the node is
 *                    inserted.
 *    key  <in>    == (long) Key of the node.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Sep 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/
void btree_search(bnode *root, void *data, long key)
{
  bnode *tmp;

  tmp=nodeSearch(root,key);

  if (tmp!=NULL)
    memcpy(&data,tmp->data,sizeof(data));
  else data=NULL;
}

bnode* nodeSearch(bnode *root, long key)
{
  if(root->key==key)
  {
    return root;
  }
  if (root->key<key)
    nodeSearch(root->right,key);

  if (root->key>key)
    nodeSearch(root->left,key);

  if (root->right==NULL&&root->left==NULL)
  {
    return NULL;
  }

  return NULL;
}

/*************************************************************************
 *
 *N btree_next
 *
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Purpose
 *P
 *    This module is used to browse through the binary tree.
 *    The tree is browsed in the following manner:
 *    Suppose we have a tree which number is 1, it's left children is 2
 *    and right is 3. 2's left child is 4 and right is 5. 3's childrens
 *    are 6 and 7.
 *    Then the tree is browsed through in the following order:
 *    2-4-5-3-6-7. Remember, you give the root as the argument in the
 *    first call, so this function won't return it!
 *
 *    Example of usage:
 *
 *    node=root;
 *    while (node!=NULL)
 *    {
 *       Do_Something();
 *       node=btree_next(node);
 *    }
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  Parameters
 *P
 *    return <out> == (bnode *) Next node in the tree.
 *    curr <in>    == (bnode *) Current node.
 *E
 *::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 *
 *  History
 *H
 *    Marko Poutiainen  Oct 1994                          BC++ 3.1 ANSI C
 *E
 *************************************************************************/

bnode *btree_next(bnode *curr)
{
  if (curr->left) return curr->left;
  if (curr->right) return curr->right;
  while (curr->parent)
  {
    if (curr->parent->left==curr) return curr->parent->right;
    curr=curr->parent;
  }
  return NULL;
}

void btree_delete(bnode *root, long key)
{
#if 0

  bnode *tmp,*tmp2;

  while (tmp->right!=NULL && tmp->left!=NULL)
  {
    if (tmp->data==key)
    {
      tmp2=(
      if (tmp->parent->key<tmp->key)
      {
        tmp->parent->right=
      }

      if (tmp->parent->key>tmp->key)
      {

      }
    }
  }

  balance(root);

#endif
}

void balance(bnode *root)
{

}

void btree_nuke(bnode *root)
{
  if (root->right!=NULL && root->left!=NULL)
  if (root->left==NULL)
    btree_nuke(root->right);
  else btree_nuke(root->left);
}

void delNode()
{

}
