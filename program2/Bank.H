//////////////////////////////////////////////////////////////////////
//	Title:  	Bank.H for program 2                                //
//	Date:  		07/25/2023                                          //
//	Author: 	Alexis Ouellette                                    //
//	Purpose:	The header for file for "Bank Class." This file     //
//    contains the linked list operation function prototypes.       //
//////////////////////////////////////////////////////////////////////
#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <string> 


//declaring standard input stream to make code more readable
using std::string; 
using std::cout; 
using std::endl; 

using namespace std; 

//////////////////////////////////////////////////////////
//   Bank Class                                         //
//   Purpose: This class is a linked list to hold and   //
//      manipulate the items on each bank.              //
//////////////////////////////////////////////////////////
class Bank
{
    //private members
    private:
        //structure to hold a single item in a list
        struct BankNode
        {
            string item; //value of the item
            struct BankNode* next; //pointer to the next node

        };

        BankNode *head; 
        BankNode *tail; 

    //public members
    public: 

        //constructor 
        Bank()
        {
            head = NULL; 
            tail = NULL;
        }
        
        //destuctor
        ~Bank(); 

        //linked list operations
        int getLength(); 
        void addItem(string itemName);
        void removeItem(string);
        void displayBank();
        bool containsItem(string);
        void deleteAll();

};

#endif