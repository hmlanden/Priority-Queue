/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    total = 0;
    head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    //While there is still another element to look at:
    while (head != NULL) {
        Cell* nextCell = head->next;
        delete head;
        head = nextCell;
    }
}

int LinkedListPriorityQueue::size() {	
	return total;
}

bool LinkedListPriorityQueue::isEmpty() {	
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
    //Create a new cell.
    Cell* cell = new Cell;
    cell->word = value;
    cell->next = NULL;
    total ++;
    
    /*
     * Insert the cell into the list.
     */
    
    //If there's nothing in the list.
    if(head == NULL){
        head = cell;
        return;
    }
    //If the word appears at the beginning of the list.
    else if(cell->word < head->word){
        cell->next = head;
        head = cell;
        return;
    }
    //Otherwise, iterate through the list and insert the cell at the appropriate point.
    insertCell(head, cell);
}

string LinkedListPriorityQueue::peek() {
    //If the queue is empty, return an error to the user.
    if(isEmpty()){
        error("There are no elements to look at.");
    }
    
    //Otherwise, return the word in the first cell (because it's a sorted list).
	return head->word;
}

string LinkedListPriorityQueue::dequeueMin() {
    //If the list is empty, return an error to the user.
    if(isEmpty()){
        error("There are no elements to remove.");
    }
    
    //Obtain value to return
    string first = head->word;
    
    //Get value that will be the new head when we remove that first value.
    Cell* newHead = head->next;
    
    //Remove value that we are returning.
    delete head;
    
    //Increment size.
    total --;
    
    //Set head equal to new head value.
    head = newHead;
    
	return first;
}



/*
 * This helper function inserts the new cell into the queue when the addition
 * doesn't fall into either of the two edge cases mentioned in enqueue. It 
 * iterates through the queue until it finds where to put the new cell, as 
 * appropriate based on alphabetical order.
 */
void LinkedListPriorityQueue::insertCell(Cell* &head, Cell* &cell){
    //Start at the beginning of the list, where there is no previous cell.
    Cell* current = head;
    Cell* previous = NULL;
    
    //Iterate through the linked list until there's nothing left.
    while(current != NULL){
        
        //If it's smaller than the word we're looking at, insert new cell by linking to previous.
        if(cell->word < current->word){
            previous->next = cell;
            cell->next = current;
            return;
        }
        //If the new word is lexigraphically larger, set previous to current and move current forward.
        previous = current;
        current = current->next;
    }
    previous->next = cell;
}
