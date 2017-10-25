#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_FA17_A5P2
{
   // Constructor
   cnPtrQueue::cnPtrQueue()
   :numItems(0) {}

   bool cnPtrQueue::empty() const { return numItems == 0; }

   cnPtrQueue::size_type cnPtrQueue::size() const { return numItems; }

   CNode* cnPtrQueue::front()
   {
      if (outStack.empty())
      {
         // Flush inStack
         while (!inStack.empty())
         {
            outStack.push( inStack.top() );
            inStack.pop();
         }
      }
      return outStack.top();
   }

   void cnPtrQueue::push(CNode* cnPtr)
   {
      inStack.push(cnPtr);
      numItems++;
   }

   void cnPtrQueue::pop()
   {
      if (outStack.empty())
      {
         // Flush inStack
         while (!inStack.empty())
         {
            outStack.push( inStack.top() );
            inStack.pop();
         }
      }
      outStack.pop();
      numItems--;
   }
}

