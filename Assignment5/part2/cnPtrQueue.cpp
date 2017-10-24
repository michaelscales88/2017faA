#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_FA17_A5P2
{
   // Constructor
   cnPtrQueue::cnPtrQueue() {}

   bool cnPtrQueue::empty() const { return numItems == 0; }

   cnPtrQueue::size_type cnPtrQueue::size() const { return numItems; }

   CNode* cnPtrQueue::front() { return new CNode; }

   void cnPtrQueue::push(CNode* cnPtr) {}

   void cnPtrQueue::pop() {}

}

