//////////////////////////////////////////////////////////////////////
//	Title:  	Main.cpp for program 2                              //
//	Date:  		07/25/2023                                          //
//	Author: 	Alexis Ouellette                                    //
//	Purpose:	The implementation of a singly-linked list for the  //
//   fox, chicken, and grain game. The game logic is expressed here //
//////////////////////////////////////////////////////////////////////
#include "Bank.H"

#include <iostream>
#include <fstream>
#include <string> 

//declaring standard input stream to make code more readable
using std::string; 
using std::cout; 
using std::endl; 
using namespace std; 

//function defintions
void displayGameInstructions();
void initializeGame(Bank& south, Bank& north);
bool checkGameState(Bank& south, Bank& north, string farmer);
int lossCondition(Bank& south, Bank& north, string farmer);

int main()
{
    //define Bank objects for each bank
    Bank north; 
    Bank south; 

    string farmer; //holds farmers location
    string item;  //holds user choice of item

    bool okMove = false;  //checks for valid move
    bool playAgain = true; //to keep loop going until user quits
    char choice; //user choice to play again 
   
    ofstream outFile("FarmerGame.txt");  //outfile for results of win

    //display the game instructions 
    displayGameInstructions(); 

    //initialize the banks 
    initializeGame(south, north);

    //farmer's location initialized to the south bank
    farmer = "south";

    do
    {
    //while loop to play until the game is over or user wants to quit
    while(checkGameState(south, north, farmer) == true )
    {
        //display banks
        cout << "\n\nSouth Bank: " << endl;
        south.displayBank();
        cout <<  "\nNorth Bank: " << endl;
        north.displayBank(); 

        //display banks to file
        outFile << "\n\nSouth Bank: " << endl;
        outFile << "\nNorth Bank: " << endl;

        //display farmers location 
        cout << "\nThe farmer is on the " << farmer << " bank." << endl; 

        //get user input
        cout << "\nWhat should the farmer take with him?: "; 
        getline(cin, item); 

        //send to file
        outFile << "\nThe farmer is on the " << farmer << " bank." << endl; 
        outFile << "\nWhat should the farmer take with him?: " << item << endl; 

            //if farmer is in the south bank
            if(farmer == "south")
            {
                //if user chooses nothing 
                if(item == "nothing")
                {
                    cout << "\nThe farmer takes nothing with him." << endl;
                    outFile << "\nThe farmer takes nothing with him." << endl;
                    farmer = "north"; //move farmer to opposite bank 
                }

                //check if viable move 
                okMove = south.containsItem(item);

                //if viable move
                if(okMove == true)
                {
                    south.removeItem(item); //remove from south bank
                    north.addItem(item); //add to northbank 
                    farmer = "north"; //movev farmer to oppoiste bank

                    cout << "\nThe farmer takes the " << item << " with him." << endl; 
                    outFile << "\n\nThe farmer takes the " << item << " with him." << endl;
                }
            }

            //if the farmer is on the north bank
            else if(farmer == "north")
            {
                if(item == "nothing")
                {
                    cout << "\nThe farmer takes nothing with him." << endl;
                    outFile << "\nThe farmer takes nothing with him." << endl;
                    
                    farmer = "south"; 
                }

                //check if viable move
                okMove = north.containsItem(item);

                //if viable move
                if(okMove == true)
                {
                    north.removeItem(item); //remove from north bank
                    south.addItem(item); //add to south bank
                    farmer = "south"; //move farmer location 

                    cout << "\nThe farmer takes the " << item << " with him." << endl;
                    outFile << "\nThe farmer takes the " << item << " with him." << endl;
                }
            }

        //check game condition 
        if(checkGameState(south, north, farmer) == false)
        {
            //determines which condition caused the loss and 
            // prints the results
            int cond = 0; 
            cond = lossCondition(south, north, farmer);

            if(cond == 1 || cond == 2)
            {
                cout << "\nThe fox ate the chicken! You lost!" << endl;
                outFile << "\nThe fox ate the chicken! You lost!" << endl;
            }

            else if(cond == 3 || cond == 4)
            {
                cout << "The chicken ate the grain! You lost!" << endl; 
                outFile << "The chicken ate the grain! You lost!" << endl; 
            }

            cout << "Do you want to play again (y/n): " << endl;
            cin >> choice; 
            outFile << "Do you want to playAgain (y/n):  " << choice << endl;
            
            //ask user if they want to play again 
            if(choice != 'y' || choice != 'Y')
            {
                playAgain = false; 
            }
            //reinitialize game
            else if(choice == 'y' || choice == 'Y')
            {               
                playAgain = true; 
                initializeGame(south, north);
                farmer = "south"; 
            }
        }
        
        //check if game is won - if all 3 items are on the north bank
        else if(north.getLength() == 3)
        {
            cout << "Yay! The farmer got his fox, chicken, and grain safely across the river! You won!" << endl;
            cout << "Do you want to playAgain (y/n): ";
            cin >> choice; 

            outFile << "Yay! The farmer got his fox, chicken, and grain safely across the river! You won!" << endl;
            outFile << "Do you want to playAgain (y/n): " << choice << endl;

            if(choice != 'y' || choice != 'Y')
            {
                playAgain = false; 
            }

            else if(choice == 'y' || choice == 'Y')
            {               
                playAgain = true; 
                initializeGame(south, north);
                farmer = "south"; 
            }

        }
        }
    }while(playAgain == true); 
    
    return 0; 
   }
        
