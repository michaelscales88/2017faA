#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2017
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity)
      :used(0),
      current_index(0),
      capacity(initial_capacity)
   {
      if (capacity < 1) capacity = 1;

      data = new(nothrow) value_type[capacity];
   }

   sequence::sequence(const sequence& source)
      :used(source.used),
      current_index(source.current_index), 
      capacity(source.capacity)
   {
      data = new(nothrow) value_type[capacity];

      for (size_type i = 0; i < used; i++)
         data[i] = source.data[i];
   }

   sequence::~sequence()
   {
      delete [] data;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      if (new_capacity < 1) new_capacity = 1;
      bool needs_resize = (new_capacity != capacity) ? true : false;
      if (needs_resize)
      {
         if (new_capacity < used) new_capacity = used; 

         value_type* tempArray = new(nothrow) value_type[new_capacity];
         for (size_type i = 0; i < used; i++)
            tempArray[i] = data[i];

         delete [] data;
         capacity = new_capacity;
         data = tempArray;
      }
   }

   void sequence::start()
   {
      current_index = 0;
   }

   void sequence::advance()
   {
      if (is_item()) current_index++;
   }

   void sequence::insert(const value_type& entry)
   {
      if (used == capacity) resize(capacity * 1.25 + 1);
      bool empty = !used && !current_index,
           no_current_item = current_index == used;
      used++;
      // No-shift cases
      if (empty) data[current_index] = entry;
      // Shift cases
      else
      {
         if (no_current_item) current_index = 0;
         for (size_type i = used - 1; i > current_index; i--)
            data[i] = data[i - 1];
         data[current_index] = entry;
      }
   }

   void sequence::attach(const value_type& entry)
   {
      if (used == capacity) resize(capacity * 1.25 + 1);
      bool empty = !used && !current_index,
           no_current_item = current_index == used;
      used++;
      // No-shift cases
      if (empty || no_current_item) data[current_index] = entry;
      // Shift cases
      else
      {
         for (size_type i = used - 1; i > current_index + 1; i--)
            data[i] = data[i - 1];
         advance();
         data[current_index] = entry;
      }
   }

   void sequence::remove_current()
   {
      if (is_item())
      {
         for (size_type i = current_index; i < used - 1; i++)
            data[i] = data[i + 1];
         used--;
      }
   }

   sequence& sequence::operator=(const sequence& source)
   {
      if (this != &source)
      {
         value_type* tempArray = new(nothrow) value_type[source.capacity];
         for (size_type i = 0; i < source.used; i++)
            tempArray[i] = source.data[i];

         delete [] data;
         data = tempArray;
         used = source.used;
         current_index = source.current_index;
         capacity = source.capacity;
      }
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used; 
   }

   bool sequence::is_item() const
   {
      return used > current_index;
   }

   sequence::value_type sequence::current() const
   {
      assert(is_item());
      return data[current_index]; 
   }
}

