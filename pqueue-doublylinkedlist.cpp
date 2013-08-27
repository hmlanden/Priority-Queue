/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    total = 0;
    head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while(head != NULL){
        Cell* next = head->next;
        delete head;
        head = next;
    }
}

int DoublyLinkedListPriorityQueue::size() {
	return total;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {	
	return size() == 0;
}


void DoublyLinkedListPriorityQueue::enqueue(string value) {
    //Crate a new cell with the value given.
    Cell* cell = new Cell;
    cell->word = value;
    cell->next = head;
    cell->previous = NULL;
    
    /*
     * Enqueue the cell as appropriate, adjusting the head pointer.
     */
    
    //If there are no other cells, the new cell is the head.
    if(isEmpty()){
        head = cell;
    }
    //In all other cases, put the cell in front of the head and make it the new head.
    else{
        head->previous = cell;
        head = cell;
    }
    
    //Increment the total number of cells.
    total ++;
}


string DoublyLinkedListPriorityQueue::peek() {
    //If the queue is empty, return an error to the user.
    if(isEmpty()){
        error("No elements to look at.");
    }
    
    //Find the first word.
    string firstWord = findFirstWord();
    
	return firstWord;
}


string DoublyLinkedListPriorityQueue::dequeueMin() {
    //If the queue is empty, return an error to the user.
    if(isEmpty()){
        error("No elements to dequeue.");
    }
    string firstWord;
    
    //Remove the word we're dequeueing and fix all the pointers, and get the word to return.
    removeFirstWord(firstWord);
    
    //Increment the total.
    total--;
    
    //Return the word we are dequeueing.
	return firstWord;
}



/*
 * This helper method iterates through the linked list and finds the first word, and
 * sets the first pointer to point at that word. It finds the first word by constantly
 * updating the first pointer and firstWord to be the smallest word we've seen so far.
 */
string DoublyLinkedListPriorityQueue::findFirstWord(){
    string firstWord = head->word;
    Cell* current = head;
    first = head;
    
    //While we still have elements to look at:
    while(current != NULL){
        
        //If the word we're looking at is smaller than our current first word:
        if(current->word < firstWord){
            
            //Set our first word to be the word we're looking at.
            first = current;
            firstWord = first->word;
        }
        
        //Move forward to next cell in the list.
        current = current->next;
    }
    return firstWord;
}



/*
 * This helper method removes the word we will be returning and resets
 * all the pointers that are involved (i.e. head, first, and the previous/next
 * pointers of the cells on either side of the cell being removed.
 */
void DoublyLinkedListPriorityQueue::removeFirstWord(string &firstWord){
    
    //Get first word, which will be returned as an output parameter.
    firstWord = DoublyLinkedListPriorityQueue::findFirstWord();
    
    //Get the previous and next cells of the cell we are going to remove.
    Cell* previousCell = first->previous;
    Cell* nextCell = first->next;
    
    
    /*
     * Reset the previous, next, and head pointers depending on what is and isn't null.
     */
    
    //If previous is null, then we are looking at the head of the list and need to update the head.
    if(previousCell == NULL){
        head = nextCell;
    }
    //If previous isn't null, we can update the previous pointer as normal.
    else{
        previousCell->next = nextCell;
    }
    
    
    //If next is null, we are looking at the end of the list and don't do anything.
    //Otherwise, link previous and next cell.
    if(nextCell != NULL){
        nextCell->previous = previousCell;
    }
    
    
    /*
     * Delete the cell we are dequeueing.
     */
    delete first;
    first = head;
}

