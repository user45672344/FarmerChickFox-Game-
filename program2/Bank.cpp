//////////////////////////////////////////////////////////////////////
//	Title:  	Bank.cpp for program 2                              //
//	Date:  		07/25/2023                                          //
//	Author: 	Alexis Ouellette                                    //
//	Purpose:	The file contains the implementations of the linked //
//    list operations.                                              //
//////////////////////////////////////////////////////////////////////
#include "Bank.H"

#include <iostream>
#include <fstream>
#include <string> 

//declaring standard input stream to make code more readable
using std::string; 
using std::cout; 
using std::endl; 

//////////////////////////////////////////////////////////
//   name: getLength()                                  //
//   purpose: this function calculations the number of  //
//     elements in the list and returns that number     //  
//////////////////////////////////////////////////////////         
int Bank::getLength()
{
    int count = 0; 
    BankNode* nodePtr = head; 
    while(nodePtr != NULL)
    {
        count++;
        nodePtr = nodePtr->next; 
    }
    return count; 
}

//////////////////////////////////////////////////////////
//   name: addItem(string itemName                      //
//   purpose: this function adds a new element to the   //  
//     list                                             //
//////////////////////////////////////////////////////////    
void Bank::addItem(string itemName)
{
   //create a new node and set next pointer to null
    BankNode* newNode; 
    newNode = new BankNode; 
    newNode->item = itemName; 
    newNode->next = NULL; 

    //if the list is empty
   if(head == NULL)
   {
        head = newNode; 
        tail = newNode;
   }

    //if the list is not empty 
    else
    {
        //end node points to new node and tail is set to 
        // the new node
        tail->next = newNode; 
        tail = newNode; 
    }

}

//////////////////////////////////////////////////////////
//   name: removeIem(string itemName)                   //
//   purpose: this functions deletes an item from the   //
//      lidt
//////////////////////////////////////////////////////////  
void Bank::removeItem(string itemName)
{
    BankNode* nodePtr; //pointer to traverse the list
    BankNode* prev; //pointer to point to the previoud node

    //if list is empty no nothing
    if(!head)
        return; 

    //check if the first node is it 
    if(head->item == itemName)
    {
        nodePtr = head->next; 
        delete head; 
        head = nodePtr; 
    }
    //if it is not it
    else 
    {
        nodePtr = head; 

        //skip nodes until its found 
        while(nodePtr != NULL && nodePtr->item != itemName)
        {
            prev = nodePtr;
			nodePtr = nodePtr->next;
        }

        //if pointer is not at the end of the list
        if (nodePtr)
		{
			if(nodePtr == tail)
			{
				tail = prev;
			}
            //link previous node to the node after
			prev->next = nodePtr->next;

            //delete the pointer 
			delete nodePtr;
		}
    }
}

//////////////////////////////////////////////////////////
//   name: displayBank()                                //
//   purpose: this function will display all the items  //
//     that are in the list
//////////////////////////////////////////////////////////  
void Bank::displayBank() 
{
    //if empty 
    if(!head)
    {
        cout << "<Empty>" << endl;
    }

    //while curr node is the head node the items
    // will be printed it 
    BankNode* curr;
    curr = head; 
    while(curr)
    {
        cout << curr->item << endl;
        curr = curr->next; 
    } 
}

//////////////////////////////////////////////////////////
//   name: containsItem(string itemName)                //
//   purpose: this function searches through the list   //
//     and returns true if the item is found and false  //
//     if the item is not found 
//////////////////////////////////////////////////////////  
bool Bank::containsItem(string item)
{
    bool foundItem = false; 
    BankNode* nodePtr; //pointer to traverse the list

    nodePtr = head; 

    //if node is not pointing to null
    while(nodePtr != NULL)
    {
        if(nodePtr->item == item)
        {
            foundItem = true; 
            return true; 
        }
        //go through the list 
        nodePtr = nodePtr->next; 
    }

    //if pointer is empty 
    if(nodePtr == NULL)
    {
        foundItem = false; 
        return false; 
    }
    
    return foundItem; 

}

//////////////////////////////////////////////////////////
//   name:  deleteAll()                                 //
//   purpose: this function will delete all the current // 
//     nodes in the list to initialize a new game       //        
//////////////////////////////////////////////////////////  
void Bank::deleteAll()
{
    BankNode* nodePtr = head; 

    while(head != NULL)
    {
        head = nodePtr->next; 
        delete nodePtr; 

        nodePtr = head; 
    }
}

//destuctor
Bank::~Bank()
{
	BankNode* nodePtr;   //to traverse the list
	BankNode* nextNode;  //points to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not empty
	while (nodePtr != NULL)
	{
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;
        
		nodePtr = nextNode; 
    }
}