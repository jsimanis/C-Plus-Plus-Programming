// Jacquelyn Simanis
// Implementation of a queue of CustomerData objects

#include "Queue.h"

Queue::Queue(){
    size =0;
    head= nullptr;
    tail = nullptr;
}

//add to end of line
bool Queue::enqueue(CustomerData newValue){
    Node* newNode = new Node (newValue, nullptr);

    if (head){ //list is not empty
        tail->next = newNode;
        tail = newNode;
        size++;
        return true;
    }
    else{ //list is empty
        head = newNode;
        tail = newNode;
        size++; 
        return true;
    }
    
}

CustomerData Queue::dequeue(){
    
    CustomerData firstCust = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return firstCust;
}

CustomerData Queue::front(){
    return head->data;
}
