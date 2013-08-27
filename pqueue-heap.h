/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
    string* root;
    string** elements;
    
    //Keep track of total number of elements.
    int total;
    
    //The current length of the array and the function to grow it.
    int length;
    void growTree(string**&);
    
    //Helper functions for bubbling up values.
    void bubbleUp(string*&, int, string**&);
    void bubbleUpSwap(string*,int, string*,string**&);
    
    //Helpers functions necessary to bubble down values.
    void bubbleDown(string*&, string**&);
    void bubbleDownSwap(string*, int, string*, string**&);
    bool hasLeftChild(int, string**&);
    bool hasRightChild(int, string**&);

};

#endif