//////////////////////////////////////////////////////////
//   name:  displayGameInstructions()                   //
//   purpose: this function displays the game rules     //        
//////////////////////////////////////////////////////////  
void displayGameInstructions()
{
   cout << "\n     Welcome to Fox, Chicken, and Grain!" << endl; 

   cout << "\nA farmer must get his fox, chicken, and grain safely" << endl; 
   cout << "across a river from the south bank to the north bank." << endl;
   cout << "The farmer can take at most one thing with him when" << endl; 
   cout << "he makes a trip across. Unfortunately, if the farmer" << endl; 
   cout << "leaves the fox and the chicken together, the fox will" << endl; 
   cout << "eat the chicken. If the farmer leaves the chicken" << endl; 
   cout << "and the grain together, the chicken will eat the grain." << endl; 

   cout << "Help the farmer by entering the name of what you" << endl; 
   cout << "want him to carry on his next trip to the opposite bank." << endl; 
   cout << "If you want the farmer to cross the river without" << endl; 
   cout << "carrying anything, enter 'nothing' at the prompt." << endl; 
}

//////////////////////////////////////////////////////////
//   name:  initializeGame(Bank& south, Bank& north)    //
//   purpose: this function sets the beginning game     //
//     state                                            //
//////////////////////////////////////////////////////////  
void initializeGame(Bank& south, Bank& north)
{
    //clear the list 
    south.deleteAll();
    north.deleteAll(); 

    //add the items
    south.addItem("fox");
    south.addItem("chicken");
    south.addItem("grain");
}

/////////////////////////////////////////////////////////////////////////
//   name:  checkGameState(Bank& south, Bank& north, string farmer)    //
//   purpose:  thid function checks for an losing condition  and       //
//      returns false to end the game if a loss condition is found,    //
//      reutrns true if no loss condition is found                     //
/////////////////////////////////////////////////////////////////////////
bool checkGameState(Bank& south, Bank& north, string farmer)
{

    if(south.containsItem("fox") && south.containsItem("chicken") && (farmer == "north"))
    {
        return false; 
    }
    if(north.containsItem("fox") && north.containsItem("chicken") && (farmer == "south"))
    {
        return false; 
    }
    if(south.containsItem("chicken") && south.containsItem("grain") && (farmer == "north"))
    {
        return false; 
    }
    if(north.containsItem("chicken") && north.containsItem("grain") && (farmer == "south"))
    {
        return false; 
    }

    return true; 
}

/////////////////////////////////////////////////////////////////////////
//   name:  lossCondition(Bank& south, Bank& north, string farmer)     //
//   purpose:  this function determines which condition was the losing //
//      one and returns the intergar assigned to it                    //
/////////////////////////////////////////////////////////////////////////
int lossCondition(Bank& south, Bank& north, string farmer)
{   
    int lostCond = 0; 

    if(south.containsItem("fox") && south.containsItem("chicken") && (farmer == "north"))
    {
        lostCond = 1;  
    }
    if(north.containsItem("fox") && north.containsItem("chicken") && (farmer == "south"))
    {
        lostCond = 2; 
    }
    if(south.containsItem("chicken") && south.containsItem("grain") && (farmer == "north"))
    {
        lostCond = 3; 
    }
    if(north.containsItem("chicken") && north.containsItem("grain") && (farmer == "south"))
    {
        lostCond = 4; 
    }

    return lostCond; 
}