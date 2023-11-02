//Connor Sullivan
//Sep-13-2023
//COCS220

//Librarys
#include <fstream>
#include <iostream>
#include <cmath>
#include "Link.h"

using namespace std;



int main(){
//Head of list
Node* head = NULL;//Head of list

//Streams
ifstream input;
ofstream output;

//Variables for item
float subTotal = 0;
int number = -1; //User input
char name[50];//name of food
char tax; //tax
char sale; //Unit measurment
int current;//Current item
float price;//Price
bool found; //Flag if found
	    
//Open file
input.open("item.txt", ios::in);
if(!input){
	cerr << "No file found" <<endl;
	exit(1);
}

//Main Loop
int userInput = -1;
while(userInput != 4){
	//Validate input
	cout << "\n1: Add Item\n2: Delete Item\n3: Print List\n4: Quit\nEnter: ";	
	while(!(cin >> userInput)){
		cout << "1: Add Item\n2: Delete Item\n3: Print List\n4: Quit\nEnter: ";	
		cin.clear();
		cin.ignore();
		continue;
	}
	switch(userInput){
		//Case 1: Input to list
		case 1:
			found = false;//Set found to false initally For each item being searched

			//Reset the search 
			input.clear();
			input.seekg(0);

			//Get the item number	      
			cout << "\nEnter Item Number: ";
			while(!(cin >> number)){ //This validates user input
				cout << "\nError enter a number: ";
				cin.clear();
				cin.ignore();
			}

			//Begin the linear search
			while(!input.eof() && !found){
				while(input >> current >> name >> tax >> sale >> price){
					if(current == number){
						found = true;
						break;
					}
				}

			}

			//If found add to list
			if(!found)
				cout << "\nItem not found " <<endl;

			//If the item is found in the list
			else if(found == true){
				//Insert node
				insertNode(head,current, name, sale, tax, price, 0);
			}
			break;

			//Case 2: delete from list
		case 2:
			//Get item number to be deleted
			cout << "\nItem Number: ";
			while(!(cin >> number)){
				cout << "Choose a number: ";
				cin.clear();
				cin.ignore();
			}

			//Delete item
			deleteItem(head, number);
			break;

		//Case 3: Print
		case 3:
			printList(head);
			break;

		case 4: 
			saveList(head);
			break;

		default:
			cout << "\nEnter a valid input" <<endl;
			break;
		
	
	}	
}




//Write to outfile
output << "Sub Total:" << setw(78) << fixed << setprecision(2) << subTotal << endl;

//Close the streas
input.close();
output.close();


return 0;
}




