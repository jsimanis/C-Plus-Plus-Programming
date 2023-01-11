
// Jacquelyn Simanis and Mary Elaine Califf
//Header file for a queue of CustomerData objects

#ifndef QUEUE_H
#define QUEUE_H
#include "CustomerData.h"

class Queue
{
public:
  // constructor
  Queue();

  int getSize() { return size; }  

  bool isEmpty() { return (size==0); }

  // adds a new value to the queue
  bool enqueue(CustomerData newValue);

  // removes a value from the queue and returns it
  // Precondition: queue must not be empty
  CustomerData dequeue();

  // return item at the front of the queue without removing it
  // Precondtion: queue must not be empty
  CustomerData front() ;

private:
  struct Node
  {
    CustomerData data;
    Node* next;

    Node(CustomerData dataVal, Node* nextPtr = nullptr) : data(dataVal), next(nextPtr) {}
  }; 

 int size;
 Node* head; 
 Node* tail;

};

#endif
