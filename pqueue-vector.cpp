/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
    wordIndex = 0;
}

VectorPriorityQueue::~VectorPriorityQueue() {

}

int VectorPriorityQueue::size() {	
	return wordList.size();
}

bool VectorPriorityQueue::isEmpty() {
	return VectorPriorityQueue::size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
    wordList.push_back(value);
}

string VectorPriorityQueue::peek() {
    //If there are no elements in queue, return error to user.
    if(wordList.isEmpty()){
        error("No words in list.");
    }
    
    //Otherwise, find next word and return value.
    string nextWord = findNextWord(wordList);
    return nextWord;
}

string VectorPriorityQueue::dequeueMin() {
    //If there are no elements in queue, return error to user.
    if(wordList.isEmpty()){
        error("No words in list");
    }
    
    //Otherwise, find next word.
    string nextWord = findNextWord(wordList);
    
    //Remove word from queue.
    wordList.remove(wordIndex);
    
    //Reset wordIndex value.
    wordIndex = 0;
    
    return nextWord;
}


/*
 * This helper function finds the word we want to return. It does so by
 * iterating through the entire vector, setting the nextWord variable to 
 * be the smallest value at every turn.
 */
string VectorPriorityQueue::findNextWord(Vector<string> &wordList){
    wordIndex = 0;
    string nextWord = wordList[0];
    
    //Iterate through entire vector.
    for(int i = 0; i < wordList.size(); i++){
        
        //If the current word is smaller than our previous smallest word, set it to be nextWord.
        if(wordList[i] < nextWord){
            nextWord = wordList[i];
            wordIndex = i;
        }
    }
    
    //Return result.
    return nextWord;
}

