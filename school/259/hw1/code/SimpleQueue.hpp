/*____________________________________________________________________________
  
  FILE....: SimpleQueue.h
  CREATED.: 21 November 2001
  AUTHOR..: Vincent Scheib, Joerg Haber
  
  COMMENTS: Very simple stack template, want high efficiency.
            
  REVISION: 
            
                               Copyright (C) 2001, Vincent Scheib, Joerg Haber
  ____________________________________________________________________________*/

#ifndef SIMPLEQUEUE_H
#define SIMPLEQUEUE_H

#include <assert.h>
#include <memory.h>


template <class Type, long iResizeToNumerator = 2, long iResizeToDenominator = 1>
class SimpleQueue  
{
public:
  SimpleQueue();
  virtual ~SimpleQueue();
  
  inline void        push(const Type &element);
  inline const Type &top();
  inline void        pop();
  
  bool               isEmpty()      { return size == 0; }
  long               getSize()      { return size; }
  inline long        getCapacity()  { return capacity; }
  
private:
  Type * data;
  long   size;
  long   top_index;
  long   capacity;
};



//______________________________________________________________________________
//  Function   : ::SimpleQueue() Constructor
//  Description: 
//______________________________________________________________________________
template <class Type, long iResizeToNumerator, long iResizeToDenominator>
SimpleQueue<Type, iResizeToNumerator, iResizeToDenominator>::SimpleQueue()
{
  assert(iResizeToDenominator > 0);
  assert(iResizeToNumerator > iResizeToDenominator);
  data      = NULL;
  size      = 0;
  top_index = 0;
  capacity  = 0;
}

//______________________________________________________________________________
//  Function   : ::~SimpleQueue Destructor
//  Description: 
//______________________________________________________________________________
template <class Type, long iResizeToNumerator, long iResizeToDenominator>
SimpleQueue<Type, iResizeToNumerator, iResizeToDenominator>::~SimpleQueue()
{
  assert(size == 0); // User of queue should delete all elements.
  if (data)
    delete data;
}


//______________________________________________________________________________
//  Function   : SimpleQueue::push
//  Description: 
//______________________________________________________________________________
template <class Type, long iResizeToNumerator, long iResizeToDenominator>
void SimpleQueue<Type, iResizeToNumerator, iResizeToDenominator>::push(const Type &element)
{
  if (capacity == 0)
  {
    data = new Type [iResizeToDenominator];
    capacity = iResizeToDenominator;
  }
  else if (size == capacity)
  {
    Type *const temp_data = data;
    int old_capacity = capacity;
    capacity *= iResizeToNumerator / iResizeToDenominator;
    data = new Type [capacity];
    memcpy(data, &temp_data[top_index], sizeof(Type) * (old_capacity - top_index));
    memcpy(&data[old_capacity - top_index], temp_data, sizeof(Type) * top_index);
    delete temp_data;
    top_index = 0;
  }
  
  int index = (top_index+size)%capacity;
  data[index] = element;
  size++;
}


//______________________________________________________________________________
//  Function   : &SimpleQueue::top
//  Description: 
//______________________________________________________________________________
template <class Type, long iResizeToNumerator, long iResizeToDenominator>
const Type &SimpleQueue<Type, iResizeToNumerator, iResizeToDenominator>::top()
{
  assert(size > 0);
  assert(size <= capacity);

  return data[top_index];
}


//______________________________________________________________________________
//  Function   : SimpleQueue::pop
//  Description: 
//______________________________________________________________________________
template <class Type, long iResizeToNumerator, long iResizeToDenominator>
void SimpleQueue<Type, iResizeToNumerator, iResizeToDenominator>::pop()
{
  assert(size > 0);

  size--;
  top_index = (top_index+1)%capacity;
}

#endif // SIMPLEQUEUE_H
