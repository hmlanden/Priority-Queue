/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

const int INDEX_INITIAL = 1;

HeapPriorityQueue::HeapPriorityQueue() {
    total = 0;
    
    //Set initial length.
    length = 10;
    
    //Initialize array of elements and set them all to NULL.
    elements = new string*[length];
    for(int i = 0; i < length; i++){
        elements[i] = NULL;
    }
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] elements;
}

int HeapPriorityQueue::size() {
	return total;
}

bool HeapPriorityQueue::isEmpty() {	
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
    //Create new node with the value as the word.
    string* newWord = new string(value);
    
    /*
     * Insert node into tree.
     */
    
    //If there's no other elements, this element becomes the root
    if(isEmpty()){
        root = newWord;
    }
    //For all other cases:
    else{
        //Find next empty spot and insert:
        elements[size() + 1] = newWord;
        
        //Swap with parent nodes as needed until tree is valid again.
        bubbleUp(elements[size() + 1], size() + 1, elements);
      
    }
    //Increment the total.
    total ++;
    
    //If necessary, grow the tree.
    if(total == length){
        growTree(elements);
    }
}

string HeapPriorityQueue::peek() {
    //If there are no elements, return error to the user.
    if(isEmpty()){
        error("There are no elements in the queue.");
    }
    
    //Return the root to the user, since it's the smallest element.
    string result = *root;
	return result;
}

string HeapPriorityQueue::dequeueMin() {
    //If there are no elements, return error to the user.
    if(isEmpty()){
        error("There are no elements in the queue.");
    }
    
    //Obtain result, which is the root.
    string result = *root;
    
    //Swap the root and the last element added.
    string* end = elements[total + 1];
    string* front = elements[1];
    front = end;
    root = front;
    
    //Reorder elements so as to maintain the integrity of the tree.
    bubbleDown(root, elements);
    
    //Increment the total.
    total --;
    
    //Return the result.
	return result;
}


/*
 * Helper Function Section
 */

/*
 * This function increases the size of the array by creating a new
 * array and copying over the elements into a new array that is twice
 * as long.
 */
void HeapPriorityQueue::growTree(string** &elements){
    //Double the length and create the new array.
    int newLength = length * 2;
    string** newArray = new string*[newLength];
    
    //Copy over elements from old array.
    for(int i = 0; i < length; i++){
        newArray[i] = elements[i];
    }
    
    //Set remaining elements to be null.
    for(int i = length + 1; i < newLength; i++){
        newArray[i] = NULL;
    }
    
    //Set instance variables equal to new values.
    length = newLength;
    elements = newArray;
    
    //Deallocate memory.
    delete newArray;
}


/*
 * This wrapper function sets up the recursive function that takes care
 * of bubbling up the new elements as needed.
 */
void HeapPriorityQueue::bubbleUp(string* &newElement, int index, string** &elements){
    string* parent = new string(*elements[index/2]);
    bubbleUpSwap(newElement, index, parent,elements);
    
}

/* RECURSION ALERT:
 *
 */
void HeapPriorityQueue::bubbleUpSwap(string* element, int index, string* parent, string** &elements){
    /* BASE CASE: 
     * We can stop swapping elements up as soon as the parent is smaller than the child.
     */
    if(parent < element || index < 1){
        return;
    }
    
    /* RECURSIVE STEP:
     * If the parent is bigger than the child, we need to swap the two. If they're equal...let's
     * just ignore that.
     */
    //Set child and parent values aside.
    string* childToSwap = element;
    string* parentToSwap = parent;
    
    //Swap the values of child and parent.
    parent = childToSwap;
    element = parentToSwap;
    
    //Recurse!
    bubbleUpSwap(element, index/2, elements[index/2], elements);
    
}



/*
 * This wrapper function sets up the recursive function that takes care 
 * of bubbling down elements after dequeueing as needed.
 */
void HeapPriorityQueue::bubbleDown(string* &root, string** &elements){
    //Initialize variables we need to track in recursion.
    string* child = new string("");
    int index = INDEX_INITIAL;
    
    //Recurse!
    bubbleDownSwap(root, index, child, elements);
    
    //Handle memory deallocation.
    delete child;
}


/* RECURSION ALERT:
 * This functions recursively bubbles down the new root after dequeueing until the binary
 * search tree is rebalanced.
 */
void HeapPriorityQueue::bubbleDownSwap(string* parent, int index, string* child, string** &elements){
    /* BASE CASE:
     * We can stop swapping elements down as soon as the child is bigger than the parent element.
     */
    if(child > parent || index > size()){
        return;
    }
    
    /* RECURSIVE STEP:
     * If the parent is bigger than either of the children, we need to swap the parent with the child
     * it is smaller than. If both children are equal, we will automatically swap with the left child.
     */
    if(hasLeftChild(index, elements)){
        string* leftChild = elements[index * 2];
        
        //If the left child is smaller than the parent, swap down.
        if(leftChild < parent){
            //Obtain original values/
            string* original = parent;
            parent = leftChild;
            
            //Swap the two.
            child = original;
            bubbleDownSwap(parent, index * 2, child, elements);
        }
    }
    if(hasRightChild(index, elements)){
        string* rightChild = elements[index * 2 + 1];
        
        if(rightChild < parent){
            //Obtain original values.
            string* original = parent;
            parent = rightChild;
            
            //Swap the two.
            child = original;
            bubbleDownSwap(parent, index * 2 + 1, child, elements);
        }
    }
}

/*
 * This function returns whether or not a left child of the parent we are
 * currently looking at exists.
 */
bool HeapPriorityQueue::hasLeftChild(int index, string** &elements){
    return elements[index * 2] != NULL;
}


/*
 * This function returns whether or not a right child of the parent we are
 * currently looking at exists.
 */
bool HeapPriorityQueue::hasRightChild(int index, string** &elements){
    return elements[index * 2 + 1] != NULL;
}