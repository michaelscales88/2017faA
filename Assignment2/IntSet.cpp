/* Programmer: Michael Scales
 * Assignment 2
 * Data Structures
 * 9/20/2017
 */
#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;


void IntSet::resize(int new_capacity)
{
   // check if we need to resize
   bool needsResize = (new_capacity != capacity) ? true : false;

   if (needsResize && (new_capacity > used))
   {
      int* tempArray = new(nothrow) int[new_capacity];
      for (int i = 0; i < used; ++i)
         tempArray[i] = data[i];

      delete [] data;
      capacity = new_capacity;
      data = tempArray;
   }
}

IntSet::IntSet(int initial_capacity)
   :capacity(initial_capacity), used(0) 
{
   if (capacity < 1) { capacity = DEFAULT_CAPACITY; }
   // return a null ptr if new fails
   data =  new(nothrow) int[capacity];
}

IntSet::IntSet(const IntSet& src)
   :capacity(src.capacity), used(src.used)
{
   // return a null ptr if new fails
   data =  new(nothrow) int[capacity];

   for (int i = 0; i < used; ++i)
      data[i] = src.data[i];
}


IntSet::~IntSet()
{
   delete [] data;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
   // check for self assignment
   if (this != &rhs)
   {
      delete [] data;
      capacity = rhs.capacity;
      used = rhs.used;
      data = new(nothrow) int[rhs.capacity];

      for (int i = 0; i < rhs.used; ++i)
         data[i] = rhs.data[i];
   }
   return *this;
}

int IntSet::size() const
{
   return used;
}

bool IntSet::isEmpty() const
{
   return (used == 0);
}

bool IntSet::contains(int anInt) const
{
   bool found = false;
   if (used > 0)
   {
      for (int i = 0; i < used; ++i)
      {
         if (data[i] == anInt)
         {
            found = true;
            break;
         }
      }
   }
   return found;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   bool isSubset = true;

   if (! isEmpty()) 
   {
      for (int i = 0; i < used; i++)
      {
         if (! otherIntSet.contains(data[i]))
         {
            isSubset = false;
            break;
         }
      }
   }
   return isSubset;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   IntSet thisSet = *this;
   for (int i = 0; i < otherIntSet.used; i++)
      thisSet.add(otherIntSet.data[i]);

   return thisSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet thisSet = *this;
   int temp;
   for (int i = used; i > 0; --i)
   {
      temp = thisSet.data[i - 1];
      if (! otherIntSet.contains(temp)) 
      {
         thisSet.remove(temp); 
      }
   }
   return thisSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   IntSet thisSet = *this;

   for (int i = 0; i < otherIntSet.used; ++i)
      thisSet.remove(otherIntSet.data[i]);
   return thisSet;
}

void IntSet::reset()
{
   used = 0;
}

bool IntSet::add(int anInt)
{
   bool success = false;
   // Check used > 0 and membership
   // Only add distinct elements
   if (! contains(anInt))
   {
      if (used == capacity) { resize(capacity * 1.25 + 1); }
      data[used] = anInt;
      ++used;
      success = true;
   }
   return success;
}

bool IntSet::remove(int anInt)
{
   bool success = false;
   // Check used > 0 and membership
   if (contains(anInt))
   {
      for (int itemIdx = 0; itemIdx < used; ++itemIdx)
         if (data[itemIdx] == anInt) 
         {
            for (int shiftPos = itemIdx; shiftPos < used; ++shiftPos)
               data[shiftPos] = data[shiftPos + 1];
            break;
         }
      used--;
      success = true;
   }
   return success;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   bool isEqual = false;
   // Empty sets are equal
   if (is1.isEmpty() && is2.isEmpty()) { isEqual = true; }
   // 1-to-1 relationships are equal
   else { isEqual = is1.isSubsetOf(is2) && is2.isSubsetOf(is1); }
   return isEqual;
}
