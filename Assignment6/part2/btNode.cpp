#include <iostream>
#include "btNode.h"
using namespace std;

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

void bst_insert(btNode*& bst_root, int insInt)
{
   if (bst_root == 0) {
      // Create root if bst is empty
      bst_root = new btNode();
      bst_root->data = insInt;
      bst_root->left = bst_root->right = 0;
   } else {
      btNode* cursor = bst_root;
      while (true) {
         // Overwrite condition
         if (cursor->data == insInt) {
            cursor->data = insInt;
            break;
         }
         // Shift conditions
         if (cursor->data > insInt) {
            if (cursor->left == 0) {
               cursor->left = new btNode();
               cursor = cursor->left;
               cursor->data = insInt;
               cursor->left = cursor->right = 0;
               break;
            } else cursor = cursor->left;
         } else {
            if (cursor->right == 0) {
               cursor->right = new btNode();
               cursor = cursor->right;
               cursor->data = insInt;
               cursor->left = cursor->right = 0;
               break;
            } else cursor = cursor->right;
         }
      }
   }
}

bool bst_remove(btNode*& bst_root, int remInt)
{
   // Base case
   if (bst_root == 0) return false;
   else {
      if (bst_root->data == remInt) {
         // Delete leaf
         if (bst_root->left == 0 && bst_root->right == 0) {
            delete bst_root;
            bst_root = 0;
         }
         // Node with one child
         else if (bst_root->left == 0) {
            btNode* cursor = bst_root;
            bst_root = bst_root->right;
            delete cursor;
         }
         else if (bst_root->right == 0) {
            btNode* cursor = bst_root;
            bst_root = bst_root->left;
            delete cursor;
         }
         // Node with two children
         else bst_remove_max(bst_root->left, bst_root->data);
         return true;
      } else {
         if (bst_root->data > remInt)
            return bst_remove(bst_root->left, remInt);
         else
            return bst_remove(bst_root->right, remInt);
      }
   }
}

void bst_remove_max(btNode*& bst_root, int& remInt)
{
   // Base case
   if (bst_root != 0) {
      // Max value
      if (bst_root->right == 0) {
         remInt = bst_root->data;
         btNode* cursor = bst_root;
         bst_root = bst_root->left;
         delete cursor;
      } else bst_remove_max(bst_root->right, remInt);
   }
}
